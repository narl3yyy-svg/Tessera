#include "tsr/doc/Document.h"
#include "OcafApp.h"

#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_NamedData.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>

#include <sstream>
#include <vector>

namespace tsr::doc {

namespace {
constexpr int kParamsTag = 1;
constexpr int kBodiesTag = 2;
// Plan §2 asks for unbounded undo; OCAF needs a number. A million steps is
// unbounded for practical purposes and is recorded in SPEC/DIVERGENCES.md.
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

std::string Document::ocafBytes() const {
  std::ostringstream os(std::ios::binary);
  const PCDM_StoreStatus st = ocafApplication()->SaveAs(doc_, os);
  if (st != PCDM_SS_OK) throw DocumentError("OCAF store failed (PCDM_StoreStatus " + std::to_string(st) + ")");
  return os.str();
}

} // namespace tsr::doc
