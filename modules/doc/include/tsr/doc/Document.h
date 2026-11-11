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
//   0:1:3      Features (the timeline), in order; one child per feature:
//                TDataStd_Name       feature name ("Box1")
//                TDataStd_NamedData  "command" (id), "inputs" (JSON), "error" (last recompute), "suppressed" (int)
//
// Bodies are the result of replaying the features in order (recompute()).
// Removed entries keep their label with no attributes, so label tags stay
// stable ids; readers skip empty labels.
//
// Every mutation happens inside a transaction (CommandContext). One committed
// transaction is one undo step.
#include "tsr/core/Command.h"
#include "tsr/core/CommandRegistry.h"

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

struct Feature {
  int id = 0;              // stable within a document (OCAF label tag)
  std::string name;        // "Box1"
  std::string commandId;   // "tsr.primitive.box"
  Inputs inputs;
  std::string error;       // why the last recompute failed, empty if it worked
  bool suppressed = false;
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
  std::optional<Body> body(const std::string& name) const;
  void addBody(const std::string& name, const TopoDS_Shape& shape);
  void replaceBody(const std::string& name, const TopoDS_Shape& shape);
  void removeBody(const std::string& name);
  std::string nextBodyName() const;   // "Body<n>", n above every existing number

  // Design history.
  std::vector<Feature> features() const;
  std::optional<Feature> feature(int id) const;
  void recordFeature(const Command& cmd, const Inputs& inputs) override;
  void setFeatureInputs(int id, const Inputs& inputs);
  void setFeatureSuppressed(int id, bool suppressed);
  void removeFeature(int id);
  // Rebuilds every body by replaying the features in order. A feature that
  // fails keeps its error and the replay continues. Requires a transaction.
  void recompute(const CommandRegistry& registry);

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
