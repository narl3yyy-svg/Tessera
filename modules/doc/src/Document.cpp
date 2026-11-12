#include "tsr/doc/Document.h"
#include "OcafApp.h"

#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_NamedData.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>

#include <nlohmann/json.hpp>

#include "tsr/doc/DocCommands.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <algorithm>
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
}

void Document::requireTransaction(const char* what) const {
  if (!doc_->HasOpenCommand())
    throw DocumentError(std::string(what) + " requires an open transaction");
}

void Document::openTransaction(const std::string& name) {
  if (doc_->HasOpenCommand()) throw DocumentError("a transaction is already open");
  doc_->NewCommand();
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
  const bool ok = doc_->Undo();
  modified_ = modified_ || ok;
  return ok;
}

bool Document::redo() {
  if (!canRedo()) return false;
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

ExpressionEnv Document::expressionEnv() const {
  ExpressionEnv env;
  env.lengthUnit = parseUnit(lengthUnit()).value_or(Unit::Millimeter);
  // Copy the values so the lookup does not walk OCAF per name.
  auto values = std::make_shared<std::map<std::string, Quantity>>();
  for (const auto& p : userParameters())
    (*values)[p.name] = quantityOf(p.value, parseUnit(p.unit).value_or(Unit::None));
  env.lookup = [values](const std::string& n) -> std::optional<Quantity> {
    auto it = values->find(n);
    if (it == values->end()) return std::nullopt;
    return it->second;
  };
  return env;
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

void Document::evaluateFeatureExpressions(const Command& cmd, Inputs& in) const {
  const Inputs original = in;
  for (const auto& [k, v] : original) {
    if (k.size() < 2 || k[0] != '=') continue;
    const auto* text = std::get_if<std::string>(&v);
    const InputDef* d = cmd.def().input(k.substr(1));
    if (!text || !d || (d->type != InputType::Real && d->type != InputType::Integer)) continue;
    double x = 0;
    try {
      x = evaluate(*text, d->unit);
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
  for (TDF_ChildIterator it(doc_->Main().FindChild(kBodiesTag, false)); it.More(); it.Next()) {
    Handle(TNaming_NamedShape) ns;
    if (!it.Value().FindAttribute(TNaming_NamedShape::GetID(), ns) || ns->IsEmpty()) continue;
    out.push_back({nameOf(it.Value()), ns->Get()});
  }
  return out;
}

void Document::addBody(const std::string& name, const TopoDS_Shape& shape) {
  requireTransaction("addBody");
  if (shape.IsNull()) throw DocumentError("cannot add a null body");
  const TDF_Label l = doc_->Main().FindChild(kBodiesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(name));
  TNaming_Builder(l).Generated(shape);
}

std::optional<Body> Document::body(const std::string& name) const {
  for (auto& b : bodies())
    if (b.name == name) return b;
  return std::nullopt;
}

void Document::replaceBody(const std::string& name, const TopoDS_Shape& shape) {
  requireTransaction("replaceBody");
  if (shape.IsNull()) throw DocumentError("cannot set a null body");
  const TDF_Label l = findBodyLabel(doc_, name);
  if (l.IsNull()) throw DocumentError("no body named '" + name + "'");
  TNaming_Builder(l).Generated(shape);
}

void Document::removeBody(const std::string& name) {
  requireTransaction("removeBody");
  const TDF_Label l = findBodyLabel(doc_, name);
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
    out.push_back(std::move(f));
  }
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
  const TDF_Label l = doc_->Main().FindChild(kFeaturesTag, false).NewChild();
  TDataStd_Name::Set(l, ext(name));
  Handle(TDataStd_NamedData) nd = TDataStd_NamedData::Set(l);
  nd->SetString("command", ext(d.id));
  nd->SetString("inputs", ext(toJson(inputs).dump()));
  nd->SetString("error", ext(""));
  nd->SetInteger("suppressed", 0);
}

void Document::setFeatureInputs(int id, const Inputs& inputs) {
  requireTransaction("setFeatureInputs");
  featureData(doc_, id)->SetString("inputs", ext(toJson(inputs).dump()));
}

void Document::setFeatureSuppressed(int id, bool suppressed) {
  requireTransaction("setFeatureSuppressed");
  featureData(doc_, id)->SetInteger("suppressed", suppressed ? 1 : 0);
}

void Document::removeFeature(int id) {
  requireTransaction("removeFeature");
  (void)featureData(doc_, id);
  doc_->Main().FindChild(kFeaturesTag, false).FindChild(id, false).ForgetAllAttributes(true);
}

void Document::recompute(const CommandRegistry& registry) {
  requireTransaction("recompute");
  for (int tag : {kBodiesTag, kSketchesTag, kPlanesTag})
    for (TDF_ChildIterator it(doc_->Main().FindChild(tag, false)); it.More(); it.Next())
      if (it.Value().HasAttribute()) it.Value().ForgetAllAttributes(true);

  for (const Feature& f : features()) {
    std::string error;
    if (!f.suppressed) {
      if (const Command* cmd = registry.find(f.commandId)) {
        try {
          Inputs in = f.inputs;
          evaluateFeatureExpressions(*cmd, in);
          if (in != f.inputs) featureData(doc_, f.id)->SetString("inputs", ext(toJson(in).dump()));
          cmd->apply(in, *this);
        } catch (const std::exception& e) {
          error = e.what();
        }
      } else {
        error = "unknown command '" + f.commandId + "'";
      }
    }
    Handle(TDataStd_NamedData) nd = featureData(doc_, f.id);
    if (stringOf(nd, "error") != error) nd->SetString("error", ext(error));
  }
}

std::string Document::ocafBytes() const {
  std::ostringstream os(std::ios::binary);
  const PCDM_StoreStatus st = ocafApplication()->SaveAs(doc_, os);
  if (st != PCDM_SS_OK) throw DocumentError("OCAF store failed (PCDM_StoreStatus " + std::to_string(st) + ")");
  return os.str();
}

} // namespace tsr::doc
