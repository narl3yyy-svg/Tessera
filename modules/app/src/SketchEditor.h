#pragma once
// Sketch mode: draws, constrains and dimensions one sketch in the 3D view.
//
// The editor works on its own copy of the sketch and only touches the
// document on Finish (one undo step: create the sketch feature, or change an
// existing one so the timeline replays). Inside sketch mode it keeps its own
// undo history.
#include "Viewport.h"

#include "tsr/doc/Session.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <AIS_InteractiveObject.hxx>

#include <QObject>
#include <QPointer>
#include <QString>

#include "tsr/core/Units.h"

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
  Tool tool() const { return tool_; }
  void setConstruction(bool on) { construction_ = on; }
  bool construction() const { return construction_; }

  void undo();
  void redo();
  bool canUndo() const { return !undo_.empty(); }
  bool canRedo() const { return !redo_.empty(); }
  void deleteSelection();
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

  // ViewInteractor
  void mousePress(QMouseEvent* e) override;
  void mouseMove(QMouseEvent* e) override;
  void mouseRelease(QMouseEvent* e) override;
  void mouseDoubleClick(QMouseEvent* e) override;
  bool keyPress(QKeyEvent* e) override;

  // Typing a value while drawing (like the on-canvas input): a length for a
  // line, a diameter for a circle, "w x h" for a rectangle. For tests too.
  bool typeValue(const QString& text);

signals:
  void changed();
  void message(const QString& text);

private:
  struct Hit {
    enum Kind { None, Point, Entity, Label } kind = None;
    int index = -1;
  };
  struct Pick {
    Hit hit;
    double x = 0, y = 0;
  };

  bool toSketch(const QPointF& pos, double& x, double& y) const;
  double tolerance() const;   // hit radius in sketch units
  Hit hitTest(double x, double y, bool pointsFirst = true) const;
  Hit hitEntity(double x, double y) const;
  int snapPoint(double x, double y, int exclude = -1) const;
  int materialize(const Pick& p);   // the picked point, created if it was empty space
  Pick pickPoint(double x, double y, int exclude = -1) const;
  void press(double x, double y, Qt::KeyboardModifiers mods, const QPointF& widgetPos);
  void constraintPick(double x, double y);
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
  QString labelText(const sketch::Constraint& c) const;

  void snapToGrid(double& x, double& y) const;
  QString lengthText(double cm) const;
  void openTypedBox(const QString& initial);

  doc::Session& session_;
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
  QPointF pressPos_;
  QPointer<QLineEdit> valueBox_;

  std::vector<Handle(AIS_InteractiveObject)> objects_;
  std::vector<Handle(AIS_InteractiveObject)> preview_;
};

} // namespace tsr::app
