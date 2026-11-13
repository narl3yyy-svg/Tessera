#pragma once
// Sketch mode: draws, constrains and dimensions one sketch in the 3D view.
//
// The editor works on its own copy of the sketch and only touches the
// document on Finish (one undo step: create the sketch feature, or change an
// existing one so the timeline replays). Inside sketch mode it keeps its own
// undo history.
#include "Viewport.h"

#include <TopoDS_Edge.hxx>

#include "tsr/doc/Session.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <AIS_InteractiveObject.hxx>
#include <Quantity_Color.hxx>

#include <QObject>
#include <QPointer>
#include <QString>

#include "tsr/core/Units.h"

#include <array>
#include <optional>
#include <vector>

class QLineEdit;

namespace tsr::app {

class SketchEditor final : public QObject, public ViewInteractor {
  Q_OBJECT
public:
  enum class Tool {
    Select, Line, Rectangle, Circle, Arc, Point, Dimension,
    Coincident, HorizontalVertical, Parallel, Perpendicular, Equal, Tangent, Fix, Midpoint, Concentric,
    CenterRectangle, Polygon, Slot, Trim, Collinear, Symmetry,
    Spline, Fillet, Offset, Chamfer, Extend, Mirror, Project,
  };

  // featureId < 0: a new sketch named `name`.
  SketchEditor(doc::Session& session, Viewport* viewport, const QString& name, const QString& plane, double offset,
               int featureId, const sketch::Sketch& initial, QObject* parent = nullptr);
  ~SketchEditor() override;

  QString name() const { return name_; }
  const sketch::Sketch& sketch() const { return sk_; }
  const sketch::SolveResult& status() const { return res_; }
  const gp_Ax3& frame() const { return frame_; }

  void setTool(Tool t);
  // Space: the last drawing tool again (after Esc went back to selecting).
  void repeatLastTool() { setTool(lastTool_); }
  Tool tool() const { return tool_; }
  void setConstruction(bool on) {
    construction_ = on;
    emit changed();
  }

  // What the canvas shows (Sketch Palette > Options).
  struct Display {
    bool profiles = true;       // closed regions shaded
    bool points = true;
    bool dimensions = true;
    bool constraints = true;    // constraint glyphs
    bool construction = true;   // construction curves
    bool projected = true;      // geometry projected from bodies
  };
  const Display& display() const { return display_; }
  void setDisplay(const Display& d);
  bool construction() const { return construction_; }

  void undo();
  void redo();
  bool canUndo() const { return !undo_.empty(); }
  bool canRedo() const { return !redo_.empty(); }
  void deleteSelection();
  // X / Normal-Construction with curves selected: flips those curves between
  // normal and construction. False when no curve is selected.
  bool toggleSelectedConstruction();
  QStringList parameterNames() const;   // user parameters, for value suggestions
  // Right-click: selects what is under the widget position if nothing
  // selected is there (so the menu acts on it). True if anything is selected.
  bool selectAt(const QPointF& widgetPos);
  bool hasSelection() const { return !selection_.empty(); }
  // Esc: abandons the current drawing step, then the tool.
  void escape();

  // Adds a constraint if it keeps the sketch solvable; empty or an error.
  std::string constrain(const sketch::Constraint& c);

  // Commits to the document. Returns empty on success, else the error (the
  // editor stays open).
  std::string finish();

  // For scripted tests: a left click at sketch coordinates (cm), and typing a
  // value into the open dimension box.
  void clickAt(double x, double y);
  bool submitValue(const QString& text);
  void hoverAt(double x, double y) {   // as if the cursor moved there (tests, screenshots)
    cursorX_ = x;
    cursorY_ = y;
    updatePreview(x, y);
  }

  // ViewInteractor
  void mousePress(QMouseEvent* e) override;
  void mouseMove(QMouseEvent* e) override;
  void mouseRelease(QMouseEvent* e) override;
  void mouseDoubleClick(QMouseEvent* e) override;
  bool keyPress(QKeyEvent* e) override;
  bool eventFilter(QObject* watched, QEvent* e) override;

  // Typing a value while drawing (like the on-canvas input): a length for a
  // line, a diameter for a circle, "w x h" for a rectangle. For tests too.
  bool typeValue(const QString& text);

signals:
  void changed();
  void toolChanged();
  void message(const QString& text);

private:
  struct Hit {
    enum Kind { None, Point, Entity, Label } kind = None;
    int index = -1;
  };
  struct Pick {
    Hit hit;
    double x = 0, y = 0;
    int onEntity = -1;     // lands on this curve: a point-on-curve constraint is added
    int midpointOf = -1;   // at this line's midpoint: a midpoint constraint is added
    int perpendicularTo = -1;   // the new line is perpendicular to this line
    int tangentTo = -1;         // the new line is tangent to this arc (or continues this line)
    int parallelTo = -1;        // the new line is parallel to this line
    int bodyArc = -1;           // on this curved body edge: it is projected too
    bool bodyPoint = false;     // on body geometry: the point is projected (fixed)
    int bodySegment = -1;       // on this straight body edge: the edge is projected too
    bool onXAxis = false;       // on the sketch's X axis (lined up with the origin): kept there
    bool onYAxis = false;       // on the sketch's Y axis
  };

  // Where the cursor snaps while drawing, like the familiar sketcher:
  // existing points, line midpoints, body vertices and edges lying in the
  // sketch plane, curves, horizontal/vertical from the previous point,
  // alignment with other points, then the grid.
  struct Snap {
    enum Kind { Free, Point, Midpoint, OnCurve, BodyVertex, BodyEdge, Grid } kind = Free;
    double x = 0, y = 0;
    int point = -1;
    int entity = -1;
    bool horizontal = false, vertical = false;   // H/V from the previous point
    bool perpendicular = false, tangent = false; // to the curve the line starts from
    bool parallel = false;                       // to `reference`, a line elsewhere
    int reference = -1;                          // that curve
    int bodySegment = -1;                        // BodyEdge: which straight body edge
    int bodyArc = -1;                            // BodyEdge: which curved body edge
    int alignX = -1, alignY = -1;                // lined up with these points
    double fromX = 0, fromY = 0;                 // the previous point (for H/V guides)
  };
  Snap snapAt(double x, double y, int exclude = -1) const;
  void showSnap(const Snap& s);
  // Body geometry lying in the sketch plane (sketch coordinates).
  struct PlaneEdges {
    std::vector<std::pair<double, double>> vertices;
    std::vector<std::array<double, 4>> segments;          // x1, y1, x2, y2
    std::vector<std::array<double, 5>> arcs;              // cx, cy, r, a0, sweep (full circle: sweep 2*pi)
  } bodyEdges_;
  bool projectEdgeShape(const TopoDS_Edge& edge, PlaneEdges& out) const;
  void collectBodyEdges();
  // Constraint labels that belong to projected geometry are not shown.
  bool onlyProjected(const sketch::Constraint& c) const;
  // The curve (line or arc) that ends at `point`, if exactly one does, and
  // its direction there, pointing out of the curve.
  int curveEndingAt(int point, int exclude = -1) const;
  std::optional<std::pair<double, double>> leavingDirection(int entity, int point) const;
  // Click and drag from the end of a line (Line tool): a tangent arc.
  bool arcDrag_ = false;
  bool arcDragMoved_ = false;
  bool arcEndsChain_ = false;   // started by a double-click: no drag ends the chain
  int arcFrom_ = -1;   // the point it starts at
  int arcRef_ = -1;    // the curve it is tangent to
  bool tangentArc(double x, double y, double& cx, double& cy, double& r, bool& ccw) const;
  void finishArcDrag(double x, double y);

public:
  // Tests: a click-and-drag from the line chain's last point to (x, y).
  bool dragTangentArcForTest(double x, double y);
  // Tests: Mirror's Enter (objects picked, now the mirror line).
  void mirrorObjectsDoneForTest() { if (!picks_.empty()) mirrorLineStage_ = true; }

private:

  bool toSketch(const QPointF& pos, double& x, double& y) const;
  double tolerance() const;   // hit radius in sketch units
  Hit hitTest(double x, double y, bool pointsFirst = true) const;
  Hit hitEntity(double x, double y) const;
  int snapPoint(double x, double y, int exclude = -1) const;
  int materialize(const Pick& p);   // the picked point, created if it was empty space
  Pick pickPoint(double x, double y, int exclude = -1) const;
  void press(double x, double y, Qt::KeyboardModifiers mods, const QPointF& widgetPos);
  void constraintPick(double x, double y);
  int projectSegment(const std::array<double, 4>& g);
  int projectArc(const std::array<double, 5>& g);
  void projectAt(const QPointF& widgetPos);
  void evaluateConstraintPicks();
  void applyToSelection(const std::vector<Hit>& selected);
  static bool isConstraintTool(Tool t);
  static bool snapsSuppressed();   // Ctrl held
  void dimensionPick(double x, double y, const QPointF& widgetPos);
  void askValue(const sketch::Constraint& c, const QPointF& widgetPos, int editIndex = -1);
  double currentValue(const sketch::Constraint& c) const;
  void autoHorizontalVertical(int line);

  void checkpoint();   // before a change: push undo state
  void solveAndShow();
  void resetSteps();
  void rebuild();
  void updatePreview(double x, double y);
  void clearPreview();
  std::optional<std::pair<double, double>> labelAnchor(int constraintIndex) const;
  // Dimensions drawn as in the familiar sketcher: extension lines, a
  // dimension line with arrows (or a leader / an arc), the value at (lx, ly).
  std::pair<double, double> dimensionBase(const sketch::Constraint& c) const;
  void addDimensionGraphics(const sketch::Constraint& c, double lx, double ly, const Quantity_Color& colour,
                            std::vector<Handle(AIS_InteractiveObject)>& out) const;
  // Dimension tool: the dimension the picks make with the cursor at (x, y)
  // (where the cursor is decides horizontal / vertical / aligned).
  std::optional<sketch::Constraint> dimensionCandidate(double x, double y) const;
  int dragLabel_ = -1;   // Select: a dimension's value being dragged
  QString labelText(const sketch::Constraint& c) const;

  // On-canvas size boxes (the heads-up inputs). After the first click of a
  // drawing tool they show the live sizes; typing a value locks it (Tab moves
  // to the next box, Enter creates the shape), and locked values become
  // dimensions on the new geometry.
  struct HudField {
    QPointer<QLineEdit> edit;
    enum Kind { Length, Angle, Count } kind = Length;
    bool locked = false;
    bool editing = false;
    double value = 0;
  };
  std::vector<HudField> hud_;
  bool hudTool() const;
  void ensureHud();
  void clearHud();
  bool hudLocked(size_t i) const { return i < hud_.size() && hud_[i].locked; }
  double hudValue(size_t i) const { return i < hud_.size() ? hud_[i].value : 0; }
  bool hudAnyLocked() const;
  bool lockField(size_t i);
  void commitHud();
  std::pair<double, double> hudTarget(double x, double y) const;
  void updateHud(double x, double y);
  int polygonSides() const;
  void trimAt(double x, double y);

  void snapToGrid(double& x, double& y) const;
  // Spline / Fillet / Offset
  void finishSpline(bool closed);
  std::vector<std::pair<double, double>> curveSamples(int entity) const;   // sketch coordinates
  double entityDistance(int entity, double x, double y) const;
  double filletRadiusAt(double x, double y) const;
  double offsetAt(double x, double y, double magnitude) const;   // signed: the side of the cursor
  std::pair<int, int> filletLines_{-1, -1};
  int firstFilletLine_ = -1;
  int offsetEntity_ = -1;
  bool mirrorLineStage_ = false;      // Mirror: objects picked, now the mirror line
  void mirrorPick(double x, double y);
  QString lengthText(double cm) const;

  doc::Session& session_;
  Tool lastTool_ = Tool::Line;
  Unit unit_ = Unit::Millimeter;
  double cursorX_ = 0, cursorY_ = 0;
  QPointer<Viewport> view_;
  QString name_;
  QString plane_;
  double offset_ = 0;
  int featureId_ = -1;
  gp_Ax3 frame_;
  gp_Ax3 previousGrid_;

  sketch::Sketch sk_;
  sketch::SolveResult res_;
  std::vector<sketch::Sketch> undo_, redo_;

  Tool tool_ = Tool::Line;
  bool construction_ = false;
  std::vector<Pick> steps_;       // clicks so far in the current drawing tool
  std::vector<Pick> picks_;       // constraint / dimension picks so far
  int chainStart_ = -1;           // first point of a line chain (once created)
  Hit hover_;
  std::vector<Hit> selection_;
  int dragPoint_ = -1;
  int dragLine_ = -1;
  double dragX_ = 0, dragY_ = 0;
  bool dragged_ = false;
  bool boxing_ = false;      // Select: a press on empty space; a drag draws a box
  bool boxShown_ = false;
  void selectInBox(const QPointF& from, const QPointF& to, Qt::KeyboardModifiers mods);
  QPointF pressPos_;
  QPointer<QLineEdit> valueBox_;

  Display display_;
  std::vector<Handle(AIS_InteractiveObject)> objects_;
  std::vector<Handle(AIS_InteractiveObject)> preview_;
};

} // namespace tsr::app
