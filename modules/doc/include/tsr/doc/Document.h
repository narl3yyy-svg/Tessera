#pragma once
// tsr-doc: the design document, stored in an OCAF TDocStd_Document.
//
// Label layout (P0):
//   0:1        Main
//   0:1:1      User parameters; one child per parameter:
//                TDataStd_Name       parameter name
//                TDataStd_NamedData  "expression", "unit", "comment" (strings), "value" (real, internal units)
//   0:1:2      Bodies; one child per body:
//                TDataStd_Name       body name
//                TNaming_NamedShape  the B-rep
//
// Every mutation happens inside a transaction (CommandContext). One committed
// transaction is one undo step.
#include "tsr/core/Command.h"

#include <TDocStd_Document.hxx>
#include <TopoDS_Shape.hxx>

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace tsr::doc {

class DocumentError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

struct UserParameter {
  std::string name;
  std::string expression; // as typed, e.g. "10 mm"
  std::string unit;       // "mm", "deg", "" ...
  std::string comment;
  double value = 0;       // evaluated, internal units
};

struct Body {
  std::string name;
  TopoDS_Shape shape;
};

class Document final : public CommandContext {
public:
  Document();  // new, empty document
  ~Document() override;
  Document(const Document&) = delete;
  Document& operator=(const Document&) = delete;

  // .tsr persistence (see TsrFile.cpp and plan §4.6). Throws DocumentError.
  static std::unique_ptr<Document> load(const std::filesystem::path& path);
  void save(const std::filesystem::path& path);

  // CommandContext
  void openTransaction(const std::string& name) override;
  void commitTransaction() override;
  void abortTransaction() override;
  bool hasOpenTransaction() const override;

  bool canUndo() const;
  bool canRedo() const;
  bool undo();
  bool redo();
  bool isModified() const { return modified_; }

  // Model. Mutators require an open transaction and throw DocumentError
  // otherwise.
  std::vector<UserParameter> userParameters() const;
  std::optional<UserParameter> userParameter(const std::string& name) const;
  void addUserParameter(const UserParameter& p);

  std::vector<Body> bodies() const;
  void addBody(const std::string& name, const TopoDS_Shape& shape);

  std::string defaultLengthUnit() const { return "mm"; }

  const Handle(TDocStd_Document)& ocaf() const { return doc_; }

  // Raw OCAF binary of the document (document/ocaf.xbf in the .tsr).
  std::string ocafBytes() const;

private:
  struct FromOcaf {};
  Document(FromOcaf, Handle(TDocStd_Document) doc);
  void initLayout();
  void requireTransaction(const char* what) const;

  Handle(TDocStd_Document) doc_;
  bool modified_ = false;
};

} // namespace tsr::doc
