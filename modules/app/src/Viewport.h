#pragma once
// The 3D canvas: an OCCT AIS viewer rendered inside a QOpenGLWidget.
//
// Navigation follows the common CAD convention: middle-drag pans,
// Shift+middle-drag orbits, the wheel zooms about the cursor, left click/drag
// selects, right click opens the context menu. The ViewCube (top right)
// snaps to standard views.
#include "tsr/doc/Document.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_ViewCube.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

#include <QOpenGLWidget>
#include <QStringList>

#include <map>
#include <string>
#include <vector>

namespace tsr::app {

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
  bool gridVisible() const { return grid_; }
  void setOrbitTool(bool on);   // left-drag orbits instead of selecting
  void setPanTool(bool on);     // left-drag pans

  QStringList selectedBodies() const;
  void clearSelection();

signals:
  void bodyClicked(const QString& name);
  void selectionChanged();
  void contextMenuRequested(const QPoint& globalPos);

protected:
  void initializeGL() override;
  void paintGL() override;
  void paintEvent(QPaintEvent* e) override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void wheelEvent(QWheelEvent* e) override;

  // AIS_ViewController
  void OnSelectionChanged(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;
  void handleViewRedraw(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) override;

private:
  void bindLeftButton();
  void rebuild();
  void applyStyle(const Handle(AIS_Shape)& s);
  static Graphic3d_MaterialAspect bodyMaterial();
  Graphic3d_Vec2i toPixels(const QPointF& p) const;
  Aspect_Drawable nativeDrawable();
  void updateView() { update(); }

  Handle(V3d_Viewer) viewer_;
  Handle(V3d_View) view_;
  Handle(AIS_InteractiveContext) context_;
  Handle(AIS_ViewCube) cube_;

  std::vector<doc::Body> bodies_;
  std::map<std::string, Handle(AIS_Shape)> shapes_;
  std::map<std::string, bool> hidden_;

  Style style_ = Style::ShadedEdges;
  bool grid_ = true;
  bool orbitTool_ = false;
  bool panTool_ = false;
  bool glReady_ = false;
  bool fittedOnce_ = false;
  QString reason_;
  QPointF pressPos_;
};

} // namespace tsr::app
