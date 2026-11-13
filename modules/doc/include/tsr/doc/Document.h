#pragma once
// tsr-doc: the design document, stored in an OCAF TDocStd_Document.
//
// Label layout (P0):
//   0:1        Main
//   0:1:1      User parameters; one child per parameter:
//                TDataStd_Name       parameter name
//                TDataStd_NamedData  "expression", "unit", "comment" (strings), "value" (real, internal units)
//              Expressions may refer to other parameters; values are re-evaluated
//              whenever one changes (cycles are rejected).
//   0:1:2      Bodies; one child per body:
//                TDataStd_Name       body name
//                TNaming_NamedShape  the B-rep
//   0:1:4      Sketches (results of sketch features); one child per sketch:
//                TDataStd_Name       sketch name ("Sketch1")
//                TDataStd_NamedData  "plane" (spec), "offset" (real), "data" (solved sketch JSON)
//   0:1:5      Construction planes; one child per plane: TDataStd_Name, NamedData "spec"
//   0:1:6      Construction axes; one child per axis: TDataStd_Name, NamedData reals ox,oy,oz,dx,dy,dz
//   0:1:7      Construction points; one child per point: TDataStd_Name, NamedData reals x,y,z
//   0:1:8      Components; one child per component: TDataStd_Name, NamedData "bodies" ("Body1;Body2")
//   0:1:3      Features (the timeline), in order; one child per feature:
//                TDataStd_Name       feature name ("Box1")
//                TDataStd_NamedData  "command" (id), "inputs" (JSON), "error" (last recompute), "suppressed" (int)
//              Inputs given as expressions keep the text under "=<input id>"
//              (tsr::expressionKey); recompute evaluates them before replay.
//
// Bodies are the result of replaying the features in order (recompute()).
// Removed entries keep their label with no attributes, so label tags stay
// stable ids; readers skip empty labels.
//
// Every mutation happens inside a transaction (CommandContext). One committed
// transaction is one undo step.
#include "tsr/core/Command.h"
#include "tsr/core/CommandRegistry.h"
#include "tsr/core/Expression.h"

#include <TDocStd_Document.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pnt.hxx>

#include <filesystem>
#include <map>
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
  std::string name;      // the name features use (generated on replay: Body1, Body2 ...)
  TopoDS_Shape shape;
  std::string display;   // what the person called it (Browser, API); name if never renamed
};

struct SketchRecord {
  std::string name;
  std::string plane;   // tsr::sketch::planeFrame spec
  double offset = 0;
  std::string data;    // solved sketch JSON
};

struct ConstructionPlane {
  std::string name;   // "Plane1"
  std::string spec;   // custom:... frame (tsr::sketch::planeFrame)
};

struct ConstructionAxis {
  std::string name;   // "Axis1"
  gp_Ax1 axis;
};

struct ConstructionPoint {
  std::string name;   // "Point1"
  gp_Pnt point;
};

struct Component {
  std::string name;                 // "Component1"
  std::vector<std::string> bodies;  // bodies that belong to it
};

struct Feature {
  int id = 0;              // stable within a document (OCAF label tag)
  std::string name;        // "Box1"
  std::string commandId;   // "tsr.primitive.box"
  Inputs inputs;
  std::string error;       // why the last recompute failed, empty if it worked
  bool suppressed = false;
  bool rolledBack = false; // after the history marker: not replayed
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
  // Changes a parameter's expression and comment and re-evaluates every
  // parameter. Throws DocumentError (unknown name, bad expression, cycle).
  // Features are not replayed; call recompute() afterwards.
  void setUserParameter(const std::string& name, const std::string& expression, const std::string& comment);
  // Throws DocumentError if anything still refers to the parameter.
  void removeUserParameter(const std::string& name);
  // What refers to a parameter: "parameter <name>" or a feature name.
  std::vector<std::string> parameterUsers(const std::string& name) const;

  // Expressions. Names resolve to user parameters; bare numbers in a length
  // take the document's length unit.
  ExpressionEnv expressionEnv() const;
  // `unit` is an input's display unit: a length unit stands for the
  // document's length unit. Throws DocumentError.
  double evaluate(const std::string& text, Unit unit) const;
  double evaluateExpression(const std::string& text, Unit unit) override { return evaluate(text, unit); }

  std::vector<Body> bodies() const;
  std::optional<Body> body(const std::string& name) const;
  void addBody(const std::string& name, const TopoDS_Shape& shape);
  void replaceBody(const std::string& name, const TopoDS_Shape& shape);
  void removeBody(const std::string& name);
  std::string nextBodyName() const;   // "Body<n>", n above every existing number

  std::vector<SketchRecord> sketches() const;
  std::optional<SketchRecord> sketch(const std::string& name) const;
  void setSketch(const SketchRecord& s);   // adds, or replaces the one with that name
  std::string nextSketchName() const;

  // Construction planes (results of Construct features).
  std::vector<ConstructionPlane> planes() const;
  std::optional<ConstructionPlane> plane(const std::string& name) const;
  void setPlane(const ConstructionPlane& p);   // adds, or replaces the one with that name
  std::string nextPlaneName() const;
  // Resolves "XY"/"XZ"/"YZ"/"custom:..." or a construction plane's name,
  // moved by `offset` along its normal. Throws DocumentError.
  gp_Ax3 planeFrame(const std::string& spec, double offset = 0) const;

  // Construction axes and points (results of Construct features).
  std::vector<ConstructionAxis> axes() const;
  std::optional<ConstructionAxis> axis(const std::string& name) const;
  void setAxis(const ConstructionAxis& a);   // adds, or replaces the one with that name
  std::string nextAxisName() const;
  // "X", "Y", "Z" (world axes through the origin) or a construction axis's
  // name. Throws DocumentError.
  gp_Ax1 axisFrame(const std::string& spec) const;
  // Components (results of New Component features). Bodies not in any
  // component belong to the root.
  std::vector<Component> components() const;
  std::optional<Component> component(const std::string& name) const;
  void setComponent(const Component& c);
  std::string nextComponentName() const;
  std::optional<std::string> componentOfBody(const std::string& body) const;
  std::vector<ConstructionPoint> points() const;
  std::optional<ConstructionPoint> point(const std::string& name) const;
  void setPoint(const ConstructionPoint& p);
  std::string nextPointName() const;

  // Design history.
  std::vector<Feature> features() const;
  std::optional<Feature> feature(int id) const;
  void recordFeature(const Command& cmd, const Inputs& inputs) override;
  // The timeline, as in the familiar tool: features in order, and the history
  // marker (how many of them are replayed; new features go in at the marker).
  // marker == number of features: at the end.
  int historyMarker() const;
  void setTimeline(const std::vector<int>& order, int marker);   // requires a transaction
  void setFeatureInputs(int id, const Inputs& inputs);
  void setFeatureSuppressed(int id, bool suppressed);
  void removeFeature(int id);
  // Rebuilds every body by replaying the features in order. A feature that
  // fails keeps its error and the replay continues. Requires a transaction.
  void recompute(const CommandRegistry& registry);

  // What a feature did to the bodies: each body it changed, before and after
  // (a null shape: not there). Known for features replayed or made since the
  // document was opened; otherwise the history is replayed (needs the
  // registry and an open transaction). Null if the feature made no geometry.
  struct FeatureEffect {
    std::map<std::string, std::pair<TopoDS_Shape, TopoDS_Shape>> bodies;
    // The tool solids the feature combined with a body ("join", "cut",
    // "intersect") or added as new bodies ("new"). A pattern of the feature
    // re-applies these at each copy, as the familiar tool does; features
    // without tools are patterned by what they changed.
    struct Tool {
      TopoDS_Shape shape;
      std::string op;
      std::string target;
    };
    std::vector<Tool> tools;
  };
  const FeatureEffect* featureEffect(int id);
  void setRegistry(const CommandRegistry* registry) { registry_ = registry; }

  // Renaming. Bodies keep the names the replay generates; a rename stores
  // the name shown, and every name a body had (old or new) still finds it.
  // Sketches and features are renamed outright and every feature input that
  // refers to the old name is updated. All require a transaction.
  void renameBody(const std::string& name, const std::string& newName);
  std::string bodyName(const std::string& nameOrAlias) const;   // the internal name
  void renameSketch(const std::string& name, const std::string& newName);
  void renameFeature(int id, const std::string& newName);
  // Called by commands while they apply: the tool they combined with `target`.
  void noteTool(const TopoDS_Shape& tool, const std::string& op, const std::string& target) {
    pendingTools_.push_back({tool, op, target});
  }

  // Display unit for lengths: "mm" (default) or "in". Stored in the document.
  std::string defaultLengthUnit() const { return lengthUnit(); }
  std::string lengthUnit() const;
  void setLengthUnit(const std::string& unit);   // requires a transaction

  const Handle(TDocStd_Document)& ocaf() const { return doc_; }

  // Raw OCAF binary of the document (document/ocaf.xbf in the .tsr).
  std::string ocafBytes() const;

private:
  struct FromOcaf {};
  Document(FromOcaf, Handle(TDocStd_Document) doc);
  void initLayout();
  void requireTransaction(const char* what) const;
  void reevaluateParameters();
  // Evaluates the "=<id>" expressions of a feature's inputs into their values.
  void evaluateFeatureExpressions(const Command& cmd, Inputs& in) const;

  std::map<std::string, TopoDS_Shape> bodyShapes() const;
  static FeatureEffect effectOf(const std::map<std::string, TopoDS_Shape>& before,
                                const std::map<std::string, TopoDS_Shape>& after);

  Handle(TDocStd_Document) doc_;
  bool modified_ = false;
  std::map<int, FeatureEffect> effects_;           // in memory only
  std::map<std::string, TopoDS_Shape> txnBodies_;  // bodies when the transaction opened
  std::vector<FeatureEffect::Tool> pendingTools_;    // tools noted by the command applying now
  const CommandRegistry* registry_ = nullptr;
  bool replaying_ = false;
};

} // namespace tsr::doc
