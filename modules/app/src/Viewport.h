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
#include <gp_Ax3.hxx>

#include <QOpenGLWidget>
#include <QStringList>

#include <map>
#include <optional>
#include <string>
#include <vector>

class QKeyEvent;
class QMouseEvent;

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
  TopoDS_Shape curves;
  TopoDS_Shape construction;
  std::vector<sketch::Profile> profiles;
  bool visible = true;
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
  // Bodies drawn see-through (while a sketch is being edited).
  void setBodiesGhosted(bool on);
  bool gridVisible() const { return grid_; }
  void setOrbitTool(bool on);   // left-drag orbits instead of selecting
  void setPanTool(bool on);     // left-drag pans

  QStringList selectedBodies() const;
  void clearSelection();

  // Sketches and their profiles (closed regions).
  void setSketches(std::vector<SketchDisplay> sketches);
  void setProfilePicking(bool on);   // profiles become clickable (Extrude)
  void setPickedProfiles(const std::string& sketch, const std::vector<int>& indices);
  // Origin planes and flat body faces become clickable (Create Sketch).
  void setPlanePicking(bool on);
  bool planePicking() const { return planePicking_; }
  // Body edges become clickable (Fillet, Chamfer); picked ones are highlighted.
  void setEdgePicking(bool on);
  void setPickedEdges(const std::vector<TopoDS_Shape>& edges);
  // The current shape of a displayed body (what the user sees and clicks).
  TopoDS_Shape bodyShape(const QString& name) const;

  // For the sketch editor.
  void setInteractor(ViewInteractor* interactor);
  const Handle(AIS_InteractiveContext)& aisContext() const { return context_; }
  bool planePoint(const QPointF& widgetPos, const gp_Ax3& frame, gp_Pnt& out) const;
  double modelPerPixel() const;   // model length of one logical pixel
  // Looks straight at the plane, centred on `center` (default: the plane origin).
  void lookAt(const gp_Ax3& frame, double size = 0, std::optional<gp_Pnt> center = std::nullopt);
  void setGridPlane(const gp_Ax3& frame);   // the layout grid follows the active sketch
  void redraw() { update(); }

signals:
  void profileClicked(const QString& sketch, int index);
  void edgeClicked(const QString& body, const TopoDS_Shape& edge);
  void planePicked(const QString& spec, const QString& label);
  void bodyClicked(const QString& name);
  void selectionChanged();
  void contextMenuRequested(const QPoint& globalPos);
  void statusMessage(const QString& text);

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

  // AIS_ViewController
  void OnSelectionChanged(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;
  void handleViewRedraw(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;

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
  std::vector<std::pair<Handle(AIS_Shape), std::string>> planeObjects_;
  bool profilePicking_ = false;
  bool edgePicking_ = false;
  bool ghosted_ = false;
  std::vector<Handle(AIS_Shape)> pickedEdgeObjects_;
  bool planePicking_ = false;
  std::string pickedSketch_;
  std::vector<int> pickedProfiles_;
  ViewInteractor* interactor_ = nullptr;

  bool orbitTool_ = false;
  bool panTool_ = false;
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
};

} // namespace tsr::app
