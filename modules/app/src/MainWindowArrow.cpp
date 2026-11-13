// MainWindow: the in-canvas drag arrow for the open command panel. Extrude
// (sketch profiles or body faces), Press Pull, Fillet and Chamfer get an
// arrow at the geometry they act on; dragging it sets their distance or
// radius live, and the box beside it takes typed values and expressions.
#include "CommandDialog.h"
#include "MainWindow.h"
#include "ParameterCompleter.h"
#include "SketchEditor.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <gp_Cylinder.hxx>
#include <BRepTools.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS.hxx>
#include <QLineEdit>

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

// Centre of what the open pattern copies: the geometry the picked features
// added or removed, else the body.
std::optional<gp_Pnt> MainWindow::patternCentre() {
  if (!active_) return std::nullopt;
  auto& doc = session_.document();
  auto centreOf = [](const TopoDS_Shape& s) -> std::optional<gp_Pnt> {
    if (s.IsNull()) return std::nullopt;
    Bnd_Box box;
    BRepBndLib::Add(s, box);
    if (box.IsVoid()) return std::nullopt;
    double x0, y0, z0, x1, y1, z1;
    box.Get(x0, y0, z0, x1, y1, z1);
    return gp_Pnt((x0 + x1) / 2, (y0 + y1) / 2, (z0 + z1) / 2);
  };
  if (active_->textInput(QStringLiteral("patternType")) == QLatin1String("Features")) {
    const QString first = active_->currentFeatures().section(QLatin1Char(';'), 0, 0);
    if (first.isEmpty()) return std::nullopt;
    if (auto it = patternCentres_.find(first); it != patternCentres_.end()) return it->second;
    for (const auto& f : doc.features())
      if (QString::fromStdString(f.name) == first)
        if (const auto* e = doc.featureEffect(f.id))
          for (const auto& [body, change] : e->bodies) {
            const auto& [before, after] = change;
            if (after.IsNull()) continue;
            TopoDS_Shape part = after;
            if (!before.IsNull()) {
              try {
                part = kernel::boolean(kernel::BooleanOp::Cut, after, before);
              } catch (const std::exception&) {
                try {
                  part = kernel::boolean(kernel::BooleanOp::Cut, before, after);   // a cut feature
                } catch (const std::exception&) {
                  part = after;
                }
              }
            }
            if (const auto c = centreOf(part)) {
              patternCentres_[first] = *c;
              return c;
            }
          }
    return std::nullopt;
  }
  QString body = active_->currentBody();
  if (body.isEmpty() && !doc.bodies().empty()) body = QString::fromStdString(doc.bodies().back().name);
  return centreOf(viewport_->bodyShape(body));
}

void MainWindow::updateDragArrow() {
  if (sectionPanel_) return;   // Section Analysis drives the arrow itself
  auto off = [this] {
    arrowInput_.clear();
    arrowInput2_.clear();
    if (!active_) patternCentres_.clear();
    viewport_->clearDragArrow();
  };
  // The instruction beside the cursor, as in the familiar tools.
  QString hint;
  if (active_) {
    const QString cid = active_->commandId();
    if (cid == QLatin1String(doc::kCmdExtrude))
      hint = active_->waitingForSelection() ? tr("Select sketch profiles or planar faces to extrude")
                                            : tr("Specify distance and taper angle");
    else if (cid == QLatin1String(doc::kCmdFillet) || cid == QLatin1String(doc::kCmdChamfer))
      hint = active_->currentEdges().isEmpty() ? tr("Select edges") : tr("Specify size, or select more edges");
    else if (cid == QLatin1String(doc::kCmdPressPull))
      hint = active_->currentFaces().isEmpty() ? tr("Select faces to push or pull") : tr("Specify distance");
    else if (cid == QLatin1String(doc::kCmdThread))
      hint = active_->currentFaces().isEmpty() ? tr("Select a cylindrical face") : QString();
    else if (cid == QLatin1String(doc::kCmdShell))
      hint = active_->currentFaces().isEmpty() ? tr("Select faces to remove, or set the thickness") : tr("Specify thickness");
    else if (cid == QLatin1String(doc::kCmdOffsetFace))
      hint = active_->currentFaces().isEmpty() ? tr("Select faces to offset") : tr("Specify distance");
  }
  viewport_->setCursorHint(hint);
  if (!active_) return off();
  if (active_->waitingForSelection()) return off();
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
  } else if (id == QLatin1String(doc::kCmdRectPattern)) {
    // An arrow along each direction from what is being patterned; the second
    // only when there is more than one row.
    const auto centre = patternCentre();
    if (!centre) return off();
    gp_Dir d1, d2;
    try {
      d1 = doc.axisFrame(active_->textInput(QStringLiteral("direction1")).toStdString()).Direction();
      d2 = doc.axisFrame(active_->textInput(QStringLiteral("direction2")).toStdString()).Direction();
    } catch (const std::exception&) {
      return off();
    }
    const auto v1 = active_->realInput(QStringLiteral("distance1"));
    const auto v2 = active_->realInput(QStringLiteral("distance2"));
    if (!v1) return off();
    arrowInput_ = QStringLiteral("distance1");
    viewport_->setDragArrow(*centre, d1, *v1, active_->displayText(arrowInput_));
    attachArrowCompleters();
    if (v2 && active_->intInput(QStringLiteral("quantity2")).value_or(1) > 1) {
      arrowInput2_ = QStringLiteral("distance2");
      viewport_->setDragArrow(*centre, d2, *v2, active_->displayText(arrowInput2_), 1);
    } else {
      arrowInput2_.clear();
      viewport_->clearSecondArrow();
    }
    return;
  } else if (id == QLatin1String(doc::kCmdThread)) {
    // Full Length off: an arrow for the offset from the face's end and one for
    // the threaded length from there, both along the cylinder.
    if (active_->textInput(QStringLiteral("fullLength")) != QLatin1String("No")) return off();
    const auto faces = pickedFaces();
    if (faces.empty() || faces.front().ShapeType() != TopAbs_FACE) return off();
    const TopoDS_Face face = TopoDS::Face(faces.front());
    BRepAdaptor_Surface s(face, true);
    if (s.GetType() != GeomAbs_Cylinder) return off();
    const gp_Cylinder cyl = s.Cylinder();
    double u0, u1, v0, v1;
    BRepTools::UVBounds(face, u0, u1, v0, v1);
    const gp_Dir z = cyl.Axis().Direction();
    // On the face, on the side the face's middle is.
    const gp_Pnt mid = s.Value((u0 + u1) / 2, (v0 + v1) / 2);
    gp_Vec radial(cyl.Axis().Location(), mid);
    radial -= gp_Vec(z) * radial.Dot(gp_Vec(z));
    const gp_Pnt end = cyl.Axis().Location().Translated(gp_Vec(z) * v0 + radial);
    const auto offset = active_->realInput(QStringLiteral("offset"));
    const auto length = active_->realInput(QStringLiteral("length"));
    if (!offset || !length) return off();
    arrowInput_ = QStringLiteral("length");
    viewport_->setDragArrow(end.Translated(gp_Vec(z) * *offset), z, *length, active_->displayText(arrowInput_));
    arrowInput2_ = QStringLiteral("offset");
    viewport_->setDragArrow(end, z, *offset, active_->displayText(arrowInput2_), 1);
    attachArrowCompleters();
    return;
  } else if (id == QLatin1String(doc::kCmdPressPull) || id == QLatin1String(doc::kCmdOffsetFace)) {
    input = QStringLiteral("distance");
    place = facesPlacement(pickedFaces());
  } else if (id == QLatin1String(doc::kCmdShell)) {
    // Thickness: from the open face, into the body.
    input = QStringLiteral("thickness");
    place = facesPlacement(pickedFaces());
    if (place) {
      place->dir.Reverse();
      if (active_->textInput(QStringLiteral("direction")) == QLatin1String("Outside")) place->dir.Reverse();
    }
  } else if (id == QLatin1String(doc::kCmdHole)) {
    // Depth: at the first position, along the hole into the face.
    if (active_->textInput(QStringLiteral("placement")) != QLatin1String("On Face") ||
        active_->textInput(QStringLiteral("extent")) == QLatin1String("All"))
      return off();
    const QStringList pts = active_->textInput(QStringLiteral("points")).split(QLatin1Char(';'), Qt::SkipEmptyParts);
    if (pts.isEmpty()) return off();
    const QStringList xyz = pts.front().split(QLatin1Char(','));
    if (xyz.size() != 3) return off();
    const TopoDS_Shape body = viewport_->bodyShape(active_->currentBody());
    const auto at = body.IsNull() ? std::nullopt
                                  : kernel::pointOnBody(body, {xyz[0].toDouble(), xyz[1].toDouble(), xyz[2].toDouble()});
    if (!at) return off();
    input = QStringLiteral("depth");
    place = ArrowPlacement{gp_Pnt(at->point.x, at->point.y, at->point.z), gp_Dir(-at->normal.x, -at->normal.y, -at->normal.z)};
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
  attachArrowCompleters();
  // Two Sides: a second arrow pointing the other way sets side 2's distance.
  const auto value2 = id == QLatin1String(doc::kCmdExtrude) &&
                              active_->textInput(QStringLiteral("direction")) == QLatin1String("Two Sides")
                          ? active_->realInput(QStringLiteral("distance2"))
                          : std::nullopt;
  if (value2) {
    arrowInput2_ = QStringLiteral("distance2");
    viewport_->setDragArrow(place->base, place->dir.Reversed(), *value2, active_->displayText(arrowInput2_), 1);
  } else {
    arrowInput2_.clear();
    viewport_->clearSecondArrow();
  }
}

void MainWindow::attachArrowCompleters() {
  for (int i = 0; i < 2; ++i)
    if (QLineEdit* box = viewport_->dragArrowBox(i))
      ParameterCompleter::attach(box, [this] {
        QStringList n;
        for (const auto& prm : session_.document().userParameters()) n << QString::fromStdString(prm.name);
        return n;
      });
}

void MainWindow::onDragArrow(double value) {
  if (sectionPanel_ && !sectionPicking_) {
    emit sectionArrowMoved(value);
    return;
  }
  if (!active_ || arrowInput_.isEmpty()) return;
  const QString id = active_->commandId();
  // Fillet and chamfer sizes, and pattern distances, stay positive.
  if (id == QLatin1String(doc::kCmdRectPattern) || id == QLatin1String(doc::kCmdThread))
    value = std::max(value, viewport_->modelPerPixel());
  if (id == QLatin1String(doc::kCmdFillet) || id == QLatin1String(doc::kCmdChamfer) ||
      id == QLatin1String(doc::kCmdShell) || id == QLatin1String(doc::kCmdHole))
    value = std::max(value, viewport_->modelPerPixel());   // sizes and depths stay positive
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
