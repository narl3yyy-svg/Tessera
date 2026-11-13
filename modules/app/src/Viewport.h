#pragma once
// The 3D canvas: an OCCT AIS viewer rendered inside a QOpenGLWidget.
//
// Navigation follows the common CAD convention: middle-drag pans,
// Shift+middle-drag orbits, the wheel zooms about the cursor, left click/drag
// selects, right click opens the context menu. The ViewCube (top right)
// snaps to standard views.
#include "tsr/doc/Document.h"
#include "tsr/sketch/SketchGeometry.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_ViewCube.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <Graphic3d_ClipPlane.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Face.hxx>
#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>

#include <QOpenGLWidget>
#include <QImage>
#include <QStringList>

#include <map>
#include <optional>
#include <string>
#include <vector>

class QKeyEvent;
class QLabel;
class QLineEdit;
class QMouseEvent;
class QTimer;

namespace tsr::app {

// Takes over the left mouse button and keys while active (sketch editing).
// Middle-button navigation and the wheel keep working.
class ViewInteractor {
public:
  virtual ~ViewInteractor() = default;
  virtual void mousePress(QMouseEvent*) {}
  virtual void mouseMove(QMouseEvent*) {}
  virtual void mouseRelease(QMouseEvent*) {}
  virtual void mouseDoubleClick(QMouseEvent*) {}
  virtual bool keyPress(QKeyEvent*) { return false; }
};

// A finished sketch as shown in the canvas.
struct SketchDisplay {
  std::string name;
  gp_Ax3 frame;
  TopoDS_Shape curves;        // under-defined curves (blue, as in the familiar tool)
  TopoDS_Shape fixedCurves;   // fully defined ones (black; white on the dark theme)
  TopoDS_Shape construction;
  std::vector<sketch::Profile> profiles;
  bool visible = true;
};

// Surface analysis shown instead of the plain bodies (Inspect panel).
enum class AnalysisKind { None, Zebra, Draft, CurvatureMap };
struct AnalysisSettings {
  AnalysisKind kind = AnalysisKind::None;
  int stripes = 12;                    // Zebra: stripes per half turn of the normal
  gp_Dir stripeAxis = gp::DZ();        // Zebra: stripes run around this direction
  gp_Dir pull = gp::DZ();              // Draft: pull direction
  double draftAngle = 0.0174532925;    // Draft: required angle (rad)
  double curvatureScale = 1.0;         // Curvature Map: colour scale (cm)
};

class Viewport : public QOpenGLWidget, public AIS_ViewController {
  Q_OBJECT
public:
  enum class Style { Shaded, ShadedEdges, Wireframe };

  explicit Viewport(QWidget* parent = nullptr);
  ~Viewport() override;

  // False when no OpenGL view could be created (e.g. QT_QPA_PLATFORM=offscreen).
  // Everything else keeps working; the canvas then shows a message.
  bool available() const { return glReady_; }
  QString unavailableReason() const { return reason_; }

  void setBodies(const std::vector<doc::Body>& bodies);
  void setBodyVisible(const QString& name, bool visible);
  bool isBodyVisible(const QString& name) const;

  void fitAll();
  void home();
  void viewFrom(V3d_TypeOfOrientation orientation);
  void setStyle(Style s);
  Style style() const { return style_; }
  void setGridVisible(bool visible);
  void applyTheme();   // background, grid and ViewCube colours

  // Layout grid spacing (cm) and snapping sketch points to it.
  void setGridSpacing(double cm);
  // The grid step in use (cm): with the adaptive grid (the default, as in the
  // familiar tool) a 1-2-5 step that follows the zoom, else the fixed spacing.
  // Grid snapping uses the same step.
  double gridSpacing() const;
  double fixedGridSpacing() const { return gridSpacing_; }
  void setAdaptiveGrid(bool on);
  bool adaptiveGrid() const { return adaptiveGrid_; }
  void setGridSnap(bool on) { gridSnap_ = on; }
  bool gridSnap() const { return gridSnap_; }

  // Navigation (Preferences): mouse scheme, zoom direction, orbit, camera.
  enum class NavPreset { Fusion, SolidWorks, Tinkercad };
  void setNavigation(NavPreset preset, bool reverseZoom, bool constrainedOrbit, bool perspective);
  NavPreset navPreset() const { return navPreset_; }
  bool perspective() const { return perspective_; }

  // What a normal click selects: empty = whole bodies; default faces and edges.
  void setSelectionFilter(const std::vector<TopAbs_ShapeEnum>& types);
  const std::vector<TopAbs_ShapeEnum>& selectionFilter() const { return selectFilter_; }

  QImage capture();   // the canvas as an image
  // Bodies drawn see-through (while a sketch is being edited).
  void setBodiesGhosted(bool on);
  bool gridVisible() const { return grid_; }
  void setOrbitTool(bool on);   // left-drag orbits instead of selecting
  void setPanTool(bool on);     // left-drag pans

  QStringList selectedBodies() const;
  // The body under a canvas point (its shown name), empty if none.
  QString bodyNameAt(const QPointF& pos);
  // Faces, edges and vertices selected (with a selection filter), by body.
  std::vector<std::pair<QString, TopoDS_Shape>> selectedSubShapes() const;
  void clearSelection();

  // Window / crossing selection, as in the familiar tool: drag left to right
  // for a window (solid blue box, only what is wholly inside), right to left
  // for a crossing (dashed green box, anything it touches). Shift adds,
  // Ctrl removes. The sketch editor draws the same box.
  void showSelectionBox(const QPointF& from, const QPointF& to);
  void hideSelectionBox();
  // True while a box's picks are being reported: they add, never toggle off.
  bool boxPicking() const { return boxPicking_; }

  // Sketches and their profiles (closed regions).
  void setSketches(std::vector<SketchDisplay> sketches);
  void setProfilePicking(bool on);   // profiles become clickable (Extrude)
  void setPickedProfiles(const std::string& sketch, const std::vector<int>& indices);
  // Origin planes and flat body faces become clickable (Create Sketch).
  void setPlanePicking(bool on);
  bool planePicking() const { return planePicking_; }
  // While plane picking: the centre of each origin plane's square (tests).
  const std::vector<std::pair<std::string, gp_Pnt>>& planeCentres() const { return planeCentres_; }
  // Construction planes (name, frame), drawn as translucent squares; they are
  // clickable while plane picking is on.
  void setConstructionPlanes(const std::vector<std::pair<std::string, gp_Ax3>>& planes);
  // Construction axes (dashed lines) and points (small rings), with names.
  void setConstructionAxesPoints(const std::vector<std::pair<std::string, gp_Ax1>>& axes,
                                 const std::vector<std::pair<std::string, gp_Pnt>>& points);
  // Parts of bodies become clickable (edges for Fillet, faces for Shell,
  // vertices/edges/faces for Measure); picked ones are highlighted.
  void setSubShapePicking(const std::vector<TopAbs_ShapeEnum>& types);
  void setEdgePicking(bool on) { setSubShapePicking(on ? std::vector<TopAbs_ShapeEnum>{TopAbs_EDGE} : std::vector<TopAbs_ShapeEnum>{}); }
  void setPickedShapes(const std::vector<TopoDS_Shape>& shapes);
  void setPickedEdges(const std::vector<TopoDS_Shape>& edges) { setPickedShapes(edges); }

  // Section analysis: bodies are cut by the plane (the side the normal points
  // to is removed) and the cut faces are filled with a hatch.
  void setSection(bool on, const gp_Pln& plane = gp_Pln());

  // Surface analysis (Zebra, Draft, Curvature Map) replaces the shaded
  // bodies until set back to None; the comb draws along the given edges.
  void setAnalysis(const AnalysisSettings& a);
  const AnalysisSettings& analysis() const { return analysis_; }
  void setCurvatureComb(const std::vector<TopoDS_Shape>& edges, double scale);
  bool sectionOn() const { return sectionOn_; }

  // Measure overlay: a line between two points with a label; none to clear.
  void setMeasureLine(bool on, const gp_Pnt& from = gp_Pnt(), const gp_Pnt& to = gp_Pnt(), const QString& label = QString());
  // A marker with a label at a point (Center of Mass); none to clear.
  void setMarker(bool on, const gp_Pnt& at = gp_Pnt(), const QString& label = QString());
  // The current shape of a displayed body (what the user sees and clicks).
  TopoDS_Shape bodyShape(const QString& name) const;

  // For the sketch editor.
  void setInteractor(ViewInteractor* interactor);
  const Handle(AIS_InteractiveContext)& aisContext() const { return context_; }
  bool planePoint(const QPointF& widgetPos, const gp_Ax3& frame, gp_Pnt& out) const;
  double modelPerPixel() const;   // model length of one logical pixel
  QPointF toWidget(const gp_Pnt& p) const;   // where a 3D point appears in the widget
  // Looks straight at the plane, centred on `center` (default: the plane origin).
  void lookAt(const gp_Ax3& frame, double size = 0, std::optional<gp_Pnt> center = std::nullopt);
  void setGridPlane(const gp_Ax3& frame);   // the layout grid follows the active sketch
  void redraw() { update(); }

  // In-canvas drag arrow (Extrude distance, Fillet radius, Press Pull ...):
  // an arrow at base + dir * value. Press and drag it along dir to change the
  // value; the box beside it shows the value and takes typed values or
  // expressions. `text` is what the box shows when it is not being edited.
  // `which` 1 is a second, independent arrow (the other side of a Two Sides
  // extrude); it reports through secondArrowMoved / secondArrowTyped.
  void setDragArrow(const gp_Pnt& base, const gp_Dir& dir, double value, const QString& text, int which = 0);
  void clearDragArrow();     // both arrows
  void clearSecondArrow();   // arrow 1 only
  bool dragArrowActive(int which = 0) const { return which >= 0 && which < 2 && arrows_[which].has_value(); }
  double dragArrowValue(int which = 0) const { return dragArrowActive(which) ? arrows_[which]->value : 0.0; }
  QLineEdit* dragArrowBox(int which = 0) const { return which >= 0 && which < 2 ? arrowBoxes_[which] : nullptr; }
  // Tests: as if the arrow were dragged to `value` and released.
  void dragArrowForTest(double value, int which = 0);
  // Where to grab the arrow (widget coordinates), when there is one.
  std::optional<QPointF> dragArrowHandle(int which = 0) const;
  // A short instruction that follows the cursor ("Select sketch profiles or
  // planar faces to extrude"); empty hides it.
  void setCursorHint(const QString& text);
  // Draws these shapes instead of the named bodies (empty: back to normal).
  void setBodyOverrides(const std::map<std::string, TopoDS_Shape>& shapes);
  // The nearest shown body face under a widget position (null if none), and
  // the sketch plane spec of a flat one there (empty if none or curved).
  TopoDS_Face faceAt(const QPointF& pos) const;
  QString sketchPlaneAt(const QPointF& pos) const;
  // The point of a shown body under a widget position (ray cast), if any.
  std::optional<gp_Pnt> pointAt(const QPointF& pos) const;
  QPointF lastPressPos() const { return pressPos_; }
  static QString faceSketchSpec(const TopoDS_Face& face);

signals:
  void profileClicked(const QString& sketch, int index);
  void subShapeClicked(const QString& body, const TopoDS_Shape& shape);
  void planePicked(const QString& spec, const QString& label);
  void bodyClicked(const QString& name);
  void selectionChanged();
  void contextMenuRequested(const QPoint& globalPos);
  void statusMessage(const QString& text);
  void dragArrowMoved(double value);      // while the arrow is dragged
  void dragArrowReleased(double value);   // mouse released
  void dragArrowTyped(const QString& text);   // Enter in the value box
  void secondArrowMoved(double value);        // the second arrow, while dragged
  void secondArrowTyped(const QString& text); // Enter in the second value box

protected:
  void initializeGL() override;
  void paintGL() override;
  void paintEvent(QPaintEvent* e) override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void wheelEvent(QWheelEvent* e) override;
  void mouseDoubleClickEvent(QMouseEvent* e) override;
  void keyPressEvent(QKeyEvent* e) override;
  // Tab goes to the sketch editor (size boxes) instead of moving focus.
  bool focusNextPrevChild(bool next) override;
  void leaveEvent(QEvent* e) override;

  // AIS_ViewController
  void OnSelectionChanged(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;
  void handleViewRedraw(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;
  // Hover: near an edge of the face under the cursor, the edge lights up.
  void handleDynamicHighlight(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;
  Handle(SelectMgr_EntityOwner) frontEdgeOwner() const;

private:
  void bindLeftButton();
  void rebuild();
  void rebuildSketches();
  void applyPickModes();
  bool handlePickSelection();   // profile / plane clicks; true if consumed
  Aspect_VKeyMouse aisButtons(Qt::MouseButtons b) const;
  void applyStyle(const Handle(AIS_Shape)& s);
  static Graphic3d_MaterialAspect bodyMaterial();
  Graphic3d_Vec2i toPixels(const QPointF& p) const;
  Aspect_Drawable nativeDrawable();
  void updateView() { update(); }
  // After a programmatic camera or grid change: the main layers must be
  // re-rendered, not just the immediate layer.
  void redrawAll() {
    if (!view_.IsNull()) view_->Invalidate();
    update();
  }

  Handle(V3d_Viewer) viewer_;
  Handle(V3d_View) view_;
  Handle(AIS_InteractiveContext) context_;
  Handle(AIS_ViewCube) cube_;

  std::vector<doc::Body> bodies_;
  std::map<std::string, Handle(AIS_Shape)> shapes_;
  std::map<std::string, bool> hidden_;
  std::map<std::string, TopoDS_Shape> overrides_;

  Style style_ = Style::ShadedEdges;
  bool grid_ = true;
  struct ProfileObject {
    Handle(AIS_Shape) shape;
    std::string sketch;
    int index = 0;
  };
  std::vector<SketchDisplay> sketches_;
  std::vector<Handle(AIS_Shape)> sketchCurves_;
  std::vector<ProfileObject> profileObjects_;
  std::vector<std::pair<Handle(AIS_InteractiveObject), std::string>> planeObjects_;
  std::vector<std::pair<std::string, gp_Pnt>> planeCentres_;
  std::vector<std::pair<std::string, gp_Ax3>> constructionPlanes_;
  std::vector<std::pair<std::string, gp_Ax1>> constructionAxes_;
  std::vector<std::pair<std::string, gp_Pnt>> constructionPoints_;
  std::vector<std::pair<Handle(AIS_InteractiveObject), std::string>> constructionObjects_;
  void rebuildConstruction();
  bool profilePicking_ = false;
  std::vector<TopAbs_ShapeEnum> pickTypes_;
  bool sectionOn_ = false;
  Handle(Graphic3d_ClipPlane) clip_;
  std::vector<Handle(AIS_InteractiveObject)> measureObjects_;
  std::vector<Handle(AIS_InteractiveObject)> markerObjects_;
  AnalysisSettings analysis_;
  std::vector<Handle(AIS_InteractiveObject)> analysisObjects_;
  std::vector<Handle(AIS_InteractiveObject)> combObjects_;
  void buildAnalysis();
  void clearAnalysisObjects();
  bool ghosted_ = false;
  std::vector<Handle(AIS_Shape)> pickedObjects_;
  bool planePicking_ = false;
  std::string pickedSketch_;
  std::vector<int> pickedProfiles_;
  ViewInteractor* interactor_ = nullptr;

  double gridSpacing_ = 1.0;
  bool adaptiveGrid_ = true;
  double appliedGridStep_ = 0;   // what the viewer's grid shows now
  void updateGridStep();
  bool gridSnap_ = false;
  NavPreset navPreset_ = NavPreset::Fusion;
  bool reverseZoom_ = false;
  bool perspective_ = false;
  // As in the familiar tool, a click picks the face or edge under the cursor
  // (empty: whole bodies, the Select Bodies filter).
  std::vector<TopAbs_ShapeEnum> selectFilter_{TopAbs_FACE, TopAbs_EDGE};
  void bindNavigation();

  bool orbitTool_ = false;
  bool panTool_ = false;
  // The left button in the default select mode is handled here (click and
  // window / crossing box), not by the view controller.
  bool ownsLeftButton() const { return !interactor_ && !orbitTool_ && !panTool_; }
  void clickSelect(const QPointF& pos, Qt::KeyboardModifiers mods);
  void boxSelect(const QPointF& from, const QPointF& to, Qt::KeyboardModifiers mods);
  QWidget* selectionBox_ = nullptr;
  QTimer* hoverTimer_ = nullptr;   // a short rest over a body shows its name
  QPointF hoverPos_;
  bool leftDown_ = false;
  bool boxDrag_ = false;
  bool boxPicking_ = false;
  bool glReady_ = false;
  bool fittedOnce_ = false;
  QString reason_;
  QPointF pressPos_;
  struct PendingLook {
    gp_Ax3 frame;
    double size;
    std::optional<gp_Pnt> center;
  };
  std::optional<PendingLook> pendingLook_;   // lookAt before GL was ready

  struct DragArrow {
    gp_Pnt base;
    gp_Dir dir;
    double value = 0;
  };
  std::optional<DragArrow> arrows_[2];   // 0: main arrow, 1: second side
  int arrowDragging_ = -1;                // index of the arrow being dragged
  int arrowHover_ = -1;
  double arrowGrab_ = 0;   // value minus the cursor's position along the arrow at press
  std::vector<Handle(AIS_InteractiveObject)> arrowObjects_[2];
  QLineEdit* arrowBoxes_[2] = {nullptr, nullptr};
  bool anyArrow() const { return arrows_[0].has_value() || arrows_[1].has_value(); }
  void rebuildArrow(int which);
  void rebuildArrows();
  void placeArrowBoxes();
  // Focus the first arrow's value box with its text selected.
  void selectArrowValue();
  void clearArrow(int which);
  void emitArrow(int which, double value, bool released);
  int arrowAt(const QPointF& pos) const;   // the arrow under the cursor, or -1
  std::optional<double> arrowParam(int which, const QPointF& pos) const;
  bool arrowMousePress(QMouseEvent* e);
  bool arrowMouseMove(QMouseEvent* e);
  bool arrowMouseRelease(QMouseEvent* e);
  QLabel* pickHint_ = nullptr;   // "Select a plane or planar face" beside the cursor
  QString cursorHint_;
  // While picking edges/faces/vertices: a bold highlight of the one under the cursor.
  Handle(AIS_InteractiveObject) hoverObject_;
  TopoDS_Shape hoverShape_;
  // With no command running: the edge / vertex under the cursor and the ones
  // selected, drawn thick over everything (the view's own highlight is thin).
  void showIdleHover(const TopoDS_Shape& s);
  // Double-click on an edge: the loop of edges round the face it bounds.
  bool selectEdgeLoop(const QPointF& pos);
  // Click and hold: a list of everything under the cursor (Select Other).
  void showSelectOther(const QPointF& pos);
  QTimer* holdTimer_ = nullptr;
  void refreshSelectionOverlay();
  Handle(AIS_InteractiveObject) idleHover_;
  TopoDS_Shape idleHoverShape_;
  std::vector<Handle(AIS_InteractiveObject)> selectionOverlay_;
  void updateHoverHighlight(const QPointF& pos);
  void clearHoverHighlight();
};

} // namespace tsr::app
