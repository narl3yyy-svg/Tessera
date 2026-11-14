// Viewport: surface analysis displays (Inspect panel).
//   Zebra          black and white stripes from the surface normal: kinks and
//                  curvature jumps show as broken or bent stripes.
//   Draft          green where faces have at least the draft angle towards the
//                  pull direction, red where they slope against it by that
//                  much, yellow in between (not enough draft).
//   Curvature Map  mean curvature from blue (concave) through green (flat) to
//                  red (convex).
//   Curvature Comb teeth along edges, as long as the curvature there.
//   Accessibility  green where the surface faces the direction a tool comes
//                  from, red where it faces away (no shadowing by other
//                  faces yet).
//   Minimum Radius red where the surface curves tighter than a radius
//                  (a cutter of that radius cannot reach in), green elsewhere.
//   Isocurve       the faces' surface lines (U and V), over the shaded bodies.
#include "Viewport.h"

#include <AIS_Shape.hxx>
#include <AIS_Triangulation.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepLProp_CLProps.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <Poly_Triangulation.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>

#include <algorithm>
#include <cmath>
#include <array>
#include <numbers>
#include <tuple>
#include <vector>

namespace tsr::app {

namespace {
// AIS_Triangulation colours: alpha << 24 | blue << 16 | green << 8 | red.
int packed(int r, int g, int b) { return (255 << 24) | (b << 16) | (g << 8) | r; }

int shade(int r, int g, int b, double light) {
  auto f = [&](int c) { return std::clamp(static_cast<int>(c * light), 0, 255); };
  return packed(f(r), f(g), f(b));
}

// Blue (-1) -> green (0) -> red (+1).
int ramp(double t) {
  t = std::clamp(t, -1.0, 1.0);
  if (t < 0) return packed(static_cast<int>(40 * (1 + t)), static_cast<int>(200 * (1 + t)), static_cast<int>(60 - 195 * t));
  return packed(static_cast<int>(40 + 215 * t), static_cast<int>(200 * (1 - t)), static_cast<int>(60 * (1 - t)));
}
} // namespace

void Viewport::setAnalysis(const AnalysisSettings& a) {
  analysis_ = a;
  if (glReady_) rebuild();
}

void Viewport::clearAnalysisObjects() {
  if (context_.IsNull()) return;
  for (auto& o : analysisObjects_) context_->Remove(o, false);
  analysisObjects_.clear();
}

// Coloured meshes of the bodies for the active analysis (called by rebuild()).
void Viewport::buildAnalysis() {
  clearAnalysisObjects();
  if (analysis_.kind == AnalysisKind::None || context_.IsNull()) return;
  if (analysis_.kind == AnalysisKind::Isocurve) {
    // The bodies stay shaded; their surface lines go on top.
    for (const auto& body : bodies_) {
      if (hidden_[body.name]) continue;
      Handle(AIS_Shape) a = new AIS_Shape(body.shape);
      const Quantity_Color c(0.15, 0.45, 0.95, Quantity_TOC_sRGB);
      a->SetColor(c);
      const Handle(Prs3d_Drawer)& dr = a->Attributes();
      dr->SetUIsoAspect(new Prs3d_IsoAspect(c, Aspect_TOL_SOLID, 1.0, analysis_.isoLines));
      dr->SetVIsoAspect(new Prs3d_IsoAspect(c, Aspect_TOL_SOLID, 1.0, analysis_.isoLines));
      dr->SetIsoOnPlane(true);
      dr->SetFreeBoundaryDraw(false);
      dr->SetUnFreeBoundaryDraw(false);
      context_->Display(a, AIS_WireFrame, -1, false);
      analysisObjects_.push_back(a);
    }
    return;
  }
  const gp_Dir pull = analysis_.pull;
  const gp_Dir stripeAxis = analysis_.stripeAxis;
  const gp_Dir e1 = std::abs(stripeAxis.Z()) < 0.9 ? gp_Dir(gp_Vec(stripeAxis).Crossed(gp_Vec(0, 0, 1)))
                                                  : gp_Dir(gp_Vec(stripeAxis).Crossed(gp_Vec(1, 0, 0)));
  const gp_Dir e2 = stripeAxis.Crossed(e1);
  const double draftLimit = std::sin(analysis_.draftAngle);
  // A fixed light from the viewer's upper left, for some shading.
  const gp_Dir light(0.35, -0.45, 0.82);

  for (const auto& body : bodies_) {
    if (hidden_[body.name]) continue;
    Bnd_Box box;
    BRepBndLib::Add(body.shape, box);
    double x0, y0, z0, x1, y1, z1;
    box.Get(x0, y0, z0, x1, y1, z1);
    const double size = std::hypot(x1 - x0, y1 - y0, z1 - z0);
    BRepMesh_IncrementalMesh mesh(body.shape, std::max(size * 0.002, 1e-4), false, 0.15, false);
    std::vector<gp_Pnt> nodes;
    std::vector<int> colours;
    std::vector<std::array<int, 3>> tris;
    for (TopExp_Explorer it(body.shape, TopAbs_FACE); it.More(); it.Next()) {
      const TopoDS_Face face = TopoDS::Face(it.Current());
      TopLoc_Location loc;
      const Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);
      if (tri.IsNull()) continue;
      const bool reversed = face.Orientation() == TopAbs_REVERSED;
      BRepAdaptor_Surface surf(face, false);
      BRepLProp_SLProps props(surf, 2, 1e-7);
      const int base = static_cast<int>(nodes.size());
      for (int i = 1; i <= tri->NbNodes(); ++i) {
        const gp_Pnt p = tri->Node(i).Transformed(loc);
        nodes.push_back(p);
        gp_Dir n = gp::DZ();
        double mean = 0, tightest = 0;   // mean curvature; largest principal curvature (absolute)
        bool ok = false;
        if (tri->HasUVNodes()) {
          const gp_Pnt2d uv = tri->UVNode(i);
          props.SetParameters(uv.X(), uv.Y());
          if (props.IsNormalDefined()) {
            n = props.Normal();
            if (reversed) n.Reverse();
            ok = true;
            if (props.IsCurvatureDefined()) {
              mean = props.MeanCurvature() * (reversed ? -1 : 1);
              tightest = std::max(std::abs(props.MaxCurvature()), std::abs(props.MinCurvature()));
            }
          }
        }
        const double lit = ok ? 0.55 + 0.45 * std::max(0.0, gp_Vec(n).Dot(gp_Vec(light))) : 0.8;
        int c = packed(200, 200, 200);
        switch (analysis_.kind) {
          case AnalysisKind::Zebra: {
            // Bands of the normal's tilt towards the stripe axis (like a row of
            // lights reflected in the surface): horizontal axis Z gives
            // horizontal stripes. Smooth faces show smooth, unbroken bands.
            const double tilt = std::asin(std::clamp(gp_Vec(n).Dot(gp_Vec(stripeAxis)), -1.0, 1.0));
            const double around = std::atan2(gp_Vec(n).Dot(gp_Vec(e2)), gp_Vec(n).Dot(gp_Vec(e1)));
            const double ang = tilt * 2 + 0.15 * std::sin(around);   // a slight wave so flat faces read too
            const int band = static_cast<int>(std::floor((ang + 2 * std::numbers::pi) / (std::numbers::pi / analysis_.stripes)));
            c = band % 2 == 0 ? shade(245, 245, 245, lit) : shade(25, 25, 25, 1.0);
            break;
          }
          case AnalysisKind::Draft: {
            const double s = gp_Vec(n).Dot(gp_Vec(pull));   // sin of the draft angle
            c = s >= draftLimit - 1e-9    ? shade(60, 190, 80, lit)
                : s <= -draftLimit + 1e-9 ? shade(210, 60, 50, lit)
                                          : shade(235, 200, 40, lit);
            break;
          }
          case AnalysisKind::CurvatureMap:
            c = ramp(mean * analysis_.curvatureScale);
            break;
          case AnalysisKind::Accessibility:
            c = gp_Vec(n).Dot(gp_Vec(pull)) > 1e-9 ? shade(60, 190, 80, lit) : shade(210, 60, 50, lit);
            break;
          case AnalysisKind::MinimumRadius:
            c = tightest * analysis_.minRadius > 1 + 1e-9 ? shade(210, 60, 50, lit) : shade(60, 190, 80, lit);
            break;
          case AnalysisKind::None:
          case AnalysisKind::Isocurve:
            break;
        }
        colours.push_back(c);
      }
      for (int t = 1; t <= tri->NbTriangles(); ++t) {
        int a, b, d;
        tri->Triangle(t).Get(a, b, d);
        if (reversed) std::swap(b, d);
        tris.push_back({base + a, base + b, base + d});
      }
    }
    if (nodes.empty() || tris.empty()) continue;
    Handle(Poly_Triangulation) all = new Poly_Triangulation(static_cast<int>(nodes.size()), static_cast<int>(tris.size()), false);
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i) all->SetNode(i + 1, nodes[i]);
    for (int i = 0; i < static_cast<int>(tris.size()); ++i)
      all->SetTriangle(i + 1, Poly_Triangle(tris[i][0], tris[i][1], tris[i][2]));
    Handle(TColStd_HArray1OfInteger) col = new TColStd_HArray1OfInteger(1, static_cast<int>(colours.size()));
    for (int i = 0; i < static_cast<int>(colours.size()); ++i) col->SetValue(i + 1, colours[i]);
    Handle(AIS_Triangulation) ais = new AIS_Triangulation(all);
    ais->SetColors(col);
    // A neutral white material, so the vertex colours show as they are.
    Graphic3d_MaterialAspect white(Graphic3d_NameOfMaterial_UserDefined);
    white.SetDiffuseColor(Quantity_Color(Quantity_NOC_WHITE));
    white.SetAmbientColor(Quantity_Color(0.6, 0.6, 0.6, Quantity_TOC_RGB));
    white.SetSpecularColor(Quantity_Color(Quantity_NOC_BLACK));
    white.SetEmissiveColor(Quantity_Color(Quantity_NOC_BLACK));
    ais->SetMaterial(white);
    context_->Display(ais, 0, -1, false);
    analysisObjects_.push_back(ais);
  }
}

void Viewport::setCurvatureComb(const std::vector<TopoDS_Shape>& edges, double scale) {
  if (context_.IsNull()) return;
  for (auto& o : combObjects_) context_->Remove(o, false);
  combObjects_.clear();
  TopoDS_Compound teeth, outline;
  BRep_Builder b;
  b.MakeCompound(teeth);
  b.MakeCompound(outline);
  bool any = false;
  for (const auto& e : edges) {
    if (e.IsNull() || e.ShapeType() != TopAbs_EDGE) continue;
    BRepAdaptor_Curve c(TopoDS::Edge(e));
    BRepLProp_CLProps props(c, 2, 1e-7);
    const int n = 60;
    BRepBuilderAPI_MakePolygon tips;
    for (int i = 0; i <= n; ++i) {
      const double t = c.FirstParameter() + (c.LastParameter() - c.FirstParameter()) * i / n;
      props.SetParameter(t);
      const gp_Pnt p = c.Value(t);
      gp_Pnt tip = p;
      if (props.IsTangentDefined()) {
        const double k = props.Curvature();
        if (k > 1e-9) {
          gp_Dir nrm;
          props.Normal(nrm);
          // Teeth point away from the centre of curvature.
          tip = p.Translated(-gp_Vec(nrm) * k * scale);
          if (p.Distance(tip) > 1e-9) b.Add(teeth, BRepBuilderAPI_MakeEdge(p, tip).Edge());
        }
      }
      tips.Add(tip);
      any = true;
    }
    if (tips.IsDone()) b.Add(outline, tips.Wire());
  }
  if (any) {
    const Quantity_Color teethColor(0.95, 0.55, 0.15, Quantity_TOC_sRGB), lineColor(0.95, 0.3, 0.3, Quantity_TOC_sRGB);
    for (auto [shape, colour, width] : {std::tuple{TopoDS_Shape(teeth), teethColor, 1.2}, {TopoDS_Shape(outline), lineColor, 2.0}}) {
      Handle(AIS_Shape) a = new AIS_Shape(shape);
      a->SetColor(colour);
      a->Attributes()->SetWireAspect(new Prs3d_LineAspect(colour, Aspect_TOL_SOLID, width));
      context_->Display(a, AIS_WireFrame, -1, false);
      context_->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
      combObjects_.push_back(a);
    }
  }
  redrawAll();
}

} // namespace tsr::app
