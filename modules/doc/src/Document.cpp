#include "tsr/doc/Document.h"
#include "OcafApp.h"

#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_NamedData.hxx>
#include <TDataStd_DataMapOfStringString.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringString.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <Standard_Failure.hxx>
#include <gp.hxx>

#include <nlohmann/json.hpp>

#include "tsr/doc/DocCommands.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

namespace tsr::doc {

namespace {
constexpr int kParamsTag = 1;
constexpr int kBodiesTag = 2;
constexpr int kFeaturesTag = 3;
constexpr int kSketchesTag = 4;
constexpr int kPlanesTag = 5;
constexpr int kAxesTag = 6;
constexpr int kPointsTag = 7;
constexpr int kComponentsTag = 8;
constexpr int kBodyNamesTag = 9;
constexpr int kNamedViewsTag = 10;
constexpr int kFavoritesTag = 11;   // favourite parameters: "list" = "a,b,c"
constexpr int kBodyLooksTag = 12;   // "color:<body>" = #rrggbb, "material:<body>" = name

// A feature's model parameter names, stored as "distance=d5;taperAngle=d6".
std::map<std::string, std::string> parseNames(const std::string& s) {
  std::map<std::string, std::string> out;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, ';'))
    if (const auto eq = item.find('='); eq != std::string::npos) out[item.substr(0, eq)] = item.substr(eq + 1);
  return out;
}
std::string joinNames(const std::map<std::string, std::string>& names) {
  std::string out;
  for (const auto& [k, v] : names) out += (out.empty() ? "" : ";") + k + "=" + v;
  return out;
}

// `text` with every whole identifier `from` replaced by `to` (numbers and
// longer names that contain it are left alone).
std::string replaceIdentifier(const std::string& text, const std::string& from, const std::string& to) {
  auto start = [](char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '_'; };
  auto part = [](char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; };
  std::string out;
  size_t i = 0;
  while (i < text.size()) {
    if (start(text[i]) && (i == 0 || !part(text[i - 1]))) {
      size_t j = i;
      while (j < text.size() && part(text[j])) ++j;
      const std::string tok = text.substr(i, j - i);
      out += tok == from ? to : tok;
      i = j;
    } else {
      out += text[i++];
    }
  }
  return out;
}   // body renames: "alias:<name>" -> internal, "show:<internal>" -> shown
// Plan §2 asks for unbounded undo; OCAF needs a number. A million steps is
// unbounded for practical purposes and is recorded in docs/KNOWN_GAPS.md.
constexpr int kUndoLimit = 1'000'000;

TCollection_ExtendedString ext(const std::string& s) {
  return TCollection_ExtendedString(s.c_str(), /*isMultiByte=*/true);
}

std::string utf8(const TCollection_ExtendedString& s) {
  const int len = s.LengthOfCString();
  std::vector<char> buf(static_cast<size_t>(len) + 1, '\0');
  Standard_PCharacter p = buf.data();
  s.ToUTF8CString(p);
  return std::string(buf.data(), static_cast<size_t>(len));
}

std::string nameOf(const TDF_Label& l) {
  Handle(TDataStd_Name) n;
  return l.FindAttribute(TDataStd_Name::GetID(), n) ? utf8(n->Get()) : std::string{};
}

std::string stringOf(const Handle(TDataStd_NamedData)& nd, const char* key) {
  const TCollection_ExtendedString k(key);
  return nd->HasString(k) ? utf8(nd->GetString(k)) : std::string{};
}

nlohmann::json toJson(const Inputs& in) {
  nlohmann::json j = nlohmann::json::object();
  for (const auto& [k, v] : in)
    std::visit([&](const auto& x) {
      using T = std::decay_t<decltype(x)>;
      if constexpr (std::is_same_v<T, std::monostate>) j[k] = nullptr;
      else j[k] = x;
    }, v);
  return j;
}

Inputs fromJson(const std::string& text) {
  Inputs in;
  const auto j = nlohmann::json::parse(text, nullptr, /*allow_exceptions=*/false);
  if (!j.is_object()) return in;
  for (const auto& [k, v] : j.items()) {
    if (v.is_boolean()) in[k] = v.get<bool>();
    else if (v.is_number_integer()) in[k] = v.get<std::int64_t>();
    else if (v.is_number()) in[k] = v.get<double>();
    else if (v.is_string()) in[k] = v.get<std::string>();
    else in[k] = std::monostate{};
  }
  return in;
}

int bodyNumber(const std::string& name) {
  if (name.rfind("Body", 0) != 0 || name.size() == 4 || name.size() > 12) return 0;
  for (size_t i = 4; i < name.size(); ++i)
    if (!std::isdigit(static_cast<unsigned char>(name[i]))) return 0;
  return std::stoi(name.substr(4));
}

Handle(TDataStd_NamedData) featureData(const Handle(TDocStd_Document)& doc, int id) {
  const TDF_Label l = doc->Main().FindChild(kFeaturesTag, false).FindChild(id, false);
  Handle(TDataStd_NamedData) nd;
  if (l.IsNull() || !l.FindAttribute(TDataStd_NamedData::GetID(), nd))
    throw DocumentError("no feature with id " + std::to_string(id));
  return nd;
}

TDF_Label findBodyLabel(const Handle(TDocStd_Document)& doc, const std::string& name) {
  for (TDF_ChildIterator it(doc->Main().FindChild(kBodiesTag, false)); it.More(); it.Next()) {
    Handle(TNaming_NamedShape) ns;
    if (it.Value().FindAttribute(TNaming_NamedShape::GetID(), ns) && !ns->IsEmpty() && nameOf(it.Value()) == name)
      return it.Value();
  }
  return {};
}
TDF_Label findParameterLabel(const Handle(TDocStd_Document)& doc, const std::string& name) {
  for (TDF_ChildIterator it(doc->Main().FindChild(kParamsTag, false)); it.More(); it.Next())
    if (it.Value().IsAttribute(TDataStd_NamedData::GetID()) && nameOf(it.Value()) == name) return it.Value();
  return {};
}
} // namespace

Document::Document() {
  ocafApplication()->NewDocument(TCollection_ExtendedString(kOcafFormat), doc_);
  if (doc_.IsNull()) throw DocumentError("OCAF could not create a document");
  initLayout();
  // A layout version on the root: an empty design still has something to
  // store (OCAF refuses to save a document with no attributes at all).
  TDataStd_Integer::Set(doc_->Main(), 1);
}

Document::Document(FromOcaf, Handle(TDocStd_Document) doc) : doc_(std::move(doc)) { initLayout(); }

Document::~Document() {
  if (doc_.IsNull()) return;
  if (doc_->HasOpenCommand()) doc_->AbortCommand();
  ocafApplication()->Close(doc_);
}

void Document::initLayout() {
  doc_->SetUndoLimit(kUndoLimit);
  // Creating labels is not an undoable modification; attributes are.
  doc_->Main().FindChild(kParamsTag, true);
  doc_->Main().FindChild(kBodiesTag, true);
  doc_->Main().FindChild(kFeaturesTag, true);
  doc_->Main().FindChild(kSketchesTag, true);
  doc_->Main().FindChild(kPlanesTag, true);
  doc_->Main().FindChild(kAxesTag, true);
  doc_->Main().FindChild(kPointsTag, true);
  doc_->Main().FindChild(kComponentsTag, true);
  doc_->Main().FindChild(kBodyNamesTag, true);
  doc_->Main().FindChild(kNamedViewsTag, true);
  doc_->Main().FindChild(kFavoritesTag, true);
  doc_->Main().FindChild(kBodyLooksTag, true);
}

std::vector<NamedView> Document::namedViews() const {
  std::vector<NamedView> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kNamedViewsTag, true)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;   // removed by undo
    NamedView v;
    v.name = nameOf(it.Value());
    const char* axes = "xyz";
    for (int i = 0; i < 3; ++i) {
      const std::string k(1, axes[i]);
      v.eye[i] = nd->GetReal(ext("eye" + k));
      v.target[i] = nd->GetReal(ext("target" + k));
      v.up[i] = nd->GetReal(ext("up" + k));
    }
    v.size = nd->GetReal("size");
    out.push_back(std::move(v));
  }
  return out;
}

static TDF_Label findNamedView(const Handle(TDocStd_Document)& doc, const std::string& name) {
  for (TDF_ChildIterator it(doc->Main().FindChild(kNamedViewsTag, true)); it.More(); it.Next())
    if (it.Value().IsAttribute(TDataStd_NamedData::GetID()) && nameOf(it.Value()) == name) return it.Value();
  return {};
}

static void checkViewName(const std::string& name) {
  if (name.empty() || name.find_first_not_of(' ') == std::string::npos) throw DocumentError("a view needs a name");
  for (const char* fixed : {"TOP", "FRONT", "RIGHT", "HOME"})
    if (name == fixed) throw DocumentError("'" + name + "' is one of the standard views");
}

void Document::addNamedView(const NamedView& v) {
  requireTransaction("addNamedView");
  checkViewName(v.name);
  if (!findNamedView(doc_, v.name).IsNull()) throw DocumentError("a view named '" + v.name + "' already exists");
  const TDF_Label l = doc_->Main().FindChild(kNamedViewsTag, true).NewChild();
  TDataStd_Name::Set(l, ext(v.name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  const char* axes = "xyz";
  for (int i = 0; i < 3; ++i) {
    const std::string k(1, axes[i]);
    nd->SetReal(ext("eye" + k), v.eye[i]);
    nd->SetReal(ext("target" + k), v.target[i]);
    nd->SetReal(ext("up" + k), v.up[i]);
  }
  nd->SetReal("size", v.size);
}

void Document::renameNamedView(const std::string& name, const std::string& newName) {
  requireTransaction("renameNamedView");
  const TDF_Label l = findNamedView(doc_, name);
  if (l.IsNull()) throw DocumentError("no view named '" + name + "'");
  if (newName == name) return;
  checkViewName(newName);
  if (!findNamedView(doc_, newName).IsNull()) throw DocumentError("a view named '" + newName + "' already exists");
  TDataStd_Name::Set(l, ext(newName));
}

void Document::removeNamedView(const std::string& name) {
  requireTransaction("removeNamedView");
  const TDF_Label l = findNamedView(doc_, name);
  if (l.IsNull()) throw DocumentError("no view named '" + name + "'");
  l.ForgetAllAttributes(true);
}

void Document::requireTransaction(const char* what) const {
  if (!doc_->HasOpenCommand())
    throw DocumentError(std::string(what) + " requires an open transaction");
}

void Document::openTransaction(const std::string& name) {
  if (doc_->HasOpenCommand()) throw DocumentError("a transaction is already open");
  doc_->NewCommand();
  txnBodies_ = bodyShapes();
  pendingTools_.clear();
  (void)name; // OCAF transaction names are not persisted; kept for the undo UI later.
}

void Document::commitTransaction() {
  requireTransaction("commit");
  if (doc_->CommitCommand()) modified_ = true;
}

void Document::abortTransaction() {
  requireTransaction("abort");
  doc_->AbortCommand();
}

bool Document::hasOpenTransaction() const { return doc_->HasOpenCommand(); }

bool Document::canUndo() const { return !doc_->HasOpenCommand() && doc_->GetAvailableUndos() > 0; }
bool Document::canRedo() const { return !doc_->HasOpenCommand() && doc_->GetAvailableRedos() > 0; }

bool Document::undo() {
  if (!canUndo()) return false;
  effects_.clear();   // the history may differ now; replayed when needed
  const bool ok = doc_->Undo();
  modified_ = modified_ || ok;
  return ok;
}

bool Document::redo() {
  if (!canRedo()) return false;
  effects_.clear();
  const bool ok = doc_->Redo();
  modified_ = modified_ || ok;
  return ok;
}

std::vector<UserParameter> Document::userParameters() const {
  std::vector<UserParameter> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kParamsTag, false)); it.More(); it.Next()) {
    const TDF_Label l = it.Value();
    Handle(TDataStd_NamedData) nd;
    if (!l.FindAttribute(TDataStd_NamedData::GetID(), nd)) continue; // removed by undo
    UserParameter p;
    p.name = nameOf(l);
    p.expression = stringOf(nd, "expression");
    p.unit = stringOf(nd, "unit");
    p.comment = stringOf(nd, "comment");
    p.value = nd->HasReal("value") ? nd->GetReal("value") : 0.0;
    out.push_back(std::move(p));
  }
  return out;
}

std::optional<UserParameter> Document::userParameter(const std::string& name) const {
  for (auto& p : userParameters())
    if (p.name == name) return p;
  return std::nullopt;
}

void Document::addUserParameter(const UserParameter& p) {
  requireTransaction("addUserParameter");
  if (userParameter(p.name)) throw DocumentError("parameter '" + p.name + "' already exists");
  const TDF_Label l = doc_->Main().FindChild(kParamsTag, false).NewChild();
  TDataStd_Name::Set(l, ext(p.name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  nd->SetString("expression", ext(p.expression));
  nd->SetString("unit", ext(p.unit));
  nd->SetString("comment", ext(p.comment));
  nd->SetReal("value", p.value);
}

void Document::setUserParameter(const std::string& name, const std::string& expression, const std::string& comment) {
  requireTransaction("setUserParameter");
  const TDF_Label l = findParameterLabel(doc_, name);
  if (l.IsNull()) throw DocumentError("no parameter named '" + name + "'");
  Handle(TDataStd_NamedData) nd;
  l.FindAttribute(TDataStd_NamedData::GetID(), nd);
  nd->SetString("expression", ext(expression));
  nd->SetString("comment", ext(comment));
  reevaluateParameters();
}

void Document::removeUserParameter(const std::string& name) {
  requireTransaction("removeUserParameter");
  const TDF_Label l = findParameterLabel(doc_, name);
  if (l.IsNull()) throw DocumentError("no parameter named '" + name + "'");
  const auto users = parameterUsers(name);
  if (!users.empty()) {
    std::string list;
    for (const auto& u : users) list += (list.empty() ? "" : ", ") + u;
    throw DocumentError("'" + name + "' is still used by " + list);
  }
  l.ForgetAllAttributes(true);
}

std::vector<std::string> Document::parameterUsers(const std::string& name) const {
  auto refersTo = [&](const std::string& text) {
    try {
      const auto refs = expressionReferences(text);
      return std::find(refs.begin(), refs.end(), name) != refs.end();
    } catch (const ExpressionError&) {
      return false;
    }
  };
  std::vector<std::string> out;
  for (const auto& p : userParameters())
    if (p.name != name && refersTo(p.expression)) out.push_back("parameter " + p.name);
  for (const auto& f : features()) {
    bool used = false;
    for (const auto& [k, v] : f.inputs)
      if (auto t = std::get_if<std::string>(&v); t && k.size() > 1 && k[0] == '=') used = used || refersTo(*t);
    if (!used && f.commandId == kCmdSketch)
      if (auto it = f.inputs.find("data"); it != f.inputs.end())
        if (auto data = std::get_if<std::string>(&it->second)) {
          try {
            for (const auto& c : sketch::Sketch::fromJson(*data).constraints)
              used = used || (!c.expression.empty() && refersTo(c.expression));
          } catch (const sketch::SketchError&) {
          }
        }
    if (used) out.push_back(f.name);
  }
  return out;
}

ExpressionEnv Document::expressionEnv() const { return currentParams().env; }

Document::ParamSet Document::paramSet(const std::vector<ModelParameter>& dims, const std::vector<UserParameter>& users,
                                      const std::vector<ModelParameter>& valueParams) const {
  ParamSet out;
  out.env.lengthUnit = parseUnit(lengthUnit()).value_or(Unit::Millimeter);
  // Copy the values so the lookup does not walk OCAF per name.
  auto values = std::make_shared<std::map<std::string, Quantity>>();
  auto text = [](double v) {
    std::ostringstream os;
    os.precision(17);
    os << v;
    return os.str();
  };
  for (const auto& p : users) {
    (*values)[p.name] = quantityOf(p.value, parseUnit(p.unit).value_or(Unit::None));
    out.text[p.name] = text(p.value);
  }
  for (const auto* list : {&dims, &valueParams})
    for (const auto& m : *list)
      if (!values->count(m.name)) {
        (*values)[m.name] = quantityOf(m.value, m.unit);
        out.text[m.name] = text(m.value);
      }
  out.env.lookup = [values](const std::string& n) -> std::optional<Quantity> {
    auto it = values->find(n);
    if (it == values->end()) return std::nullopt;
    return it->second;
  };
  return out;
}

Document::ParamSet Document::currentParams() const {
  return paramSet(sketchDimensions(sketches()), userParameters(), featureValueParameters());
}

double Document::evaluate(const std::string& text, Unit unit) const {
  const ExpressionEnv env = expressionEnv();
  const Unit expected = dimensionOf(unit) == Dimension::Length ? env.lengthUnit : unit;
  try {
    return tsr::evaluateExpression(text, expected, env);
  } catch (const ExpressionError& e) {
    throw DocumentError(e.what());
  }
}

double Document::evaluate(const std::string& text, Unit unit, const std::map<std::string, Quantity>& extra) const {
  ExpressionEnv env = expressionEnv();
  auto base = env.lookup;
  env.lookup = [base, &extra](const std::string& n) -> std::optional<Quantity> {
    if (auto it = extra.find(n); it != extra.end()) return it->second;
    return base(n);
  };
  const Unit expected = dimensionOf(unit) == Dimension::Length ? env.lengthUnit : unit;
  try {
    return tsr::evaluateExpression(text, expected, env);
  } catch (const ExpressionError& e) {
    throw DocumentError(e.what());
  }
}

// Read from the computed sketches (their data holds each dimension's
// evaluated value), so open, undo and redo need nothing extra.
std::vector<ModelParameter> Document::modelParameters() const {
  auto out = sketchDimensions(sketches());
  auto values = featureValueParameters();
  out.insert(out.end(), values.begin(), values.end());
  return out;
}

std::vector<ModelParameter> Document::sketchDimensions(const std::vector<SketchRecord>& sketchList) {
  std::vector<ModelParameter> out;
  for (const auto& rec : sketchList) {
    try {
      for (const auto& c : sketch::Sketch::fromJson(rec.data).constraints)
        if (!c.name.empty() && !c.driven && sketch::isDimension(c.type)) {
          const bool angle = c.type == sketch::ConstraintType::Angle;
          out.push_back({c.name, c.expression, rec.name, c.value, angle, angle ? Unit::Degree : Unit::Millimeter, {}, {}});
        }
    } catch (const std::exception&) {
    }
  }
  return out;
}

// Feature values (an extrude's distance, a fillet's radius ...): each shown
// value has its name, as in the familiar Parameters table.
std::vector<ModelParameter> Document::featureValueParameters() const {
  std::vector<ModelParameter> out;
  if (!registry_) return out;
  for (const auto& f : features()) {
    const Command* cmd = registry_->find(f.commandId);
    if (!cmd || f.parameterNames.empty()) continue;
    for (const InputDef& d : cmd->def().inputs) {
      const auto n = f.parameterNames.find(d.id);
      if (n == f.parameterNames.end() || !isInputVisible(d, f.inputs)) continue;
      const auto it = f.inputs.find(d.id);
      if (it == f.inputs.end()) continue;
      double v = 0;
      if (const auto* x = std::get_if<double>(&it->second)) v = *x;
      else if (const auto* i = std::get_if<std::int64_t>(&it->second)) v = static_cast<double>(*i);
      else continue;
      const Unit u = d.type == InputType::Integer ? Unit::None : d.unit;
      out.push_back({n->second, inputExpression(f.inputs, d.id), f.name, v, dimensionOf(u) == Dimension::Angle, u,
                     d.id, d.label});
    }
  }
  return out;
}

void Document::nameFeatureParameters(int featureId, const Command& cmd, const Inputs& inputs) {
  if (cmd.def().id == kCmdSketch) return;   // a sketch's values are its dimensions
  Handle(TDataStd_NamedData) nd = featureData(doc_, featureId);
  auto names = parseNames(stringOf(nd, "params"));
  std::vector<std::string> taken;
  for (const auto& [k, v] : names) taken.push_back(v);
  bool changed = false;
  for (const InputDef& d : cmd.def().inputs) {
    if (d.type != InputType::Real && d.type != InputType::Integer) continue;
    if (names.count(d.id) || !inputs.count(d.id) || !isInputVisible(d, inputs)) continue;
    names[d.id] = nextDimensionName(taken);
    taken.push_back(names[d.id]);
    changed = true;
  }
  if (changed) nd->SetString("params", ext(joinNames(names)));
}

void Document::renameParameter(const std::string& name, const std::string& newName) {
  requireTransaction("renameParameter");
  if (newName == name) return;
  if (!isValidParameterName(newName))
    throw DocumentError("'" + newName + "' cannot be a parameter name (letters, digits and underscores; "
                        "not a unit or function name)");
  const auto models = modelParameters();
  auto taken = [&](const std::string& n) {
    if (userParameter(n)) return true;
    for (const auto& m : models)
      if (m.name == n) return true;
    return false;
  };
  if (!taken(name)) throw DocumentError("no parameter named '" + name + "'");
  if (taken(newName)) throw DocumentError("a parameter named '" + newName + "' already exists");
  // The parameter itself.
  if (const TDF_Label l = findParameterLabel(doc_, name); !l.IsNull()) TDataStd_Name::Set(l, ext(newName));
  for (const auto& f : features()) {
    Handle(TDataStd_NamedData) nd = featureData(doc_, f.id);
    auto names = f.parameterNames;
    bool renamed = false;
    for (auto& [k, v] : names)
      if (v == name) {
        v = newName;
        renamed = true;
      }
    if (renamed) nd->SetString("params", ext(joinNames(names)));
    // Expressions that use it, and a sketch dimension of that name.
    Inputs in = f.inputs;
    bool changed = false;
    for (auto& [k, v] : in) {
      auto* text = std::get_if<std::string>(&v);
      if (!text) continue;
      if (k.size() > 1 && k[0] == '=') {
        const std::string t = replaceIdentifier(*text, name, newName);
        changed = changed || t != *text;
        *text = t;
      } else if (k == "data" && f.commandId == kCmdSketch) {
        auto j = nlohmann::json::parse(*text, nullptr, false);
        if (j.is_discarded() || !j.contains("constraints")) continue;
        bool sk = false;
        for (auto& c : j["constraints"]) {
          if (c.contains("name") && c["name"] == name) {
            c["name"] = newName;
            sk = true;
          }
          if (c.contains("expr") && c["expr"].is_string()) {
            const std::string e = c["expr"], t = replaceIdentifier(e, name, newName);
            if (t != e) {
              c["expr"] = t;
              sk = true;
            }
          }
        }
        if (sk) {
          *text = j.dump();
          changed = true;
        }
      }
    }
    if (changed) nd->SetString("inputs", ext(toJson(in).dump()));
  }
  for (const auto& p : userParameters()) {
    const std::string t = replaceIdentifier(p.expression, name, newName);
    if (t == p.expression) continue;
    Handle(TDataStd_NamedData) nd;
    findParameterLabel(doc_, p.name).FindAttribute(TDataStd_NamedData::GetID(), nd);
    nd->SetString("expression", ext(t));
  }
  const auto favs = favoriteParameters();
  if (std::find(favs.begin(), favs.end(), name) != favs.end()) {
    setParameterFavorite(name, false);
    setParameterFavorite(newName, true);
  }
}

std::vector<std::string> Document::favoriteParameters() const {
  Handle(TDataStd_NamedData) nd;
  std::vector<std::string> out;
  if (!doc_->Main().FindChild(kFavoritesTag, true).FindAttribute(TDataStd_NamedData::GetID(), nd)) return out;
  std::stringstream ss(stringOf(nd, "list"));
  std::string item;
  while (std::getline(ss, item, ','))
    if (!item.empty()) out.push_back(item);
  return out;
}

void Document::setParameterFavorite(const std::string& name, bool favorite) {
  requireTransaction("setParameterFavorite");
  auto list = favoriteParameters();
  const auto it = std::find(list.begin(), list.end(), name);
  if (favorite == (it != list.end())) return;
  if (favorite) list.push_back(name);
  else list.erase(it);
  std::string joined;
  for (const auto& n : list) joined += (joined.empty() ? "" : ",") + n;
  const TDF_Label l = doc_->Main().FindChild(kFavoritesTag, true);
  Handle(TDataStd_NamedData) nd;
  if (!l.FindAttribute(TDataStd_NamedData::GetID(), nd)) nd = TDataStd_NamedData::Set(l);
  nd->SetString("list", ext(joined));
}

std::string Document::nextDimensionName(const std::vector<std::string>& alsoTaken) const {
  int top = 0;
  auto take = [&](const std::string& n) {
    if (n.size() < 2 || n.size() > 9 || n[0] != 'd') return;
    for (size_t i = 1; i < n.size(); ++i)
      if (!std::isdigit(static_cast<unsigned char>(n[i]))) return;
    top = std::max(top, std::stoi(n.substr(1)));
  };
  for (const auto& n : alsoTaken) take(n);
  for (const auto& p : userParameters()) take(p.name);
  // Every sketch feature, computed or not (rolled back, failed), keeps its names.
  for (const auto& f : features()) {
    for (const auto& [k, n] : f.parameterNames) take(n);
    if (f.commandId != "tsr.sketch.create") continue;
    const auto it = f.inputs.find("data");
    const auto* data = it == f.inputs.end() ? nullptr : std::get_if<std::string>(&it->second);
    if (!data) continue;
    try {
      for (const auto& c : sketch::Sketch::fromJson(*data).constraints) take(c.name);
    } catch (const std::exception&) {
    }
  }
  return "d" + std::to_string(top + 1);
}

void Document::reevaluateParameters() {
  const auto params = userParameters();
  std::map<std::string, size_t> index;
  for (size_t i = 0; i < params.size(); ++i) index[params[i].name] = i;
  std::vector<int> state(params.size(), 0);   // 0 new, 1 evaluating, 2 done
  std::vector<double> values(params.size(), 0.0);
  const Unit docLength = parseUnit(lengthUnit()).value_or(Unit::Millimeter);
  auto unitOf = [&](size_t i) { return parseUnit(params[i].unit).value_or(Unit::None); };

  std::function<Quantity(size_t)> eval = [&](size_t i) -> Quantity {
    if (state[i] == 2) return quantityOf(values[i], unitOf(i));
    if (state[i] == 1) throw DocumentError("parameter '" + params[i].name + "' refers to itself");
    state[i] = 1;
    ExpressionEnv env;
    env.lengthUnit = docLength;
    env.lookup = [&](const std::string& n) -> std::optional<Quantity> {
      auto it = index.find(n);
      if (it == index.end()) return std::nullopt;
      return eval(it->second);
    };
    try {
      values[i] = tsr::evaluateExpression(params[i].expression, unitOf(i), env);
    } catch (const ExpressionError& e) {
      throw DocumentError(params[i].name + ": " + e.what());
    }
    state[i] = 2;
    return quantityOf(values[i], unitOf(i));
  };
  for (size_t i = 0; i < params.size(); ++i) (void)eval(i);

  for (size_t i = 0; i < params.size(); ++i) {
    if (params[i].value == values[i]) continue;
    Handle(TDataStd_NamedData) nd;
    if (findParameterLabel(doc_, params[i].name).FindAttribute(TDataStd_NamedData::GetID(), nd))
      nd->SetReal("value", values[i]);
  }
}

void Document::evaluateFeatureExpressions(const Command& cmd, Inputs& in, const ExpressionEnv* env) const {
  const Inputs original = in;
  for (const auto& [k, v] : original) {
    if (k.size() < 2 || k[0] != '=') continue;
    const auto* text = std::get_if<std::string>(&v);
    const InputDef* d = cmd.def().input(k.substr(1));
    if (!text || !d || (d->type != InputType::Real && d->type != InputType::Integer)) continue;
    double x = 0;
    try {
      if (env) {
        const Unit expected = dimensionOf(d->unit) == Dimension::Length ? env->lengthUnit : d->unit;
        try {
          x = tsr::evaluateExpression(*text, expected, *env);
        } catch (const ExpressionError& e) {
          throw DocumentError(e.what());
        }
      } else {
        x = evaluate(*text, d->unit);
      }
    } catch (const DocumentError& e) {
      throw DocumentError(d->label + ": " + e.what());
    }
    Value value = x;
    if (d->type == InputType::Integer) {
      const double n = std::round(x);
      if (std::abs(n - x) > 1e-9) throw DocumentError(d->label + ": must be a whole number");
      value = static_cast<std::int64_t>(n);
    }
    if (auto err = checkInputValue(*d, value); !err.empty()) throw DocumentError(err);
    in[d->id] = value;
  }
}

std::vector<Body> Document::bodies() const {
  std::vector<Body> out;
  Handle(TDataStd_NamedData) names;
  doc_->Main().FindChild(kBodyNamesTag, false).FindAttribute(TDataStd_NamedData::GetID(), names);
  Handle(TDataStd_NamedData) looks;
  const TDF_Label looksLabel = doc_->Main().FindChild(kBodyLooksTag, false);
  if (!looksLabel.IsNull()) looksLabel.FindAttribute(TDataStd_NamedData::GetID(), looks);
  for (TDF_ChildIterator it(doc_->Main().FindChild(kBodiesTag, false)); it.More(); it.Next()) {
    Handle(TNaming_NamedShape) ns;
    if (!it.Value().FindAttribute(TNaming_NamedShape::GetID(), ns) || ns->IsEmpty()) continue;
    const std::string n = nameOf(it.Value());
    std::string shown = names.IsNull() ? std::string() : stringOf(names, ("show:" + n).c_str());
    Body b{n, ns->Get(), shown.empty() ? n : shown, {}, {}};
    if (!looks.IsNull()) {
      b.color = stringOf(looks, ("color:" + n).c_str());
      b.material = stringOf(looks, ("material:" + n).c_str());
    }
    out.push_back(std::move(b));
  }
  return out;
}

const std::vector<PhysicalMaterial>& physicalMaterials() {
  static const std::vector<PhysicalMaterial> list = {
      {"Steel", 7.85, "#8c9198"},          {"Stainless Steel", 8.00, "#b8bcc2"}, {"Aluminum", 2.70, "#c9ced4"},
      {"Brass", 8.50, "#c8a648"},          {"Copper", 8.96, "#c27a4e"},          {"Titanium", 4.43, "#8f8a85"},
      {"Cast Iron", 7.20, "#5d6066"},      {"ABS Plastic", 1.04, "#e6e6e0"},     {"PLA", 1.24, "#f2f2ee"},
      {"PETG", 1.27, "#d8e8ef"},           {"Nylon", 1.14, "#efe9dc"},           {"Polycarbonate", 1.20, "#dfe8f0"},
      {"Rubber", 1.10, "#2e2e30"},         {"Glass", 2.50, "#cfe3ea"},           {"Oak", 0.75, "#a8763e"},
      {"Pine", 0.50, "#d9b27a"},           {"Concrete", 2.40, "#a3a29c"},
  };
  return list;
}

const PhysicalMaterial* findMaterial(const std::string& name) {
  for (const auto& m : physicalMaterials())
    if (m.name == name) return &m;
  return nullptr;
}

void Document::setBodyColor(const std::string& name, const std::string& color) {
  requireTransaction("setBodyColor");
  const std::string internal = bodyName(name);
  if (!body(internal)) throw DocumentError("no body named '" + name + "'");
  if (!color.empty()) {
    const bool ok = color.size() == 7 && color[0] == '#' &&
                    std::all_of(color.begin() + 1, color.end(), [](char c) { return std::isxdigit(static_cast<unsigned char>(c)); });
    if (!ok) throw DocumentError("Appearance: a colour is written #rrggbb");
  }
  Handle(TDataStd_NamedData) nd;
  const TDF_Label l = doc_->Main().FindChild(kBodyLooksTag, true);
  if (!l.FindAttribute(TDataStd_NamedData::GetID(), nd)) nd = TDataStd_NamedData::Set(l);
  nd->SetString(ext("color:" + internal), ext(color));
}

void Document::setBodyMaterial(const std::string& name, const std::string& material) {
  requireTransaction("setBodyMaterial");
  const std::string internal = bodyName(name);
  if (!body(internal)) throw DocumentError("no body named '" + name + "'");
  if (!material.empty() && !findMaterial(material)) throw DocumentError("Physical Material: no material named '" + material + "'");
  Handle(TDataStd_NamedData) nd;
  const TDF_Label l = doc_->Main().FindChild(kBodyLooksTag, true);
  if (!l.FindAttribute(TDataStd_NamedData::GetID(), nd)) nd = TDataStd_NamedData::Set(l);
  nd->SetString(ext("material:" + internal), ext(material));
}

std::string Document::bodyName(const std::string& nameOrAlias) const {
  for (const auto& b : bodies())
    if (b.name == nameOrAlias) return b.name;
  Handle(TDataStd_NamedData) names;
  if (doc_->Main().FindChild(kBodyNamesTag, false).FindAttribute(TDataStd_NamedData::GetID(), names)) {
    const std::string internal = stringOf(names, ("alias:" + nameOrAlias).c_str());
    if (!internal.empty()) return internal;
  }
  return nameOrAlias;
}

void Document::renameBody(const std::string& name, const std::string& newName) {
  requireTransaction("renameBody");
  const std::string internal = bodyName(name);
  if (!body(internal)) throw DocumentError("no body named '" + name + "'");
  if (newName.empty()) throw DocumentError("a body needs a name");
  for (const auto& b : bodies())
    if (b.name != internal && (b.name == newName || b.display == newName))
      throw DocumentError("there is already a body named '" + newName + "'");
  const TDF_Label l = doc_->Main().FindChild(kBodyNamesTag, true);
  Handle(TDataStd_NamedData) names;
  if (!l.FindAttribute(TDataStd_NamedData::GetID(), names)) names = TDataStd_NamedData::Set(l);
  names->SetString(ext("show:" + internal), ext(newName));
  names->SetString(ext("alias:" + newName), ext(internal));
}

namespace {
// Replaces `from` by `to` in every string input of every feature: whole
// values and items of ';' lists.
void replaceReferences(Document& doc, const std::string& from, const std::string& to) {
  for (const auto& f : doc.features()) {
    Inputs in = f.inputs;
    bool changed = false;
    for (auto& [k, v] : in) {
      auto* s = std::get_if<std::string>(&v);
      if (!s || s->empty()) continue;
      std::string out;
      size_t start = 0;
      bool hit = false;
      while (start <= s->size()) {
        const size_t end = std::min(s->find(';', start), s->size());
        std::string item = s->substr(start, end - start);
        if (item == from) {
          item = to;
          hit = true;
        }
        out += (start ? ";" : "") + item;
        start = end + 1;
      }
      if (hit) {
        *s = out;
        changed = true;
      }
    }
    if (changed) doc.setFeatureInputs(f.id, in);
  }
}
} // namespace

void Document::renameSketch(const std::string& name, const std::string& newName) {
  requireTransaction("renameSketch");
  if (!sketch(name)) throw DocumentError("no sketch named '" + name + "'");
  if (newName.empty()) throw DocumentError("a sketch needs a name");
  if (sketch(newName)) throw DocumentError("there is already a sketch named '" + newName + "'");
  for (const auto& f : features())
    if (f.name == name && f.commandId == "tsr.sketch.create") {
      Inputs in = f.inputs;
      in["name"] = newName;   // the sketch keeps this name on every replay
      setFeatureInputs(f.id, in);
      TDataStd_Name::Set(doc_->Main().FindChild(kFeaturesTag, false).FindChild(f.id, false), ext(newName));
    }
  replaceReferences(*this, name, newName);
}

void Document::renameFeature(int id, const std::string& newName) {
  requireTransaction("renameFeature");
  const auto f = feature(id);
  if (!f) throw DocumentError("no feature with id " + std::to_string(id));
  if (f->commandId == "tsr.sketch.create") return renameSketch(f->name, newName);
  if (newName.empty()) throw DocumentError("a feature needs a name");
  for (const auto& g : features())
    if (g.id != id && g.name == newName) throw DocumentError("there is already a feature named '" + newName + "'");
  TDataStd_Name::Set(doc_->Main().FindChild(kFeaturesTag, false).FindChild(id, false), ext(newName));
  replaceReferences(*this, f->name, newName);
}

void Document::addBody(const std::string& name, const TopoDS_Shape& shape) {
  requireTransaction("addBody");
  if (shape.IsNull()) throw DocumentError("cannot add a null body");
  const TDF_Label l = doc_->Main().FindChild(kBodiesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(name));
  TNaming_Builder(l).Generated(shape);
}

std::optional<Body> Document::body(const std::string& name) const {
  const std::string internal = bodyName(name);   // a renamed body answers to its new name too
  for (auto& b : bodies())
    if (b.name == internal) return b;
  return std::nullopt;
}

void Document::replaceBody(const std::string& name, const TopoDS_Shape& shape) {
  requireTransaction("replaceBody");
  if (shape.IsNull()) throw DocumentError("cannot set a null body");
  const TDF_Label l = findBodyLabel(doc_, bodyName(name));
  if (l.IsNull()) throw DocumentError("no body named '" + name + "'");
  TNaming_Builder(l).Generated(shape);
}

void Document::removeBody(const std::string& name) {
  requireTransaction("removeBody");
  const TDF_Label l = findBodyLabel(doc_, bodyName(name));
  if (l.IsNull()) throw DocumentError("no body named '" + name + "'");
  l.ForgetAllAttributes(true);
}

std::string Document::nextBodyName() const {
  int n = 0;
  for (const auto& b : bodies()) n = std::max(n, bodyNumber(b.name));
  return "Body" + std::to_string(n + 1);
}

std::string Document::lengthUnit() const {
  Handle(TDataStd_NamedData) nd;
  if (doc_->Main().FindAttribute(TDataStd_NamedData::GetID(), nd)) {
    const std::string u = stringOf(nd, "lengthUnit");
    if (!u.empty()) return u;
  }
  return "mm";
}

void Document::setLengthUnit(const std::string& unit) {
  requireTransaction("setLengthUnit");
  if (unit != "mm" && unit != "in" && unit != "cm" && unit != "m")
    throw DocumentError("unsupported length unit '" + unit + "'");
  TDataStd_NamedData::Set(doc_->Main())->SetString("lengthUnit", ext(unit));
}

std::vector<SketchRecord> Document::sketches() const {
  std::vector<SketchRecord> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kSketchesTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;
    SketchRecord s;
    s.name = nameOf(it.Value());
    s.plane = stringOf(nd, "plane");
    s.offset = nd->HasReal("offset") ? nd->GetReal("offset") : 0.0;
    s.data = stringOf(nd, "data");
    out.push_back(std::move(s));
  }
  return out;
}

std::optional<SketchRecord> Document::sketch(const std::string& name) const {
  for (auto& s : sketches())
    if (s.name == name) return s;
  return std::nullopt;
}

void Document::setSketch(const SketchRecord& s) {
  requireTransaction("setSketch");
  TDF_Label l;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kSketchesTag, false)); it.More(); it.Next())
    if (it.Value().IsAttribute(TDataStd_NamedData::GetID()) && nameOf(it.Value()) == s.name) l = it.Value();
  if (l.IsNull()) l = doc_->Main().FindChild(kSketchesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(s.name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  nd->SetString("plane", ext(s.plane));
  nd->SetReal("offset", s.offset);
  nd->SetString("data", ext(s.data));
}

std::string Document::nextSketchName() const {
  // Never reuse a name a feature still carries (an extrude may refer to it).
  const auto fs = features();
  for (int n = 1;; ++n) {
    const std::string name = "Sketch" + std::to_string(n);
    if (sketch(name)) continue;
    if (std::any_of(fs.begin(), fs.end(), [&](const Feature& f) { return f.name == name; })) continue;
    return name;
  }
}

std::vector<ConstructionPlane> Document::planes() const {
  std::vector<ConstructionPlane> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kPlanesTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;
    out.push_back({nameOf(it.Value()), stringOf(nd, "spec")});
  }
  return out;
}

std::optional<ConstructionPlane> Document::plane(const std::string& name) const {
  for (auto& p : planes())
    if (p.name == name) return p;
  return std::nullopt;
}

void Document::setPlane(const ConstructionPlane& p) {
  requireTransaction("setPlane");
  TDF_Label l;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kPlanesTag, false)); it.More(); it.Next())
    if (it.Value().IsAttribute(TDataStd_NamedData::GetID()) && nameOf(it.Value()) == p.name) l = it.Value();
  if (l.IsNull()) l = doc_->Main().FindChild(kPlanesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(p.name));
  TDataStd_NamedData::Set(l)->SetString("spec", ext(p.spec));
}

std::string Document::nextPlaneName() const {
  const auto fs = features();
  for (int n = 1;; ++n) {
    const std::string name = "Plane" + std::to_string(n);
    if (plane(name)) continue;
    if (std::any_of(fs.begin(), fs.end(), [&](const Feature& f) { return f.name == name; })) continue;
    return name;
  }
}

gp_Ax3 Document::planeFrame(const std::string& spec, double offset) const {
  try {
    if (const auto p = plane(spec)) return sketch::planeFrame(p->spec, offset);
    return sketch::planeFrame(spec, offset);
  } catch (const sketch::SketchError& e) {
    throw DocumentError(e.what());
  }
}

namespace {
TDF_Label namedChild(const Handle(TDocStd_Document)& doc, int tag, const std::string& name) {
  for (TDF_ChildIterator it(doc->Main().FindChild(tag, false)); it.More(); it.Next())
    if (it.Value().IsAttribute(TDataStd_NamedData::GetID()) && nameOf(it.Value()) == name) return it.Value();
  return {};
}
double realOf(const Handle(TDataStd_NamedData)& nd, const char* key) {
  const TCollection_ExtendedString k(key);
  return nd->HasReal(k) ? nd->GetReal(k) : 0.0;
}
// A free name "<base><n>": not used by an existing item or by a feature.
template <class Exists>
std::string freeName(const std::vector<Feature>& fs, const char* base, Exists exists) {
  for (int n = 1;; ++n) {
    const std::string name = base + std::to_string(n);
    if (exists(name)) continue;
    if (std::any_of(fs.begin(), fs.end(), [&](const Feature& f) { return f.name == name; })) continue;
    return name;
  }
}
} // namespace

std::vector<ConstructionAxis> Document::axes() const {
  std::vector<ConstructionAxis> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kAxesTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;
    try {
      out.push_back({nameOf(it.Value()), gp_Ax1(gp_Pnt(realOf(nd, "ox"), realOf(nd, "oy"), realOf(nd, "oz")),
                                                gp_Dir(realOf(nd, "dx"), realOf(nd, "dy"), realOf(nd, "dz")))});
    } catch (const Standard_Failure&) {
    }
  }
  return out;
}

std::optional<ConstructionAxis> Document::axis(const std::string& name) const {
  for (auto& a : axes())
    if (a.name == name) return a;
  return std::nullopt;
}

void Document::setAxis(const ConstructionAxis& a) {
  requireTransaction("setAxis");
  TDF_Label l = namedChild(doc_, kAxesTag, a.name);
  if (l.IsNull()) l = doc_->Main().FindChild(kAxesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(a.name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  const gp_Pnt o = a.axis.Location();
  const gp_Dir d = a.axis.Direction();
  nd->SetReal("ox", o.X());
  nd->SetReal("oy", o.Y());
  nd->SetReal("oz", o.Z());
  nd->SetReal("dx", d.X());
  nd->SetReal("dy", d.Y());
  nd->SetReal("dz", d.Z());
}

std::string Document::nextAxisName() const {
  return freeName(features(), "Axis", [&](const std::string& n) { return axis(n).has_value(); });
}

gp_Ax1 Document::axisFrame(const std::string& spec) const {
  if (spec == "X") return gp::OX();
  if (spec == "Y") return gp::OY();
  if (spec == "Z" || spec.empty()) return gp::OZ();
  if (const auto a = axis(spec)) return a->axis;
  throw DocumentError("unknown axis '" + spec + "'");
}

std::vector<Component> Document::components() const {
  std::vector<Component> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kComponentsTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;
    Component c;
    c.name = nameOf(it.Value());
    std::stringstream ss(stringOf(nd, "bodies"));
    std::string b;
    while (std::getline(ss, b, ';'))
      if (!b.empty()) c.bodies.push_back(b);
    out.push_back(std::move(c));
  }
  return out;
}

std::optional<Component> Document::component(const std::string& name) const {
  for (auto& c : components())
    if (c.name == name) return c;
  return std::nullopt;
}

void Document::setComponent(const Component& c) {
  requireTransaction("setComponent");
  TDF_Label l = namedChild(doc_, kComponentsTag, c.name);
  if (l.IsNull()) l = doc_->Main().FindChild(kComponentsTag, false).NewChild();
  TDataStd_Name::Set(l, ext(c.name));
  std::string joined;
  for (const auto& b : c.bodies) joined += (joined.empty() ? "" : ";") + b;
  TDataStd_NamedData::Set(l)->SetString("bodies", ext(joined));
}

std::string Document::nextComponentName() const {
  return freeName(features(), "Component", [&](const std::string& n) { return component(n).has_value(); });
}

std::optional<std::string> Document::componentOfBody(const std::string& body) const {
  for (const auto& c : components())
    if (std::find(c.bodies.begin(), c.bodies.end(), body) != c.bodies.end()) return c.name;
  return std::nullopt;
}

std::vector<ConstructionPoint> Document::points() const {
  std::vector<ConstructionPoint> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kPointsTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue;
    out.push_back({nameOf(it.Value()), gp_Pnt(realOf(nd, "x"), realOf(nd, "y"), realOf(nd, "z"))});
  }
  return out;
}

std::optional<ConstructionPoint> Document::point(const std::string& name) const {
  for (auto& p : points())
    if (p.name == name) return p;
  return std::nullopt;
}

void Document::setPoint(const ConstructionPoint& p) {
  requireTransaction("setPoint");
  TDF_Label l = namedChild(doc_, kPointsTag, p.name);
  if (l.IsNull()) l = doc_->Main().FindChild(kPointsTag, false).NewChild();
  TDataStd_Name::Set(l, ext(p.name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  nd->SetReal("x", p.point.X());
  nd->SetReal("y", p.point.Y());
  nd->SetReal("z", p.point.Z());
}

std::string Document::nextPointName() const {
  return freeName(features(), "Point", [&](const std::string& n) { return point(n).has_value(); });
}

namespace {
// Timeline order and marker, kept on the features label.
Handle(TDataStd_NamedData) timelineData(const Handle(TDocStd_Document)& doc, bool create) {
  const TDF_Label l = doc->Main().FindChild(kFeaturesTag, false);
  Handle(TDataStd_NamedData) nd;
  if (!l.FindAttribute(TDataStd_NamedData::GetID(), nd) && create) nd = TDataStd_NamedData::Set(l);
  return nd;
}
} // namespace

int Document::historyMarker() const {
  const auto all = features();
  int n = static_cast<int>(all.size());
  const Handle(TDataStd_NamedData) nd = timelineData(doc_, false);
  // -1 (or nothing stored): at the end.
  if (!nd.IsNull() && nd->HasInteger("marker") && nd->GetInteger("marker") >= 0) n = std::min(nd->GetInteger("marker"), n);
  return n;
}

void Document::setTimeline(const std::vector<int>& order, int marker) {
  requireTransaction("setTimeline");
  std::string s;
  for (int id : order) s += (s.empty() ? "" : ",") + std::to_string(id);
  const Handle(TDataStd_NamedData) nd = timelineData(doc_, true);
  nd->SetString("order", ext(s));
  nd->SetInteger("marker", marker >= static_cast<int>(order.size()) ? -1 : std::max(0, marker));
}

std::vector<Feature> Document::features() const {
  std::vector<Feature> out;
  for (TDF_ChildIterator it(doc_->Main().FindChild(kFeaturesTag, false)); it.More(); it.Next()) {
    Handle(TDataStd_NamedData) nd;
    if (!it.Value().FindAttribute(TDataStd_NamedData::GetID(), nd)) continue; // removed
    Feature f;
    f.id = it.Value().Tag();
    f.name = nameOf(it.Value());
    f.commandId = stringOf(nd, "command");
    f.inputs = fromJson(stringOf(nd, "inputs"));
    f.error = stringOf(nd, "error");
    f.suppressed = nd->HasInteger("suppressed") && nd->GetInteger("suppressed") != 0;
    f.parameterNames = parseNames(stringOf(nd, "params"));
    out.push_back(std::move(f));
  }
  // The saved order (features made since come after, in the order made).
  const Handle(TDataStd_NamedData) tl = timelineData(doc_, false);
  if (!tl.IsNull() && tl->HasString("order")) {
    std::vector<int> order;
    std::stringstream ss(stringOf(tl, "order"));
    std::string item;
    while (std::getline(ss, item, ','))
      if (!item.empty()) order.push_back(std::stoi(item));
    auto rank = [&](int id) {
      const auto it = std::find(order.begin(), order.end(), id);
      return it == order.end() ? static_cast<long>(order.size()) + id : static_cast<long>(it - order.begin());
    };
    std::stable_sort(out.begin(), out.end(), [&](const Feature& a, const Feature& b) { return rank(a.id) < rank(b.id); });
  }
  int marker = static_cast<int>(out.size());
  if (!tl.IsNull() && tl->HasInteger("marker") && tl->GetInteger("marker") >= 0)
    marker = std::min(marker, tl->GetInteger("marker"));
  for (int i = marker; i < static_cast<int>(out.size()); ++i) out[i].rolledBack = true;
  return out;
}

std::optional<Feature> Document::feature(int id) const {
  for (auto& f : features())
    if (f.id == id) return f;
  return std::nullopt;
}

void Document::recordFeature(const Command& cmd, const Inputs& inputs) {
  requireTransaction("recordFeature");
  const CommandDef& d = cmd.def();
  int n = 1;
  for (const auto& f : features())
    if (f.commandId == d.id) ++n;
  std::string base = d.name;
  base.erase(std::remove(base.begin(), base.end(), ' '), base.end());
  if (const auto slash = base.find('/'); slash != std::string::npos) base.resize(slash);   // "Move/Copy" -> "Move"
  std::string name = base + std::to_string(n);
  if (!d.nameInput.empty())
    if (auto it = inputs.find(d.nameInput); it != inputs.end())
      if (auto s = std::get_if<std::string>(&it->second); s && !s->empty()) name = *s;
  // Rolled back: the new feature goes in at the history marker.
  std::vector<int> order;
  int marker = -1;
  {
    const auto before = features();
    const int m = historyMarker();
    if (m < static_cast<int>(before.size())) {
      for (const auto& f : before) order.push_back(f.id);
      marker = m;
    }
  }
  const TDF_Label l = doc_->Main().FindChild(kFeaturesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  nd->SetString("command", ext(d.id));
  nd->SetString("inputs", ext(toJson(inputs).dump()));
  nd->SetString("error", ext(""));
  nd->SetInteger("suppressed", 0);
  nameFeatureParameters(l.Tag(), cmd, inputs);
  effects_[l.Tag()] = effectOf(txnBodies_, bodyShapes());
  effects_[l.Tag()].tools = pendingTools_;
  // Added at the end of a timeline whose replay is remembered: remember this
  // step too, so editing any feature later restores everything before it.
  if (marker < 0 && registry_) {
    const auto all = features();
    const std::string context = replayContext();
    if (!all.empty() && all.back().id == l.Tag() && replaySteps_.size() + 1 == all.size() &&
        (replaySteps_.empty() || context == replayContext_)) {
      replayContext_ = context;
      std::optional<Inputs> evaluated;
      std::string early;
      ReplayStep step = captureStep();
      step.key = replayKey(all.back(), currentParams(), evaluated, early);
      step.effect = effects_[l.Tag()];
      if (early.empty()) replaySteps_.push_back(std::move(step));
    }
  }
  if (marker >= 0) {
    order.insert(order.begin() + marker, l.Tag());
    setTimeline(order, marker + 1);
  }
}

std::map<std::string, TopoDS_Shape> Document::bodyShapes() const {
  std::map<std::string, TopoDS_Shape> out;
  for (const auto& b : bodies()) out[b.name] = b.shape;
  return out;
}

Document::FeatureEffect Document::effectOf(const std::map<std::string, TopoDS_Shape>& before,
                                           const std::map<std::string, TopoDS_Shape>& after) {
  FeatureEffect e;
  for (const auto& [name, shape] : after) {
    const auto it = before.find(name);
    if (it == before.end()) e.bodies[name] = {TopoDS_Shape(), shape};
    else if (!it->second.IsSame(shape)) e.bodies[name] = {it->second, shape};
  }
  for (const auto& [name, shape] : before)
    if (!after.count(name)) e.bodies[name] = {shape, TopoDS_Shape()};
  return e;
}

const Document::FeatureEffect* Document::featureEffect(int id) {
  if (auto it = effects_.find(id); it != effects_.end()) return it->second.bodies.empty() ? nullptr : &it->second;
  if (replaying_ || !registry_ || !hasOpenTransaction()) return nullptr;
  recompute(*registry_);   // fills effects_ for every feature
  if (auto it = effects_.find(id); it != effects_.end() && !it->second.bodies.empty()) return &it->second;
  return nullptr;
}

void Document::setFeatureInputs(int id, const Inputs& inputs) {
  requireTransaction("setFeatureInputs");
  featureData(doc_, id)->SetString("inputs", ext(toJson(inputs).dump()));
  // A value shown only now (Extent changed to Distance ...) gets its name.
  if (registry_)
    if (const auto f = feature(id))
      if (const Command* cmd = registry_->find(f->commandId)) nameFeatureParameters(id, *cmd, inputs);
}

void Document::setFeatureSuppressed(int id, bool suppressed) {
  requireTransaction("setFeatureSuppressed");
  featureData(doc_, id)->SetInteger("suppressed", suppressed ? 1 : 0);
}

void Document::removeFeature(int id) {
  requireTransaction("removeFeature");
  {
    const auto all = features();
    const int m = historyMarker();
    std::vector<int> order;
    int pos = -1;
    for (size_t i = 0; i < all.size(); ++i) {
      if (all[i].id == id) pos = static_cast<int>(i);
      else order.push_back(all[i].id);
    }
    if (pos >= 0 && m < static_cast<int>(all.size())) setTimeline(order, pos < m ? m - 1 : m);
  }
  (void)featureData(doc_, id);
  doc_->Main().FindChild(kFeaturesTag, false).FindChild(id, false).ForgetAllAttributes(true);
}

// What a feature is replayed with: its place, command, state, evaluated
// inputs, and the values of every parameter its inputs name (sketch
// dimension expressions read parameters directly, not through the inputs).
std::string Document::replayKey(const Feature& f, const ParamSet& paramSet, std::optional<Inputs>& evaluated,
                                std::string& early) const {
  const auto& params = paramSet.text;
  std::string k = std::to_string(f.id) + '|' + f.name + '|' + f.commandId + '|' + (f.suppressed ? 's' : '-') +
                  (f.rolledBack ? 'r' : '-') + '|';
  if (f.rolledBack || f.suppressed) return k;
  const std::string raw = toJson(f.inputs).dump();
  for (size_t a = 0; a < raw.size();) {
    if (!(std::isalpha(static_cast<unsigned char>(raw[a])) || raw[a] == '_')) {
      ++a;
      continue;
    }
    size_t b = a;
    while (b < raw.size() && (std::isalnum(static_cast<unsigned char>(raw[b])) || raw[b] == '_')) ++b;
    if (auto it = params.find(raw.substr(a, b - a)); it != params.end()) k += it->first + '=' + it->second + ';';
    a = b;
  }
  k += '|';
  const Command* cmd = registry_ ? registry_->find(f.commandId) : nullptr;
  if (!cmd) {
    early = "unknown command '" + f.commandId + "'";
  } else {
    try {
      Inputs in = f.inputs;
      evaluateFeatureExpressions(*cmd, in, &paramSet.env);
      k += toJson(in).dump();
      evaluated = std::move(in);
    } catch (const std::exception& e) {
      early = e.what();
    } catch (const Standard_Failure& e) {
      early = std::string("geometry kernel failure: ") + e.GetMessageString();
    }
  }
  return k + '!' + early;
}

// Everything a replay reads besides what the keys hold and what earlier
// features made: the units and body names.
std::string Document::replayContext() const {
  std::ostringstream os;
  os.precision(17);
  os << lengthUnit() << '\n';
  Handle(TDataStd_NamedData) names;
  if (doc_->Main().FindChild(kBodyNamesTag, false).FindAttribute(TDataStd_NamedData::GetID(), names)) {
    std::map<std::string, std::string> sorted;
    for (TDataStd_DataMapIteratorOfDataMapOfStringString it(names->GetStringsContainer()); it.More(); it.Next())
      sorted[utf8(it.Key())] = utf8(it.Value());
    for (const auto& [k, v] : sorted) os << "n " << k << '=' << v << '\n';
  }
  return os.str();
}

Document::ReplayStep Document::captureStep() const {
  ReplayStep s;
  for (const auto& b : bodies()) s.bodies.emplace_back(b.name, b.shape);
  s.sketches = sketches();
  s.planes = planes();
  s.axes = axes();
  s.points = points();
  s.components = components();
  s.dims = sketchDimensions(s.sketches);
  return s;
}

void Document::restoreStep(const ReplayStep& s) {
  for (const auto& [name, shape] : s.bodies) addBody(name, shape);
  for (const auto& r : s.sketches) setSketch(r);
  for (const auto& p : s.planes) setPlane(p);
  for (const auto& a : s.axes) setAxis(a);
  for (const auto& p : s.points) setPoint(p);
  for (const auto& c : s.components) setComponent(c);
}

void Document::recompute(const CommandRegistry& registry) {
  requireTransaction("recompute");
  for (int tag : {kBodiesTag, kSketchesTag, kPlanesTag, kAxesTag, kPointsTag, kComponentsTag})
    for (TDF_ChildIterator it(doc_->Main().FindChild(tag, false)); it.More(); it.Next())
      if (it.Value().HasAttribute()) it.Value().ForgetAllAttributes(true);

  registry_ = &registry;
  replaying_ = true;
  struct Done {
    bool& flag;
    ~Done() { flag = false; }
  } done{replaying_};
  effects_.clear();

  // What each feature will be replayed with. Expressions are evaluated
  // first: a parameter change shows in the inputs, so the key changes.
  const std::vector<Feature> fs = features();
  std::vector<std::optional<Inputs>> evaluated(fs.size());
  std::vector<std::string> keys(fs.size()), early(fs.size());

  // The longest run of unchanged features from the start is restored. Each
  // key is worked out with the sketches as the step before it left them.
  const std::string context = replayContext();
  size_t reuse = 0;
  const char* full = std::getenv("TSR_FULL_REPLAY");
  if (context == replayContext_ && !(full && *full && *full != '0')) {
    const std::vector<ModelParameter> none;
    const auto users = userParameters();
    const auto values = featureValueParameters();
    while (reuse < fs.size() && reuse < replaySteps_.size()) {
      keys[reuse] = replayKey(fs[reuse], paramSet(reuse == 0 ? none : replaySteps_[reuse - 1].dims, users, values),
                              evaluated[reuse], early[reuse]);
      if (replaySteps_[reuse].key != keys[reuse]) break;
      ++reuse;
    }
  }
  replayContext_ = context;
  replaySteps_.resize(reuse);
  if (reuse > 0) restoreStep(replaySteps_[reuse - 1]);

  for (size_t i = 0; i < fs.size(); ++i) {
    const Feature& f = fs[i];
    Handle(TDataStd_NamedData) nd = featureData(doc_, f.id);
    if (evaluated[i] && *evaluated[i] != f.inputs) nd->SetString("inputs", ext(toJson(*evaluated[i]).dump()));
    if (i < reuse) {
      effects_[f.id] = replaySteps_[i].effect;
      if (!f.rolledBack && stringOf(nd, "error") != replaySteps_[i].error) nd->SetString("error", ext(replaySteps_[i].error));
      continue;
    }
    // Worked out now, with the sketches the features before it made.
    evaluated[i].reset();
    early[i].clear();
    keys[i] = replayKey(f, currentParams(), evaluated[i], early[i]);
    if (evaluated[i] && *evaluated[i] != f.inputs) nd->SetString("inputs", ext(toJson(*evaluated[i]).dump()));
    std::string error = early[i];
    pendingTools_.clear();
    if (f.rolledBack) {   // after the history marker
      effects_[f.id] = FeatureEffect{};
    } else {
      const auto before = bodyShapes();
      if (!f.suppressed && error.empty()) {
        try {
          registry.find(f.commandId)->apply(*evaluated[i], *this);
        } catch (const std::exception& e) {
          error = e.what();
        } catch (const Standard_Failure& e) {
          error = std::string("geometry kernel failure: ") + e.GetMessageString();
        } catch (...) {
          error = "geometry kernel failure";
        }
      }
      effects_[f.id] = error.empty() ? effectOf(before, bodyShapes()) : FeatureEffect{};
      if (error.empty()) effects_[f.id].tools = pendingTools_;
      if (stringOf(nd, "error") != error) nd->SetString("error", ext(error));
    }
    ReplayStep step = captureStep();
    step.key = keys[i];
    step.effect = effects_[f.id];
    step.error = error;
    replaySteps_.push_back(std::move(step));
  }
  lastReused_ = static_cast<int>(reuse);
  lastReplayed_ = static_cast<int>(fs.size() - reuse);
}

std::string Document::ocafBytes() const {
  std::ostringstream os(std::ios::binary);
  const PCDM_StoreStatus st = ocafApplication()->SaveAs(doc_, os);
  if (st != PCDM_SS_OK) throw DocumentError("OCAF store failed (PCDM_StoreStatus " + std::to_string(st) + ")");
  return os.str();
}

} // namespace tsr::doc
