// Viewport: sketches, profiles, plane picking and the sketch-editor hooks.
#include "Viewport.h"
#include "Theme.h"

#include <AIS_Point.hxx>
#include <AIS_TextLabel.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Prs3d_PointAspect.hxx>
#include <Graphic3d_Camera.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <TopoDS.hxx>
#include <gp_Pln.hxx>

#include <QMouseEvent>

#include <algorithm>

namespace tsr::app {

namespace {
Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }

void lineStyle(const Handle(AIS_Shape)& s, const Quantity_Color& c, double width, Aspect_TypeOfLine type) {
  s->SetColor(c);
  s->SetWidth(width);
  s->Attributes()->SetWireAspect(new Prs3d_LineAspect(c, type, width));
  s->Attributes()->SetLineAspect(new Prs3d_LineAspect(c, type, width));
}

void faceStyle(const Handle(AIS_Shape)& s, const Quantity_Color& c, double transparency) {
  Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
  m.SetDiffuseColor(c);
  m.SetAmbientColor(c);
  m.SetSpecularColor(Quantity_Color(Quantity_NOC_BLACK));
  m.SetEmissiveColor(Quantity_Color(c.Rgb() * 0.3f));
  s->SetMaterial(m);
  s->SetTransparency(transparency);
  s->Attributes()->SetFaceBoundaryDraw(false);
}
} // namespace

void Viewport::setInteractor(ViewInteractor* interactor) {
  interactor_ = interactor;
  if (interactor_ && !context_.IsNull()) context_->ClearSelected(false);
  redrawAll();
}

bool Viewport::planePoint(const QPointF& pos, const gp_Ax3& frame, gp_Pnt& out) const {
  if (view_.IsNull()) return false;
  const Graphic3d_Vec2i px = toPixels(pos);
  Standard_Real x, y, z, vx, vy, vz;
  view_->ConvertWithProj(px.x(), px.y(), x, y, z, vx, vy, vz);
  const gp_Pnt p(x, y, z);
  const gp_Vec d(vx, vy, vz);
  const gp_Vec n(frame.Direction());
  const double denom = d.Dot(n);
  if (std::abs(denom) < 1e-12) return false;
  const double t = gp_Vec(p, frame.Location()).Dot(n) / denom;
  out = p.Translated(d * t);
  return true;
}

QPointF Viewport::toWidget(const gp_Pnt& p) const {
  if (view_.IsNull()) return QPointF(width() / 2.0, height() / 2.0);
  Standard_Integer x = 0, y = 0;
  view_->Convert(p.X(), p.Y(), p.Z(), x, y);
  const qreal r = devicePixelRatioF();
  return QPointF(x / r, y / r);
}

double Viewport::modelPerPixel() const {
  if (view_.IsNull()) return 0.01;
  return view_->Convert(100) / 100.0 * devicePixelRatioF();
}

void Viewport::lookAt(const gp_Ax3& frame, double size, std::optional<gp_Pnt> center) {
  if (view_.IsNull()) return;
  if (!glReady_) {
    pendingLook_ = PendingLook{frame, size, center};
    return;
  }
  AbortViewAnimation();
  // Look straight at the plane: eye on its normal, sketch Y up.
  const Handle(Graphic3d_Camera)& cam = view_->Camera();
  const gp_Pnt c = center.value_or(frame.Location());
  const double dist = std::max(cam->Distance(), 1.0);
  cam->SetEyeAndCenter(c.Translated(gp_Vec(frame.Direction()) * dist), c);
  cam->SetUp(frame.YDirection());
  if (size > 0) view_->SetSize(size);
  view_->ZFitAll();
  redrawAll();
}

void Viewport::setGridPlane(const gp_Ax3& frame) {
  if (viewer_.IsNull()) return;
  viewer_->SetPrivilegedPlane(frame);
  if (grid_) viewer_->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
  redrawAll();
}

// ---------------------------------------------------------------------------
void Viewport::setSketches(std::vector<SketchDisplay> sketches) {
  sketches_ = std::move(sketches);
  if (glReady_) rebuildSketches();
}

void Viewport::rebuildSketches() {
  if (context_.IsNull()) return;
  for (auto& s : sketchCurves_) context_->Remove(s, false);
  for (auto& p : profileObjects_) context_->Remove(p.shape, false);
  sketchCurves_.clear();
  profileObjects_.clear();

  for (const auto& sk : sketches_) {
    if (!sk.visible) continue;
    if (!sk.curves.IsNull()) {
      Handle(AIS_Shape) c = new AIS_Shape(sk.curves);
      const QColor sc = themeColors().sketchFinished;
      lineStyle(c, rgb(sc.red(), sc.green(), sc.blue()), 2.0, Aspect_TOL_SOLID);
      context_->Display(c, AIS_WireFrame, -1, false);
      sketchCurves_.push_back(c);
    }
    if (!sk.construction.IsNull()) {
      Handle(AIS_Shape) c = new AIS_Shape(sk.construction);
      lineStyle(c, rgb(230, 130, 40), 1.2, Aspect_TOL_DASH);
      context_->Display(c, AIS_WireFrame, -1, false);
      sketchCurves_.push_back(c);
    }
    for (int i = 0; i < static_cast<int>(sk.profiles.size()); ++i) {
      Handle(AIS_Shape) f = new AIS_Shape(sk.profiles[i].face);
      const bool picked = sk.name == pickedSketch_ &&
                          std::find(pickedProfiles_.begin(), pickedProfiles_.end(), i) != pickedProfiles_.end();
      faceStyle(f, picked ? rgb(40, 120, 230) : rgb(150, 190, 240), picked ? 0.35 : (profilePicking_ ? 0.6 : 0.82));
      context_->Display(f, AIS_Shaded, 0, false);
      profileObjects_.push_back({f, sk.name, i});
    }
  }
  applyPickModes();
  redrawAll();
}

void Viewport::setProfilePicking(bool on) {
  if (profilePicking_ == on) return;
  profilePicking_ = on;
  if (!on) {
    pickedSketch_.clear();
    pickedProfiles_.clear();
  }
  if (glReady_) rebuildSketches();
}

void Viewport::setPickedProfiles(const std::string& sketch, const std::vector<int>& indices) {
  pickedSketch_ = sketch;
  pickedProfiles_ = indices;
  if (glReady_) rebuildSketches();
}

void Viewport::setConstructionPlanes(const std::vector<std::pair<std::string, gp_Ax3>>& planes) {
  constructionPlanes_ = planes;
  rebuildConstruction();
}

void Viewport::setConstructionAxesPoints(const std::vector<std::pair<std::string, gp_Ax1>>& axes,
                                         const std::vector<std::pair<std::string, gp_Pnt>>& points) {
  constructionAxes_ = axes;
  constructionPoints_ = points;
  rebuildConstruction();
}

void Viewport::rebuildConstruction() {
  if (context_.IsNull()) return;
  for (auto& [o, n] : constructionObjects_) context_->Remove(o, false);
  constructionObjects_.clear();
  Standard_Real vw = 10, vh = 10;
  if (!view_.IsNull()) view_->Size(vw, vh);
  const double half = std::max(2.0, std::min(vw, vh) * 0.22);
  for (const auto& [name, frame] : constructionPlanes_) {
    const TopoDS_Face face = BRepBuilderAPI_MakeFace(gp_Pln(frame), -half, half, -half, half).Face();
    Handle(AIS_Shape) s = new AIS_Shape(face);
    faceStyle(s, rgb(240, 160, 60), 0.75);
    s->Attributes()->SetFaceBoundaryDraw(true);
    s->Attributes()->SetFaceBoundaryAspect(new Prs3d_LineAspect(rgb(240, 160, 60), Aspect_TOL_SOLID, 1.5));
    context_->Display(s, AIS_Shaded, 0, false);
    if (!planePicking_) context_->Deactivate(s);
    constructionObjects_.emplace_back(s, name);
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(TCollection_ExtendedString(name.c_str()));
    t->SetPosition(frame.Location().Translated(gp_Vec(frame.XDirection()) * half + gp_Vec(frame.YDirection()) * half));
    t->SetHeight(12);
    t->SetColor(rgb(240, 170, 80));
    context_->Display(t, 0, -1, false);
    constructionObjects_.emplace_back(t, std::string());
  }
  const Quantity_Color orange = rgb(240, 160, 60);
  auto label = [&](const std::string& name, const gp_Pnt& at) {
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(TCollection_ExtendedString(name.c_str()));
    t->SetPosition(at);
    t->SetHeight(12);
    t->SetColor(rgb(240, 170, 80));
    context_->Display(t, 0, -1, false);
    constructionObjects_.emplace_back(t, std::string());
  };
  // Axes: long dashed lines through their origin.
  const double reach = half * 2.5;
  for (const auto& [name, ax] : constructionAxes_) {
    const gp_Vec d(ax.Direction());
    const gp_Pnt a = ax.Location().Translated(-d * reach), b = ax.Location().Translated(d * reach);
    Handle(AIS_Shape) l = new AIS_Shape(BRepBuilderAPI_MakeEdge(a, b).Shape());
    lineStyle(l, orange, 2.0, Aspect_TOL_DASH);
    context_->Display(l, AIS_WireFrame, -1, false);
    constructionObjects_.emplace_back(l, std::string());
    label(name, b);
  }
  // Points: small rings, drawn over the bodies.
  for (const auto& [name, p] : constructionPoints_) {
    Handle(AIS_Point) pt = new AIS_Point(new Geom_CartesianPoint(p));
    pt->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_O_POINT, orange, 2.5));
    context_->Display(pt, 0, -1, false);
    context_->SetZLayer(pt, Graphic3d_ZLayerId_Topmost);
    constructionObjects_.emplace_back(pt, std::string());
    label(name, p.Translated(gp_Vec(0, 0, modelPerPixel() * 12)));
  }
  redrawAll();
}

void Viewport::setPlanePicking(bool on) {
  planePicking_ = on;
  if (context_.IsNull()) return;
  for (auto& [shape, spec] : planeObjects_) context_->Remove(shape, false);
  planeObjects_.clear();
  if (on) {
    // Origin planes as small translucent squares in the positive quadrants
    // (sized to the view), the origin axes and the origin point. The plane
    // under the cursor lights up before it is clicked.
    Standard_Real vw = 10, vh = 10;
    if (!view_.IsNull()) view_->Size(vw, vh);
    const double size = std::max(1.0, std::min(vw, vh) * 0.2);
    const double gap = size * 0.08;
    const Quantity_Color beige = rgb(226, 170, 140);
    Handle(Prs3d_Drawer) hover = new Prs3d_Drawer();
    hover->SetColor(rgb(235, 235, 235));
    hover->SetTransparency(0.15f);
    hover->SetDisplayMode(AIS_Shaded);
    hover->SetZLayer(Graphic3d_ZLayerId_Top);
    for (const char* spec : {"XY", "XZ", "YZ"}) {
      const gp_Ax3 frame = sketch::planeFrame(spec);
      // XZ's sketch Y is world Z and its X is world X; YZ's are world Y/Z.
      const TopoDS_Face face = BRepBuilderAPI_MakeFace(gp_Pln(frame), gap, gap + size, gap, gap + size).Face();
      Handle(AIS_Shape) s = new AIS_Shape(face);
      faceStyle(s, beige, 0.5);
      s->Attributes()->SetFaceBoundaryDraw(true);
      s->Attributes()->SetFaceBoundaryAspect(new Prs3d_LineAspect(rgb(200, 140, 110), Aspect_TOL_SOLID, 1.0));
      s->SetDynamicHilightAttributes(hover);
      context_->Display(s, AIS_Shaded, 0, false);
      planeObjects_.emplace_back(s, spec);
    }
    const struct { gp_Dir d; Quantity_Color c; } axes[] = {
        {gp::DX(), rgb(220, 60, 60)}, {gp::DY(), rgb(70, 200, 80)}, {gp::DZ(), rgb(60, 110, 235)}};
    for (const auto& a : axes) {
      Handle(AIS_Shape) l = new AIS_Shape(BRepBuilderAPI_MakeEdge(gp::Origin(), gp::Origin().Translated(gp_Vec(a.d) * size * 1.25)).Shape());
      lineStyle(l, a.c, 3.0, Aspect_TOL_SOLID);
      context_->Display(l, AIS_WireFrame, -1, false);
      planeObjects_.emplace_back(l, std::string());
    }
    Handle(AIS_Point) origin = new AIS_Point(new Geom_CartesianPoint(gp::Origin()));
    origin->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_BALL, rgb(240, 240, 240), 2.5));
    context_->Display(origin, 0, -1, false);
    context_->SetZLayer(origin, Graphic3d_ZLayerId_Topmost);
    planeObjects_.emplace_back(origin, std::string());
  }
  for (auto& [o, n] : constructionObjects_) {
    if (n.empty()) continue;
    context_->Deactivate(o);
    if (on) context_->Activate(o, 0);
  }
  applyPickModes();
  redrawAll();
}

void Viewport::setSubShapePicking(const std::vector<TopAbs_ShapeEnum>& types) {
  if (pickTypes_ == types) return;
  pickTypes_ = types;
  if (types.empty()) setPickedShapes({});
  applyPickModes();
}

void Viewport::setPickedShapes(const std::vector<TopoDS_Shape>& shapes) {
  if (context_.IsNull()) return;
  for (auto& e : pickedObjects_) context_->Remove(e, false);
  pickedObjects_.clear();
  for (const auto& s : shapes) {
    if (s.IsNull()) continue;
    Handle(AIS_Shape) a = new AIS_Shape(s);
    const Quantity_Color blue = rgb(0, 160, 255);
    if (s.ShapeType() == TopAbs_FACE) {
      faceStyle(a, blue, 0.45);
      context_->Display(a, AIS_Shaded, -1, false);
    } else {
      lineStyle(a, blue, 4.0, Aspect_TOL_SOLID);
      a->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_BALL, blue, 3.0));
      context_->Display(a, AIS_WireFrame, -1, false);
      context_->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
    }
    pickedObjects_.push_back(a);
  }
  redrawAll();
}

void Viewport::setSection(bool on, const gp_Pln& plane) {
  sectionOn_ = on;
  if (on) {
    if (clip_.IsNull()) {
      clip_ = new Graphic3d_ClipPlane();
      clip_->SetCapping(true);
      clip_->SetCappingHatch(Aspect_HS_DIAGONAL_45);
      clip_->SetCappingHatchOn();
      clip_->SetUseObjectMaterial(false);
      Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
      m.SetDiffuseColor(rgb(214, 96, 70));
      m.SetAmbientColor(rgb(214, 96, 70));
      clip_->SetCappingMaterial(m);
    }
    // Graphic3d clips away the side the plane normal points to.
    clip_->SetEquation(plane);
    clip_->SetOn(true);
  }
  if (glReady_) rebuild();
}

void Viewport::setMeasureLine(bool on, const gp_Pnt& from, const gp_Pnt& to, const QString& label) {
  if (context_.IsNull()) return;
  for (auto& o : measureObjects_) context_->Remove(o, false);
  measureObjects_.clear();
  if (on && from.Distance(to) > 1e-9) {
    Handle(AIS_Shape) l = new AIS_Shape(BRepBuilderAPI_MakeEdge(from, to).Shape());
    lineStyle(l, rgb(255, 200, 40), 2.5, Aspect_TOL_DASH);
    context_->Display(l, AIS_WireFrame, -1, false);
    context_->SetZLayer(l, Graphic3d_ZLayerId_Topmost);
    measureObjects_.push_back(l);
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(TCollection_ExtendedString(label.toUtf8().constData(), true));
    t->SetPosition(gp_Pnt((from.XYZ() + to.XYZ()) / 2));
    t->SetHeight(15);
    t->SetColor(rgb(255, 214, 90));
    context_->Display(t, 0, -1, false);
    context_->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
    measureObjects_.push_back(t);
  }
  redrawAll();
}

void Viewport::setMarker(bool on, const gp_Pnt& at, const QString& label) {
  if (context_.IsNull()) return;
  for (auto& o : markerObjects_) context_->Remove(o, false);
  markerObjects_.clear();
  if (on) {
    Handle(AIS_Point) p = new AIS_Point(new Geom_CartesianPoint(at));
    p->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_RING3, rgb(255, 200, 40), 3.0));
    context_->Display(p, 0, -1, false);
    context_->SetZLayer(p, Graphic3d_ZLayerId_Topmost);
    markerObjects_.push_back(p);
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(TCollection_ExtendedString(label.toUtf8().constData(), true));
    t->SetPosition(at);
    t->SetHeight(14);
    t->SetColor(rgb(255, 214, 90));
    context_->Display(t, 0, -1, false);
    context_->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
    markerObjects_.push_back(t);
  }
  redrawAll();
}

TopoDS_Shape Viewport::bodyShape(const QString& name) const {
  for (const auto& b : bodies_)
    if (b.name == name.toStdString()) return b.shape;
  return {};
}

void Viewport::applyPickModes() {
  if (context_.IsNull()) return;
  const int faceMode = AIS_Shape::SelectionMode(TopAbs_FACE);
  for (const auto& [name, shape] : shapes_) {
    if (!context_->IsDisplayed(shape)) continue;
    context_->Deactivate(shape);
    if (planePicking_) context_->Activate(shape, faceMode);
    else if (!pickTypes_.empty())
      for (TopAbs_ShapeEnum t : pickTypes_) context_->Activate(shape, AIS_Shape::SelectionMode(t));
    else if (!selectFilter_.empty())
      for (TopAbs_ShapeEnum t : selectFilter_) context_->Activate(shape, AIS_Shape::SelectionMode(t));
    else context_->Activate(shape, 0);
  }
  for (auto& s : sketchCurves_) context_->Deactivate(s);
  for (auto& p : profileObjects_) {
    context_->Deactivate(p.shape);
    if (profilePicking_) context_->Activate(p.shape, 0);
  }
}

bool Viewport::handlePickSelection() {
  if (context_.IsNull()) return false;
  context_->InitSelected();
  if (!context_->MoreSelected()) return false;
  const Handle(AIS_InteractiveObject) obj = context_->SelectedInteractive();
  const Handle(SelectMgr_EntityOwner) owner = context_->SelectedOwner();

  for (const auto& p : profileObjects_)
    if (p.shape == obj) {
      context_->ClearSelected(false);
      emit profileClicked(QString::fromStdString(p.sketch), p.index);
      return true;
    }
  if (!pickTypes_.empty() && !planePicking_) {
    const Handle(StdSelect_BRepOwner) brep = Handle(StdSelect_BRepOwner)::DownCast(owner);
    if (!brep.IsNull() && brep->HasShape()) {
      for (const auto& [name, shape] : shapes_)
        if (shape == obj) {
          const TopoDS_Shape picked = brep->Shape();
          context_->ClearSelected(false);
          emit subShapeClicked(QString::fromStdString(name), picked);
          return true;
        }
    }
  }
  if (!planePicking_) return false;
  for (const auto& [o, name] : constructionObjects_)
    if (o == obj && !name.empty()) {
      context_->ClearSelected(false);
      emit planePicked(QString::fromStdString(name), QString::fromStdString(name));
      return true;
    }
  for (const auto& [shape, spec] : planeObjects_)
    if (shape == obj && !spec.empty()) {
      context_->ClearSelected(false);
      emit planePicked(QString::fromStdString(spec), tr("%1 plane").arg(QString::fromStdString(spec)));
      return true;
    }
  // A flat face of a body.
  const Handle(StdSelect_BRepOwner) brep = Handle(StdSelect_BRepOwner)::DownCast(owner);
  if (!brep.IsNull() && brep->Shape().ShapeType() == TopAbs_FACE) {
    const TopoDS_Face face = TopoDS::Face(brep->Shape());
    BRepAdaptor_Surface surf(face, true);
    context_->ClearSelected(false);
    if (surf.GetType() != GeomAbs_Plane) {
      emit statusMessage(tr("That face is not flat; pick a flat face or an origin plane."));
      return true;
    }
    gp_Pln pln = surf.Plane();
    gp_Ax3 frame = pln.Position();
    // Outward normal: follow the face orientation.
    if (face.Orientation() == TopAbs_REVERSED) frame = gp_Ax3(frame.Location(), frame.Direction().Reversed(), frame.XDirection());
    // Put the sketch origin on the plane where the world origin projects.
    const gp_Pnt o(0, 0, 0);
    const gp_Vec d(frame.Location(), o);
    const gp_Pnt proj = o.Translated(-gp_Vec(frame.Direction()) * d.Dot(gp_Vec(frame.Direction())));
    frame.SetLocation(proj);
    emit planePicked(QString::fromStdString(sketch::customPlaneSpec(frame)), tr("face"));
    return true;
  }
  return false;
}

} // namespace tsr::app
