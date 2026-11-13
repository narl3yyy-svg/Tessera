#include "Viewport.h"
#include "Theme.h"

#include <AIS_AnimationCamera.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Grid.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Graphic3d_Camera.hxx>
#include <Graphic3d_TransformPers.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Standard_Failure.hxx>
#include <StdSelect_BRepOwner.hxx>

#include <QGuiApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QPainter>
#include <QSurfaceFormat>
#include <QLabel>
#include <QTimer>
#include <QWheelEvent>

#include <cmath>

namespace tsr::app {

namespace {

// QOpenGLWidget renders into its own FBO; OCCT must draw into that one
// (wrapped below) and must not treat it as sRGB.
class QtFrameBuffer : public OpenGl_FrameBuffer {
  DEFINE_STANDARD_RTTI_INLINE(QtFrameBuffer, OpenGl_FrameBuffer)
public:
  void BindBuffer(const Handle(OpenGl_Context)& ctx) override {
    OpenGl_FrameBuffer::BindBuffer(ctx);
    ctx->SetFrameBufferSRGB(true, false);
  }
  void BindDrawBuffer(const Handle(OpenGl_Context)& ctx) override {
    OpenGl_FrameBuffer::BindDrawBuffer(ctx);
    ctx->SetFrameBufferSRGB(true, false);
  }
};

// OCCT's mouse/modifier constants are separate unnamed enums; combine as ints.
constexpr unsigned keys(unsigned mouse, unsigned flags = 0) { return mouse | flags; }

Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }
Quantity_Color qc(const QColor& c) { return rgb(c.red(), c.green(), c.blue()); }

Aspect_VKeyMouse toVKeys(Qt::MouseButtons b) {
  Aspect_VKeyMouse k = Aspect_VKeyMouse_NONE;
  if (b & Qt::LeftButton) k |= Aspect_VKeyMouse_LeftButton;
  if (b & Qt::MiddleButton) k |= Aspect_VKeyMouse_MiddleButton;
  // Right button is reserved for the context menu.
  return k;
}

Aspect_VKeyFlags toVKeys(Qt::KeyboardModifiers m) {
  Aspect_VKeyFlags f = Aspect_VKeyFlags_NONE;
  if (m & Qt::ShiftModifier) f |= Aspect_VKeyFlags_SHIFT;
  if (m & Qt::ControlModifier) f |= Aspect_VKeyFlags_CTRL;
  if (m & Qt::AltModifier) f |= Aspect_VKeyFlags_ALT;
  if (m & Qt::MetaModifier) f |= Aspect_VKeyFlags_META;
  return f;
}

} // namespace

// Light grey satin, similar in spirit to the neutral body colour CAD tools use
// so that faces read clearly under the key/fill lights.
Graphic3d_MaterialAspect Viewport::bodyMaterial() {
  Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
  const Quantity_Color base = rgb(188, 194, 202);
  m.SetDiffuseColor(base);
  m.SetAmbientColor(Quantity_Color(base.Rgb() * 0.45f));
  m.SetSpecularColor(Quantity_Color(0.22, 0.22, 0.22, Quantity_TOC_RGB));
  m.SetEmissiveColor(Quantity_Color(Quantity_NOC_BLACK));
  m.SetShininess(0.35f);
  return m;
}

Viewport::Viewport(QWidget* parent) : QOpenGLWidget(parent) {
  setObjectName(QStringLiteral("viewport"));
  setMouseTracking(true);
  setFocusPolicy(Qt::StrongFocus);
  setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
  setMinimumSize(200, 150);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setStencilBufferSize(8);
  fmt.setSamples(4);
  fmt.setVersion(4, 5);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  setFormat(fmt);

  // TKOpenGl on Kubuntu is built for GLX, so it needs the X11 (xcb) platform;
  // main() selects XWayland on a Wayland desktop.
  const QString platform = QGuiApplication::platformName();
  if (platform != QLatin1String("xcb")) {
    reason_ = tr("3D view unavailable on the '%1' platform (needs xcb/X11).").arg(platform);
    return;
  }

  try {
    Handle(Aspect_DisplayConnection) display = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(display, false);
    driver->ChangeOptions().buffersNoSwap = true;      // Qt swaps
    driver->ChangeOptions().buffersOpaqueAlpha = true;
    driver->ChangeOptions().useSystemBuffer = false;   // always render to an FBO

    viewer_ = new V3d_Viewer(driver);
    // Key light from upper left, softer fill from the right, both fixed to the
    // camera so the model is always lit from the viewer's side.
    Handle(V3d_DirectionalLight) key = new V3d_DirectionalLight(gp_Dir(0.45, -0.55, -1.0), Quantity_NOC_WHITE, true);
    key->SetIntensity(0.9);
    Handle(V3d_DirectionalLight) fill = new V3d_DirectionalLight(gp_Dir(-0.7, 0.25, -0.6), Quantity_NOC_WHITE, true);
    fill->SetIntensity(0.45);
    Handle(V3d_AmbientLight) ambient = new V3d_AmbientLight(Quantity_NOC_WHITE);
    ambient->SetIntensity(0.38);
    viewer_->AddLight(key);
    viewer_->AddLight(fill);
    viewer_->AddLight(ambient);
    viewer_->SetLightOn();
    viewer_->SetRectangularGridValues(0, 0, 1.0, 1.0, 0);     // 10 mm cells
    viewer_->SetRectangularGridGraphicValues(25.0, 25.0, 0);  // 500 mm across
    viewer_->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);


    context_ = new AIS_InteractiveContext(viewer_);
    // Edges and points are picked within a few pixels, as in the familiar tool
    // (OCCT's default of 2 makes thin edges hard to hit).
    context_->SetPixelTolerance(6);
    context_->SetAutomaticHilight(true);
    {
      // Hover: light blue; selected: strong blue.
      Handle(Prs3d_Drawer) hover = context_->HighlightStyle(Prs3d_TypeOfHighlight_Dynamic);
      hover->SetColor(rgb(110, 170, 235));
      hover->SetTransparency(0.2f);
      Handle(Prs3d_Drawer) sel = context_->HighlightStyle(Prs3d_TypeOfHighlight_Selected);
      sel->SetColor(rgb(30, 120, 220));
      sel->SetTransparency(0.0f);
    }

    view_ = viewer_->CreateView();
    view_->SetImmediateUpdate(false);
    view_->SetLightOn();
    view_->SetShadingModel(Graphic3d_TypeOfShadingModel_Phong);
    view_->ChangeRenderingParams().NbMsaaSamples = 4;
    view_->ChangeRenderingParams().IsAntialiasingEnabled = true;

    view_->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GRAY40, 0.08, V3d_ZBUFFER);
    view_->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);

    cube_ = new AIS_ViewCube();
    cube_->SetSize(55);

    cube_->SetFontHeight(12);
    cube_->SetDrawAxes(false);
    cube_->SetViewAnimation(ViewAnimation());
    cube_->SetFixedAnimationLoop(false);
    cube_->SetAutoStartAnimation(true);
    cube_->SetDuration(0.35);
    cube_->SetTransformPersistence(
        new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(85, 85)));
  } catch (const Standard_Failure& f) {
    reason_ = tr("3D view unavailable: %1").arg(QString::fromUtf8(f.GetMessageString()));
    viewer_.Nullify();
    view_.Nullify();
    context_.Nullify();
    return;
  }

  pickHint_ = new QLabel(tr("Select a plane or planar face"), this);
  pickHint_->setObjectName(QStringLiteral("pickHint"));
  pickHint_->setStyleSheet(QStringLiteral("QLabel { background: rgba(40,44,52,225); color: #e8eaee; border: 1px solid #5b6472;"
                                          " padding: 2px 6px; }"));
  pickHint_->setAttribute(Qt::WA_TransparentForMouseEvents);
  pickHint_->hide();

  applyTheme();
  connect(&Theme::instance(), &Theme::changed, this, [this] {
    applyTheme();
    if (glReady_) rebuild();
  });

  // Mouse bindings (gesture = what a drag does, scheme = what a click selects).
  bindNavigation();
  AIS_MouseSelectionSchemeMap& s = ChangeMouseSelectionSchemes();
  s.Clear();
  s.Bind(Aspect_VKeyMouse_LeftButton, AIS_SelectionScheme_Replace);
  s.Bind(keys(Aspect_VKeyMouse_LeftButton, Aspect_VKeyFlags_SHIFT), AIS_SelectionScheme_XOR);
  s.Bind(keys(Aspect_VKeyMouse_LeftButton, Aspect_VKeyFlags_CTRL), AIS_SelectionScheme_XOR);
  SetStickToRayOnZoom(true);
}

Viewport::~Viewport() {
  // Release GL resources while Qt's context is current. The view itself is
  // not Remove()d: that re-binds OCCT's window after Qt has torn it down.
  if (glReady_) {
    makeCurrent();
    context_->RemoveAll(false);
    doneCurrent();
  }
}

void Viewport::bindNavigation() {
  AIS_MouseGestureMap& g = ChangeMouseGestureMap();
  g.Clear();
  switch (navPreset_) {
    case NavPreset::Fusion:   // middle pans, Shift+middle orbits
      g.Bind(Aspect_VKeyMouse_MiddleButton, AIS_MouseGesture_Pan);
      g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_SHIFT), AIS_MouseGesture_RotateOrbit);
      g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_CTRL), AIS_MouseGesture_Zoom);
      break;
    case NavPreset::SolidWorks:   // middle orbits, Ctrl+middle pans, Shift+middle zooms
      g.Bind(Aspect_VKeyMouse_MiddleButton, AIS_MouseGesture_RotateOrbit);
      g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_CTRL), AIS_MouseGesture_Pan);
      g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_SHIFT), AIS_MouseGesture_Zoom);
      break;
    case NavPreset::Tinkercad:   // right orbits, middle pans
      g.Bind(Aspect_VKeyMouse_RightButton, AIS_MouseGesture_RotateOrbit);
      g.Bind(Aspect_VKeyMouse_MiddleButton, AIS_MouseGesture_Pan);
      g.Bind(keys(Aspect_VKeyMouse_RightButton, Aspect_VKeyFlags_SHIFT), AIS_MouseGesture_Pan);
      break;
  }
  bindLeftButton();
}

void Viewport::setNavigation(NavPreset preset, bool reverseZoom, bool constrainedOrbit, bool perspective) {
  navPreset_ = preset;
  reverseZoom_ = reverseZoom;
  SetLockOrbitZUp(constrainedOrbit);
  perspective_ = perspective;
  bindNavigation();
  if (!view_.IsNull()) {
    view_->Camera()->SetProjectionType(perspective ? Graphic3d_Camera::Projection_Perspective
                                                   : Graphic3d_Camera::Projection_Orthographic);
    redrawAll();
  }
}

void Viewport::setGridSpacing(double cm) {
  gridSpacing_ = std::max(cm, 1e-4);
  updateGridStep();
}

void Viewport::setAdaptiveGrid(bool on) {
  adaptiveGrid_ = on;
  updateGridStep();
}

double Viewport::gridSpacing() const {
  if (!adaptiveGrid_ || view_.IsNull() || !glReady_) return gridSpacing_;
  // About 24 pixels per cell, rounded up to 1, 2 or 5 times a power of ten.
  double want = 0;
  try {
    want = modelPerPixel() * 24;
  } catch (const Standard_Failure&) {   // the window is not mapped yet
    return gridSpacing_;
  }
  if (!(want > 0)) return gridSpacing_;
  const double p = std::pow(10.0, std::floor(std::log10(want)));
  for (double m : {1.0, 2.0, 5.0, 10.0})
    if (m * p >= want * 0.999) return m * p;
  return 10 * p;
}

void Viewport::updateGridStep() {
  if (viewer_.IsNull() || !glReady_) return;
  const double step = gridSpacing();
  if (std::abs(step - appliedGridStep_) <= 1e-12 * std::max(1.0, step)) return;
  appliedGridStep_ = step;
  viewer_->SetRectangularGridValues(0, 0, step, step, 0);
  // Fixed: 25 cells each way; adaptive: enough to fill the view.
  const double half = step * (adaptiveGrid_ ? 120 : 25);
  viewer_->SetRectangularGridGraphicValues(half, half, 0);
  redrawAll();
}

void Viewport::setSelectionFilter(const std::vector<TopAbs_ShapeEnum>& types) {
  selectFilter_ = types;
  if (!context_.IsNull()) context_->ClearSelected(false);
  applyPickModes();
  redrawAll();
}

QImage Viewport::capture() {
  if (glReady_) return grabFramebuffer();
  return grab().toImage();
}

void Viewport::bindLeftButton() {
  AIS_MouseGestureMap& g = ChangeMouseGestureMap();
  const AIS_MouseGesture left = orbitTool_ ? AIS_MouseGesture_RotateOrbit
                              : panTool_   ? AIS_MouseGesture_Pan
                                           : AIS_MouseGesture_SelectRectangle;
  g.Bind(Aspect_VKeyMouse_LeftButton, left);
  g.Bind(keys(Aspect_VKeyMouse_LeftButton, Aspect_VKeyFlags_SHIFT), AIS_MouseGesture_SelectRectangle);
  g.Bind(keys(Aspect_VKeyMouse_LeftButton, Aspect_VKeyFlags_CTRL), AIS_MouseGesture_SelectRectangle);
}

void Viewport::setOrbitTool(bool on) {
  orbitTool_ = on;
  if (on) panTool_ = false;
  bindLeftButton();
  setCursor(on ? Qt::SizeAllCursor : Qt::ArrowCursor);
}

void Viewport::setPanTool(bool on) {
  panTool_ = on;
  if (on) orbitTool_ = false;
  bindLeftButton();
  setCursor(on ? Qt::OpenHandCursor : Qt::ArrowCursor);
}

Aspect_Drawable Viewport::nativeDrawable() {
  // The widget's own X window. OCCT may warn that its visual has no depth
  // buffer; that is harmless because it renders into Qt's FBO (wrapped in
  // paintGL), not into the window.
  return static_cast<Aspect_Drawable>(winId());
}

Graphic3d_Vec2i Viewport::toPixels(const QPointF& p) const {
  const qreal r = devicePixelRatioF();
  return Graphic3d_Vec2i(static_cast<int>(p.x() * r), static_cast<int>(p.y() * r));
}

void Viewport::initializeGL() {
  if (view_.IsNull()) return;
  const bool core = context() && context()->format().profile() == QSurfaceFormat::CoreProfile;
  Handle(OpenGl_Context) gl = new OpenGl_Context();
  if (!gl->Init(core)) {
    reason_ = tr("3D view unavailable: OCCT could not use the OpenGL context.");
    return;
  }
  Handle(Aspect_NeutralWindow) win = Handle(Aspect_NeutralWindow)::DownCast(view_->Window());
  const bool first = win.IsNull();
  if (first) {
    win = new Aspect_NeutralWindow();
    win->SetVirtual(true);
  }
  win->SetNativeHandle(nativeDrawable());
  const Graphic3d_Vec2i sz = toPixels(QPointF(width(), height()));
  win->SetSize(sz.x(), sz.y());
  try {
    view_->SetWindow(win, gl->RenderingContext());
  } catch (const Standard_Failure& f) {
    reason_ = tr("3D view unavailable: %1").arg(QString::fromUtf8(f.GetMessageString()));
    return;
  }
  glReady_ = true;
  if (qEnvironmentVariableIsSet("TSR_VIEW_DEBUG")) {
    int n = 0;
    for (V3d_ListOfLightIterator it(view_->ActiveLightIterator()); it.More(); it.Next(), ++n)
      qInfo("light %d type %d enabled %d headlight %d intensity %f", n, int(it.Value()->Type()),
            int(it.Value()->IsEnabled()), int(it.Value()->Headlight()), it.Value()->Intensity());
    qInfo("lights %d, shading model %d, gl %s", n, int(view_->ShadingModel()),
          gl->Vendor().ToCString());
  }
  if (first) {
    context_->Display(cube_, 0, 0, false);
    rebuild();
    rebuildSketches();
    home();
    if (pendingLook_) {
      lookAt(pendingLook_->frame, pendingLook_->size, pendingLook_->center);
      pendingLook_.reset();
    }
  }
}

void Viewport::paintGL() {
  if (!glReady_) return;
  if (view_->Window()->NativeHandle() != nativeDrawable()) {
    // Qt moved the context to another surface (e.g. the window was re-parented).
    initializeGL();
    return;
  }

  Handle(OpenGl_GraphicDriver) driver = Handle(OpenGl_GraphicDriver)::DownCast(viewer_->Driver());
  const Handle(OpenGl_Context)& gl = driver->GetSharedContext();
  Handle(OpenGl_FrameBuffer) fbo = gl->DefaultFrameBuffer();
  if (fbo.IsNull()) {
    fbo = new QtFrameBuffer();
    gl->SetDefaultFrameBuffer(fbo);
  }
  if (!fbo->InitWrapper(gl)) {
    glReady_ = false;
    reason_ = tr("3D view unavailable: cannot wrap the Qt framebuffer.");
    return;
  }

  Handle(Aspect_NeutralWindow) win = Handle(Aspect_NeutralWindow)::DownCast(view_->Window());
  Graphic3d_Vec2i oldSize;
  win->Size(oldSize.x(), oldSize.y());
  const Graphic3d_Vec2i newSize = fbo->GetVPSize();
  if (newSize != oldSize) {
    win->SetSize(newSize.x(), newSize.y());
    view_->MustBeResized();
    view_->Invalidate();
  }
  view_->InvalidateImmediate();
  FlushViewEvents(context_, view_, true);
  // The camera may have moved: keep the drag arrow's value box beside it.
  if (anyArrow()) QTimer::singleShot(0, this, [this] { placeArrowBoxes(); });
}

void Viewport::paintEvent(QPaintEvent* e) {
  if (!view_.IsNull() && reason_.isEmpty()) {
    QOpenGLWidget::paintEvent(e);
    return;
  }
  // No GL view: plain placeholder so the window is still usable.
  QPainter p(this);
  QLinearGradient bg(0, 0, 0, height());
  bg.setColorAt(0, themeColors().viewTop);
  bg.setColorAt(1, themeColors().viewBottom);
  p.fillRect(rect(), bg);
  p.setPen(themeColors().overlayText);
  p.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap, reason_);
}

void Viewport::handleViewRedraw(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) {
  AIS_ViewController::handleViewRedraw(ctx, view);
  if (adaptiveGrid_) updateGridStep();   // the zoom may have changed
  if (toAskNextFrame()) updateView(); // animation (ViewCube) in progress
}

Aspect_VKeyMouse Viewport::aisButtons(Qt::MouseButtons b) const {
  // While an interactor (sketch editor) is active it owns the left button;
  // in select mode the left button is handled here (clickSelect / boxSelect).
  Aspect_VKeyMouse k = toVKeys((interactor_ || ownsLeftButton()) ? (b & ~Qt::LeftButton) : b);
  if (navPreset_ == NavPreset::Tinkercad && (b & Qt::RightButton)) k |= Aspect_VKeyMouse_RightButton;
  return k;
}

void Viewport::mousePressEvent(QMouseEvent* e) {
  QOpenGLWidget::mousePressEvent(e);
  pressPos_ = e->position();
  if (arrowMousePress(e)) return;
  if (interactor_ && e->button() == Qt::LeftButton) {
    interactor_->mousePress(e);
    return;
  }
  if (e->button() == Qt::LeftButton && ownsLeftButton()) {
    leftDown_ = true;
    boxDrag_ = false;
  }
  if (!glReady_) return;
  if (UpdateMouseButtons(toPixels(e->position()), aisButtons(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::mouseDoubleClickEvent(QMouseEvent* e) {
  if (interactor_ && e->button() == Qt::LeftButton) {
    interactor_->mouseDoubleClick(e);
    return;
  }
  QOpenGLWidget::mouseDoubleClickEvent(e);
}

void Viewport::setCursorHint(const QString& text) {
  cursorHint_ = text;
  if (!pickHint_ || planePicking_) return;
  if (text.isEmpty()) {
    pickHint_->hide();
  } else if (pickHint_->isVisible() && pickHint_->text() != text) {
    pickHint_->setText(text);   // change it in place; it moves with the next mouse move
    pickHint_->adjustSize();
  }
}

bool Viewport::focusNextPrevChild(bool next) {
  if (interactor_) return false;   // keyPressEvent then gets the Tab
  return QOpenGLWidget::focusNextPrevChild(next);
}

void Viewport::leaveEvent(QEvent* e) {
  if (pickHint_) pickHint_->hide();
  clearHoverHighlight();
  QOpenGLWidget::leaveEvent(e);
}

void Viewport::keyPressEvent(QKeyEvent* e) {
  if (interactor_ && interactor_->keyPress(e)) return;
  QOpenGLWidget::keyPressEvent(e);
}

void Viewport::mouseReleaseEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseReleaseEvent(e);
  if (arrowMouseRelease(e)) return;
  if (e->button() == Qt::RightButton && (e->position() - pressPos_).manhattanLength() < 6) {
    emit contextMenuRequested(e->globalPosition().toPoint());
    return;
  }
  if (interactor_ && e->button() == Qt::LeftButton) {
    interactor_->mouseRelease(e);
    return;
  }
  if (e->button() == Qt::LeftButton && leftDown_) {
    leftDown_ = false;
    const bool box = boxDrag_;
    boxDrag_ = false;
    hideSelectionBox();
    if (glReady_) {
      if (box) boxSelect(pressPos_, e->position(), e->modifiers());
      else clickSelect(e->position(), e->modifiers());
    }
    return;
  }
  if (!glReady_) return;
  if (UpdateMouseButtons(toPixels(e->position()), aisButtons(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::mouseMoveEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseMoveEvent(e);
  if (arrowMouseMove(e)) return;
  if (leftDown_ && (e->buttons() & Qt::LeftButton) && ownsLeftButton() &&
      (boxDrag_ || (e->position() - pressPos_).manhattanLength() >= 5)) {
    boxDrag_ = true;
    showSelectionBox(pressPos_, e->position());
  }
  if (!interactor_ && !pickTypes_.empty()) updateHoverHighlight(e->position());
  if (pickHint_) {
    const QString hint = planePicking_ ? tr("Select a plane or planar face") : cursorHint_;
    if (pickHint_->text() != hint) pickHint_->setText(hint);
    pickHint_->setVisible(!hint.isEmpty());
    if (!hint.isEmpty()) {
      pickHint_->adjustSize();
      pickHint_->move(e->position().toPoint() + QPoint(18, 14));
      pickHint_->raise();
    }
  }
  if (interactor_) interactor_->mouseMove(e);
  if (!glReady_) return;
  if (UpdateMousePosition(toPixels(e->position()), aisButtons(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::wheelEvent(QWheelEvent* e) {
  QOpenGLWidget::wheelEvent(e);
  if (!glReady_) return;
  const double delta = (reverseZoom_ ? -1.0 : 1.0) * e->angleDelta().y() / 8.0;
  if (UpdateZoom(Aspect_ScrollDelta(toPixels(e->position()), delta))) updateView();
  // The arrow keeps its size on screen; rebuild once the zoom has applied.
  if (anyArrow()) QTimer::singleShot(0, this, [this] { rebuildArrows(); });
}

void Viewport::OnSelectionChanged(const Handle(AIS_InteractiveContext)&, const Handle(V3d_View)&) {
  if (handlePickSelection()) return;
  const QStringList sel = selectedBodies();
  if (sel.size() == 1) emit bodyClicked(sel.first());
  emit selectionChanged();
}

QStringList Viewport::selectedBodies() const {
  QStringList out;
  if (context_.IsNull()) return out;
  for (context_->InitSelected(); context_->MoreSelected(); context_->NextSelected()) {
    const Handle(AIS_InteractiveObject) obj = context_->SelectedInteractive();
    for (const auto& [name, shape] : shapes_)
      if (shape == obj) out << QString::fromStdString(name);
  }
  return out;
}

namespace {
// The window / crossing box drawn over the canvas.
class SelectionBox : public QWidget {
public:
  explicit SelectionBox(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setObjectName(QStringLiteral("selectionBox"));
  }
  bool crossing = false;

protected:
  void paintEvent(QPaintEvent*) override {
    QPainter p(this);
    const QColor c = crossing ? QColor(60, 176, 67) : QColor(47, 143, 232);
    QColor fill = c;
    fill.setAlpha(40);
    p.fillRect(rect(), fill);
    QPen pen(c, 1, crossing ? Qt::DashLine : Qt::SolidLine);
    p.setPen(pen);
    p.drawRect(rect().adjusted(0, 0, -1, -1));
  }
};
} // namespace

void Viewport::showSelectionBox(const QPointF& from, const QPointF& to) {
  auto* box = static_cast<SelectionBox*>(selectionBox_);
  if (!box) selectionBox_ = box = new SelectionBox(this);
  box->crossing = to.x() < from.x();
  box->setGeometry(QRectF(from, to).normalized().toAlignedRect());
  box->show();
  box->raise();
  box->update();
}

void Viewport::hideSelectionBox() {
  if (selectionBox_) selectionBox_->hide();
}

void Viewport::clickSelect(const QPointF& pos, Qt::KeyboardModifiers mods) {
  const Graphic3d_Vec2i p = toPixels(pos);
  context_->MoveTo(p.x(), p.y(), view_, false);
  context_->SelectDetected((mods & (Qt::ShiftModifier | Qt::ControlModifier)) ? AIS_SelectionScheme_XOR
                                                                               : AIS_SelectionScheme_Replace);
  OnSelectionChanged(context_, view_);
  updateView();
}

void Viewport::boxSelect(const QPointF& from, const QPointF& to, Qt::KeyboardModifiers mods) {
  const Graphic3d_Vec2i a = toPixels(from), b = toPixels(to);
  const AIS_SelectionScheme scheme = (mods & Qt::ShiftModifier)     ? AIS_SelectionScheme_Add
                                     : (mods & Qt::ControlModifier) ? AIS_SelectionScheme_Remove
                                                                    : AIS_SelectionScheme_Replace;
  // Right to left: a crossing box (anything touched); else wholly inside.
  context_->MainSelector()->AllowOverlapDetection(to.x() < from.x());
  context_->SelectRectangle(Graphic3d_Vec2i(std::min(a.x(), b.x()), std::min(a.y(), b.y())),
                            Graphic3d_Vec2i(std::max(a.x(), b.x()), std::max(a.y(), b.y())), view_, scheme);
  context_->MainSelector()->AllowOverlapDetection(false);
  // While a command picks profiles, faces or edges, each one boxed is
  // reported as a pick (adding to the command's selection).
  std::vector<std::pair<QString, int>> profiles;
  std::vector<std::pair<QString, TopoDS_Shape>> subs;
  for (context_->InitSelected(); context_->MoreSelected(); context_->NextSelected()) {
    const Handle(AIS_InteractiveObject) obj = context_->SelectedInteractive();
    bool isProfile = false;
    for (const auto& pr : profileObjects_)
      if (pr.shape == obj) {
        profiles.emplace_back(QString::fromStdString(pr.sketch), pr.index);
        isProfile = true;
      }
    if (isProfile || pickTypes_.empty() || planePicking_) continue;
    const Handle(StdSelect_BRepOwner) brep = Handle(StdSelect_BRepOwner)::DownCast(context_->SelectedOwner());
    if (brep.IsNull() || !brep->HasShape()) continue;
    for (const auto& [name, shape] : shapes_)
      if (shape == obj) subs.emplace_back(QString::fromStdString(name), brep->Shape());
  }
  if (!profiles.empty() || !subs.empty() || !pickTypes_.empty() || planePicking_) {
    context_->ClearSelected(false);
    // No command and no Shift / Ctrl: the box replaces what was selected.
    if (pickTypes_.empty() && !planePicking_ && scheme == AIS_SelectionScheme_Replace) emit selectionChanged();
    boxPicking_ = true;
    for (const auto& [sketch, index] : profiles) emit profileClicked(sketch, index);
    for (const auto& [body, shape] : subs) emit subShapeClicked(body, shape);
    boxPicking_ = false;
  } else {
    const QStringList sel = selectedBodies();
    if (sel.size() == 1) emit bodyClicked(sel.first());
    emit selectionChanged();
  }
  updateView();
}

std::vector<std::pair<QString, TopoDS_Shape>> Viewport::selectedSubShapes() const {
  std::vector<std::pair<QString, TopoDS_Shape>> out;
  if (context_.IsNull()) return out;
  for (context_->InitSelected(); context_->MoreSelected(); context_->NextSelected()) {
    const Handle(StdSelect_BRepOwner) brep = Handle(StdSelect_BRepOwner)::DownCast(context_->SelectedOwner());
    if (brep.IsNull() || !brep->HasShape()) continue;
    const TopAbs_ShapeEnum t = brep->Shape().ShapeType();
    if (t != TopAbs_FACE && t != TopAbs_EDGE && t != TopAbs_VERTEX) continue;
    const Handle(AIS_InteractiveObject) obj = context_->SelectedInteractive();
    for (const auto& [name, shape] : shapes_)
      if (shape == obj) out.emplace_back(QString::fromStdString(name), brep->Shape());
  }
  return out;
}

void Viewport::clearSelection() {
  if (context_.IsNull()) return;
  context_->ClearSelected(false);
  redrawAll();
}

void Viewport::setBodies(const std::vector<doc::Body>& bodies) {
  bodies_ = bodies;
  if (glReady_) rebuild();
}

void Viewport::applyStyle(const Handle(AIS_Shape)& s) {
  const Handle(Prs3d_Drawer)& d = s->Attributes();
  d->SetFaceBoundaryDraw(style_ == Style::ShadedEdges);
  d->SetFaceBoundaryUpperContinuity(GeomAbs_C0); // sharp edges only, no seams on round faces
  d->SetFaceBoundaryAspect(new Prs3d_LineAspect(qc(themeColors().edges), Aspect_TOL_SOLID, 1.0));
  context_->SetDisplayMode(s, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, false);
}

void Viewport::setBodyOverrides(const std::map<std::string, TopoDS_Shape>& shapes) {
  overrides_ = shapes;
  if (!context_.IsNull()) rebuild();
}

void Viewport::rebuild() {
  // Keep selection by name across rebuilds.
  const QStringList selected = selectedBodies();
  for (auto& [name, shape] : shapes_) context_->Remove(shape, false);
  shapes_.clear();

  for (const auto& b : bodies_) {
    const auto ov = overrides_.find(b.name);
    Handle(AIS_Shape) s = new AIS_Shape(ov != overrides_.end() ? ov->second : b.shape);
    s->SetMaterial(bodyMaterial());
    if (ghosted_) s->SetTransparency(0.78);
    if (sectionOn_ && !clip_.IsNull()) s->AddClipPlane(clip_);
    applyStyle(s);
    shapes_[b.name] = s;
    // Under a surface analysis the coloured meshes stand in for the bodies.
    if (!hidden_[b.name] && analysis_.kind == AnalysisKind::None) {
      context_->Display(s, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, 0, false);
      if (selected.contains(QString::fromStdString(b.name))) context_->AddOrRemoveSelected(s, false);
    }
  }
  buildAnalysis();
  applyPickModes();
  if (!fittedOnce_ && !bodies_.empty()) {
    fittedOnce_ = true;
    fitAll();
  }
  redrawAll();
}

void Viewport::setBodyVisible(const QString& name, bool visible) {
  const std::string n = name.toStdString();
  hidden_[n] = !visible;
  auto it = shapes_.find(n);
  if (it == shapes_.end() || context_.IsNull()) return;
  if (visible) context_->Display(it->second, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, 0, false);
  else context_->Erase(it->second, false);
  redrawAll();
}

bool Viewport::isBodyVisible(const QString& name) const {
  auto it = hidden_.find(name.toStdString());
  return it == hidden_.end() || !it->second;
}

void Viewport::fitAll() {
  if (view_.IsNull()) return;
  bool any = false;
  for (const auto& [name, shape] : shapes_) any = any || context_->IsDisplayed(shape);
  if (any) {
    view_->FitAll(0.15, false); // objects with transform persistence (ViewCube) are ignored
    view_->ZFitAll();
  } else {
    view_->SetSize(30.0); // empty design: show about 300 mm of the grid
  }
  redrawAll();
}

void Viewport::home() {
  if (view_.IsNull()) return;
  AbortViewAnimation();
  view_->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
  fitAll();
}

void Viewport::viewFrom(V3d_TypeOfOrientation o) {
  if (view_.IsNull()) return;
  AbortViewAnimation();
  view_->SetProj(o);
  fitAll();
}

void Viewport::setStyle(Style s) {
  style_ = s;
  if (glReady_) rebuild();
}

void Viewport::setBodiesGhosted(bool on) {
  if (ghosted_ == on) return;
  ghosted_ = on;
  if (glReady_) rebuild();
}

void Viewport::applyTheme() {
  if (view_.IsNull()) {
    update();
    return;
  }
  const auto& c = themeColors();
  view_->SetBgGradientColors(qc(c.viewTop), qc(c.viewBottom), Aspect_GradientFillMethod_Vertical);
  viewer_->Grid()->SetColors(qc(c.grid), qc(c.gridMajor));
  cube_->SetBoxColor(qc(c.cubeBox));
  cube_->SetTextColor(qc(c.cubeText));
  cube_->SetInnerColor(qc(c.cubeText));
  if (!context_.IsNull() && context_->IsDisplayed(cube_)) context_->Redisplay(cube_, false);
  view_->TriedronErase();
  view_->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, qc(c.overlayText), 0.08, V3d_ZBUFFER);
  redrawAll();
}

void Viewport::setGridVisible(bool visible) {
  grid_ = visible;
  if (viewer_.IsNull()) return;
  if (visible) viewer_->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
  else viewer_->DeactivateGrid();
  redrawAll();
}

} // namespace tsr::app
