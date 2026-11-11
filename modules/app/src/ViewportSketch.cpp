// Viewport: sketches, profiles, plane picking and the sketch-editor hooks.
#include "Viewport.h"

#include <BRepAdaptor_Surface.hxx>
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
  updateView();
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
      lineStyle(c, rgb(40, 70, 120), 2.0, Aspect_TOL_SOLID);
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
  updateView();
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

void Viewport::setPlanePicking(bool on) {
  planePicking_ = on;
  if (context_.IsNull()) return;
  for (auto& [shape, spec] : planeObjects_) context_->Remove(shape, false);
  planeObjects_.clear();
  if (on) {
    // Origin planes as translucent squares, sized to the current view.
    Standard_Real vw = 10, vh = 10;
    if (!view_.IsNull()) view_->Size(vw, vh);
    const double half = std::max(2.0, std::min(vw, vh) * 0.3);
    struct P {
      const char* spec;
      gp_Ax3 frame;
      Quantity_Color color;
    };
    const P planes[] = {
        {"XY", sketch::planeFrame("XY"), rgb(90, 140, 220)},
        {"XZ", sketch::planeFrame("XZ"), rgb(90, 190, 120)},
        {"YZ", sketch::planeFrame("YZ"), rgb(220, 110, 90)},
    };
    for (const auto& p : planes) {
      const TopoDS_Face face = BRepBuilderAPI_MakeFace(gp_Pln(p.frame), 0, half, 0, half).Face();
      Handle(AIS_Shape) s = new AIS_Shape(face);
      faceStyle(s, p.color, 0.55);
      s->Attributes()->SetFaceBoundaryDraw(true);
      s->Attributes()->SetFaceBoundaryAspect(new Prs3d_LineAspect(p.color, Aspect_TOL_SOLID, 1.5));
      context_->Display(s, AIS_Shaded, 0, false);
      planeObjects_.emplace_back(s, p.spec);
    }
  }
  applyPickModes();
  updateView();
}

void Viewport::setEdgePicking(bool on) {
  if (edgePicking_ == on) return;
  edgePicking_ = on;
  if (!on) setPickedEdges({});
  applyPickModes();
}

void Viewport::setPickedEdges(const std::vector<TopoDS_Shape>& edges) {
  if (context_.IsNull()) return;
  for (auto& e : pickedEdgeObjects_) context_->Remove(e, false);
  pickedEdgeObjects_.clear();
  for (const auto& e : edges) {
    if (e.IsNull()) continue;
    Handle(AIS_Shape) a = new AIS_Shape(e);
    lineStyle(a, rgb(0, 160, 255), 4.0, Aspect_TOL_SOLID);
    context_->Display(a, AIS_WireFrame, -1, false);
    context_->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
    pickedEdgeObjects_.push_back(a);
  }
  updateView();
}

TopoDS_Shape Viewport::bodyShape(const QString& name) const {
  for (const auto& b : bodies_)
    if (b.name == name.toStdString()) return b.shape;
  return {};
}

void Viewport::applyPickModes() {
  if (context_.IsNull()) return;
  const int faceMode = AIS_Shape::SelectionMode(TopAbs_FACE);
  const int edgeMode = AIS_Shape::SelectionMode(TopAbs_EDGE);
  for (const auto& [name, shape] : shapes_) {
    if (!context_->IsDisplayed(shape)) continue;
    context_->Deactivate(shape);
    context_->Activate(shape, planePicking_ ? faceMode : edgePicking_ ? edgeMode : 0);
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
  if (edgePicking_) {
    const Handle(StdSelect_BRepOwner) brep = Handle(StdSelect_BRepOwner)::DownCast(owner);
    if (!brep.IsNull() && brep->Shape().ShapeType() == TopAbs_EDGE) {
      for (const auto& [name, shape] : shapes_)
        if (shape == obj) {
          const TopoDS_Shape edge = brep->Shape();
          context_->ClearSelected(false);
          emit edgeClicked(QString::fromStdString(name), edge);
          return true;
        }
    }
  }
  if (!planePicking_) return false;
  for (const auto& [shape, spec] : planeObjects_)
    if (shape == obj) {
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
