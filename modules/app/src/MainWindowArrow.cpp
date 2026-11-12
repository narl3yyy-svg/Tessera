// MainWindow: the in-canvas drag arrow for the open command panel. Extrude
// (sketch profiles or body faces), Press Pull, Fillet and Chamfer get an
// arrow at the geometry they act on; dragging it sets their distance or
// radius live, and the box beside it takes typed values and expressions.
#include "CommandDialog.h"
#include "MainWindow.h"
#include "SketchEditor.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS.hxx>

#include <algorithm>
#include <cmath>

namespace tsr::app {

namespace {

struct ArrowPlacement {
  gp_Pnt base;
  gp_Dir dir;
};

// Centre and common outward normal of flat faces.
std::optional<ArrowPlacement> facesPlacement(const std::vector<TopoDS_Shape>& faces) {
  GProp_GProps all;
  std::optional<gp_Dir> normal;
  for (const auto& f : faces) {
    if (f.IsNull() || f.ShapeType() != TopAbs_FACE) continue;
    BRepAdaptor_Surface s(TopoDS::Face(f), true);
    if (s.GetType() != GeomAbs_Plane) continue;
    gp_Dir n = s.Plane().Axis().Direction();
    if (f.Orientation() == TopAbs_REVERSED) n.Reverse();
    if (!normal) normal = n;
    GProp_GProps g;
    BRepGProp::SurfaceProperties(f, g);
    all.Add(g);
  }
  if (!normal || all.Mass() <= 0) return std::nullopt;
  return ArrowPlacement{all.CentreOfMass(), *normal};
}

// Midpoint of an edge and the direction into its body, across the edge
// (where a fillet or chamfer grows).
std::optional<ArrowPlacement> edgePlacement(const TopoDS_Shape& edge, const TopoDS_Shape& body) {
  if (edge.IsNull() || edge.ShapeType() != TopAbs_EDGE || body.IsNull()) return std::nullopt;
  BRepAdaptor_Curve c(TopoDS::Edge(edge));
  const double t = (c.FirstParameter() + c.LastParameter()) / 2;
  gp_Pnt mid;
  gp_Vec tangent;
  c.D1(t, mid, tangent);
  Bnd_Box box;
  BRepBndLib::Add(body, box);
  if (box.IsVoid()) return std::nullopt;
  double x0, y0, z0, x1, y1, z1;
  box.Get(x0, y0, z0, x1, y1, z1);
  gp_Vec in(mid, gp_Pnt((x0 + x1) / 2, (y0 + y1) / 2, (z0 + z1) / 2));
  if (tangent.Magnitude() > 1e-12) {
    const gp_Vec u = tangent.Normalized();
    in -= u * in.Dot(u);
  }
  if (in.Magnitude() < 1e-9) return std::nullopt;
  return ArrowPlacement{mid, gp_Dir(in)};
}

} // namespace

// The faces picked in the canvas, else the panel's face references resolved
// on the body (editing an existing feature).
std::vector<TopoDS_Shape> MainWindow::pickedFaces() const {
  std::vector<TopoDS_Shape> out;
  for (const auto& s : pickedEdges_)
    if (!s.IsNull() && s.ShapeType() == TopAbs_FACE) out.push_back(s);
  if (!out.empty() || !active_) return out;
  try {
    const TopoDS_Shape body = viewport_->bodyShape(active_->currentBody());
    if (!body.IsNull()) out = kernel::resolveFaces(body, active_->currentFaces().toStdString());
  } catch (const std::exception&) {
  }
  return out;
}

void MainWindow::updateDragArrow() {
  auto off = [this] {
    arrowInput_.clear();
    viewport_->clearDragArrow();
  };
  if (!active_) return off();
  const QString id = active_->commandId();
  const auto& doc = session_.document();
  std::optional<ArrowPlacement> place;
  QString input;

  if (id == QLatin1String(doc::kCmdExtrude)) {
    if (active_->textInput(QStringLiteral("extent")) != QLatin1String("Distance")) return off();
    input = QStringLiteral("distance");
    const QString faces = active_->currentFaces();
    if (!faces.isEmpty()) {
      place = facesPlacement(pickedFaces());
    } else {
      QString sketchName = active_->currentSketch();
      if (sketchName.isEmpty() && !doc.sketches().empty()) sketchName = QString::fromStdString(doc.sketches().back().name);
      const auto rec = doc.sketch(sketchName.toStdString());
      if (!rec) return off();
      try {
        const gp_Ax3 frame = doc.planeFrame(rec->plane, rec->offset);
        const auto profiles = sketch::profiles(sketch::Sketch::fromJson(rec->data), frame);
        std::vector<int> picked;
        for (const QString& item : active_->currentProfiles().split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
          const auto xy = item.split(QLatin1Char(','));
          if (xy.size() == 2) picked.push_back(sketch::profileAt(profiles, frame, xy[0].toDouble(), xy[1].toDouble()));
        }
        GProp_GProps all;
        for (int i = 0; i < static_cast<int>(profiles.size()); ++i) {
          if (!picked.empty() && std::find(picked.begin(), picked.end(), i) == picked.end()) continue;
          GProp_GProps g;
          BRepGProp::SurfaceProperties(profiles[i].face, g);
          all.Add(g);
        }
        if (all.Mass() <= 0) return off();
        place = ArrowPlacement{all.CentreOfMass(), frame.Direction()};
      } catch (const std::exception&) {
        return off();
      }
    }
    if (place && active_->textInput(QStringLiteral("start")) == QLatin1String("Offset"))
      place->base.Translate(gp_Vec(place->dir) * active_->realInput(QStringLiteral("startOffset")).value_or(0));
  } else if (id == QLatin1String(doc::kCmdPressPull)) {
    input = QStringLiteral("distance");
    place = facesPlacement(pickedFaces());
  } else if (id == QLatin1String(doc::kCmdFillet) || id == QLatin1String(doc::kCmdChamfer)) {
    input = id == QLatin1String(doc::kCmdFillet) ? QStringLiteral("radius") : QStringLiteral("distance");
    for (const auto& e : pickedEdges_)
      if (!e.IsNull()) {
        place = edgePlacement(e, viewport_->bodyShape(active_->currentBody()));
        break;
      }
  }
  const auto value = input.isEmpty() ? std::nullopt : active_->realInput(input);
  if (!place || !value) return off();
  arrowInput_ = input;
  viewport_->setDragArrow(place->base, place->dir, *value, active_->displayText(input));
}

void MainWindow::onDragArrow(double value) {
  if (!active_ || arrowInput_.isEmpty()) return;
  const QString id = active_->commandId();
  // Fillet and chamfer sizes stay positive.
  if (id == QLatin1String(doc::kCmdFillet) || id == QLatin1String(doc::kCmdChamfer))
    value = std::max(value, viewport_->modelPerPixel());
  // Extruding body faces: pulling out joins, pushing in cuts (as Fusion does).
  if (id == QLatin1String(doc::kCmdExtrude) && !active_->currentFaces().isEmpty()) {
    const QString op = active_->textInput(QStringLiteral("operation"));
    if (value < 0 && op == QLatin1String("Join")) active_->setInputForTest(QStringLiteral("operation"), QStringLiteral("Cut"));
    if (value > 0 && op == QLatin1String("Cut")) active_->setInputForTest(QStringLiteral("operation"), QStringLiteral("Join"));
  }
  if (std::abs(value) < 1e-9) return;   // zero is never valid for these inputs
  active_->setRealInput(arrowInput_, value);
}

} // namespace tsr::app
