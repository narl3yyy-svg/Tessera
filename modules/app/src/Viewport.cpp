#include "Viewport.h"

#include <AIS_AnimationCamera.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Grid.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Graphic3d_TransformPers.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Standard_Failure.hxx>
#include <StdSelect_BRepOwner.hxx>

#include <QGuiApplication>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QPainter>
#include <QSurfaceFormat>
#include <QWheelEvent>

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
    viewer_->Grid()->SetColors(rgb(205, 211, 218), rgb(160, 168, 178));

    context_ = new AIS_InteractiveContext(viewer_);
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
    view_->SetBgGradientColors(rgb(250, 251, 253), rgb(196, 206, 218), Aspect_GradientFillMethod_Vertical);
    view_->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GRAY40, 0.08, V3d_ZBUFFER);
    view_->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);

    cube_ = new AIS_ViewCube();
    cube_->SetSize(55);
    cube_->SetBoxColor(rgb(236, 239, 243));
    cube_->SetTextColor(rgb(60, 66, 74));
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

  // Mouse bindings (gesture = what a drag does, scheme = what a click selects).
  AIS_MouseGestureMap& g = ChangeMouseGestureMap();
  g.Clear();
  g.Bind(Aspect_VKeyMouse_MiddleButton, AIS_MouseGesture_Pan);
  g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_SHIFT), AIS_MouseGesture_RotateOrbit);
  g.Bind(keys(Aspect_VKeyMouse_MiddleButton, Aspect_VKeyFlags_CTRL), AIS_MouseGesture_Zoom);
  bindLeftButton();
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
    home();
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
}

void Viewport::paintEvent(QPaintEvent* e) {
  if (!view_.IsNull() && reason_.isEmpty()) {
    QOpenGLWidget::paintEvent(e);
    return;
  }
  // No GL view: plain placeholder so the window is still usable.
  QPainter p(this);
  QLinearGradient bg(0, 0, 0, height());
  bg.setColorAt(0, QColor(250, 251, 253));
  bg.setColorAt(1, QColor(196, 206, 218));
  p.fillRect(rect(), bg);
  p.setPen(QColor(90, 98, 110));
  p.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap, reason_);
}

void Viewport::handleViewRedraw(const Handle(AIS_InteractiveContext)& ctx, const Handle(V3d_View)& view) {
  AIS_ViewController::handleViewRedraw(ctx, view);
  if (toAskNextFrame()) updateView(); // animation (ViewCube) in progress
}

void Viewport::mousePressEvent(QMouseEvent* e) {
  QOpenGLWidget::mousePressEvent(e);
  pressPos_ = e->position();
  if (!glReady_) return;
  if (UpdateMouseButtons(toPixels(e->position()), toVKeys(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::mouseReleaseEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseReleaseEvent(e);
  if (e->button() == Qt::RightButton && (e->position() - pressPos_).manhattanLength() < 6) {
    emit contextMenuRequested(e->globalPosition().toPoint());
    return;
  }
  if (!glReady_) return;
  if (UpdateMouseButtons(toPixels(e->position()), toVKeys(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::mouseMoveEvent(QMouseEvent* e) {
  QOpenGLWidget::mouseMoveEvent(e);
  if (!glReady_) return;
  if (UpdateMousePosition(toPixels(e->position()), toVKeys(e->buttons()), toVKeys(e->modifiers()), false))
    updateView();
}

void Viewport::wheelEvent(QWheelEvent* e) {
  QOpenGLWidget::wheelEvent(e);
  if (!glReady_) return;
  if (UpdateZoom(Aspect_ScrollDelta(toPixels(e->position()), e->angleDelta().y() / 8.0))) updateView();
}

void Viewport::OnSelectionChanged(const Handle(AIS_InteractiveContext)&, const Handle(V3d_View)&) {
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

void Viewport::clearSelection() {
  if (context_.IsNull()) return;
  context_->ClearSelected(false);
  updateView();
}

void Viewport::setBodies(const std::vector<doc::Body>& bodies) {
  bodies_ = bodies;
  if (glReady_) rebuild();
}

void Viewport::applyStyle(const Handle(AIS_Shape)& s) {
  const Handle(Prs3d_Drawer)& d = s->Attributes();
  d->SetFaceBoundaryDraw(style_ == Style::ShadedEdges);
  d->SetFaceBoundaryUpperContinuity(GeomAbs_C0); // sharp edges only, no seams on round faces
  d->SetFaceBoundaryAspect(new Prs3d_LineAspect(rgb(30, 34, 40), Aspect_TOL_SOLID, 1.0));
  context_->SetDisplayMode(s, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, false);
}

void Viewport::rebuild() {
  // Keep selection by name across rebuilds.
  const QStringList selected = selectedBodies();
  for (auto& [name, shape] : shapes_) context_->Remove(shape, false);
  shapes_.clear();

  for (const auto& b : bodies_) {
    Handle(AIS_Shape) s = new AIS_Shape(b.shape);
    s->SetMaterial(bodyMaterial());
    applyStyle(s);
    shapes_[b.name] = s;
    if (!hidden_[b.name]) {
      context_->Display(s, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, 0, false);
      if (selected.contains(QString::fromStdString(b.name))) context_->AddOrRemoveSelected(s, false);
    }
  }
  if (!fittedOnce_ && !bodies_.empty()) {
    fittedOnce_ = true;
    fitAll();
  }
  updateView();
}

void Viewport::setBodyVisible(const QString& name, bool visible) {
  const std::string n = name.toStdString();
  hidden_[n] = !visible;
  auto it = shapes_.find(n);
  if (it == shapes_.end() || context_.IsNull()) return;
  if (visible) context_->Display(it->second, style_ == Style::Wireframe ? AIS_WireFrame : AIS_Shaded, 0, false);
  else context_->Erase(it->second, false);
  updateView();
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
  updateView();
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

void Viewport::setGridVisible(bool visible) {
  grid_ = visible;
  if (viewer_.IsNull()) return;
  if (visible) viewer_->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
  else viewer_->DeactivateGrid();
  updateView();
}

} // namespace tsr::app
