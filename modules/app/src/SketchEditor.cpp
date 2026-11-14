#include "ProfileCache.h"
#include "SketchEditor.h"
#include "ParameterCompleter.h"
#include "Theme.h"

#include "tsr/core/Expression.h"
#include "tsr/core/Units.h"
#include "tsr/doc/DocCommands.h"

#include "tsr/sketch/SketchOps.h"

#include <BRepAdaptor_Curve.hxx>
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <AIS_Point.hxx>
#include <AIS_Shape.hxx>
#include <AIS_TextLabel.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_PointAspect.hxx>

#include <QCheckBox>
#include <QCursor>
#include <QPushButton>
#include <QFormLayout>
#include <QFontDatabase>
#include <QDialogButtonBox>
#include <QDialog>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QStyle>
#include <QKeyEvent>
#include <QLineEdit>
#include <QRegularExpression>
#include <QGuiApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTimer>

#include <algorithm>
#include <optional>
#include <tuple>
#include <cmath>
#include <numbers>

namespace tsr::app {

namespace {
// A plain line between two existing points (previews, spline frames).
sketch::Entity lineEntity(int a, int b) {
  sketch::Entity e;
  e.type = sketch::EntityType::Line;
  e.a = a;
  e.b = b;
  return e;
}
} // namespace

using sketch::Constraint;
using sketch::ConstraintType;
using sketch::Entity;
using sketch::EntityType;

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kHVTolerance = 0.0524; // tan(3 degrees): draw "almost horizontal" -> horizontal

Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }

Quantity_Color qc(const QColor& c) { return rgb(c.red(), c.green(), c.blue()); }
// Free / fully constrained colours depend on the theme (blue/black on a
// light canvas, light blue/white on a dark one).
Quantity_Color freeColor() { return qc(themeColors().sketchFree); }
Quantity_Color fixedColor() { return qc(themeColors().sketchFixed); }
const Quantity_Color kConstruction = rgb(235, 130, 30);
const Quantity_Color kSelected = rgb(0, 190, 255);
const Quantity_Color kHover = rgb(255, 170, 0);
const Quantity_Color kPreview = rgb(90, 160, 240);

Handle(AIS_Shape) wire(const TopoDS_Shape& s, const Quantity_Color& c, double width, Aspect_TypeOfLine type) {
  Handle(AIS_Shape) a = new AIS_Shape(s);
  a->SetColor(c);
  a->SetWidth(width);
  a->Attributes()->SetWireAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetLineAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetFreeBoundaryAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetUnFreeBoundaryAspect(new Prs3d_LineAspect(c, type, width));
  return a;
}

// The circle through three points: false when they are (nearly) in line.
bool circumcircle(double ax, double ay, double bx, double by, double cx, double cy, double& ox, double& oy, double& r) {
  const double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
  const double scale = std::max({std::hypot(bx - ax, by - ay), std::hypot(cx - ax, cy - ay), 1e-12});
  if (std::abs(d) < 1e-9 * scale * scale) return false;
  const double a2 = ax * ax + ay * ay, b2 = bx * bx + by * by, c2 = cx * cx + cy * cy;
  ox = (a2 * (by - cy) + b2 * (cy - ay) + c2 * (ay - by)) / d;
  oy = (a2 * (cx - bx) + b2 * (ax - cx) + c2 * (bx - ax)) / d;
  r = std::hypot(ax - ox, ay - oy);
  return true;
}

// Does the counter-clockwise arc from angle s to e pass through m?
bool ccwContains(double s, double e, double m) {
  const double twoPi = 2 * std::numbers::pi;
  auto norm = [&](double a) { return a - twoPi * std::floor(a / twoPi); };
  return norm(m - s) < norm(e - s);
}

TCollection_ExtendedString ext(const QString& s) {
  return TCollection_ExtendedString(s.toUtf8().constData(), /*isMultiByte=*/true);
}

double segDistance(double px, double py, double ax, double ay, double bx, double by) {
  const double dx = bx - ax, dy = by - ay;
  const double l2 = dx * dx + dy * dy;
  double t = l2 > 0 ? ((px - ax) * dx + (py - ay) * dy) / l2 : 0;
  t = std::clamp(t, 0.0, 1.0);
  return std::hypot(px - (ax + t * dx), py - (ay + t * dy));
}

bool angleInArc(double a, double from, double to) {
  auto norm = [](double v) {
    while (v < 0) v += 2 * kPi;
    while (v >= 2 * kPi) v -= 2 * kPi;
    return v;
  };
  const double span = norm(to - from);
  return norm(a - from) <= span;
}
} // namespace

SketchEditor::SketchEditor(doc::Session& session, Viewport* viewport, const QString& name, const QString& plane,
                           double offset, int featureId, const sketch::Sketch& initial, QObject* parent)
    : QObject(parent), session_(session), view_(viewport), name_(name), plane_(plane), offset_(offset),
      featureId_(featureId), sk_(initial) {
  try {
    frame_ = session_.document().planeFrame(plane.toStdString(), offset);
  } catch (const std::exception&) {
    frame_ = sketch::planeFrame("XY", offset);
  }
  unit_ = parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);
  res_ = sketch::solve(sk_);
  view_->setInteractor(this);
  view_->setGridPlane(frame_);
  collectBodyEdges();
  // Frame the existing geometry (a new sketch keeps the current zoom).
  if (sk_.points.size() > 1) {
    double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    for (const auto& p : sk_.points) {
      x0 = std::min(x0, p.x), y0 = std::min(y0, p.y), x1 = std::max(x1, p.x), y1 = std::max(y1, p.y);
    }
    for (const auto& e : sk_.entities)
      if (sketch::isRound(e.type)) {
        const auto& c = sk_.points[e.center];
        x0 = std::min(x0, c.x - e.radius), y0 = std::min(y0, c.y - e.radius);
        x1 = std::max(x1, c.x + e.radius), y1 = std::max(y1, c.y + e.radius);
      }
    const double size = std::max({x1 - x0, y1 - y0, 1.0}) * 1.6;
    view_->lookAt(frame_, size, sketch::toWorld(frame_, (x0 + x1) / 2, (y0 + y1) / 2));
  } else {
    view_->lookAt(frame_);
  }
  setTool(Tool::Line);
  connect(&Theme::instance(), &Theme::changed, this, [this] { rebuild(); });
  rebuild();
}

SketchEditor::~SketchEditor() {
  delete valueBox_.data();   // its callbacks refer to this editor
  if (!view_) return;
  clearPreview();
  const auto& ctx = view_->aisContext();
  if (!ctx.IsNull())
    for (auto& o : objects_) ctx->Remove(o, false);
  objects_.clear();
  view_->setInteractor(nullptr);
  view_->setGridPlane(sketch::planeFrame("XY"));
  view_->redraw();
}

// ---------------------------------------------------------------------------
void SketchEditor::setTool(Tool t) {
  // Mirror and the transform tools can start from curves already selected.
  std::vector<Hit> keep;
  if (t == Tool::Mirror || isTransformTool(t))
    for (const auto& h : selection_)
      if (h.kind == Hit::Entity) keep.push_back(h);
  const std::vector<Hit> preselected = isConstraintTool(t) ? selection_ : std::vector<Hit>{};
  resetSteps();
  tool_ = t;
  if (t != Tool::Select) lastTool_ = t;
  selection_.clear();
  for (const auto& h : keep) picks_.push_back({h, 0, 0});
  if (!keep.empty() && t == Tool::Mirror) mirrorLineStage_ = true;
  clearPreview();
  emit toolChanged();
  switch (t) {
    case Tool::Select: emit message(tr("Select: click to select, drag points or lines to move them, Delete removes.")); break;
    case Tool::Line: emit message(tr("Line: click points, or type the length (Tab: angle) and press Enter. Click the first point to close.")); break;
    case Tool::Rectangle: emit message(tr("Rectangle: click a corner; type width, Tab, height, Enter (or click the other corner).")); break;
    case Tool::Circle: emit message(tr("Circle: click the centre; type the diameter and press Enter (or click).")); break;
    case Tool::Arc: emit message(tr("Arc: click the centre, the start, then the end (counter-clockwise).")); break;
    case Tool::Point: emit message(tr("Point: click to place points.")); break;
    case Tool::Project: emit message(tr("Project: click body edges to copy them into the sketch, or inside a face for all its edges.")); break;
    case Tool::Include3D: emit message(tr("Include 3D Geometry: click body edges to bring them in as they are in space, or inside a face for all its edges.")); break;
    case Tool::Spline: emit message(tr("Spline: click the points the curve passes through; Enter, double-click or Esc finishes, clicking the first point closes it.")); break;
    case Tool::Fillet: emit message(tr("Fillet: click a corner (or two lines), then type the radius and press Enter (or click).")); break;
    case Tool::Offset: emit message(tr("Offset: click a curve (a spline or ellipse on its own); its connected chain is copied. Move to the side you want, type the distance, Enter (or click).")); break;
    case Tool::Chamfer: emit message(tr("Chamfer: click a corner (or two lines), then type the distance and press Enter (or click).")); break;
    case Tool::Extend: emit message(tr("Extend: click a line near the end to lengthen it to the next curve.")); break;
    case Tool::Mirror:
      emit message(selection_.empty() ? tr("Mirror: click the curves to mirror, press Enter, then click the mirror line.")
                                      : tr("Mirror: click the mirror line."));
      break;
    case Tool::Dimension: emit message(tr("Dimension: click a line, circle or arc; or two points/lines. Type the value, Enter.")); break;
    case Tool::Coincident: emit message(tr("Coincident: click two points, or a point and a curve.")); break;
    case Tool::HorizontalVertical: emit message(tr("Horizontal/Vertical: click a line.")); break;
    case Tool::Parallel: emit message(tr("Parallel: click two lines.")); break;
    case Tool::Perpendicular: emit message(tr("Perpendicular: click two lines.")); break;
    case Tool::Equal: emit message(tr("Equal: click two lines, or two circles/arcs.")); break;
    case Tool::Tangent: emit message(tr("Tangent: click a line and a circle/arc, or two circles/arcs.")); break;
    case Tool::Fix: emit message(tr("Fix: click a point or curve to lock it in place.")); break;
    case Tool::Midpoint: emit message(tr("Midpoint: click a point, then a line.")); break;
    case Tool::Concentric: emit message(tr("Concentric: click two circles/arcs.")); break;
    case Tool::CenterRectangle: emit message(tr("Center Rectangle: click the centre, then a corner. Type sizes in the boxes (Tab, Enter).")); break;
    case Tool::Polygon: emit message(tr("Polygon: click the centre, then a corner. The boxes take the diameter and the number of sides.")); break;
    case Tool::Slot: emit message(tr("Slot: click one end centre, then the other. The boxes take length and width.")); break;
    case Tool::ThreePointRectangle: emit message(tr("3-Point Rectangle: click both ends of one side, then a point for the width.")); break;
    case Tool::TwoPointCircle: emit message(tr("2-Point Circle: click both ends of a diameter.")); break;
    case Tool::ThreePointCircle: emit message(tr("3-Point Circle: click three points on the circle.")); break;
    case Tool::ThreePointArc: emit message(tr("3-Point Arc: click the start, the end, then a point the arc passes through.")); break;
    case Tool::ControlSpline: emit message(tr("Control Point Spline: click the points of its frame; Enter or double-click finishes, Esc throws it away.")); break;
    case Tool::Conic: emit message(tr("Conic Curve: click the start, the end, then the vertex where its end tangents meet (rho 0.5; double-click the curve to change it).")); break;
    case Tool::TangentArc: emit message(tr("Tangent Arc: click the end of a line or arc, then where the arc ends. Each arc carries on from the last.")); break;
    case Tool::TwoTangentCircle: emit message(tr("2-Tangent Circle: click two lines, then place the circle.")); break;
    case Tool::ThreeTangentCircle: emit message(tr("3-Tangent Circle: click three lines.")); break;
    case Tool::OverallSlot: emit message(tr("Overall Slot: click both ends of the slot, then a point for the width.")); break;
    case Tool::ArcSlot: emit message(tr("Center Point Arc Slot: click the centre, the start, the end, then a point for the width.")); break;
    case Tool::Ellipse: emit message(tr("Ellipse: click the centre, the end of one axis, then a point for the other.")); break;
    case Tool::Text: emit message(tr("Text: click two corners of the text box (the same place twice: text on a point). Double-click a text to change it.")); break;
    case Tool::TextOnPath: emit message(tr("Text on Path: click the curve the letters stand on.")); break;
    case Tool::Break: emit message(tr("Break: click a curve to split it where it crosses others.")); break;
    case Tool::Intersect: emit message(tr("Intersect: click a body; where it crosses the sketch plane becomes curves.")); break;
    case Tool::RectPattern:
    case Tool::CircPattern:
    case Tool::MoveCopy:
    case Tool::SketchScale:
      emit message(picks_.empty() ? tr("Click the curves, then press Enter.")
                                  : tr("%n curve(s) picked: click more, or press Enter.", nullptr, static_cast<int>(picks_.size())));
      break;
    case Tool::Trim: emit message(tr("Trim: click the part of a curve to remove (up to the nearest crossings).")); break;
    case Tool::Collinear: emit message(tr("Collinear: click two lines.")); break;
    case Tool::Symmetry: emit message(tr("Symmetry: click two points, lines or circles, then the line of symmetry.")); break;
  }
  rebuild();
  if (!preselected.empty()) applyToSelection(preselected);
}

void SketchEditor::resetSteps() {
  clearHud();
  steps_.clear();
  tangentLines_.clear();
  tangentClicks_.clear();
  picks_.clear();
  chainStart_ = -1;
  filletLines_ = {-1, -1};
  firstFilletLine_ = -1;
  offsetEntity_ = -1;
  mirrorLineStage_ = false;
  xformPointStage_ = false;
  clearPreview();
}

void SketchEditor::escape() {
  if (valueBox_) {
    valueBox_->deleteLater();
    valueBox_ = nullptr;
    return;
  }
  // An unfinished spline is thrown away (Enter or a double-click keeps it).
  if (!steps_.empty() || !picks_.empty()) {
    resetSteps();
    rebuild();
  } else if (!selection_.empty()) {
    selection_.clear();
    rebuild();
  } else if (tool_ != Tool::Select) {
    setTool(Tool::Select);
  }
}

void SketchEditor::checkpoint() {
  undo_.push_back(sk_);
  if (undo_.size() > 300) undo_.erase(undo_.begin());
  redo_.clear();
}

void SketchEditor::undo() {
  if (undo_.empty()) return;
  redo_.push_back(sk_);
  sk_ = undo_.back();
  undo_.pop_back();
  resetSteps();
  selection_.clear();
  solveAndShow();
}

void SketchEditor::redo() {
  if (redo_.empty()) return;
  undo_.push_back(sk_);
  sk_ = redo_.back();
  redo_.pop_back();
  resetSteps();
  selection_.clear();
  solveAndShow();
}

void SketchEditor::solveAndShow() {
  res_ = sketch::solve(sk_);
  rebuild();
  if (res_.ok)
    emit message(res_.dof == 0 ? tr("Fully constrained.") : tr("%n degree(s) of freedom left.", nullptr, res_.dof));
  else
    emit message(QString::fromStdString(res_.message));
  emit changed();
}

std::string SketchEditor::constrain(const Constraint& c) {
  checkpoint();
  const std::string err = sketch::addConstraintChecked(sk_, c);
  if (!err.empty()) {
    undo_.pop_back();
    emit message(QString::fromStdString(err));
    rebuild();
    return err;
  }
  solveAndShow();
  return {};
}

std::string SketchEditor::finish() {
  if (valueBox_) valueBox_->deleteLater();
  const std::string data = sk_.toJson();
  if (featureId_ < 0)
    return session_.run(doc::kCmdSketch, {{"name", name_.toStdString()},
                                         {"plane", plane_.toStdString()},
                                         {"offset", offset_},
                                         {"data", data}});
  return session_.editFeature(featureId_, {{"data", data}});
}

// ---------------------------------------------------------------------------
// Picking

bool SketchEditor::toSketch(const QPointF& pos, double& x, double& y) const {
  gp_Pnt p;
  if (!view_ || !view_->planePoint(pos, frame_, p)) return false;
  sketch::toSketch(frame_, p, x, y);
  return true;
}

double SketchEditor::tolerance() const { return (view_ ? view_->modelPerPixel() : 0.01) * 8.0; }

int SketchEditor::snapPoint(double x, double y, int exclude) const {
  int best = -1;
  double bestD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.points.size()); ++i) {
    if (i == exclude) continue;
    const double d = std::hypot(sk_.points[i].x - x, sk_.points[i].y - y);
    if (d < bestD) {
      bestD = d;
      best = i;
    }
  }
  return best;
}

void SketchEditor::snapToGrid(double& x, double& y) const {
  if (!view_ || !view_->gridSnap() || snapsSuppressed()) return;
  const double g = view_->gridSpacing();
  if (g <= 0) return;
  x = std::round(x / g) * g;
  y = std::round(y / g) * g;
}

QString SketchEditor::lengthText(double cm) const {
  return QStringLiteral("%1 %2").arg(fromInternal(cm, unit_), 0, 'f', unit_ == Unit::Inch ? 3 : 2)
      .arg(QString::fromUtf8(unitSymbol(unit_).data()));
}

SketchEditor::Pick SketchEditor::pickPoint(double x, double y, int exclude) const {
  const Snap s = snapAt(x, y, exclude);
  Pick p;
  p.x = s.x;
  p.y = s.y;
  if (s.kind == Snap::Point) p.hit = {Hit::Point, s.point};
  if (s.kind == Snap::OnCurve) p.onEntity = s.entity;
  if (s.kind == Snap::Midpoint) p.midpointOf = s.entity;
  if (s.perpendicular) p.perpendicularTo = s.reference;
  if (s.parallel) p.parallelTo = s.reference;
  if (s.kind == Snap::BodyEdge && s.bodyArc >= 0) p.bodyArc = s.bodyArc;
  if (s.tangent) p.tangentTo = s.reference;
  if (s.kind == Snap::BodyVertex) p.bodyPoint = true;
  // Lined up with the origin: the point is on an origin axis, and stays on it
  // (as the familiar sketcher makes it coincident with the axis).
  if (s.kind == Snap::Free || s.kind == Snap::Grid) {
    p.onXAxis = s.alignY == 0;
    p.onYAxis = s.alignX == 0;
  }
  if (s.kind == Snap::BodyEdge) {
    p.bodyPoint = s.bodySegment < 0 && s.bodyArc < 0;
    p.bodySegment = s.bodySegment;
  }
  return p;
}

// A body edge copied into the sketch: a fixed purple line (reused if it is
// already there).
int SketchEditor::projectSegment(const std::array<double, 4>& g) {
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    if (!e.projected || e.type != EntityType::Line) continue;
    const auto &a = sk_.points[e.a], &b = sk_.points[e.b];
    if ((std::hypot(a.x - g[0], a.y - g[1]) < 1e-7 && std::hypot(b.x - g[2], b.y - g[3]) < 1e-7) ||
        (std::hypot(a.x - g[2], a.y - g[3]) < 1e-7 && std::hypot(b.x - g[0], b.y - g[1]) < 1e-7))
      return i;
  }
  const int line = sk_.addLine(g[0], g[1], g[2], g[3]);
  sk_.entities[line].projected = true;
  for (int q : {sk_.entities[line].a, sk_.entities[line].b})
    sk_.addConstraint({ConstraintType::Fix, {q}, {}, sk_.points[q].x, sk_.points[q].y});
  return line;
}

// A round body edge copied into the sketch: a fixed circle or arc.
int SketchEditor::projectArc(const std::array<double, 5>& g) {
  const bool full = std::abs(std::abs(g[4]) - 2 * kPi) < 1e-9;
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    if (!e.projected || !sketch::isRound(e.type)) continue;
    const auto& c = sk_.points[e.center];
    if (std::hypot(c.x - g[0], c.y - g[1]) < 1e-7 && std::abs(e.radius - g[2]) < 1e-7) return i;
  }
  const int c = sk_.addPoint(g[0], g[1]);
  sk_.addConstraint({ConstraintType::Fix, {c}, {}, g[0], g[1]});
  int curve;
  if (full) {
    curve = sk_.addCircleAt(c, g[2]);
  } else {
    // Stored anticlockwise: start at the end the sweep leaves from.
    const double a0 = g[4] > 0 ? g[3] : g[3] + g[4], a1 = g[4] > 0 ? g[3] + g[4] : g[3];
    const int s0 = sk_.addPoint(g[0] + g[2] * std::cos(a0), g[1] + g[2] * std::sin(a0));
    const int s1 = sk_.addPoint(g[0] + g[2] * std::cos(a1), g[1] + g[2] * std::sin(a1));
    sk_.addConstraint({ConstraintType::Fix, {s0}, {}, sk_.points[s0].x, sk_.points[s0].y});
    sk_.addConstraint({ConstraintType::Fix, {s1}, {}, sk_.points[s1].x, sk_.points[s1].y});
    curve = sk_.addArc(c, s0, s1);
  }
  sk_.entities[curve].projected = true;
  if (full) sk_.addConstraint({ConstraintType::Radius, {}, {curve}, g[2]});
  return curve;
}

// Any body edge seen along the sketch normal: a straight edge becomes a
// segment (or a point when it points straight at the plane), a circle or arc
// facing the plane becomes one. False for other curves.
bool SketchEditor::projectEdgeShape(const TopoDS_Edge& edge, PlaneEdges& out) const {
  if (BRep_Tool::Degenerated(edge)) return false;
  BRepAdaptor_Curve c(edge);
  const double t0 = c.FirstParameter(), t1 = c.LastParameter();
  const gp_Pnt p0 = c.Value(t0), p1 = c.Value(t1), pm = c.Value((t0 + t1) / 2);
  double x0, y0, x1, y1, xm, ym;
  sketch::toSketch(frame_, p0, x0, y0);
  sketch::toSketch(frame_, p1, x1, y1);
  sketch::toSketch(frame_, pm, xm, ym);
  if (c.GetType() == GeomAbs_Line) {
    if (std::hypot(x1 - x0, y1 - y0) < 1e-7) {
      out.vertices.emplace_back(x0, y0);
      return true;
    }
    out.segments.push_back({x0, y0, x1, y1});
    return true;
  }
  if (c.GetType() == GeomAbs_Circle) {
    const gp_Circ circ = c.Circle();
    if (std::abs(circ.Axis().Direction().Dot(frame_.Direction())) < 1 - 1e-9) return false;   // seen edge-on or tilted
    double cx, cy;
    sketch::toSketch(frame_, circ.Location(), cx, cy);
    const bool full = p0.Distance(p1) < 1e-7;
    const double a0 = std::atan2(y0 - cy, x0 - cx), am = std::atan2(ym - cy, xm - cx);
    double sweep = 2 * kPi;
    if (!full) {
      const double a1 = std::atan2(y1 - cy, x1 - cx);
      double s1 = a1 - a0, sm = am - a0;
      while (s1 <= 0) s1 += 2 * kPi;
      while (sm <= 0) sm += 2 * kPi;
      sweep = sm < s1 ? s1 : s1 - 2 * kPi;
    }
    out.arcs.push_back({cx, cy, circ.Radius(), a0, sweep});
    return true;
  }
  // Anything else (a tilted circle seen as an ellipse, a spline ...): points
  // along it, seen along the sketch normal.
  return projectCurvePoints(c, t0, t1, out);
}

bool SketchEditor::projectCurvePoints(const BRepAdaptor_Curve& c, double t0, double t1, PlaneEdges& out) const {
  const int n = 32;
  std::vector<std::pair<double, double>> pts;
  for (int k = 0; k <= n; ++k) {
    double x, y;
    sketch::toSketch(frame_, c.Value(t0 + (t1 - t0) * k / n), x, y);
    if (!pts.empty() && std::hypot(x - pts.back().first, y - pts.back().second) < 1e-7) continue;
    pts.emplace_back(x, y);
  }
  if (pts.size() < 2) return false;
  out.curves.push_back(std::move(pts));
  return true;
}

int SketchEditor::addProjected(const PlaneEdges& g) {
  for (const auto& s : g.segments) (void)projectSegment(s);
  for (const auto& a : g.arcs) (void)projectArc(a);
  for (const auto& pts : g.curves) {
    // A fixed spline through the points (closed when the curve is).
    const bool closed = pts.size() > 3 && std::hypot(pts.front().first - pts.back().first,
                                                     pts.front().second - pts.back().second) < 1e-7;
    std::vector<int> fit;
    for (size_t i = 0; i < pts.size() - (closed ? 1 : 0); ++i) {
      const int p = sk_.addPoint(pts[i].first, pts[i].second);
      sk_.addConstraint({ConstraintType::Fix, {p}, {}, pts[i].first, pts[i].second});
      fit.push_back(p);
    }
    if (closed) fit.push_back(fit.front());
    if (fit.size() < 2) continue;
    const int e = sk_.addSpline(fit);
    sk_.entities[e].projected = true;
  }
  for (const auto& [vx, vy] : g.vertices) {
    const int p = sk_.addPoint(vx, vy);
    sk_.addConstraint({ConstraintType::Fix, {p}, {}, vx, vy});
  }
  return static_cast<int>(g.segments.size() + g.arcs.size() + g.curves.size());
}

// Intersect: where a body crosses the sketch plane, as projected curves.
void SketchEditor::intersectAt(const QPointF& widgetPos) {
  if (!view_) return;
  const TopoDS_Face f = view_->faceAt(widgetPos);
  if (f.IsNull()) {
    emit message(tr("Intersect: click a body that crosses the sketch plane."));
    return;
  }
  TopoDS_Shape body;
  for (const auto& b : session_.document().bodies())
    for (TopExp_Explorer x(b.shape, TopAbs_FACE); x.More() && body.IsNull(); x.Next())
      if (x.Current().IsSame(f)) body = b.shape;
  if (body.IsNull()) return;
  PlaneEdges g;
  try {
    BRepAlgoAPI_Section section(body, gp_Pln(frame_), false);
    section.Approximation(true);
    section.Build();
    if (section.IsDone())
      for (TopExp_Explorer x(section.Shape(), TopAbs_EDGE); x.More(); x.Next()) (void)projectEdgeShape(TopoDS::Edge(x.Current()), g);
  } catch (const Standard_Failure&) {
  }
  if (g.segments.empty() && g.arcs.empty() && g.curves.empty()) {
    emit message(tr("Intersect: that body does not cross the sketch plane."));
    return;
  }
  checkpoint();
  const int n = addProjected(g);
  solveAndShow();
  emit message(tr("Intersect: %n curve(s) where the body crosses the sketch.", nullptr, n));
}

// Project (P): click a body edge to copy it into the sketch, seen along the
// sketch normal; click inside a face to copy all of its edges.
TopoDS_Edge SketchEditor::bodyEdgeNear(const QPointF& widgetPos) const {
  TopoDS_Edge best;
  if (!view_) return best;
  double bestD = 8.0;   // pixels
  for (const auto& b : session_.document().bodies()) {
    if (!view_->isBodyVisible(QString::fromStdString(b.name))) continue;
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(b.shape, TopAbs_EDGE, edges);
    for (int i = 1; i <= edges.Extent(); ++i) {
      const TopoDS_Edge e = TopoDS::Edge(edges(i));
      if (BRep_Tool::Degenerated(e)) continue;
      BRepAdaptor_Curve c(e);
      const double t0 = c.FirstParameter(), t1 = c.LastParameter();
      QPointF prev;
      for (int k = 0; k <= 24; ++k) {
        const QPointF q = view_->toWidget(c.Value(t0 + (t1 - t0) * k / 24.0));
        if (k > 0) {
          const QPointF ab = q - prev;
          const double l2 = ab.x() * ab.x() + ab.y() * ab.y();
          double t = l2 > 0 ? ((widgetPos - prev).x() * ab.x() + (widgetPos - prev).y() * ab.y()) / l2 : 0;
          t = std::clamp(t, 0.0, 1.0);
          const QPointF on = prev + ab * t;
          const double d = std::hypot(widgetPos.x() - on.x(), widgetPos.y() - on.y());
          if (d < bestD) {
            bestD = d;
            best = e;
          }
        }
        prev = q;
      }
    }
  }
  return best;
}

void SketchEditor::projectAt(const QPointF& widgetPos) {
  if (!view_) return;
  // The edge nearest the cursor on screen.
  const TopoDS_Edge best = bodyEdgeNear(widgetPos);
  std::vector<TopoDS_Edge> picked;
  if (!best.IsNull()) {
    picked.push_back(best);
  } else if (const TopoDS_Face f = view_->faceAt(widgetPos); !f.IsNull()) {
    for (TopExp_Explorer x(f, TopAbs_EDGE); x.More(); x.Next()) picked.push_back(TopoDS::Edge(x.Current()));
  }
  if (picked.empty()) {
    emit message(tr("Project: click a body edge, or inside a face to project all its edges."));
    return;
  }
  PlaneEdges g;
  for (const auto& e : picked) (void)projectEdgeShape(e, g);
  if (g.segments.empty() && g.arcs.empty() && g.curves.empty() && g.vertices.empty()) {
    emit message(tr("That edge cannot be projected."));
    return;
  }
  checkpoint();
  const int n = addProjected(g);
  solveAndShow();
  emit message(tr("Projected %n curve(s).", nullptr, n));
}

void SketchEditor::includeAt(const QPointF& widgetPos) {
  if (!view_) return;
  std::vector<TopoDS_Edge> picked;
  if (const TopoDS_Edge best = bodyEdgeNear(widgetPos); !best.IsNull()) {
    picked.push_back(best);
  } else if (const TopoDS_Face f = view_->faceAt(widgetPos); !f.IsNull()) {
    for (TopExp_Explorer x(f, TopAbs_EDGE); x.More(); x.Next()) picked.push_back(TopoDS::Edge(x.Current()));
  }
  if (picked.empty()) {
    emit message(tr("Include 3D Geometry: click a body edge, or inside a face to include all its edges."));
    return;
  }
  checkpoint();
  const int n = sketch::includeEdges(sk_, frame_, picked);
  if (n == 0) {
    undo_.pop_back();
    emit message(tr("That edge cannot be included."));
    return;
  }
  solveAndShow();
  emit message(tr("Included %n curve(s) in 3D.", nullptr, n));
}

bool SketchEditor::showsHandles(int spline) const {
  if (spline < 0 || spline >= static_cast<int>(sk_.entities.size())) return false;
  const auto& e = sk_.entities[spline];
  if (e.type != EntityType::Spline || e.kind != sketch::SplineKind::Fit || e.projected) return false;
  if (dragHandle_.spline == spline) return true;
  for (const auto& s : selection_) {
    if (s.kind == Hit::Entity && s.index == spline) return true;
    if (s.kind == Hit::Point && std::find(e.fit.begin(), e.fit.end(), s.index) != e.fit.end()) return true;
  }
  return false;
}

SketchEditor::HandleHit SketchEditor::handleAt(double x, double y) const {
  HandleHit best;
  double bestD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    if (!showsHandles(i)) continue;
    for (const auto& h : sketch::splineHandles(sk_, i))
      for (bool back : {false, true}) {
        const double sg = back ? -1 : 1;
        const double d = std::hypot(x - (h.x + sg * h.tx * h.arm), y - (h.y + sg * h.ty * h.arm));
        if (d < bestD) {
          bestD = d;
          best = {i, h.index, back};
        }
      }
  }
  return best;
}

void SketchEditor::moveHandle(const HandleHit& hh, double x, double y) {
  for (const auto& h : sketch::splineHandles(sk_, hh.spline)) {
    if (h.index != hh.index) continue;
    const double sg = hh.back ? -1 : 1;
    const double tx = sg * (x - h.x) / h.arm, ty = sg * (y - h.y) / h.arm;
    if (std::hypot(tx, ty) < 1e-3) return;   // on the point itself: no direction
    if (sketch::setSplineHandle(sk_, hh.spline, hh.index, tx, ty).empty()) rebuild();
    return;
  }
}

int SketchEditor::materialize(const Pick& p) {
  if (p.hit.kind == Hit::Point && p.hit.index >= 0 && p.hit.index < static_cast<int>(sk_.points.size()))
    return p.hit.index;
  const int pt = sk_.addPoint(p.x, p.y);
  // Snapped onto a curve or a line's middle: keep it there.
  if (p.onEntity >= 0 && p.onEntity < static_cast<int>(sk_.entities.size()) &&
      sk_.entities[p.onEntity].type != EntityType::Spline)
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::PointOnEntity, {pt}, {p.onEntity}});
  if (p.midpointOf >= 0 && p.midpointOf < static_cast<int>(sk_.entities.size()))
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::Midpoint, {pt}, {p.midpointOf}});
  // On body geometry: project it, as the familiar sketcher does. Straight
  // edges become fixed purple lines with the point on them; anything else
  // becomes a fixed point.
  if (p.bodySegment >= 0 && p.bodySegment < static_cast<int>(bodyEdges_.segments.size())) {
    const int line = projectSegment(bodyEdges_.segments[p.bodySegment]);
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::PointOnEntity, {pt}, {line}});
  } else if (p.bodyArc >= 0 && p.bodyArc < static_cast<int>(bodyEdges_.arcs.size())) {
    const int curve = projectArc(bodyEdges_.arcs[p.bodyArc]);
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::PointOnEntity, {pt}, {curve}});
  } else if (p.bodyPoint) {
    sk_.addConstraint({ConstraintType::Fix, {pt}, {}, p.x, p.y});
  }
  if (p.onXAxis) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Horizontal, {0, pt}, {}});
  if (p.onYAxis) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Vertical, {0, pt}, {}});
  return pt;
}

bool SketchEditor::onlyProjected(const sketch::Constraint& c) const {
  bool any = false;
  for (int e : c.entities) {
    if (e < 0 || e >= static_cast<int>(sk_.entities.size()) || !sk_.entities[e].projected) return false;
    any = true;
  }
  for (int p : c.points) {
    bool owned = false;
    for (const auto& e : sk_.entities)
      if (e.projected && (e.a == p || e.b == p || e.center == p)) owned = true;
    if (!owned) return false;
    any = true;
  }
  return any;
}

int SketchEditor::curveEndingAt(int point, int exclude) const {
  int found = -1;
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    if (i == exclude) continue;
    const auto& e = sk_.entities[i];
    if ((e.type != EntityType::Line && e.type != EntityType::Arc) || e.construction) continue;
    if (e.a == point || e.b == point) {
      if (found >= 0) return -1;   // a corner of two curves: no single direction
      found = i;
    }
  }
  return found;
}

std::optional<std::pair<double, double>> SketchEditor::leavingDirection(int entity, int point) const {
  if (entity < 0 || entity >= static_cast<int>(sk_.entities.size())) return std::nullopt;
  const auto& e = sk_.entities[entity];
  const auto& p = sk_.points[point];
  if (e.type == EntityType::Line) {
    const auto& o = sk_.points[e.a == point ? e.b : e.a];
    const double l = std::hypot(p.x - o.x, p.y - o.y);
    if (l < 1e-12) return std::nullopt;
    return std::make_pair((p.x - o.x) / l, (p.y - o.y) / l);
  }
  if (e.type == EntityType::Arc) {
    const auto& c = sk_.points[e.center];
    const double rx = p.x - c.x, ry = p.y - c.y, r = std::hypot(rx, ry);
    if (r < 1e-12) return std::nullopt;
    // Arcs run anticlockwise a -> b: leaving b goes anticlockwise, leaving a clockwise.
    if (point == e.b) return std::make_pair(-ry / r, rx / r);
    return std::make_pair(ry / r, -rx / r);
  }
  return std::nullopt;
}

bool SketchEditor::tangentArc(double x, double y, double& cx, double& cy, double& r, bool& ccw) const {
  if (arcFrom_ < 0) return false;
  const auto dir = leavingDirection(arcRef_, arcFrom_);
  if (!dir) return false;
  const auto& s = sk_.points[arcFrom_];
  const double nx = -dir->second, ny = dir->first;          // left normal
  const double ex = x - s.x, ey = y - s.y;
  const double den = 2 * (ex * nx + ey * ny);
  if (std::abs(den) < 1e-9 || std::hypot(ex, ey) < tolerance() / 2) return false;
  const double rs = (ex * ex + ey * ey) / den;               // signed: left (+) or right (-)
  cx = s.x + nx * rs;
  cy = s.y + ny * rs;
  r = std::abs(rs);
  ccw = rs > 0;
  return r < 1e6;
}

void SketchEditor::finishArcDrag(double x, double y) {
  arcDrag_ = false;
  const bool endsChain = arcEndsChain_;
  arcEndsChain_ = false;
  if (endsChain && !arcDragMoved_) {   // a plain double-click on the end: done with this chain
    resetSteps();
    rebuild();
    return;
  }
  double cx, cy, r;
  bool ccw;
  const Pick end = pickPoint(x, y, arcFrom_);
  if (!arcDragMoved_ || !tangentArc(end.x, end.y, cx, cy, r, ccw)) {
    updatePreview(x, y);
    return;
  }
  checkpoint();
  const int e = materialize(end);
  const int c = sk_.addPoint(cx, cy);
  const int arc = ccw ? sk_.addArc(c, arcFrom_, e, construction_) : sk_.addArc(c, e, arcFrom_, construction_);
  (void)sketch::addConstraintChecked(sk_, {ConstraintType::Tangent, {}, {arcRef_, arc}});
  clearHud();
  solveAndShow();
  if (!res_.ok) {
    undo();
    return;
  }
  // The line chain carries on from the end of the arc.
  steps_ = {Pick{{Hit::Point, e}, sk_.points[e].x, sk_.points[e].y}};
  emit message(tr("Tangent arc added. Keep clicking for lines, or drag from the end again for another arc."));
}

bool SketchEditor::dragTangentArcForTest(double x, double y) {
  if (tool_ != Tool::Line || steps_.empty() || steps_.back().hit.kind != Hit::Point) return false;
  arcFrom_ = steps_.back().hit.index;
  arcRef_ = curveEndingAt(arcFrom_);
  if (arcRef_ < 0) return false;
  const size_t before = sk_.entities.size();
  arcDrag_ = arcDragMoved_ = true;
  finishArcDrag(x, y);
  return sk_.entities.size() > before;
}

void SketchEditor::collectBodyEdges() {
  bodyEdges_ = {};
  const gp_Pln pln(frame_);
  auto inPlane = [&](const gp_Pnt& p) { return pln.Distance(p) < 1e-6; };
  for (const auto& b : session_.document().bodies()) {
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(b.shape, TopAbs_EDGE, edges);
    for (int i = 1; i <= edges.Extent(); ++i) {
      const TopoDS_Edge e = TopoDS::Edge(edges(i));
      if (BRep_Tool::Degenerated(e)) continue;
      BRepAdaptor_Curve c(e);
      const double t0 = c.FirstParameter(), t1 = c.LastParameter();
      const gp_Pnt p0 = c.Value(t0), p1 = c.Value(t1), pm = c.Value((t0 + t1) / 2);
      if (!inPlane(p0) || !inPlane(p1) || !inPlane(pm)) continue;
      double x0, y0, x1, y1;
      sketch::toSketch(frame_, p0, x0, y0);
      sketch::toSketch(frame_, p1, x1, y1);
      if (c.GetType() == GeomAbs_Line) {
        bodyEdges_.segments.push_back({x0, y0, x1, y1});
      } else if (c.GetType() == GeomAbs_Circle) {
        const gp_Circ circ = c.Circle();
        double cx, cy;
        sketch::toSketch(frame_, circ.Location(), cx, cy);
        const bool full = p0.Distance(p1) < 1e-7;
        double a0 = std::atan2(y0 - cy, x0 - cx), am = 0, xm, ym;
        sketch::toSketch(frame_, pm, xm, ym);
        am = std::atan2(ym - cy, xm - cx);
        // Sweep from the start through the middle point.
        double sweep = 2 * kPi;
        if (!full) {
          const double a1 = std::atan2(y1 - cy, x1 - cx);
          double s1 = a1 - a0, sm = am - a0;
          while (s1 <= 0) s1 += 2 * kPi;
          while (sm <= 0) sm += 2 * kPi;
          sweep = sm < s1 ? s1 : s1 - 2 * kPi;
        }
        bodyEdges_.arcs.push_back({cx, cy, circ.Radius(), a0, sweep});
        bodyEdges_.vertices.emplace_back(cx, cy);   // centres snap too
      } else {
        continue;
      }
      bodyEdges_.vertices.emplace_back(x0, y0);
      bodyEdges_.vertices.emplace_back(x1, y1);
    }
  }
}

// Holding Ctrl while sketching turns off snapping and automatic constraints.
bool SketchEditor::snapsSuppressed() { return QGuiApplication::keyboardModifiers() & Qt::ControlModifier; }

SketchEditor::Snap SketchEditor::snapAt(double x, double y, int exclude) const {
  Snap s;
  s.x = x;
  s.y = y;
  if (snapsSuppressed()) return s;
  const double tol = tolerance();
  // 1. Existing sketch points (ends, centres, the origin).
  if (const int p = snapPoint(x, y, exclude); p >= 0) {
    s.kind = Snap::Point;
    s.point = p;
    s.x = sk_.points[p].x;
    s.y = sk_.points[p].y;
    return s;
  }
  // 2. Line midpoints.
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    if (e.type != EntityType::Line || e.a == exclude || e.b == exclude) continue;
    const double mx = (sk_.points[e.a].x + sk_.points[e.b].x) / 2, my = (sk_.points[e.a].y + sk_.points[e.b].y) / 2;
    if (std::hypot(mx - x, my - y) < tol) {
      s.kind = Snap::Midpoint;
      s.entity = i;
      s.x = mx;
      s.y = my;
      return s;
    }
  }
  // 3. Body vertices lying in the sketch plane.
  for (const auto& [vx, vy] : bodyEdges_.vertices)
    if (std::hypot(vx - x, vy - y) < tol) {
      s.kind = Snap::BodyVertex;
      s.x = vx;
      s.y = vy;
      return s;
    }
  // 4. On a sketch curve (nearest point).
  double best = tol;
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    if (e.type == EntityType::Spline || e.a == exclude || e.b == exclude) continue;
    double px, py;
    if (e.type == EntityType::Ellipse) {
      // The nearest point of the outline (finely sampled, then projected).
      const auto pts = curveSamples(i);
      double bd = 1e300;
      px = py = 0;
      for (size_t k = 1; k < pts.size(); ++k) {
        const double ax = pts[k - 1].first, ay = pts[k - 1].second;
        const double dx = pts[k].first - ax, dy = pts[k].second - ay, l2 = dx * dx + dy * dy;
        const double t = l2 > 0 ? std::clamp(((x - ax) * dx + (y - ay) * dy) / l2, 0.0, 1.0) : 0;
        const double qx = ax + t * dx, qy = ay + t * dy, dd = std::hypot(qx - x, qy - y);
        if (dd < bd) bd = dd, px = qx, py = qy;
      }
      if (pts.empty()) continue;
    } else if (e.type == EntityType::Line) {
      const auto &a = sk_.points[e.a], &b = sk_.points[e.b];
      const double dx = b.x - a.x, dy = b.y - a.y, l2 = dx * dx + dy * dy;
      if (l2 < 1e-18) continue;
      const double t = std::clamp(((x - a.x) * dx + (y - a.y) * dy) / l2, 0.0, 1.0);
      px = a.x + t * dx;
      py = a.y + t * dy;
    } else {
      const auto& c = sk_.points[e.center];
      const double d = std::hypot(x - c.x, y - c.y);
      if (d < 1e-12) continue;
      px = c.x + (x - c.x) / d * e.radius;
      py = c.y + (y - c.y) / d * e.radius;
      if (e.type == EntityType::Arc) {
        const auto &st = sk_.points[e.a], &en = sk_.points[e.b];
        if (!angleInArc(std::atan2(py - c.y, px - c.x), std::atan2(st.y - c.y, st.x - c.x), std::atan2(en.y - c.y, en.x - c.x)))
          continue;
      }
    }
    const double d = std::hypot(px - x, py - y);
    if (d < best) {
      best = d;
      s.kind = Snap::OnCurve;
      s.entity = i;
      s.x = px;
      s.y = py;
    }
  }
  if (s.kind == Snap::OnCurve) return s;
  // 5. On a body edge lying in the sketch plane.
  for (int k = 0; k < static_cast<int>(bodyEdges_.segments.size()); ++k) {
    const auto& g = bodyEdges_.segments[k];
    const double dx = g[2] - g[0], dy = g[3] - g[1], l2 = dx * dx + dy * dy;
    if (l2 < 1e-18) continue;
    const double t = std::clamp(((x - g[0]) * dx + (y - g[1]) * dy) / l2, 0.0, 1.0);
    const double px = g[0] + t * dx, py = g[1] + t * dy, d = std::hypot(px - x, py - y);
    if (d < best) {
      best = d;
      s.kind = Snap::BodyEdge;
      s.bodySegment = k;
      s.x = px;
      s.y = py;
    }
  }
  for (const auto& g : bodyEdges_.arcs) {
    const double d0 = std::hypot(x - g[0], y - g[1]);
    if (d0 < 1e-12) continue;
    double ang = std::atan2(y - g[1], x - g[0]) - g[3];
    if (g[4] > 0) { while (ang < 0) ang += 2 * kPi; if (ang > g[4] + 1e-9) continue; }
    else { while (ang > 0) ang -= 2 * kPi; if (ang < g[4] - 1e-9) continue; }
    const double d = std::abs(d0 - g[2]);
    if (d < best) {
      best = d;
      s.kind = Snap::BodyEdge;
      s.bodySegment = -1;
      s.bodyArc = static_cast<int>(&g - bodyEdges_.arcs.data());
      s.x = g[0] + (x - g[0]) / d0 * g[2];
      s.y = g[1] + (y - g[1]) / d0 * g[2];
    }
  }
  if (s.kind == Snap::BodyEdge) return s;
  // 6. Inference: horizontal / vertical from the previous point (lines),
  //    then lined up with any other point. Each axis snaps on its own.
  // 6a. Lines leaving the end of a curve: tangent (straight on) or perpendicular to it.
  if (!steps_.empty() && tool_ == Tool::Line && steps_.back().hit.kind == Hit::Point) {
    const int from = steps_.back().hit.index;
    const int ref = curveEndingAt(from);
    if (const auto dir = leavingDirection(ref, from)) {
      const auto& o = sk_.points[from];
      const double vx = x - o.x, vy = y - o.y, len = std::hypot(vx, vy);
      if (len > tol * 2) {
        const double ux = dir->first, uy = dir->second;
        const std::pair<double, double> cands[] = {{ux, uy}, {-uy, ux}, {uy, -ux}};
        for (int k = 0; k < 3; ++k) {
          const auto [cx, cy] = cands[k];
          const double along = vx * cx + vy * cy;
          if (along <= 0) continue;
          if (std::abs(vx * cy - vy * cx) < tol) {   // within the snap distance of that direction
            s.x = o.x + cx * along;
            s.y = o.y + cy * along;
            s.reference = ref;
            (k == 0 ? s.tangent : s.perpendicular) = true;
            s.fromX = o.x;
            s.fromY = o.y;
            return s;
          }
        }
      }
    }
  }
  bool snappedX = false, snappedY = false;
  if (!steps_.empty() && (tool_ == Tool::Line || tool_ == Tool::Spline)) {
    const Pick& from = steps_.back();
    s.fromX = from.x;
    s.fromY = from.y;
    if (std::abs(y - from.y) < tol && std::abs(x - from.x) > tol) {
      s.y = from.y;
      s.horizontal = snappedY = true;
    } else if (std::abs(x - from.x) < tol && std::abs(y - from.y) > tol) {
      s.x = from.x;
      s.vertical = snappedX = true;
    }
  }
  // 6b. Parallel or perpendicular to another line in the sketch.
  if (!steps_.empty() && tool_ == Tool::Line && !s.horizontal && !s.vertical) {
    const Pick& from = steps_.back();
    const double vx = x - from.x, vy = y - from.y, len = std::hypot(vx, vy);
    if (len > tol * 2) {
      double bestDev = tol;
      for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
        const auto& e = sk_.entities[i];
        if (e.type != EntityType::Line || e.construction) continue;
        if (from.hit.kind == Hit::Point && (e.a == from.hit.index || e.b == from.hit.index)) continue;
        const auto &a = sk_.points[e.a], &b = sk_.points[e.b];
        const double l = std::hypot(b.x - a.x, b.y - a.y);
        if (l < 1e-12) continue;
        const double ux = (b.x - a.x) / l, uy = (b.y - a.y) / l;
        // Horizontal and vertical lines are covered by H/V above.
        if (std::abs(ux) < 1e-9 || std::abs(uy) < 1e-9) continue;
        for (int k = 0; k < 2; ++k) {
          const double cx = k == 0 ? ux : -uy, cy = k == 0 ? uy : ux;
          const double along = vx * cx + vy * cy;
          const double dev = std::abs(vx * cy - vy * cx);
          if (dev < bestDev) {
            bestDev = dev;
            s.x = from.x + cx * along;
            s.y = from.y + cy * along;
            s.reference = i;
            s.parallel = k == 0;
            s.perpendicular = k == 1;
            s.fromX = from.x;
            s.fromY = from.y;
          }
        }
      }
      if (s.reference >= 0) return s;
    }
  }
  double bx = tol, by = tol;
  for (int i = 0; i < static_cast<int>(sk_.points.size()); ++i) {
    if (i == exclude) continue;
    const auto& p = sk_.points[i];
    if (!snappedX && std::abs(p.x - x) < bx) {
      bx = std::abs(p.x - x);
      s.alignX = i;
    }
    if (!snappedY && std::abs(p.y - y) < by) {
      by = std::abs(p.y - y);
      s.alignY = i;
    }
  }
  if (s.alignX >= 0) {
    s.x = sk_.points[s.alignX].x;
    snappedX = true;
  }
  if (s.alignY >= 0) {
    s.y = sk_.points[s.alignY].y;
    snappedY = true;
  }
  // 7. The grid, for whatever is still free.
  if (view_ && view_->gridSnap() && view_->gridSpacing() > 0) {
    const double g = view_->gridSpacing();
    if (!snappedX) s.x = std::round(x / g) * g;
    if (!snappedY) s.y = std::round(y / g) * g;
    if (!snappedX || !snappedY) s.kind = Snap::Grid;
  }
  return s;
}

void SketchEditor::showSnap(const Snap& s) {
  if (!view_) return;
  const auto& ctx = view_->aisContext();
  if (ctx.IsNull()) return;
  const double px = view_->modelPerPixel();
  // Inference lines, dashed as in the familiar sketcher: from the previous
  // point (H/V, perpendicular, parallel) and from points lined up with the
  // cursor, however far away.
  sketch::Sketch guides;
  if (s.horizontal || s.vertical || s.tangent || s.perpendicular || s.parallel) guides.addLine(s.fromX, s.fromY, s.x, s.y);
  // Highlight the line the new one is parallel / perpendicular to.
  if ((s.parallel || s.perpendicular) && s.reference >= 0 && sk_.entities[s.reference].type == EntityType::Line &&
      !(s.tangent)) {
    const auto& e = sk_.entities[s.reference];
    guides.addLine(sk_.points[e.a].x, sk_.points[e.a].y, sk_.points[e.b].x, sk_.points[e.b].y);
  }
  if (s.alignX >= 0) guides.addLine(sk_.points[s.alignX].x, sk_.points[s.alignX].y, s.x, s.y);
  if (s.alignY >= 0) guides.addLine(sk_.points[s.alignY].x, sk_.points[s.alignY].y, s.x, s.y);
  const TopoDS_Shape gs = sketch::curves(guides, frame_, false);
  if (!gs.IsNull() && TopExp_Explorer(gs, TopAbs_EDGE).More()) {
    Handle(AIS_Shape) g = wire(gs, Quantity_Color(0.55, 0.85, 0.22, Quantity_TOC_sRGB), 1.0, Aspect_TOL_DASH);
    ctx->Display(g, AIS_WireFrame, -1, false);
    ctx->SetZLayer(g, Graphic3d_ZLayerId_Topmost);
    preview_.push_back(g);
  }
  // A marker where the cursor will land, and what it snapped to.
  QString glyph;
  switch (s.kind) {
    case Snap::Point: glyph = QStringLiteral("■"); break;           // black square: on a point
    case Snap::Midpoint: glyph = QStringLiteral("△"); break;        // triangle: midpoint
    case Snap::OnCurve: glyph = QStringLiteral("○"); break;         // circle: on the curve
    case Snap::BodyVertex: glyph = QStringLiteral("◆"); break;      // diamond: body vertex
    case Snap::BodyEdge: glyph = QStringLiteral("◇"); break;        // hollow diamond: body edge
    default: break;
  }
  // On an origin axis: the on-curve glyph (the point will stay on the axis).
  if (glyph.isEmpty() && (s.kind == Snap::Free || s.kind == Snap::Grid) && (s.alignX == 0 || s.alignY == 0))
    glyph = QStringLiteral("○");
  if (s.horizontal) glyph += QStringLiteral(" H");
  if (s.vertical) glyph += QStringLiteral(" V");
  if (s.perpendicular) glyph += QStringLiteral(" \u27C2");   // perpendicular
  if (s.tangent) glyph += QStringLiteral(" T");
  if (s.parallel) glyph += QStringLiteral(" \u2225");   // parallel
  if (s.kind == Snap::Free || s.kind == Snap::Grid) {
    if (glyph.isEmpty() && s.alignX < 0 && s.alignY < 0 && s.kind == Snap::Free) return;
  }
  Handle(AIS_Point) m = new AIS_Point(new Geom_CartesianPoint(sketch::toWorld(frame_, s.x, s.y)));
  const Quantity_Color c = s.kind == Snap::Free || s.kind == Snap::Grid ? kPreview : kHover;
  m->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_O_POINT, c, 2.0));
  ctx->Display(m, 0, -1, false);
  ctx->SetZLayer(m, Graphic3d_ZLayerId_Topmost);
  preview_.push_back(m);
  if (!glyph.isEmpty()) {
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(ext(glyph));
    t->SetPosition(sketch::toWorld(frame_, s.x + px * 12, s.y + px * 12));
    t->SetHeight(13);
    t->SetColor(kHover);
    ctx->Display(t, 0, -1, false);
    ctx->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
    preview_.push_back(t);
  }
}

SketchEditor::Hit SketchEditor::hitEntity(double x, double y) const {
  Hit best;
  double bestD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    double d = 1e300;
    if (e.type == EntityType::Line) {
      const auto& a = sk_.points[e.a];
      const auto& b = sk_.points[e.b];
      d = segDistance(x, y, a.x, a.y, b.x, b.y);
    } else if (e.type == EntityType::Spline || e.type == EntityType::Ellipse) {
      d = entityDistance(i, x, y);
    } else {
      const auto& c = sk_.points[e.center];
      d = std::abs(std::hypot(x - c.x, y - c.y) - e.radius);
      if (e.type == EntityType::Arc) {
        const double a = std::atan2(y - c.y, x - c.x);
        const auto& s = sk_.points[e.a];
        const auto& t = sk_.points[e.b];
        if (!angleInArc(a, std::atan2(s.y - c.y, s.x - c.x), std::atan2(t.y - c.y, t.x - c.x))) d = 1e300;
      }
    }
    if (d < bestD) {
      bestD = d;
      best = {Hit::Entity, i};
    }
  }
  return best;
}

SketchEditor::Hit SketchEditor::hitTest(double x, double y, bool pointsFirst) const {
  if (pointsFirst) {
    const int p = snapPoint(x, y);
    if (p >= 0) return {Hit::Point, p};
  }
  // Labels and curves: whichever is nearer wins, so a glyph next to a line
  // does not steal clicks meant for the line.
  Hit label;
  double labelD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i)
    if (auto a = labelAnchor(i)) {
      // Hidden labels (Sketch Palette) cannot be clicked.
      if (sketch::isDimension(sk_.constraints[i].type) ? !display_.dimensions : !display_.constraints) continue;
      if (onlyProjected(sk_.constraints[i])) continue;
      const double d = std::hypot(a->first - x, a->second - y);
      if (d < labelD) {
        labelD = d;
        label = {Hit::Label, i};
      }
    }
  const Hit e = hitEntity(x, y);
  if (e.kind != Hit::None) {
    const double ed = entityDistance(e.index, x, y);
    if (label.kind == Hit::None || ed <= labelD) return e;
  }
  if (label.kind != Hit::None) return label;
  if (!pointsFirst) {
    const int p = snapPoint(x, y);
    if (p >= 0) return {Hit::Point, p};
  }
  return {};
}

// ---------------------------------------------------------------------------
// Mouse

void SketchEditor::mousePress(QMouseEvent* e) {
  pressPos_ = e->position();
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  // Line tool: pressing on the chain's last point and dragging draws a
  // tangent arc (release ends it); a plain click there does nothing.
  if (tool_ == Tool::Line && !steps_.empty() && steps_.back().hit.kind == Hit::Point &&
      snapPoint(x, y) == steps_.back().hit.index) {
    arcFrom_ = steps_.back().hit.index;
    arcRef_ = curveEndingAt(arcFrom_);
    if (arcRef_ >= 0) {
      arcDrag_ = true;
      arcDragMoved_ = false;
      arcEndsChain_ = false;
      clearHud();
      return;
    }
  }
  press(x, y, e->modifiers(), e->position());
}

void SketchEditor::clickAt(double x, double y) {
  press(x, y, Qt::NoModifier, QPointF(60, 60));
  if (tool_ == Tool::Select) {
    dragged_ = false;
    const Hit h = hitTest(x, y);
    selection_.clear();
    if (h.kind != Hit::None) selection_.push_back(h);
    dragPoint_ = dragLine_ = -1;
    dragHandle_ = {};
    rebuild();
  }
}

void SketchEditor::press(double x, double y, Qt::KeyboardModifiers, const QPointF& widgetPos) {
  // Typed sizes override the cursor (the cursor still gives the direction).
  const bool locked = hudTool() && !steps_.empty() && hudAnyLocked();
  if (hudTool() && !steps_.empty()) {
    std::tie(x, y) = hudTarget(x, y);
    // The click lands where the preview showed it: snapped like the cursor
    // (unless a size was typed), so a circle's radius follows the grid too.
    // (Line and Rectangle snap their own clicks.)
    if (!locked && (tool_ == Tool::Circle || tool_ == Tool::CenterRectangle || tool_ == Tool::Polygon ||
                    tool_ == Tool::Slot)) {
      const Pick snap = pickPoint(x, y);
      x = snap.x;
      y = snap.y;
    }
  }
  auto exact = [&](double px, double py, int exclude = -1) {
    return locked ? Pick{{}, px, py} : pickPoint(px, py, exclude);
  };
  switch (tool_) {
    case Tool::Select: {
      // A tangent handle's end: drag it to set the handle.
      dragHandle_ = handleAt(x, y);
      if (dragHandle_.spline >= 0) {
        dragged_ = false;
        boxing_ = boxShown_ = false;
        dragPoint_ = dragLine_ = dragLabel_ = -1;
        return;
      }
      const Hit h = hitTest(x, y);
      dragged_ = false;
      boxing_ = h.kind == Hit::None;
      boxShown_ = false;
      dragX_ = x;
      dragY_ = y;
      dragPoint_ = (h.kind == Hit::Point && h.index > 0) ? h.index : -1;
      dragLine_ = (h.kind == Hit::Entity && sk_.entities[h.index].type == EntityType::Line) ? h.index : -1;
      dragLabel_ = (h.kind == Hit::Label && sketch::isDimension(sk_.constraints[h.index].type)) ? h.index : -1;
      return;
    }
    case Tool::Line: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      checkpoint();
      const bool lockLen = hudLocked(0);
      const double len = hudValue(0);
      const int a = materialize(steps_.back());
      const Pick end = exact(x, y, a);
      if (std::hypot(end.x - sk_.points[a].x, end.y - sk_.points[a].y) < tolerance() / 2) {
        undo_.pop_back();
        return;
      }
      const int b = materialize(end);
      if (chainStart_ < 0) chainStart_ = a;
      const int l = sk_.addLine(a, b, construction_);
      // Inferred relations first (they say more than horizontal/vertical).
      if (end.perpendicularTo >= 0)
        (void)sketch::addConstraintChecked(sk_, {ConstraintType::Perpendicular, {}, {end.perpendicularTo, l}});
      if (end.parallelTo >= 0)
        (void)sketch::addConstraintChecked(sk_, {ConstraintType::Parallel, {}, {end.parallelTo, l}});
      if (end.tangentTo >= 0 && end.tangentTo < static_cast<int>(sk_.entities.size()) &&
          sk_.entities[end.tangentTo].type == EntityType::Arc)
        (void)sketch::addConstraintChecked(sk_, {ConstraintType::Tangent, {}, {end.tangentTo, l}});
      autoHorizontalVertical(l);
      if (lockLen) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l}, len});
      const bool closed = end.hit.kind == Hit::Point && b == chainStart_;
      clearHud();
      solveAndShow();
      if (closed) {
        resetSteps();
      } else {
        steps_ = {Pick{{Hit::Point, b}, sk_.points[b].x, sk_.points[b].y}};
      }
      return;
    }
    case Tool::Rectangle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick a = steps_.front();
      const Pick c = exact(x, y);
      if (std::abs(c.x - a.x) < tolerance() / 2 || std::abs(c.y - a.y) < tolerance() / 2) return;
      const bool lockW = hudLocked(0), lockH = hudLocked(1);
      const double w = hudValue(0), h = hudValue(1);
      checkpoint();
      const int p0 = materialize(a);
      const int p2 = materialize(c);
      const int p1 = sk_.addPoint(sk_.points[p2].x, sk_.points[p0].y);
      const int p3 = sk_.addPoint(sk_.points[p0].x, sk_.points[p2].y);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
      for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l0}, w});
      if (lockH) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l1}, h});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::CenterRectangle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double hx = std::abs(x - c.x), hy = std::abs(y - c.y);
      if (hx < tolerance() / 4 || hy < tolerance() / 4) return;
      const bool lockW = hudLocked(0), lockH = hudLocked(1);
      const double w = hudValue(0), h = hudValue(1);
      checkpoint();
      const int pc = materialize(c);
      const double cx = sk_.points[pc].x, cy = sk_.points[pc].y;
      const int p0 = sk_.addPoint(cx - hx, cy - hy), p1 = sk_.addPoint(cx + hx, cy - hy);
      const int p2 = sk_.addPoint(cx + hx, cy + hy), p3 = sk_.addPoint(cx - hx, cy + hy);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      const int d0 = sk_.addLine(p0, p2, true);
      sk_.addLine(p1, p3, true);
      for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
      for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
      sk_.addConstraint({ConstraintType::Midpoint, {pc}, {d0}});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l0}, w});
      if (lockH) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l1}, h});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Polygon: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double r = std::hypot(x - c.x, y - c.y);
      if (r < tolerance() / 2) return;
      const int n = polygonSides();
      const bool lockD = hudLocked(0);
      const double d = hudValue(0);
      const double a0 = std::atan2(y - c.y, x - c.x);
      checkpoint();
      const int pc = materialize(c);
      const int circle = sk_.addCircleAt(pc, r, true);
      std::vector<int> pts, lines;
      for (int i = 0; i < n; ++i) {
        const double a = a0 + 2 * kPi * i / n;
        pts.push_back(sk_.addPoint(sk_.points[pc].x + r * std::cos(a), sk_.points[pc].y + r * std::sin(a)));
      }
      for (int i = 0; i < n; ++i) lines.push_back(sk_.addLine(pts[i], pts[(i + 1) % n], construction_));
      for (int p : pts) sk_.addConstraint({ConstraintType::PointOnEntity, {p}, {circle}});
      for (int i = 1; i < n; ++i) sk_.addConstraint({ConstraintType::Equal, {}, {lines[0], lines[i]}});
      if (lockD) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Diameter, {}, {circle}, d});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Slot: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c1 = steps_.front();
      const double len = std::hypot(x - c1.x, y - c1.y);
      if (len < tolerance() / 2) return;
      const bool lockL = hudLocked(0), lockW = hudLocked(1);
      const double width = lockW ? hudValue(1) : len / 3;
      const double r = width / 2;
      const double ux = (x - c1.x) / len, uy = (y - c1.y) / len, nx = -uy, ny = ux;
      checkpoint();
      const int pc1 = materialize(c1);
      const double x1 = sk_.points[pc1].x, y1 = sk_.points[pc1].y;
      const int pc2 = sk_.addPoint(x1 + ux * len, y1 + uy * len);
      const double x2 = sk_.points[pc2].x, y2 = sk_.points[pc2].y;
      const int a1 = sk_.addPoint(x1 + nx * r, y1 + ny * r), a2 = sk_.addPoint(x2 + nx * r, y2 + ny * r);
      const int b1 = sk_.addPoint(x1 - nx * r, y1 - ny * r), b2 = sk_.addPoint(x2 - nx * r, y2 - ny * r);
      const int la = sk_.addLine(a1, a2, construction_), lb = sk_.addLine(b2, b1, construction_);
      const int arc2 = sk_.addArc(pc2, b2, a2, construction_), arc1 = sk_.addArc(pc1, a1, b1, construction_);
      const int axis = sk_.addLine(pc1, pc2, true);
      for (int l : {la, lb})
        for (int arc : {arc1, arc2}) sk_.addConstraint({ConstraintType::Tangent, {}, {l, arc}});
      sk_.addConstraint({ConstraintType::Equal, {}, {arc1, arc2}});
      autoHorizontalVertical(axis);
      if (lockL) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {axis}, hudValue(0)});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Radius, {}, {arc1}, r});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Trim:
      trimAt(x, y);
      return;
    case Tool::Conic: {
      if (steps_.size() < 2) {
        if (!steps_.empty() && std::hypot(x - steps_[0].x, y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick v = pickPoint(x, y);
      const Pick s = steps_[0], e = steps_[1];
      // The vertex must stand off the chord.
      const double cross = (e.x - s.x) * (v.y - s.y) - (e.y - s.y) * (v.x - s.x);
      if (std::abs(cross) < 1e-9 * std::max(1.0, std::hypot(e.x - s.x, e.y - s.y))) {
        emit message(tr("The vertex must be off the line between the ends."));
        return;
      }
      checkpoint();
      const int ps = materialize(s), pe = materialize(e), pv = materialize(v);
      sk_.addConic(ps, pv, pe, 0.5, construction_);
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::ControlSpline:
    case Tool::Spline: {
      const Pick p = pickPoint(x, y);
      // Clicking the first point again closes the curve.
      if (tool_ == Tool::Spline && steps_.size() >= 3 &&
          std::hypot(p.x - steps_.front().x, p.y - steps_.front().y) < tolerance()) {
        finishSpline(true);
        return;
      }
      if (!steps_.empty() && std::hypot(p.x - steps_.back().x, p.y - steps_.back().y) < tolerance() / 4) return;
      steps_.push_back(p);
      updatePreview(x, y);
      return;
    }
    case Tool::Extend: {
      const Hit h = hitEntity(x, y);
      if (h.kind != Hit::Entity) return;
      checkpoint();
      const std::string err = sketch::extendLine(sk_, h.index, x, y);
      if (!err.empty()) {
        undo_.pop_back();
        emit message(QString::fromStdString(err));
        return;
      }
      solveAndShow();
      return;
    }
    case Tool::Mirror:
      mirrorPick(x, y);
      return;
    case Tool::Fillet:
    case Tool::Chamfer: {
      if (steps_.empty()) {
        const Hit h = hitTest(x, y);
        std::optional<std::pair<int, int>> corner;
        if (h.kind == Hit::Point) {
          corner = sketch::cornerAt(sk_, h.index);
        } else if (h.kind == Hit::Entity && sk_.entities[h.index].type == EntityType::Line) {
          if (firstFilletLine_ < 0 || firstFilletLine_ == h.index) {
            firstFilletLine_ = h.index;
            emit message(tr("Fillet: click the second line."));
            return;
          }
          corner = std::make_pair(firstFilletLine_, h.index);
        }
        if (!corner) {
          emit message(tr("Fillet: click a corner where two lines meet, or two lines."));
          return;
        }
        // The corner point, for the live radius and the box.
        const auto& la = sk_.entities[corner->first];
        const auto& lb = sk_.entities[corner->second];
        int cp = -1;
        for (int pa : {la.a, la.b})
          for (int pb : {lb.a, lb.b})
            if (cp < 0 && std::hypot(sk_.points[pa].x - sk_.points[pb].x, sk_.points[pa].y - sk_.points[pb].y) < 1e-6) cp = pa;
        if (cp < 0) {
          firstFilletLine_ = -1;
          emit message(tr("Fillet: those lines do not meet at a corner."));
          return;
        }
        filletLines_ = *corner;
        steps_.push_back(Pick{{Hit::Point, cp}, sk_.points[cp].x, sk_.points[cp].y});
        updatePreview(x, y);
        return;
      }
      const double r = hudLocked(0) ? hudValue(0) : filletRadiusAt(x, y);
      checkpoint();
      const std::string err = tool_ == Tool::Chamfer
                                  ? sketch::chamferCorner(sk_, filletLines_.first, filletLines_.second, r)
                                  : sketch::filletCorner(sk_, filletLines_.first, filletLines_.second, r);
      resetSteps();
      if (!err.empty()) {
        undo_.pop_back();
        emit message(QString::fromStdString(err));
        rebuild();
        return;
      }
      solveAndShow();
      return;
    }
    case Tool::Offset: {
      if (steps_.empty()) {
        const Hit h = hitEntity(x, y);
        const bool curve = h.kind == Hit::Entity && (sk_.entities[h.index].type == EntityType::Spline ||
                                                     sk_.entities[h.index].type == EntityType::Ellipse);
        if (h.kind != Hit::Entity || (!curve && sketch::chainOf(sk_, h.index).empty())) {
          emit message(tr("Offset: click a line, arc, circle, ellipse or spline."));
          return;
        }
        offsetEntity_ = h.index;
        steps_.push_back(Pick{h, x, y});
        updatePreview(x, y);
        return;
      }
      const double d = offsetAt(x, y, hudLocked(0) ? hudValue(0) : 0);
      checkpoint();
      const std::string err = sketch::offsetChain(sk_, offsetEntity_, d);
      resetSteps();
      if (!err.empty()) {
        undo_.pop_back();
        emit message(QString::fromStdString(err));
        rebuild();
        return;
      }
      solveAndShow();
      return;
    }
    case Tool::Circle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double r = std::hypot(x - c.x, y - c.y);
      if (r < tolerance() / 2) return;
      const bool lockD = hudLocked(0);
      checkpoint();
      const int circle = sk_.addCircleAt(materialize(c), r, construction_);
      if (lockD) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Diameter, {}, {circle}, hudValue(0)});
      resetSteps();
      solveAndShow();
      return;
    }
    case Tool::Arc: {
      if (steps_.size() < 2) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_[0], s = steps_[1];
      const double r = std::hypot(s.x - c.x, s.y - c.y);
      if (r < tolerance() / 2) {
        resetSteps();
        return;
      }
      // The end lies on the circle through the start.
      const double a = std::atan2(y - c.y, x - c.x);
      Pick end = pickPoint(c.x + r * std::cos(a), c.y + r * std::sin(a));
      checkpoint();
      const int pc = materialize(c), ps = materialize(s), pe = materialize(end);
      if (pe == ps) {
        undo_.pop_back();
        return;
      }
      sk_.addArc(pc, ps, pe, construction_);
      resetSteps();
      solveAndShow();
      return;
    }
    case Tool::ThreePointRectangle: {
      if (steps_.size() < 2) {
        if (!steps_.empty() && std::hypot(x - steps_[0].x, y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick a = steps_[0], b = steps_[1];
      const double len = std::hypot(b.x - a.x, b.y - a.y);
      if (len < 1e-12) return resetSteps();
      const Pick wpick = pickPoint(x, y);   // the width click snaps like the others
      x = wpick.x;
      y = wpick.y;
      // The width: how far the third click is across the first side.
      const double nx = -(b.y - a.y) / len, ny = (b.x - a.x) / len;
      const double h = (x - a.x) * nx + (y - a.y) * ny;
      if (std::abs(h) < tolerance() / 2) return;
      checkpoint();
      const int p0 = materialize(a), p1 = materialize(b);
      const int p2 = sk_.addPoint(sk_.points[p1].x + nx * h, sk_.points[p1].y + ny * h);
      const int p3 = sk_.addPoint(sk_.points[p0].x + nx * h, sk_.points[p0].y + ny * h);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      sk_.addConstraint({ConstraintType::Perpendicular, {}, {l0, l1}});
      sk_.addConstraint({ConstraintType::Parallel, {}, {l0, l2}});
      sk_.addConstraint({ConstraintType::Parallel, {}, {l1, l3}});
      autoHorizontalVertical(l0);   // a level or upright first side stays so
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::TwoPointCircle:
    case Tool::ThreePointCircle: {
      const size_t need = tool_ == Tool::TwoPointCircle ? 1 : 2;
      if (steps_.size() < need) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick last = pickPoint(x, y);
      double cx, cy, r;
      if (tool_ == Tool::TwoPointCircle) {
        cx = (steps_[0].x + last.x) / 2, cy = (steps_[0].y + last.y) / 2;
        r = std::hypot(last.x - steps_[0].x, last.y - steps_[0].y) / 2;
      } else if (!circumcircle(steps_[0].x, steps_[0].y, steps_[1].x, steps_[1].y, last.x, last.y, cx, cy, r)) {
        emit message(tr("Those three points are in line: pick a point off the line."));
        return;
      }
      if (r < tolerance() / 4) return;
      checkpoint();
      const int circle = sk_.addCircleAt(sk_.addPoint(cx, cy), r, construction_);
      // Picks on existing geometry stay on the circle (as the clicks were).
      std::vector<Pick> picks = steps_;
      picks.push_back(last);
      for (const Pick& p : picks)
        if (p.hit.kind == Hit::Point || p.onEntity >= 0 || p.midpointOf >= 0 || p.bodyPoint || p.bodySegment >= 0 ||
            p.bodyArc >= 0 || p.onXAxis || p.onYAxis)
          (void)sketch::addConstraintChecked(sk_, {ConstraintType::PointOnEntity, {materialize(p)}, {circle}});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::TangentArc: {
      // First click: the open end of a line or arc; the arc leaves it tangent.
      if (steps_.empty()) {
        const Pick p = pickPoint(x, y);
        const int ref = p.hit.kind == Hit::Point ? curveEndingAt(p.hit.index) : -1;
        if (ref < 0) {
          emit message(tr("Tangent Arc: click the free end of a line or arc."));
          return;
        }
        arcFrom_ = p.hit.index;
        arcRef_ = ref;
        steps_.push_back(p);
        return;
      }
      const Pick end = pickPoint(x, y, arcFrom_);
      double cx, cy, r;
      bool ccw;
      if (!tangentArc(end.x, end.y, cx, cy, r, ccw)) {
        emit message(tr("The arc's end must be off the tangent line."));
        return;
      }
      checkpoint();
      const int e = materialize(end);
      const int c = sk_.addPoint(cx, cy);
      const int arc = ccw ? sk_.addArc(c, arcFrom_, e, construction_) : sk_.addArc(c, e, arcFrom_, construction_);
      (void)sketch::addConstraintChecked(sk_, {ConstraintType::Tangent, {}, {arcRef_, arc}});
      solveAndShow();
      if (!res_.ok) {
        undo();
        return;
      }
      // The next arc carries on, tangent to this one.
      arcFrom_ = e;
      arcRef_ = arc;
      steps_ = {Pick{{Hit::Point, e}, sk_.points[e].x, sk_.points[e].y}};
      return;
    }
    case Tool::ThreePointArc: {
      if (steps_.size() < 2) {
        if (!steps_.empty() && std::hypot(x - steps_[0].x, y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick s = steps_[0], e = steps_[1];
      const Pick m = pickPoint(x, y);   // the point it passes through snaps too
      x = m.x;
      y = m.y;
      double cx, cy, r;
      if (!circumcircle(s.x, s.y, e.x, e.y, x, y, cx, cy, r)) {
        emit message(tr("The arc needs a point off the line between its ends."));
        return;
      }
      checkpoint();
      const int ps = materialize(s), pe = materialize(e);
      const int pc = sk_.addPoint(cx, cy);
      // Arcs run counter-clockwise from start to end: the one through the
      // third point decides which way round.
      const double as = std::atan2(sk_.points[ps].y - cy, sk_.points[ps].x - cx);
      const double ae = std::atan2(sk_.points[pe].y - cy, sk_.points[pe].x - cx);
      const double am = std::atan2(y - cy, x - cx);
      if (ccwContains(as, ae, am)) sk_.addArc(pc, ps, pe, construction_);
      else sk_.addArc(pc, pe, ps, construction_);
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::TwoTangentCircle:
    case Tool::ThreeTangentCircle: {
      const size_t need = tool_ == Tool::TwoTangentCircle ? 2 : 3;
      if (tangentLines_.size() < need) {
        const Hit h = hitEntity(x, y);
        if (h.kind != Hit::Entity || sk_.entities[h.index].type != EntityType::Line ||
            std::find(tangentLines_.begin(), tangentLines_.end(), h.index) != tangentLines_.end()) {
          emit message(tr("Click a line."));
          return;
        }
        tangentLines_.push_back(h.index);
        tangentClicks_.emplace_back(x, y);
        if (tangentLines_.size() < need) {
          emit message(tr("Click another line."));
          rebuild();
          return;
        }
        if (need == 2) {
          emit message(tr("Place the circle (it stays tangent to both lines)."));
          rebuild();
          return;
        }
      }
      double cx, cy, r;
      if (!tangentCircle(x, y, cx, cy, r)) {
        emit message(tr("No circle touches those lines there."));
        if (need == 3) resetSteps();
        rebuild();
        return;
      }
      checkpoint();
      const int circle = sk_.addCircleAt(sk_.addPoint(cx, cy), r, construction_);
      for (int l : tangentLines_) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Tangent, {}, {l, circle}});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::OverallSlot: {
      if (steps_.size() < 2) {
        if (!steps_.empty() && std::hypot(x - steps_[0].x, y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick e1 = steps_[0], e2 = steps_[1];
      const Pick wp = pickPoint(x, y);
      const double len = std::hypot(e2.x - e1.x, e2.y - e1.y);
      const double ux = (e2.x - e1.x) / len, uy = (e2.y - e1.y) / len, nx = -uy, ny = ux;
      const double r = std::abs((wp.x - e1.x) * nx + (wp.y - e1.y) * ny);   // half the width
      if (r < tolerance() / 4 || 2 * r >= len) {
        emit message(tr("The width must be less than the slot's length."));
        return;
      }
      checkpoint();
      // The end centres sit half a width in from the overall ends.
      const double x1 = e1.x + ux * r, y1 = e1.y + uy * r, x2 = e2.x - ux * r, y2 = e2.y - uy * r;
      const int pc1 = sk_.addPoint(x1, y1), pc2 = sk_.addPoint(x2, y2);
      const int a1 = sk_.addPoint(x1 + nx * r, y1 + ny * r), a2 = sk_.addPoint(x2 + nx * r, y2 + ny * r);
      const int b1 = sk_.addPoint(x1 - nx * r, y1 - ny * r), b2 = sk_.addPoint(x2 - nx * r, y2 - ny * r);
      const int la = sk_.addLine(a1, a2, construction_), lb = sk_.addLine(b2, b1, construction_);
      const int arc2 = sk_.addArc(pc2, b2, a2, construction_), arc1 = sk_.addArc(pc1, a1, b1, construction_);
      const int axis = sk_.addLine(pc1, pc2, true);
      for (int l : {la, lb})
        for (int arc : {arc1, arc2}) sk_.addConstraint({ConstraintType::Tangent, {}, {l, arc}});
      sk_.addConstraint({ConstraintType::Equal, {}, {arc1, arc2}});
      autoHorizontalVertical(axis);
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::ArcSlot: {
      if (steps_.size() < 3) {
        const Pick p = pickPoint(x, y);
        if (!steps_.empty() && std::hypot(p.x - steps_[0].x, p.y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(p);
        return;
      }
      const Pick c = steps_[0], s = steps_[1], e = steps_[2];
      const Pick wp = pickPoint(x, y);
      const double R = std::hypot(s.x - c.x, s.y - c.y);
      const double w2 = std::abs(std::hypot(wp.x - c.x, wp.y - c.y) - R);   // half the width
      if (w2 < tolerance() / 4 || w2 >= R) {
        emit message(tr("The width must be less than twice the arc's radius."));
        return;
      }
      const double as = std::atan2(s.y - c.y, s.x - c.x), ae = std::atan2(e.y - c.y, e.x - c.x);
      if (std::abs(std::remainder(ae - as, 2 * std::numbers::pi)) < 1e-6) return;
      checkpoint();
      const int pc = materialize(c);
      const double ox = sk_.points[pc].x, oy = sk_.points[pc].y;
      auto at = [&](double rad, double ang) { return sk_.addPoint(ox + rad * std::cos(ang), oy + rad * std::sin(ang)); };
      // The slot runs counter-clockwise from the start to the end, as arcs do.
      const int ps = at(R, as), pe = at(R, ae);
      const int os = at(R + w2, as), oe = at(R + w2, ae), is = at(R - w2, as), ie = at(R - w2, ae);
      const int path = sk_.addArc(pc, ps, pe, true);
      const int outer = sk_.addArc(pc, os, oe, construction_);
      const int inner = sk_.addArc(pc, is, ie, construction_);
      // End caps: half circles round the path's ends, bulging outwards.
      const int capS = sk_.addArc(ps, is, os, construction_);
      const int capE = sk_.addArc(pe, oe, ie, construction_);
      (void)path;
      for (int cap : {capS, capE})
        for (int side : {outer, inner}) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Tangent, {}, {cap, side}});
      (void)sketch::addConstraintChecked(sk_, {ConstraintType::Equal, {}, {capS, capE}});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Ellipse: {
      if (steps_.size() < 2) {
        const Pick p = pickPoint(x, y);
        if (!steps_.empty() && std::hypot(p.x - steps_[0].x, p.y - steps_[0].y) < tolerance() / 2) return;
        steps_.push_back(p);
        return;
      }
      const Pick c = steps_[0], a = steps_[1];
      const Pick q = pickPoint(x, y);
      const double A = std::hypot(a.x - c.x, a.y - c.y);
      // The other half axis: how far the click is across the first axis.
      const double B = std::abs((q.x - c.x) * -(a.y - c.y) / A + (q.y - c.y) * (a.x - c.x) / A);
      if (B < tolerance() / 4) return;
      checkpoint();
      const int pc = materialize(c), pa = materialize(a);
      sk_.addEllipse(pc, pa, B, construction_);
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Text: {
      // A text already there: change it; else a new one standing on the click.
      if (const int ti = textAt(x, y); ti >= 0) {
        sketch::Text t = sk_.texts[ti];
        if (editText(t, false)) {
          checkpoint();
          sk_.texts[ti] = t;
          solveAndShow();
        }
        return;
      }
      // Two corners make a box (the text aligned in it); the same place
      // twice puts the text on that point.
      const Pick p = pickPoint(x, y);
      if (steps_.empty()) {
        steps_.push_back(p);
        return;
      }
      const Pick first = steps_[0];
      const bool box = std::hypot(p.x - first.x, p.y - first.y) > tolerance() / 2;
      resetSteps();
      sketch::Text t;
      if (box) t.corner = 0;   // tells the panel it is a box
      if (!editText(t, true)) {
        rebuild();
        return;
      }
      checkpoint();
      t.point = materialize(first);
      if (box) t.corner = materialize(p);
      sk_.texts.push_back(t);
      solveAndShow();
      return;
    }
    case Tool::TextOnPath: {
      const Hit h = hitEntity(x, y);
      if (h.kind != Hit::Entity) {
        emit message(tr("Text on Path: click a line, arc, circle or spline."));
        return;
      }
      sketch::Text t;
      t.path = h.index;
      if (!editText(t, true)) return;
      checkpoint();
      t.point = sk_.entityPoints(h.index).front();
      sk_.texts.push_back(t);
      solveAndShow();
      return;
    }
    case Tool::RectPattern:
    case Tool::CircPattern:
    case Tool::MoveCopy:
    case Tool::SketchScale:
      transformPick(x, y);
      return;
    case Tool::Break:
      trimAt(x, y, true);
      return;
    case Tool::Intersect:
      intersectAt(widgetPos);
      return;
    case Tool::Project:
      projectAt(widgetPos);
      return;
    case Tool::Include3D:
      includeAt(widgetPos);
      return;
    case Tool::Point: {
      const Pick p = pickPoint(x, y);
      if (p.hit.kind == Hit::Point) return;
      checkpoint();
      (void)materialize(p);
      solveAndShow();
      return;
    }
    case Tool::Dimension:
      dimensionPick(x, y, widgetPos);
      return;
    default:
      constraintPick(x, y);
      return;
  }
}

void SketchEditor::mouseMove(QMouseEvent* e) {
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  if (arcDrag_) {
    if ((e->position() - pressPos_).manhattanLength() >= 4) arcDragMoved_ = true;
    cursorX_ = x;
    cursorY_ = y;
    clearPreview();
    const Pick end = pickPoint(x, y, arcFrom_);
    showSnap(snapAt(x, y, arcFrom_));
    double cx, cy, r;
    bool ccw;
    if (arcDragMoved_ && tangentArc(end.x, end.y, cx, cy, r, ccw)) {
      sketch::Sketch tmp;
      const int c = tmp.addPoint(cx, cy);
      const int s = tmp.addPoint(sk_.points[arcFrom_].x, sk_.points[arcFrom_].y);
      const int t = tmp.addPoint(end.x, end.y);
      ccw ? tmp.addArc(c, s, t) : tmp.addArc(c, t, s);
      const TopoDS_Shape sh = sketch::curves(tmp, frame_, false);
      if (!sh.IsNull()) {
        Handle(AIS_Shape) w = wire(sh, kPreview, 1.5, Aspect_TOL_DASH);
        view_->aisContext()->Display(w, AIS_WireFrame, -1, false);
        view_->aisContext()->SetZLayer(w, Graphic3d_ZLayerId_Topmost);
        preview_.push_back(w);
        Handle(AIS_TextLabel) lb = new AIS_TextLabel();
        lb->SetText(ext(QStringLiteral("R ") + lengthText(r)));
        lb->SetPosition(sketch::toWorld(frame_, end.x, end.y + view_->modelPerPixel() * 18));
        lb->SetHeight(13);
        lb->SetColor(qc(themeColors().sketchLabel));
        view_->aisContext()->Display(lb, 0, -1, false);
        view_->aisContext()->SetZLayer(lb, Graphic3d_ZLayerId_Topmost);
        preview_.push_back(lb);
      }
    }
    view_->redraw();
    return;
  }
  if (tool_ == Tool::Select && boxing_ && (e->buttons() & Qt::LeftButton)) {
    if (boxShown_ || (e->position() - pressPos_).manhattanLength() >= 5) {
      boxShown_ = true;
      view_->showSelectionBox(pressPos_, e->position());
      return;
    }
  }
  if ((e->buttons() & Qt::LeftButton) && dragHandle_.spline >= 0 && tool_ == Tool::Select) {
    if (!dragged_) {
      if ((e->position() - pressPos_).manhattanLength() < 4) return;
      dragged_ = true;
      checkpoint();
    }
    moveHandle(dragHandle_, x, y);
    return;
  }
  if ((e->buttons() & Qt::LeftButton) && dragLabel_ >= 0 && tool_ == Tool::Select) {
    if (!dragged_) {
      if ((e->position() - pressPos_).manhattanLength() < 4) return;
      dragged_ = true;
      checkpoint();
    }
    // The value follows the cursor; the dimension line comes with it.
    Constraint& c = sk_.constraints[dragLabel_];
    const auto [bx, by] = dimensionBase(c);
    c.hasLabel = true;
    c.labelX = x - bx;
    c.labelY = y - by;
    rebuild();
    return;
  }
  if ((e->buttons() & Qt::LeftButton) && (dragPoint_ >= 0 || dragLine_ >= 0)) {
    if (!dragged_) {
      if ((e->position() - pressPos_).manhattanLength() < 4) return;
      dragged_ = true;
      checkpoint();
    }
    sketch::Sketch trial = sk_;
    std::vector<int> locked;
    if (dragPoint_ >= 0) {
      trial.points[dragPoint_] = {x, y};
      locked = {dragPoint_};
    } else {
      const auto& l = trial.entities[dragLine_];
      for (int p : {l.a, l.b})
        if (p > 0) {
          trial.points[p].x += x - dragX_;
          trial.points[p].y += y - dragY_;
          locked.push_back(p);
        }
    }
    // Locked points that the constraints do not let move: fall back to a
    // free solve so the sketch follows as far as it can.
    auto r = sketch::solve(trial, locked);
    if (!r.ok) {
      trial = sk_;
      if (dragPoint_ >= 0) trial.points[dragPoint_] = {x, y};
      r = sketch::solve(trial);
    }
    if (r.ok) {
      sk_ = std::move(trial);
      res_ = r;
      dragX_ = x;
      dragY_ = y;
      rebuild();
    }
    return;
  }
  cursorX_ = x;
  cursorY_ = y;
  const Hit h = hitTest(x, y);
  const bool changedHover = h.kind != hover_.kind || h.index != hover_.index;
  hover_ = h;
  if (changedHover && h.kind == Hit::Label && h.index < static_cast<int>(sk_.constraints.size())) {
    const auto& c = sk_.constraints[h.index];
    if (sketch::isDimension(c.type) && !c.name.empty()) {
      QString text = QString::fromStdString(c.name) + QStringLiteral(" = ");
      if (!c.expression.empty()) text += QString::fromStdString(c.expression) + QStringLiteral(" = ");
      emit message(text + labelText(c));
    }
  }
  updatePreview(x, y);
  if (changedHover) rebuild();
}

void SketchEditor::mouseRelease(QMouseEvent* e) {
  if (arcDrag_) {
    double x, y;
    if (toSketch(e->position(), x, y)) finishArcDrag(x, y);
    else arcDrag_ = false;
    return;
  }
  if (tool_ != Tool::Select) return;
  const bool box = boxing_ && boxShown_;
  boxing_ = boxShown_ = false;
  if (box) {
    view_->hideSelectionBox();
    selectInBox(pressPos_, e->position(), e->modifiers());
    return;
  }
  const bool wasDrag = dragged_;
  const bool wasLabel = dragLabel_ >= 0;
  const bool wasHandle = dragHandle_.spline >= 0;
  dragPoint_ = dragLine_ = dragLabel_ = -1;
  dragHandle_ = {};
  if (wasHandle && !wasDrag) return;   // a click on a handle keeps the selection (double-click frees it)
  if (wasDrag && wasLabel) {
    dragged_ = false;
    emit changed();
    rebuild();
    return;
  }
  dragged_ = false;
  if (wasDrag) {
    solveAndShow();
    return;
  }
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  const Hit h = hitTest(x, y);
  const bool add = e->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier);
  if (!add) selection_.clear();
  if (h.kind != Hit::None) {
    auto it = std::find_if(selection_.begin(), selection_.end(),
                           [&](const Hit& s) { return s.kind == h.kind && s.index == h.index; });
    if (it != selection_.end()) selection_.erase(it);
    else selection_.push_back(h);
  }
  rebuild();
}

// Window (left to right): curves and points wholly inside the box. Crossing
// (right to left): anything the box touches. Shift / Ctrl add to the selection.
void SketchEditor::selectInBox(const QPointF& from, const QPointF& to, Qt::KeyboardModifiers mods) {
  const QRectF box = QRectF(from, to).normalized();
  const bool crossing = to.x() < from.x();
  auto screen = [&](double x, double y) { return view_->toWidget(sketch::toWorld(frame_, x, y)); };
  // Does the segment p-q touch the box? (Liang-Barsky clip.)
  auto segmentHits = [&](QPointF p, QPointF q) {
    double t0 = 0, t1 = 1;
    const double dx = q.x() - p.x(), dy = q.y() - p.y();
    const double ps[4] = {-dx, dx, -dy, dy};
    const double qs[4] = {p.x() - box.left(), box.right() - p.x(), p.y() - box.top(), box.bottom() - p.y()};
    for (int i = 0; i < 4; ++i) {
      if (ps[i] == 0) {
        if (qs[i] < 0) return false;
        continue;
      }
      const double t = qs[i] / ps[i];
      if (ps[i] < 0) t0 = std::max(t0, t);
      else t1 = std::min(t1, t);
      if (t0 > t1) return false;
    }
    return true;
  };
  // A curve as a polyline in sketch coordinates.
  auto samples = [&](const sketch::Entity& en) {
    std::vector<std::pair<double, double>> out;
    const auto& pts = sk_.points;
    switch (en.type) {
      case EntityType::Line:
        out = {{pts[en.a].x, pts[en.a].y}, {pts[en.b].x, pts[en.b].y}};
        break;
      case EntityType::Circle: {
        const auto& c = pts[en.center];
        for (int k = 0; k <= 72; ++k) {
          const double t = 2 * std::numbers::pi * k / 72;
          out.emplace_back(c.x + en.radius * std::cos(t), c.y + en.radius * std::sin(t));
        }
        break;
      }
      case EntityType::Arc: {
        const auto& c = pts[en.center];
        const double r = std::hypot(pts[en.a].x - c.x, pts[en.a].y - c.y);
        const double s = std::atan2(pts[en.a].y - c.y, pts[en.a].x - c.x);
        double e = std::atan2(pts[en.b].y - c.y, pts[en.b].x - c.x);
        while (e <= s) e += 2 * std::numbers::pi;   // counter-clockwise from start to end
        for (int k = 0; k <= 48; ++k) {
          const double t = s + (e - s) * k / 48;
          out.emplace_back(c.x + r * std::cos(t), c.y + r * std::sin(t));
        }
        break;
      }
      case EntityType::Spline:
        for (int p : en.fit) out.emplace_back(pts[p].x, pts[p].y);
        break;
      case EntityType::Ellipse:
        out = curveSamples(static_cast<int>(&en - sk_.entities.data()));
        break;
    }
    return out;
  };
  std::vector<Hit> found;
  std::vector<bool> used(sk_.points.size(), false);
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& en = sk_.entities[i];
    for (int p : {en.a, en.b, en.center})
      if (p >= 0 && p < static_cast<int>(used.size())) used[p] = true;
    for (int p : en.fit)
      if (p >= 0 && p < static_cast<int>(used.size())) used[p] = true;
    const auto pts = samples(en);
    if (pts.empty()) continue;
    std::vector<QPointF> w;
    for (const auto& [x, y] : pts) w.push_back(screen(x, y));
    bool all = true, any = false;
    for (const QPointF& q : w) {
      const bool in = box.contains(q);
      all = all && in;
      any = any || in;
    }
    for (size_t k = 1; !any && crossing && k < w.size(); ++k) any = segmentHits(w[k - 1], w[k]);
    if (crossing ? any : all) found.push_back({Hit::Entity, i});
  }
  // Sketch points on their own (not the ends or centres of curves).
  for (int p = 1; p < static_cast<int>(sk_.points.size()); ++p)
    if (!used[p] && box.contains(screen(sk_.points[p].x, sk_.points[p].y))) found.push_back({Hit::Point, p});
  if (!(mods & (Qt::ShiftModifier | Qt::ControlModifier))) selection_.clear();
  for (const Hit& h : found)
    if (std::none_of(selection_.begin(), selection_.end(),
                     [&](const Hit& s) { return s.kind == h.kind && s.index == h.index; }))
      selection_.push_back(h);
  emit message(found.empty() ? tr("Nothing inside the box.")
                             : tr("%n item(s) selected.", nullptr, static_cast<int>(selection_.size())));
  rebuild();
}

int SketchEditor::textAt(double x, double y) const {
  for (int i = static_cast<int>(sk_.texts.size()) - 1; i >= 0; --i) {
    const TopoDS_Shape s = sketch::textShape(sk_, frame_, i);
    if (s.IsNull()) continue;
    // The letters' box in sketch coordinates, a little grown.
    double x0 = 1e300, y0 = 1e300, x1 = -1e300, y1 = -1e300;
    for (TopExp_Explorer v(s, TopAbs_VERTEX); v.More(); v.Next()) {
      double vx, vy;
      sketch::toSketch(frame_, BRep_Tool::Pnt(TopoDS::Vertex(v.Current())), vx, vy);
      x0 = std::min(x0, vx), y0 = std::min(y0, vy), x1 = std::max(x1, vx), y1 = std::max(y1, vy);
    }
    const double m = tolerance() / 2;
    if (x >= x0 - m && x <= x1 + m && y >= y0 - m && y <= y1 + m) return i;
  }
  return -1;
}

bool SketchEditor::editText(sketch::Text& t, bool isNew) {
  // A small panel, as the familiar TEXT command: the words, their height,
  // angle and font. Enter or OK makes it.
  static double lastHeight = 0.5;
  static QString lastFont;
  QDialog dlg(view_);
  dlg.setObjectName(QStringLiteral("sketchText"));
  dlg.setWindowTitle(tr("Text"));
  auto* form = new QFormLayout(&dlg);
  // Several lines in a box (Enter starts a new line; Tab moves on).
  auto* words = new QPlainTextEdit(isNew ? QString() : QString::fromStdString(t.text));
  words->setObjectName(QStringLiteral("textValue"));
  words->setTabChangesFocus(true);
  words->setFixedHeight(t.corner >= 0 ? 64 : 30);
  if (t.corner < 0) words->setLineWrapMode(QPlainTextEdit::NoWrap);
  const bool aligned = t.corner >= 0 || t.path >= 0;
  auto* hAlign = new QComboBox;
  hAlign->setObjectName(QStringLiteral("textHAlign"));
  hAlign->addItem(tr("Left"), QStringLiteral("left"));
  hAlign->addItem(tr("Center"), QStringLiteral("center"));
  hAlign->addItem(tr("Right"), QStringLiteral("right"));
  hAlign->setCurrentIndex(std::max(0, hAlign->findData(QString::fromStdString(t.hAlign))));
  auto* vAlign = new QComboBox;
  vAlign->setObjectName(QStringLiteral("textVAlign"));
  vAlign->addItem(tr("Top"), QStringLiteral("top"));
  vAlign->addItem(tr("Middle"), QStringLiteral("middle"));
  vAlign->addItem(tr("Bottom"), QStringLiteral("bottom"));
  vAlign->setCurrentIndex(std::max(0, vAlign->findData(QString::fromStdString(t.vAlign))));
  auto* flip = new QCheckBox(tr("Flip"));
  flip->setObjectName(QStringLiteral("textFlip"));
  flip->setToolTip(tr("Run the text from the other end, on the other side of the curve"));
  flip->setChecked(t.flip);
  auto* height = new QLineEdit(QString::number(fromInternal(isNew ? lastHeight : t.height, unit_), 'g', 6) +
                               QStringLiteral(" ") + QString::fromUtf8(unitSymbol(unit_).data()));
  height->setObjectName(QStringLiteral("textHeight"));
  ParameterCompleter::attach(height, [this] { return parameterNames(); });
  auto* angle = new QLineEdit(QString::number(isNew ? 0.0 : t.angle * 180 / std::numbers::pi, 'g', 6) + QStringLiteral(" deg"));
  angle->setObjectName(QStringLiteral("textAngle"));
  auto* font = new QComboBox;
  font->setObjectName(QStringLiteral("textFont"));
  font->setEditable(true);
  font->addItem(tr("(default sans-serif)"), QString());
  for (const QString& f : {QStringLiteral("serif"), QStringLiteral("monospace")}) font->addItem(f, f);
  for (const QString& f : QFontDatabase::families()) font->addItem(f, f);
  const QString current = isNew ? lastFont : QString::fromStdString(t.font);
  if (const int k = font->findData(current); k >= 0) font->setCurrentIndex(k);
  form->addRow(tr("Text"), words);
  form->addRow(tr("Height"), height);
  form->addRow(tr("Angle"), angle);
  form->addRow(tr("Font"), font);
  if (aligned) form->addRow(t.path >= 0 ? tr("Alignment") : tr("Horizontal"), hAlign);
  if (t.corner >= 0) form->addRow(tr("Vertical"), vAlign);
  if (t.path >= 0) form->addRow(QString(), flip);
  if (t.path >= 0) angle->setEnabled(false);   // the path turns the letters
  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  buttons->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("textOk"));
  buttons->button(QDialogButtonBox::Ok)->setDefault(true);
  form->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
  words->setFocus();
  for (;;) {
    if (dlg.exec() != QDialog::Accepted) return false;
    try {
      const double h = session_.document().evaluate(height->text().toStdString(), Unit::Millimeter, localDimensions());
      const double a = session_.document().evaluate(angle->text().toStdString(), Unit::Degree);
      const QString typed = words->toPlainText();
      if (typed.trimmed().isEmpty()) throw std::runtime_error(tr("type the text").toStdString());
      if (!(h > 0)) throw std::runtime_error(tr("the height must be greater than zero").toStdString());
      // One line unless it is a box.
      t.text = (t.corner >= 0 ? typed : QString(typed).replace(QLatin1Char('\n'), QLatin1Char(' '))).toStdString();
      t.hAlign = hAlign->currentData().toString().toStdString();
      t.vAlign = t.corner >= 0 ? vAlign->currentData().toString().toStdString() : std::string("bottom");
      t.flip = t.path >= 0 && flip->isChecked();
      t.height = h;
      t.angle = a;
      t.font = font->currentData().toString().isEmpty() && font->currentIndex() != 0 ? font->currentText().toStdString()
                                                                                     : font->currentData().toString().toStdString();
      lastHeight = h;
      lastFont = QString::fromStdString(t.font);
      return true;
    } catch (const std::exception& e) {
      emit message(tr("Text: %1").arg(QString::fromUtf8(e.what())));
    }
  }
}

void SketchEditor::mouseDoubleClick(QMouseEvent* e) {
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  // Double-click a tangent handle's end (with Select): free it.
  if (tool_ == Tool::Select)
    if (const HandleHit hh = handleAt(x, y); hh.spline >= 0) {
      checkpoint();
      (void)sketch::setSplineHandle(sk_, hh.spline, hh.index, 0, 0);
      solveAndShow();
      emit message(tr("Tangent handle freed: the curve sets its own direction there again."));
      return;
    }
  // Double-click a text (with Select): change it.
  if (tool_ == Tool::Select)
    if (const int ti = textAt(x, y); ti >= 0) {
      sketch::Text t = sk_.texts[ti];
      if (editText(t, false)) {
        checkpoint();
        sk_.texts[ti] = t;
        solveAndShow();
      }
      return;
    }
  if (tool_ == Tool::Line) {
    // On the chain's end: a press-and-drag there still draws a tangent arc;
    // a double-click without moving ends the chain (decided on release).
    if (!steps_.empty() && steps_.back().hit.kind == Hit::Point && snapPoint(x, y) == steps_.back().hit.index) {
      arcFrom_ = steps_.back().hit.index;
      arcRef_ = curveEndingAt(arcFrom_);
      if (arcRef_ >= 0) {
        pressPos_ = e->position();
        arcDrag_ = true;
        arcDragMoved_ = false;
        arcEndsChain_ = true;
        clearHud();
        return;
      }
    }
    resetSteps();
    rebuild();
    return;
  }
  if (tool_ == Tool::Spline || tool_ == Tool::ControlSpline) {
    if (steps_.size() >= 2) finishSpline(false);
    return;
  }
  // Double-click a conic (with Select): change its rho.
  if (tool_ == Tool::Select) {
    const Hit c = hitEntity(x, y);
    if (c.kind == Hit::Entity && sk_.entities[c.index].type == EntityType::Spline &&
        sk_.entities[c.index].kind == sketch::SplineKind::Conic) {
      const auto v = askFields(tr("Conic Curve"), {{{tr("Rho (0 to 1)"), QStringLiteral("rho"),
                                                    QString::number(sk_.entities[c.index].radius)}}});
      if (v) {
        bool ok = false;
        const double rho = (*v)[0].toDouble(&ok);
        if (!ok || !(rho > 0 && rho < 1)) {
          emit message(tr("Rho must be between 0 and 1 (0.5 is a parabola)."));
          return;
        }
        checkpoint();
        sk_.entities[c.index].radius = rho;
        solveAndShow();
      }
      return;
    }
  }
  const Hit h = hitTest(x, y);
  if (h.kind == Hit::Label && sketch::isDimension(sk_.constraints[h.index].type))
    askValue(sk_.constraints[h.index], e->position(), h.index);
}

void SketchEditor::autoHorizontalVertical(int line) {
  if (snapsSuppressed()) return;
  const auto& l = sk_.entities[line];
  const double dx = sk_.points[l.b].x - sk_.points[l.a].x;
  const double dy = sk_.points[l.b].y - sk_.points[l.a].y;
  std::optional<ConstraintType> t;
  if (std::abs(dy) <= kHVTolerance * std::abs(dx)) t = ConstraintType::Horizontal;
  else if (std::abs(dx) <= kHVTolerance * std::abs(dy)) t = ConstraintType::Vertical;
  if (t) (void)sketch::addConstraintChecked(sk_, {*t, {}, {line}});
}

// ---------------------------------------------------------------------------
// Constraints and dimensions

void SketchEditor::constraintPick(double x, double y) {
  const bool wantsEntity = tool_ == Tool::Parallel || tool_ == Tool::Perpendicular || tool_ == Tool::Equal ||
                           tool_ == Tool::Collinear || (tool_ == Tool::Symmetry && picks_.size() == 2) ||
                           tool_ == Tool::Tangent || tool_ == Tool::Concentric || tool_ == Tool::HorizontalVertical ||
                           (tool_ == Tool::Midpoint && !picks_.empty());
  Hit h = wantsEntity ? hitEntity(x, y) : hitTest(x, y);
  if (h.kind == Hit::Label || h.kind == Hit::None) return;
  picks_.push_back({h, x, y});
  rebuild();
  evaluateConstraintPicks();
}

bool SketchEditor::isConstraintTool(Tool t) {
  switch (t) {
    case Tool::Coincident: case Tool::HorizontalVertical: case Tool::Parallel: case Tool::Perpendicular:
    case Tool::Equal: case Tool::Tangent: case Tool::Fix: case Tool::Midpoint: case Tool::Concentric:
    case Tool::Collinear: case Tool::Symmetry:
      return true;
    default:
      return false;
  }
}

// Constraint tools started with geometry already selected (the familiar
// select-then-constrain order): the selection is used as the picks. Tools
// that take one item apply to every selected one.
void SketchEditor::applyToSelection(const std::vector<Hit>& selected) {
  int applied = 0;
  for (const Hit& h : selected) {
    if (h.kind != Hit::Point && h.kind != Hit::Entity) continue;
    const bool one = tool_ == Tool::HorizontalVertical || tool_ == Tool::Fix;
    if (one) picks_.clear();
    double x = 0, y = 0;
    if (h.kind == Hit::Point) {
      x = sk_.points[h.index].x;
      y = sk_.points[h.index].y;
    }
    picks_.push_back({h, x, y});
    const auto before = sk_.constraints.size();
    evaluateConstraintPicks();
    if (sk_.constraints.size() > before) ++applied;
  }
  if (applied > 0 && picks_.empty()) {
    // Done: back to selecting, as the familiar tool does.
    QTimer::singleShot(0, this, [this] { setTool(Tool::Select); });
  }
}

void SketchEditor::evaluateConstraintPicks() {
  if (picks_.empty()) return;
  auto isLine = [&](const Hit& p) { return p.kind == Hit::Entity && sk_.entities[p.index].type == EntityType::Line; };
  auto isRound = [&](const Hit& p) { return p.kind == Hit::Entity && sketch::isRound(sk_.entities[p.index].type); };
  auto done = [&](std::vector<Constraint> cs) {
    picks_.clear();
    if (cs.size() == 1) {
      constrain(cs.front());
      return;
    }
    checkpoint();
    for (auto& c : cs) sk_.addConstraint(c);
    const auto r = sketch::solve(sk_);
    if (!r.ok) {
      sk_ = undo_.back();
      undo_.pop_back();
      emit message(QString::fromStdString(r.message));
    }
    solveAndShow();
  };
  auto fail = [&](const QString& why) {
    picks_.clear();
    emit message(why);
    rebuild();
  };

  const Hit a = picks_[0].hit;
  switch (tool_) {
    case Tool::HorizontalVertical: {
      if (!isLine(a)) return fail(tr("Horizontal/Vertical needs a line."));
      const auto& l = sk_.entities[a.index];
      const double dx = sk_.points[l.b].x - sk_.points[l.a].x, dy = sk_.points[l.b].y - sk_.points[l.a].y;
      return done({{std::abs(dx) >= std::abs(dy) ? ConstraintType::Horizontal : ConstraintType::Vertical, {}, {a.index}}});
    }
    case Tool::Fix: {
      if (a.kind == Hit::Point) {
        const auto& p = sk_.points[a.index];
        return done({{ConstraintType::Fix, {a.index}, {}, p.x, p.y}});
      }
      std::vector<Constraint> cs;
      for (int p : sk_.entityPoints(a.index)) cs.push_back({ConstraintType::Fix, {p}, {}, sk_.points[p].x, sk_.points[p].y});
      if (sk_.entities[a.index].type == EntityType::Circle)
        cs.push_back({ConstraintType::Radius, {}, {a.index}, sk_.entities[a.index].radius});
      return done(cs);
    }
    default:
      break;
  }
  if (picks_.size() < 2) {
    emit message(tr("Now pick the second item."));
    return;
  }
  const Hit b = picks_[1].hit;
  switch (tool_) {
    case Tool::Coincident:
      if (a.kind == Hit::Point && b.kind == Hit::Point) {
        if (a.index == b.index) return fail(tr("Pick two different points."));
        return done({{ConstraintType::Coincident, {a.index, b.index}}});
      }
      if (a.kind == Hit::Point && b.kind == Hit::Entity) return done({{ConstraintType::PointOnEntity, {a.index}, {b.index}}});
      if (a.kind == Hit::Entity && b.kind == Hit::Point) return done({{ConstraintType::PointOnEntity, {b.index}, {a.index}}});
      return fail(tr("Coincident needs a point and a point or curve."));
    case Tool::Parallel:
    case Tool::Perpendicular:
      if (!isLine(a) || !isLine(b) || a.index == b.index) return fail(tr("Pick two different lines."));
      return done({{tool_ == Tool::Parallel ? ConstraintType::Parallel : ConstraintType::Perpendicular, {}, {a.index, b.index}}});
    case Tool::Equal:
      if (a.index == b.index || !((isLine(a) && isLine(b)) || (isRound(a) && isRound(b))))
        return fail(tr("Pick two lines, or two circles/arcs."));
      return done({{ConstraintType::Equal, {}, {a.index, b.index}}});
    case Tool::Tangent: {
      if (a.index == b.index || (isLine(a) && isLine(b))) return fail(tr("Pick a line and a circle/arc, or two circles/arcs."));
      double internal = 0;
      if (isRound(a) && isRound(b)) {
        const auto& e1 = sk_.entities[a.index];
        const auto& e2 = sk_.entities[b.index];
        const double d = std::hypot(sk_.points[e1.center].x - sk_.points[e2.center].x,
                                    sk_.points[e1.center].y - sk_.points[e2.center].y);
        internal = d < std::max(e1.radius, e2.radius) ? 1 : 0;
      }
      return done({{ConstraintType::Tangent, {}, {a.index, b.index}, internal}});
    }
    case Tool::Concentric:
      if (!isRound(a) || !isRound(b) || a.index == b.index) return fail(tr("Pick two circles/arcs."));
      return done({{ConstraintType::Concentric, {}, {a.index, b.index}}});
    case Tool::Collinear:
      if (!isLine(a) || !isLine(b) || a.index == b.index) return fail(tr("Pick two different lines."));
      return done({{ConstraintType::Collinear, {}, {a.index, b.index}}});
    case Tool::Symmetry: {
      // Two points, two lines or two circles/arcs, then the line of symmetry.
      const bool points = a.kind == Hit::Point && b.kind == Hit::Point;
      const bool lines = isLine(a) && isLine(b) && a.index != b.index;
      const bool rounds = isRound(a) && isRound(b) && a.index != b.index;
      if (picks_.size() < 3) {
        if (!points && !lines && !rounds) return fail(tr("Pick two points, two lines or two circles, then the line."));
        emit message(tr("Now pick the line of symmetry."));
        return;
      }
      const Hit l = picks_[2].hit;
      if (!isLine(l) || l.index == a.index || l.index == b.index) return fail(tr("The third pick must be another line."));
      if (points) return done({{ConstraintType::Symmetry, {a.index, b.index}, {l.index}}});
      const auto& ea = sk_.entities[a.index];
      const auto& eb = sk_.entities[b.index];
      if (rounds)   // mirrored centres, and the same size
        return done({{ConstraintType::Symmetry, {ea.center, eb.center}, {l.index}},
                     {ConstraintType::Equal, {}, {a.index, b.index}}});
      // Lines: each end with the nearer end of the other line's mirror image.
      const auto& la = sk_.entities[l.index];
      const auto P = [&](int i) { return sk_.points[i]; };
      const double dx = P(la.b).x - P(la.a).x, dy = P(la.b).y - P(la.a).y, n2 = dx * dx + dy * dy;
      auto mirror = [&](int i, double& mx, double& my) {
        const double t = ((P(i).x - P(la.a).x) * dx + (P(i).y - P(la.a).y) * dy) / std::max(n2, 1e-18);
        const double fx = P(la.a).x + t * dx, fy = P(la.a).y + t * dy;
        mx = 2 * fx - P(i).x;
        my = 2 * fy - P(i).y;
      };
      double mx, my;
      mirror(ea.a, mx, my);
      const bool straight = std::hypot(P(eb.a).x - mx, P(eb.a).y - my) <= std::hypot(P(eb.b).x - mx, P(eb.b).y - my);
      return done({{ConstraintType::Symmetry, {ea.a, straight ? eb.a : eb.b}, {l.index}},
                   {ConstraintType::Symmetry, {ea.b, straight ? eb.b : eb.a}, {l.index}}});
    }
    case Tool::Midpoint:
      if (a.kind != Hit::Point || !isLine(b)) return fail(tr("Pick a point, then a line."));
      return done({{ConstraintType::Midpoint, {a.index}, {b.index}}});
    default:
      return fail(QString());
  }
}

void SketchEditor::dimensionPick(double x, double y, const QPointF& widgetPos) {
  const Hit h = hitTest(x, y);
  auto isLine = [&](const Hit& p) { return p.kind == Hit::Entity && sk_.entities[p.index].type == EntityType::Line; };
  auto isRound = [&](const Hit& p) {
    return p.kind == Hit::Entity && (sk_.entities[p.index].type == EntityType::Circle || sk_.entities[p.index].type == EntityType::Arc ||
                                     sk_.entities[p.index].type == EntityType::Ellipse);
  };
  if (picks_.empty()) {
    if (h.kind == Hit::None) return;
    if (h.kind == Hit::Label) {
      const Constraint& k = sk_.constraints[h.index];
      if (k.driven) emit message(tr("A driven dimension follows the geometry; it has no value to type."));
      else if (sketch::isDimension(k.type)) askValue(k, widgetPos, h.index);
      return;
    }
    if (h.kind == Hit::Entity && sk_.entities[h.index].type == EntityType::Spline) {
      emit message(tr("Splines follow their points: dimension the points instead."));
      return;
    }

    picks_.push_back({h, x, y});
    emit message(h.kind == Hit::Point ? tr("Pick a second point or a line.")
                 : isLine(h)          ? tr("Move to place the length (above or beside for horizontal / vertical) and "
                                           "click; or click another line (angle) or a point (distance).")
                 : sk_.entities[h.index].type == EntityType::Ellipse
                     ? tr("Move along the half axis to dimension and click.")
                                      : tr("Move to place the size and click."));
    updatePreview(x, y);
    rebuild();
    return;
  }
  // A second pick that makes a two-item dimension.
  const Hit a = picks_[0].hit;
  const bool same = h.kind == a.kind && h.index == a.index;
  if (picks_.size() == 1 && !same && !isRound(a) &&
      ((isLine(a) && (isLine(h) || h.kind == Hit::Point)) || (a.kind == Hit::Point && (h.kind == Hit::Point || isLine(h))))) {
    picks_.push_back({h, x, y});
    emit message(tr("Move to place the dimension and click."));
    updatePreview(x, y);
    rebuild();
    return;
  }
  // Anything else places it: the value box opens where it was put.
  const auto c = dimensionCandidate(x, y);
  if (!c) {
    if (a.kind == Hit::Point) emit message(tr("Pick a second point or a line."));
    return;
  }
  picks_.clear();
  clearPreview();
  rebuild();
  {
    // Would it over-constrain (or only repeat) what is there? Then, as the
    // familiar sketcher asks, offer a driven (reference) dimension.
    sketch::Sketch trial = sk_;
    Constraint atValue = *c;
    atValue.value = currentValue(*c);
    if (!sketch::addConstraintChecked(trial, atValue).empty()) {
      QMessageBox box(QMessageBox::Question, tr("Driven dimension"),
                      tr("Adding this dimension will over-constrain the sketch.\n"
                         "Create a driven (reference) dimension instead?"),
                      QMessageBox::Ok | QMessageBox::Cancel, view_);
      box.setObjectName(QStringLiteral("drivenDimension"));
      box.setDefaultButton(QMessageBox::Ok);
      if (box.exec() != QMessageBox::Ok) return;
      Constraint d = *c;
      d.driven = true;
      d.value = 0;
      checkpoint();
      sk_.constraints.push_back(d);
      emit message(tr("Driven dimension: it shows the size and follows the geometry."));
      solveAndShow();
      return;
    }
  }
  askValue(*c, widgetPos);
}

double SketchEditor::currentValue(const Constraint& c) const {
  const auto& P = sk_.points;
  auto len = [&](int l) {
    const auto& e = sk_.entities[l];
    return std::hypot(P[e.b].x - P[e.a].x, P[e.b].y - P[e.a].y);
  };
  switch (c.type) {
    case ConstraintType::Distance:
      if (c.points.size() == 2) return std::hypot(P[c.points[1]].x - P[c.points[0]].x, P[c.points[1]].y - P[c.points[0]].y);
      if (c.points.size() == 1) {
        const auto& e = sk_.entities[c.entities[0]];
        const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
        const auto& p = P[c.points[0]];
        return std::abs(dx * (p.y - P[e.a].y) - dy * (p.x - P[e.a].x)) / std::max(std::hypot(dx, dy), 1e-12);
      }
      return len(c.entities[0]);
    case ConstraintType::HorizontalDistance: return P[c.points[1]].x - P[c.points[0]].x;
    case ConstraintType::VerticalDistance: return P[c.points[1]].y - P[c.points[0]].y;
    case ConstraintType::Radius: return sk_.entities[c.entities[0]].radius;
    case ConstraintType::Diameter: return 2 * sk_.entities[c.entities[0]].radius;
    case ConstraintType::Angle: {
      const auto& e1 = sk_.entities[c.entities[0]];
      const auto& e2 = sk_.entities[c.entities[1]];
      const double x1 = P[e1.b].x - P[e1.a].x, y1 = P[e1.b].y - P[e1.a].y;
      const double x2 = P[e2.b].x - P[e2.a].x, y2 = P[e2.b].y - P[e2.a].y;
      return std::atan2(x1 * y2 - y1 * x2, x1 * x2 + y1 * y2);
    }
    default:
      return c.value;
  }
}

void SketchEditor::askValue(const Constraint& c, const QPointF& widgetPos, int editIndex) {
  if (valueBox_) valueBox_->deleteLater();
  const bool angle = c.type == ConstraintType::Angle;
  const Unit unit = angle ? Unit::Degree : unit_;
  const double v = editIndex >= 0 ? c.value : currentValue(c);
  auto* box = new QLineEdit(view_);
  valueBox_ = box;
  box->setObjectName(QStringLiteral("dimensionValue"));
  ParameterCompleter::attach(box, [this] { return parameterNames(); });
  if (editIndex >= 0 && !c.expression.empty())
    box->setText(QString::fromStdString(c.expression));
  else
    box->setText(QString::number(fromInternal(v, unit), 'f', angle ? 2 : 3) + QStringLiteral(" ") +
                 QString::fromUtf8(unitSymbol(unit).data()));
  box->setFixedWidth(120);
  box->move(widgetPos.toPoint() + QPoint(12, -12));
  box->show();
  box->setFocus();
  box->selectAll();
  emit message(tr("Type a value or an expression such as width / 2 (units optional) and press Enter; Esc cancels."));

  const Constraint base = c;
  connect(box, &QLineEdit::returnPressed, this, [this, box, base, unit, editIndex] {
    const std::string text = box->text().trimmed().toStdString();
    std::optional<double> value;
    try {
      value = session_.document().evaluate(text, unit == Unit::Degree ? Unit::Degree : Unit::Millimeter,
                                           localDimensions(editIndex));
    } catch (const std::exception& e) {
      emit message(tr("'%1': %2").arg(box->text(), QString::fromUtf8(e.what())));
      return;
    }
    // Plain numbers are stored as values; anything else keeps its expression
    // so the dimension follows the parameters it names.
    const std::string expression = isPlainQuantity(text) ? std::string() : text;
    if (base.type != ConstraintType::Angle && base.type != ConstraintType::HorizontalDistance &&
        base.type != ConstraintType::VerticalDistance && *value <= 0) {
      emit message(tr("The value must be greater than zero."));
      return;
    }
    valueBox_ = nullptr;
    box->deleteLater();
    if (editIndex >= 0) {
      checkpoint();
      sk_.constraints[editIndex].value = *value;
      sk_.constraints[editIndex].expression = expression;
      refreshLocalExpressions();   // dimensions that use this one follow
      const auto r = sketch::solve(sk_);
      if (!r.ok) {
        sk_ = undo_.back();
        undo_.pop_back();
        emit message(tr("That value cannot be met by the other constraints."));
        rebuild();
        return;
      }
      solveAndShow();
      return;
    }
    Constraint c2 = base;
    c2.value = *value;
    c2.expression = expression;
    // Named as in the familiar tool (d1, d2 ...): a model parameter.
    std::vector<std::string> taken;
    for (const auto& k : sk_.constraints) taken.push_back(k.name);
    c2.name = session_.document().nextDimensionName(taken);
    constrain(c2);
  });
  connect(box, &QLineEdit::editingFinished, this, [this, box] {
    if (valueBox_ == box) valueBox_ = nullptr;
    box->deleteLater();
  });
}

// ---------------------------------------------------------------------------
// On-canvas size boxes

bool SketchEditor::hudTool() const {
  switch (tool_) {
    case Tool::Line:
    case Tool::Rectangle:
    case Tool::CenterRectangle:
    case Tool::Circle:
    case Tool::Polygon:
    case Tool::Slot:
    case Tool::Fillet:
    case Tool::Chamfer:
    case Tool::Offset:
      return true;
    default:
      return false;
  }
}

bool SketchEditor::hudAnyLocked() const {
  for (size_t i = 0; i < hud_.size(); ++i)
    if (hud_[i].locked && hud_[i].kind != HudField::Count) return true;
  return false;
}

int SketchEditor::polygonSides() const {
  if (tool_ == Tool::Polygon && hud_.size() > 1 && hud_[1].locked) return std::clamp(static_cast<int>(hud_[1].value), 3, 64);
  return 6;
}

void SketchEditor::clearHud() {
  for (auto& f : hud_)
    if (f.edit) {
      f.edit->removeEventFilter(this);
      f.edit->deleteLater();
    }
  hud_.clear();
  if (view_) view_->setFocus();
}

void SketchEditor::ensureHud() {
  if (!view_ || !hudTool() || steps_.empty()) {
    if (!hud_.empty()) clearHud();
    return;
  }
  if (!hud_.empty()) return;
  std::vector<std::pair<HudField::Kind, QString>> fields;
  switch (tool_) {
    case Tool::Line: fields = {{HudField::Length, tr("Length")}, {HudField::Angle, tr("Angle")}}; break;
    case Tool::Rectangle:
    case Tool::CenterRectangle: fields = {{HudField::Length, tr("Width")}, {HudField::Length, tr("Height")}}; break;
    case Tool::Circle: fields = {{HudField::Length, tr("Diameter")}}; break;
    case Tool::Polygon: fields = {{HudField::Length, tr("Diameter")}, {HudField::Count, tr("Sides")}}; break;
    case Tool::Slot: fields = {{HudField::Length, tr("Length")}, {HudField::Length, tr("Width")}}; break;
    case Tool::Fillet: fields = {{HudField::Length, tr("Radius")}}; break;
    case Tool::Chamfer: fields = {{HudField::Length, tr("Distance")}}; break;
    case Tool::Offset: fields = {{HudField::Length, tr("Offset")}}; break;
    default: return;
  }
  for (const auto& [kind, name] : fields) {
    HudField f;
    f.kind = kind;
    auto* e = new QLineEdit(view_);
    e->setObjectName(QStringLiteral("hud") + name);
    ParameterCompleter::attach(e, [this] { return parameterNames(); });
    e->setToolTip(tr("%1: type a value, Tab for the next box, Enter to create").arg(name));
    e->setAlignment(Qt::AlignCenter);
    e->setFixedWidth(kind == HudField::Count ? 60 : 110);
    e->setStyleSheet(QStringLiteral("QLineEdit { background: rgba(30,34,40,215); color: #f0f2f5; border: 1px solid #5b6472;"
                                    " border-radius: 3px; padding: 2px; }"
                                    "QLineEdit:focus { border: 1px solid #5b6472; border-bottom: 2px solid #3d8ee8; }"
                                    "QLineEdit[locked=\"true\"] { border: 2px solid #3d8ee8; font-weight: bold; }"));
    e->installEventFilter(this);
    const size_t index = hud_.size();
    connect(e, &QLineEdit::textEdited, this, [this, index] {
      if (index < hud_.size()) hud_[index].editing = true;
    });
    e->show();
    f.edit = e;
    hud_.push_back(f);
  }
  if (!hud_.empty() && hud_[0].edit) {
    hud_[0].edit->setFocus();
    hud_[0].edit->selectAll();
  }
}

bool SketchEditor::lockField(size_t i) {
  if (i >= hud_.size() || !hud_[i].edit || !hud_[i].editing) return i < hud_.size() && hud_[i].locked;
  HudField& f = hud_[i];
  const std::string text = f.edit->text().trimmed().toStdString();
  std::optional<double> v;
  if (f.kind == HudField::Count) {
    try {
      v = static_cast<double>(std::stoi(text));
    } catch (...) {
    }
  } else {
    try {
      v = session_.document().evaluate(text, f.kind == HudField::Angle ? Unit::Degree : Unit::Millimeter);
    } catch (const std::exception&) {
    }
  }
  f.editing = false;
  if (!v || (f.kind != HudField::Angle && *v <= 0)) {
    emit message(tr("'%1' is not a valid value.").arg(f.edit->text()));
    f.locked = false;
    f.edit->setProperty("locked", false);
    return false;
  }
  f.value = *v;
  f.locked = true;
  f.edit->setProperty("locked", true);
  f.edit->style()->unpolish(f.edit);
  f.edit->style()->polish(f.edit);
  return true;
}

std::pair<double, double> SketchEditor::hudTarget(double x, double y) const {
  if (steps_.empty()) return {x, y};
  const Pick& a = steps_.back();
  double dx = x - a.x, dy = y - a.y;
  const double dist = std::hypot(dx, dy);
  const double ux = dist > 1e-12 ? dx / dist : 1, uy = dist > 1e-12 ? dy / dist : 0;
  switch (tool_) {
    case Tool::Line: {
      const double len = hudLocked(0) ? hudValue(0) : dist;
      double ang = std::atan2(uy, ux);
      if (hudLocked(1)) ang = hudValue(1);
      return {a.x + len * std::cos(ang), a.y + len * std::sin(ang)};
    }
    case Tool::Rectangle:
    case Tool::CenterRectangle: {
      const double scale = tool_ == Tool::CenterRectangle ? 0.5 : 1.0;
      const double sx = dx < 0 ? -1 : 1, sy = dy < 0 ? -1 : 1;
      const double w = hudLocked(0) ? hudValue(0) * scale : std::abs(dx);
      const double h = hudLocked(1) ? hudValue(1) * scale : std::abs(dy);
      return {a.x + sx * w, a.y + sy * h};
    }
    case Tool::Circle:
    case Tool::Polygon: {
      const double r = hudLocked(0) ? hudValue(0) / 2 : dist;
      return {a.x + ux * r, a.y + uy * r};
    }
    case Tool::Slot: {
      const double len = hudLocked(0) ? hudValue(0) : dist;
      return {a.x + ux * len, a.y + uy * len};
    }
    default:
      return {x, y};
  }
}

void SketchEditor::updateHud(double x, double y) {
  if (hud_.empty() || steps_.empty() || !view_) return;
  const Pick& a = steps_.back();
  const double dx = x - a.x, dy = y - a.y;
  const double dist = std::hypot(dx, dy);
  // Live values and where each box sits (sketch coordinates).
  std::vector<std::pair<double, std::pair<double, double>>> live;
  const double off = view_->modelPerPixel() * 22;
  switch (tool_) {
    case Tool::Line:
      live = {{dist, {(a.x + x) / 2, (a.y + y) / 2 + off}}, {std::atan2(dy, dx), {a.x + off * 2, a.y - off}}};
      break;
    // Rectangles: the boxes sit on the dimension lines, width above the top
    // edge and height left of the left edge (see updatePreview).
    case Tool::Rectangle:
      live = {{std::abs(dx), {(a.x + x) / 2, std::max(a.y, y) + off * 1.6}},
              {std::abs(dy), {std::min(a.x, x) - off * 1.6, (a.y + y) / 2}}};
      break;
    case Tool::CenterRectangle:
      live = {{2 * std::abs(dx), {a.x, a.y + std::abs(dy) + off * 1.6}},
              {2 * std::abs(dy), {a.x - std::abs(dx) - off * 1.6, a.y}}};
      break;
    case Tool::Circle:
      live = {{2 * dist, {a.x + dist * 0.7071 + off, a.y + dist * 0.7071 + off}}};
      break;
    case Tool::Polygon:
      live = {{2 * dist, {a.x + dist + off * 3, a.y}}, {static_cast<double>(polygonSides()), {a.x, a.y - off * 1.5}}};
      break;
    case Tool::Slot:
      live = {{dist, {(a.x + x) / 2, (a.y + y) / 2 + off * 2}},
              {hudLocked(1) ? hudValue(1) : dist / 3, {x + off * 3, y}}};
      break;
    case Tool::Fillet:
    case Tool::Chamfer:
      live = {{filletRadiusAt(x, y), {x + off * 3, y - off}}};
      break;
    case Tool::Offset:
      live = {{std::abs(offsetAt(x, y, 0)), {x + off * 3, y - off}}};
      break;
    default:
      return;
  }
  for (size_t i = 0; i < hud_.size() && i < live.size(); ++i) {
    HudField& f = hud_[i];
    if (!f.edit) continue;
    if (!f.locked && !f.editing) {
      if (f.kind == HudField::Angle)
        f.edit->setText(QStringLiteral("%1 deg").arg(live[i].first * 180.0 / kPi, 0, 'f', 1));
      else if (f.kind == HudField::Count)
        f.edit->setText(QString::number(static_cast<int>(live[i].first)));
      else
        f.edit->setText(lengthText(live[i].first));
      // The focused box keeps its text selected so typing replaces it.
      if (f.edit->hasFocus()) f.edit->selectAll();
    }
    const QPointF w = view_->toWidget(sketch::toWorld(frame_, live[i].second.first, live[i].second.second));
    f.edit->move(QPoint(static_cast<int>(w.x() - f.edit->width() / 2), static_cast<int>(w.y() - f.edit->height() / 2)));
    f.edit->raise();
  }
}

void SketchEditor::commitHud() {
  for (size_t i = 0; i < hud_.size(); ++i) lockField(i);
  const QPointF centre = view_ ? QPointF(view_->width() / 2.0, view_->height() / 2.0) : QPointF(60, 60);
  press(cursorX_, cursorY_, Qt::NoModifier, centre);
}

bool SketchEditor::eventFilter(QObject* watched, QEvent* e) {
  if (e->type() != QEvent::KeyPress) return QObject::eventFilter(watched, e);
  size_t i = 0;
  while (i < hud_.size() && hud_[i].edit != watched) ++i;
  if (i == hud_.size()) return QObject::eventFilter(watched, e);
  auto* k = static_cast<QKeyEvent*>(e);
  switch (k->key()) {
    case Qt::Key_Tab:
    case Qt::Key_Backtab: {
      lockField(i);
      const size_t next = k->key() == Qt::Key_Tab ? (i + 1) % hud_.size() : (i + hud_.size() - 1) % hud_.size();
      if (hud_[next].edit) {
        hud_[next].edit->setFocus();
        hud_[next].edit->selectAll();
      }
      updatePreview(cursorX_, cursorY_);
      return true;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:
      commitHud();
      return true;
    case Qt::Key_Escape:
      escape();
      return true;
    default:
      return false;
  }
}

void SketchEditor::mirrorPick(double x, double y) {
  const Hit h = hitEntity(x, y);
  if (h.kind != Hit::Entity) return;
  if (!mirrorLineStage_) {
    // Objects: clicking toggles a curve in or out.
    auto it = std::find_if(picks_.begin(), picks_.end(), [&](const Pick& p) { return p.hit.index == h.index; });
    if (it != picks_.end()) picks_.erase(it);
    else picks_.push_back({h, x, y});
    emit message(tr("Mirror: %n curve(s) picked. Press Enter, then click the mirror line.", nullptr,
                    static_cast<int>(picks_.size())));
    rebuild();
    return;
  }
  std::vector<int> objects;
  for (const auto& p : picks_) objects.push_back(p.hit.index);
  checkpoint();
  const std::string err = sketch::mirrorEntities(sk_, objects, h.index);
  if (!err.empty()) {
    undo_.pop_back();
    emit message(QString::fromStdString(err));
    return;
  }
  picks_.clear();
  mirrorLineStage_ = false;
  solveAndShow();
  emit message(tr("Mirrored. Click more curves to mirror again."));
}

std::optional<std::vector<QString>> SketchEditor::askFields(const QString& title,
                                                            const std::vector<std::array<QString, 3>>& fields,
                                                            const QString& check, bool* checked) {
  QDialog dlg(view_);
  dlg.setObjectName(QStringLiteral("sketchValues"));
  dlg.setWindowTitle(title);
  auto* form = new QFormLayout(&dlg);
  std::vector<QLineEdit*> edits;
  for (const auto& [label, id, def] : fields) {
    auto* e = new QLineEdit(def);
    e->setObjectName(id);
    ParameterCompleter::attach(e, [this] { return parameterNames(); });
    form->addRow(label, e);
    edits.push_back(e);
  }
  QCheckBox* box = nullptr;
  if (!check.isEmpty()) {
    box = new QCheckBox(check);
    box->setObjectName(QStringLiteral("valuesCheck"));
    box->setChecked(checked && *checked);
    form->addRow(box);
  }
  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  buttons->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("valuesOk"));
  form->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
  if (!edits.empty()) {
    edits.front()->setFocus();
    edits.front()->selectAll();
  }
  if (dlg.exec() != QDialog::Accepted) return std::nullopt;
  if (box && checked) *checked = box->isChecked();
  std::vector<QString> out;
  for (auto* e : edits) out.push_back(e->text().trimmed());
  return out;
}

void SketchEditor::transformPick(double x, double y) {
  if (xformPointStage_) {
    // The pattern's centre / the scale's base point.
    const Pick p = pickPoint(x, y);
    xformPointStage_ = false;
    if (tool_ == Tool::CircPattern) {
      checkpoint();
      const int c = materialize(p);
      undo_.pop_back();   // the pattern makes its own undo step
      transformApply(c, sk_.points[c].x, sk_.points[c].y);
    } else {
      transformApply(-1, p.x, p.y);
    }
    return;
  }
  const Hit h = hitEntity(x, y);
  if (h.kind != Hit::Entity) return;
  auto it = std::find_if(picks_.begin(), picks_.end(), [&](const Pick& p) { return p.hit.index == h.index; });
  if (it != picks_.end()) picks_.erase(it);
  else picks_.push_back({h, x, y});
  emit message(tr("%n curve(s) picked: click more, or press Enter.", nullptr, static_cast<int>(picks_.size())));
  rebuild();
}

void SketchEditor::transformEnter() {
  if (picks_.empty()) {
    emit message(tr("Click the curves first."));
    return;
  }
  if (tool_ == Tool::CircPattern || tool_ == Tool::SketchScale) {
    xformPointStage_ = true;
    emit message(tool_ == Tool::CircPattern ? tr("Click the pattern's centre point.") : tr("Click the base point to scale about."));
    return;
  }
  transformApply(-1, 0, 0);
}

void SketchEditor::transformApply(int centerPoint, double cx, double cy) {
  std::vector<int> ents;
  for (const auto& p : picks_) ents.push_back(p.hit.index);
  const QString mm = QString::fromUtf8(unitSymbol(unit_).data());
  auto length = [&](const QString& t) {
    return session_.document().evaluate(t.toStdString(), Unit::Millimeter, localDimensions());
  };
  auto angle = [&](const QString& t) { return session_.document().evaluate(t.toStdString(), Unit::Degree, localDimensions()); };
  auto count = [&](const QString& t) {
    return static_cast<int>(std::lround(session_.document().evaluate(t.toStdString(), Unit::None, localDimensions())));
  };
  std::string err;
  sketch::Sketch trial = sk_;
  try {
    switch (tool_) {
      case Tool::RectPattern: {
        const auto v = askFields(tr("Rectangular Pattern"),
                                 {{{tr("Quantity"), QStringLiteral("patternCount1"), QStringLiteral("3")},
                                   {tr("Distance"), QStringLiteral("patternSpacing1"), QStringLiteral("10 ") + mm},
                                   {tr("Quantity (across)"), QStringLiteral("patternCount2"), QStringLiteral("1")},
                                   {tr("Distance (across)"), QStringLiteral("patternSpacing2"), QStringLiteral("10 ") + mm},
                                   {tr("Direction"), QStringLiteral("patternAngle"), QStringLiteral("0 deg")}}});
        if (!v) return;
        err = sketch::rectangularPattern(trial, ents, angle((*v)[4]), count((*v)[0]), length((*v)[1]), count((*v)[2]),
                                         length((*v)[3]));
        break;
      }
      case Tool::CircPattern: {
        const auto v = askFields(tr("Circular Pattern"),
                                 {{{tr("Quantity"), QStringLiteral("patternCount1"), QStringLiteral("6")},
                                   {tr("Angle"), QStringLiteral("patternAngle"), QStringLiteral("360 deg")}}});
        if (!v) return;
        err = sketch::circularPattern(trial, ents, centerPoint, count((*v)[0]), angle((*v)[1]));
        break;
      }
      case Tool::MoveCopy: {
        bool copy = false;
        const auto v = askFields(tr("Move/Copy"),
                                 {{{tr("X distance"), QStringLiteral("moveX"), QStringLiteral("10 ") + mm},
                                   {tr("Y distance"), QStringLiteral("moveY"), QStringLiteral("0 ") + mm},
                                   {tr("Angle"), QStringLiteral("moveAngle"), QStringLiteral("0 deg")}}},
                                 tr("Create Copy"), &copy);
        if (!v) return;
        // Turns go about the middle of the picked curves.
        double sx = 0, sy = 0;
        int n = 0;
        for (int e : ents)
          for (int p : sk_.entityPoints(e)) sx += sk_.points[p].x, sy += sk_.points[p].y, ++n;
        sketch::Placement pl;
        pl.dx = length((*v)[0]);
        pl.dy = length((*v)[1]);
        pl.angle = angle((*v)[2]);
        pl.cx = n ? sx / n : 0;
        pl.cy = n ? sy / n : 0;
        err = copy ? sketch::copyEntities(trial, ents, pl) : sketch::placeEntities(trial, ents, pl);
        break;
      }
      case Tool::SketchScale: {
        const auto v = askFields(tr("Sketch Scale"), {{{tr("Scale factor"), QStringLiteral("scaleFactor"), QStringLiteral("2")}}});
        if (!v) return;
        sketch::Placement pl;
        pl.scale = session_.document().evaluate((*v)[0].toStdString(), Unit::None, localDimensions());
        pl.cx = cx, pl.cy = cy;
        err = sketch::placeEntities(trial, ents, pl);
        break;
      }
      default:
        return;
    }
  } catch (const std::exception& e) {
    err = e.what();
  }
  if (!err.empty()) {
    emit message(QString::fromStdString(err));
    return;
  }
  checkpoint();
  sk_ = std::move(trial);
  picks_.clear();
  solveAndShow();
  emit message(tr("Done. Click curves to go again."));
}

bool SketchEditor::keyPress(QKeyEvent* e) {
  if (isTransformTool(tool_) && !xformPointStage_ && (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)) {
    transformEnter();
    return true;
  }
  if (tool_ == Tool::Mirror && !mirrorLineStage_ && !picks_.empty() &&
      (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter || e->key() == Qt::Key_Tab)) {
    mirrorLineStage_ = true;
    emit message(tr("Mirror: click the mirror line."));
    return true;
  }
  if ((tool_ == Tool::Spline || tool_ == Tool::ControlSpline) && steps_.size() >= 2 &&
      (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)) {
    finishSpline(false);
    return true;
  }
  // Typing while drawing goes into the first size box (like the on-canvas input).
  if (!hudTool() || steps_.empty()) return false;
  ensureHud();
  if (hud_.empty() || !hud_[0].edit) return false;
  if (e->key() == Qt::Key_Tab) {
    hud_[0].edit->setFocus();
    hud_[0].edit->selectAll();
    return true;
  }
  const QString t = e->text();
  if (t.isEmpty() || !(t[0].isDigit() || t[0] == QLatin1Char('.') || t[0] == QLatin1Char('-'))) return false;
  hud_[0].edit->setFocus();
  hud_[0].edit->setText(t);
  hud_[0].editing = true;
  return true;
}

bool SketchEditor::typeValue(const QString& text) {
  if (steps_.empty() || !hudTool()) return false;
  ensureHud();
  const QStringList parts = text.split(QRegularExpression(QStringLiteral("[xX*,]")), Qt::SkipEmptyParts);
  if (parts.isEmpty()) return false;
  for (int i = 0; i < parts.size() && i < static_cast<int>(hud_.size()); ++i) {
    if (!hud_[i].edit) continue;
    hud_[i].edit->setText(parts[i].trimmed());
    hud_[i].editing = true;
    if (!lockField(i)) return false;
  }
  // A single value for a rectangle means a square.
  if ((tool_ == Tool::Rectangle || tool_ == Tool::CenterRectangle) && parts.size() == 1 && hud_.size() > 1) {
    hud_[1].value = hud_[0].value;
    hud_[1].locked = true;
  }
  const size_t before = sk_.entities.size();
  commitHud();
  return sk_.entities.size() > before;
}

// ---------------------------------------------------------------------------
// Trim

void SketchEditor::trimAt(double x, double y, bool breakOnly) {
  const Hit h = hitEntity(x, y);
  if (h.kind != Hit::Entity) return;
  const int ei = h.index;
  const auto& P = sk_.points;
  const Entity target = sk_.entities[ei];
  if (target.type == EntityType::Spline || target.type == EntityType::Ellipse) {
    checkpoint();
    const std::string err = sketch::trimCurve(sk_, ei, x, y, breakOnly);
    if (!err.empty()) {
      undo_.pop_back();
      emit message(QString::fromStdString(err));
      return;
    }
    selection_.clear();
    solveAndShow();
    if (breakOnly) emit message(tr("Broken where it crosses. Click another curve to break it."));
    return;
  }

  // Intersections of the picked curve with every other curve, as parameters
  // along it: t in [0,1] for lines, angle for circles/arcs.
  std::vector<double> cuts;
  auto lineCircle = [&](double ax, double ay, double bx, double by, double cx, double cy, double r,
                        std::vector<std::pair<double, double>>& out) {
    const double dx = bx - ax, dy = by - ay;
    const double fx = ax - cx, fy = ay - cy;
    const double A = dx * dx + dy * dy, B = 2 * (fx * dx + fy * dy), Cc = fx * fx + fy * fy - r * r;
    const double disc = B * B - 4 * A * Cc;
    if (A < 1e-18 || disc < 0) return;
    for (double sgn : {-1.0, 1.0}) {
      const double t = (-B + sgn * std::sqrt(disc)) / (2 * A);
      out.emplace_back(t, std::atan2(ay + t * dy - cy, ax + t * dx - cx));
    }
  };
  auto onArc = [&](const Entity& e, double ang) {
    if (e.type != EntityType::Arc) return true;
    const auto& c = P[e.center];
    return angleInArc(ang, std::atan2(P[e.a].y - c.y, P[e.a].x - c.x), std::atan2(P[e.b].y - c.y, P[e.b].x - c.x));
  };
  for (int j = 0; j < static_cast<int>(sk_.entities.size()); ++j) {
    if (j == ei) continue;
    const Entity& o = sk_.entities[j];
    if (o.type == EntityType::Spline || o.type == EntityType::Ellipse) {
      // No closed form: crossings found numerically, as line / angle parameters.
      for (const auto& q : sketch::crossings(sk_, ei, j)) {
        if (target.type == EntityType::Line) {
          const auto &a = P[target.a], &b = P[target.b];
          const double dx = b.x - a.x, dy = b.y - a.y, l2 = dx * dx + dy * dy;
          if (l2 > 0) cuts.push_back(((q.x - a.x) * dx + (q.y - a.y) * dy) / l2);
        } else {
          const auto& c = P[target.center];
          cuts.push_back(std::atan2(q.y - c.y, q.x - c.x));
        }
      }
      continue;
    }
    if (target.type == EntityType::Line) {
      const auto &a = P[target.a], &b = P[target.b];
      if (o.type == EntityType::Line) {
        const auto &c = P[o.a], &d = P[o.b];
        const double den = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
        if (std::abs(den) < 1e-14) continue;
        const double t = ((c.x - a.x) * (d.y - c.y) - (c.y - a.y) * (d.x - c.x)) / den;
        const double u = ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x)) / den;
        if (u >= -1e-9 && u <= 1 + 1e-9) cuts.push_back(t);
      } else {
        std::vector<std::pair<double, double>> hits;
        lineCircle(a.x, a.y, b.x, b.y, P[o.center].x, P[o.center].y, o.radius, hits);
        for (const auto& [t, ang] : hits)
          if (onArc(o, ang)) cuts.push_back(t);
      }
    } else {
      const auto& c = P[target.center];
      if (o.type == EntityType::Line) {
        std::vector<std::pair<double, double>> hits;
        lineCircle(P[o.a].x, P[o.a].y, P[o.b].x, P[o.b].y, c.x, c.y, target.radius, hits);
        for (const auto& [t, ang] : hits)
          if (t >= -1e-9 && t <= 1 + 1e-9) cuts.push_back(ang);
      } else {
        const auto& c2 = P[o.center];
        const double d = std::hypot(c2.x - c.x, c2.y - c.y);
        if (d < 1e-12 || d > target.radius + o.radius || d < std::abs(target.radius - o.radius)) continue;
        const double base = std::atan2(c2.y - c.y, c2.x - c.x);
        const double half = std::acos(std::clamp((target.radius * target.radius + d * d - o.radius * o.radius) /
                                                     (2 * target.radius * d), -1.0, 1.0));
        for (double ang : {base - half, base + half}) {
          const double px = c.x + target.radius * std::cos(ang), py = c.y + target.radius * std::sin(ang);
          if (onArc(o, std::atan2(py - c2.y, px - c2.x))) cuts.push_back(ang);
        }
      }
    }
  }

  checkpoint();
  auto detachPoint = [&](int pt) {
    // Remove a point that no curve uses any more.
    for (const auto& e : sk_.entities) {
      if (e.a == pt || e.b == pt || e.center == pt) return;
      for (int f : e.fit)
        if (f == pt) return;
    }
    if (pt > 0) sk_.removePoints({pt});
  };
  // Constraints that only hold for the whole curve are dropped.
  auto dropDimensions = [&](int entity) {
    for (int k = static_cast<int>(sk_.constraints.size()) - 1; k >= 0; --k) {
      const auto& c = sk_.constraints[k];
      const bool refs = std::find(c.entities.begin(), c.entities.end(), entity) != c.entities.end();
      const bool keep = c.type == ConstraintType::Horizontal || c.type == ConstraintType::Vertical ||
                        c.type == ConstraintType::Parallel || c.type == ConstraintType::Perpendicular ||
                        c.type == ConstraintType::Collinear || c.type == ConstraintType::Concentric ||
                        c.type == ConstraintType::Radius || c.type == ConstraintType::Diameter;
      if (refs && !keep) sk_.removeConstraint(k);
    }
  };

  if (breakOnly) {
    // Break: split at the nearest crossings either side of the click; the
    // pieces stay one curve (collinear lines, arcs of one circle).
    auto norm = [](double v) {
      while (v < 0) v += 2 * kPi;
      while (v >= 2 * kPi) v -= 2 * kPi;
      return v;
    };
    bool split = false;
    if (target.type == EntityType::Line) {
      const auto a = P[target.a], b = P[target.b];
      const double dx = b.x - a.x, dy = b.y - a.y, l2 = dx * dx + dy * dy;
      const double t0 = l2 > 0 ? ((x - a.x) * dx + (y - a.y) * dy) / l2 : 0;
      double lo = -1, hi = 2;
      for (double t : cuts) {
        if (t > 1e-6 && t < t0 && t > lo) lo = t;
        if (t < 1 - 1e-6 && t > t0 && t < hi) hi = t;
      }
      int last = ei;
      for (double t : {lo, hi}) {
        if (t <= 0 || t >= 1) continue;
        if (!split) dropDimensions(ei);
        const int p = sk_.addPoint(a.x + dx * t, a.y + dy * t);
        const int end = sk_.entities[last].b;
        sk_.entities[last].b = p;
        const int piece = sk_.addLine(p, end, target.construction);
        sk_.addConstraint({ConstraintType::Collinear, {}, {last, piece}});
        last = piece;
        split = true;
      }
    } else if (target.type == EntityType::Circle) {
      const auto c = P[target.center];
      const double clickAng = std::atan2(y - c.y, x - c.x);
      double after = 1e9, before = 1e9, angAfter = 0, angBefore = 0;
      for (double ang : cuts) {
        const double da = norm(ang - clickAng), db = norm(clickAng - ang);
        if (da > 1e-9 && da < after) after = da, angAfter = ang;
        if (db > 1e-9 && db < before) before = db, angBefore = ang;
      }
      if (cuts.size() >= 2 && norm(angAfter - angBefore) > 1e-9) {
        dropDimensions(ei);
        const double r = target.radius;
        const int pa = sk_.addPoint(c.x + r * std::cos(angAfter), c.y + r * std::sin(angAfter));
        const int pb = sk_.addPoint(c.x + r * std::cos(angBefore), c.y + r * std::sin(angBefore));
        Entity& e = sk_.entities[ei];
        e.type = EntityType::Arc;   // the clicked piece: from the crossing before the click round to the one after
        e.a = pb;
        e.b = pa;
        const int rest = sk_.addArc(target.center, pa, pb, target.construction);
        sk_.addConstraint({ConstraintType::Equal, {}, {ei, rest}});
        split = true;
      }
    } else {
      const auto c = P[target.center];
      const double r = target.radius;
      const double start = std::atan2(P[target.a].y - c.y, P[target.a].x - c.x);
      const double span = norm(std::atan2(P[target.b].y - c.y, P[target.b].x - c.x) - start);
      const double u0 = norm(std::atan2(y - c.y, x - c.x) - start);
      double lo = -1, hi = 1e9;
      for (double ang : cuts) {
        const double u = norm(ang - start);
        if (u <= 1e-6 || u >= span - 1e-6) continue;
        if (u < u0 && u > lo) lo = u;
        if (u > u0 && u < hi) hi = u;
      }
      int last = ei;
      for (double u : {lo, hi}) {
        if (u <= 0 || u >= 1e8) continue;
        if (!split) dropDimensions(ei);
        const int p = sk_.addPoint(c.x + r * std::cos(start + u), c.y + r * std::sin(start + u));
        const int end = sk_.entities[last].b;
        sk_.entities[last].b = p;
        const int piece = sk_.addArc(target.center, p, end, target.construction);
        sk_.addConstraint({ConstraintType::Equal, {}, {last, piece}});
        last = piece;
        split = true;
      }
    }
    if (!split) {
      undo_.pop_back();
      emit message(tr("Break: nothing crosses that curve there."));
      return;
    }
    selection_.clear();
    solveAndShow();
    emit message(tr("Broken where it crosses. Click another curve to break it."));
    return;
  }

  if (target.type == EntityType::Line) {
    const auto a = P[target.a], b = P[target.b];
    const double dx = b.x - a.x, dy = b.y - a.y, l2 = dx * dx + dy * dy;
    const double t0 = l2 > 0 ? ((x - a.x) * dx + (y - a.y) * dy) / l2 : 0;
    double lo = -1, hi = 2;
    for (double t : cuts) {
      if (t > 1e-6 && t < t0 && t > lo) lo = t;
      if (t < 1 - 1e-6 && t > t0 && t < hi) hi = t;
    }
    const bool hasLo = lo > 0, hasHi = hi < 1;
    if (!hasLo && !hasHi) {
      sk_.removeEntities({ei});
    } else {
      dropDimensions(ei);
      const int oldA = target.a, oldB = target.b;
      if (hasLo && hasHi) {
        const int pl = sk_.addPoint(a.x + dx * lo, a.y + dy * lo);
        const int ph = sk_.addPoint(a.x + dx * hi, a.y + dy * hi);
        sk_.entities[ei].b = pl;
        sk_.addLine(ph, oldB, target.construction);
      } else if (hasLo) {
        sk_.entities[ei].b = sk_.addPoint(a.x + dx * lo, a.y + dy * lo);
        detachPoint(oldB);
      } else {
        sk_.entities[ei].a = sk_.addPoint(a.x + dx * hi, a.y + dy * hi);
        detachPoint(oldA);
      }
    }
  } else {
    const auto c = P[target.center];
    const double r = target.radius;
    const double clickAng = std::atan2(y - c.y, x - c.x);
    auto norm = [](double v) {
      while (v < 0) v += 2 * kPi;
      while (v >= 2 * kPi) v -= 2 * kPi;
      return v;
    };
    if (target.type == EntityType::Circle) {
      if (cuts.size() < 2) {
        sk_.removeEntities({ei});
      } else {
        // Keep the arc from the first crossing after the click round to the last one before it.
        double after = 1e9, before = 1e9, angAfter = 0, angBefore = 0;
        for (double ang : cuts) {
          const double da = norm(ang - clickAng), db = norm(clickAng - ang);
          if (da > 1e-9 && da < after) after = da, angAfter = ang;
          if (db > 1e-9 && db < before) before = db, angBefore = ang;
        }
        dropDimensions(ei);
        Entity& e = sk_.entities[ei];
        e.type = EntityType::Arc;
        e.a = sk_.addPoint(c.x + r * std::cos(angAfter), c.y + r * std::sin(angAfter));
        e.b = sk_.addPoint(c.x + r * std::cos(angBefore), c.y + r * std::sin(angBefore));
      }
    } else {
      const double start = std::atan2(P[target.a].y - c.y, P[target.a].x - c.x);
      const double span = norm(std::atan2(P[target.b].y - c.y, P[target.b].x - c.x) - start);
      const double u0 = norm(clickAng - start);
      double lo = -1, hi = 1e9;
      for (double ang : cuts) {
        const double u = norm(ang - start);
        if (u <= 1e-6 || u >= span - 1e-6) continue;
        if (u < u0 && u > lo) lo = u;
        if (u > u0 && u < hi) hi = u;
      }
      const bool hasLo = lo > 0, hasHi = hi < 1e8;
      if (!hasLo && !hasHi) {
        sk_.removeEntities({ei});
      } else {
        dropDimensions(ei);
        const int oldA = target.a, oldB = target.b, centre = target.center;
        auto at = [&](double u) { return sk_.addPoint(c.x + r * std::cos(start + u), c.y + r * std::sin(start + u)); };
        if (hasLo && hasHi) {
          const int pl = at(lo), ph = at(hi);
          sk_.entities[ei].b = pl;
          sk_.addArc(centre, ph, oldB, target.construction);
        } else if (hasLo) {
          sk_.entities[ei].b = at(lo);
          detachPoint(oldB);
        } else {
          sk_.entities[ei].a = at(hi);
          detachPoint(oldA);
        }
      }
    }
  }
  selection_.clear();
  solveAndShow();
}

bool SketchEditor::submitValue(const QString& text) {
  if (!valueBox_) return false;
  valueBox_->setText(text);
  emit valueBox_->returnPressed();
  return true;
}

QStringList SketchEditor::parameterNames() const {
  QStringList n;
  for (const auto& prm : session_.document().userParameters()) n << QString::fromStdString(prm.name);
  for (const auto& [name, q] : localDimensions()) n << QString::fromStdString(name);
  for (const auto& m : session_.document().modelParameters())
    if (!n.contains(QString::fromStdString(m.name))) n << QString::fromStdString(m.name);
  return n;
}

std::map<std::string, Quantity> SketchEditor::localDimensions(int skip) const {
  std::map<std::string, Quantity> out;
  for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i) {
    const auto& c = sk_.constraints[i];
    if (i == skip || c.name.empty() || c.driven || !sketch::isDimension(c.type)) continue;
    out[c.name] = quantityOf(c.value, c.type == ConstraintType::Angle ? Unit::Degree : Unit::Millimeter);
  }
  return out;
}

void SketchEditor::refreshLocalExpressions() {
  // A few passes: a dimension may use another that uses a third.
  for (int pass = 0; pass < 8; ++pass) {
    bool changed = false;
    for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i) {
      auto& c = sk_.constraints[i];
      if (c.expression.empty() || c.driven || !sketch::isDimension(c.type)) continue;
      try {
        const double v = session_.document().evaluate(
            c.expression, c.type == ConstraintType::Angle ? Unit::Degree : Unit::Millimeter, localDimensions(i));
        if (std::abs(v - c.value) > 1e-12) {
          c.value = v;
          changed = true;
        }
      } catch (const std::exception&) {
      }
    }
    if (!changed) return;
  }
}

bool SketchEditor::toggleSelectedConstruction() {
  std::vector<int> ents;
  for (const auto& h : selection_)
    if (h.kind == Hit::Entity && !sk_.entities[h.index].projected) ents.push_back(h.index);
  if (ents.empty()) return false;
  checkpoint();
  // All construction if any is normal, else all normal.
  const bool make = std::any_of(ents.begin(), ents.end(), [&](int i) { return !sk_.entities[i].construction; });
  for (int i : ents) sk_.entities[i].construction = make;
  solveAndShow();
  emit message(make ? tr("Changed to construction geometry.") : tr("Changed to normal geometry."));
  return true;
}

bool SketchEditor::selectAt(const QPointF& widgetPos) {
  double x, y;
  if (!toSketch(widgetPos, x, y)) return !selection_.empty();
  const Hit h = hitTest(x, y);
  if (h.kind == Hit::None) return !selection_.empty();
  const bool already = std::any_of(selection_.begin(), selection_.end(),
                                   [&](const Hit& s) { return s.kind == h.kind && s.index == h.index; });
  if (!already) {
    selection_ = {h};
    rebuild();
  }
  return true;
}

void SketchEditor::deleteSelection() {
  if (selection_.empty()) return;
  std::vector<int> ents, pts, cons;
  for (const auto& h : selection_) {
    if (h.kind == Hit::Entity) ents.push_back(h.index);
    else if (h.kind == Hit::Point && h.index > 0) pts.push_back(h.index);
    else if (h.kind == Hit::Label) cons.push_back(h.index);
  }
  checkpoint();
  std::sort(cons.rbegin(), cons.rend());
  for (int c : cons) sk_.removeConstraint(c);
  sk_.removeItems(ents, pts);
  selection_.clear();
  solveAndShow();
}

// ---------------------------------------------------------------------------
// Display

std::optional<std::pair<double, double>> SketchEditor::labelAnchor(int ci) const {
  const Constraint& c = sk_.constraints.at(ci);
  if (sketch::isDimension(c.type) && c.hasLabel) {
    const auto [bx, by] = dimensionBase(c);
    return std::make_pair(bx + c.labelX, by + c.labelY);
  }
  const double px = view_ ? view_->modelPerPixel() : 0.01;
  const auto& P = sk_.points;
  auto lineMid = [&](int l, double off, double& x, double& y) {
    const auto& e = sk_.entities[l];
    const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
    const double n = std::max(std::hypot(dx, dy), 1e-12);
    x = (P[e.a].x + P[e.b].x) / 2 - dy / n * off;
    y = (P[e.a].y + P[e.b].y) / 2 + dx / n * off;
  };
  // Stack geometric glyphs on the same entity.
  int stack = 0;
  for (int i = 0; i < ci; ++i)
    if (!sketch::isDimension(sk_.constraints[i].type) && !c.entities.empty() && !sk_.constraints[i].entities.empty() &&
        sk_.constraints[i].entities[0] == c.entities[0])
      ++stack;
  double x = 0, y = 0;
  switch (c.type) {
    case ConstraintType::Coincident:
    case ConstraintType::PointOnEntity:
      return std::nullopt;   // shown by the geometry itself
    case ConstraintType::Fix:
      return std::make_pair(P[c.points[0]].x + 10 * px, P[c.points[0]].y + 10 * px);
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance:
      if (c.points.size() == 2) {
        const auto& p = P[c.points[0]];
        const auto& q = P[c.points[1]];
        if (c.type == ConstraintType::HorizontalDistance)   // above the pair
          return std::make_pair((p.x + q.x) / 2, std::max(p.y, q.y) + 14 * px);
        if (c.type == ConstraintType::VerticalDistance)     // left of the pair
          return std::make_pair(std::min(p.x, q.x) - 24 * px, (p.y + q.y) / 2);
        return std::make_pair((p.x + q.x) / 2, (p.y + q.y) / 2 + 14 * px);
      }
      if (c.points.size() == 1) {
        lineMid(c.entities[0], 0, x, y);
        return std::make_pair((x + P[c.points[0]].x) / 2, (y + P[c.points[0]].y) / 2);
      }
      lineMid(c.entities[0], 16 * px, x, y);
      return std::make_pair(x, y);
    case ConstraintType::Radius:
    case ConstraintType::Diameter:
    case ConstraintType::Concentric: {
      const auto& e = sk_.entities[c.entities[0]];
      const double r = e.radius + (c.type == ConstraintType::Concentric ? 10 * px : 14 * px);
      return std::make_pair(P[e.center].x + r * 0.7071, P[e.center].y + r * 0.7071);
    }
    case ConstraintType::Angle: {
      double x2, y2;
      lineMid(c.entities[0], 0, x, y);
      lineMid(c.entities[1], 0, x2, y2);
      return std::make_pair((x + x2) / 2 + 10 * px, (y + y2) / 2 + 10 * px);
    }
    case ConstraintType::Midpoint:
      return std::make_pair(P[c.points[0]].x + 9 * px, P[c.points[0]].y - 9 * px);
    default: {
      if (c.entities.empty()) {   // e.g. horizontal between two points
        if (c.points.size() < 2) return std::nullopt;
        // A point kept on an origin axis: the glyph sits by the point.
        if (c.points[0] == 0 || c.points[1] == 0) {
          const int q = c.points[0] == 0 ? c.points[1] : c.points[0];
          return std::make_pair(P[q].x + 9 * px, P[q].y + 9 * px);
        }
        return std::make_pair((P[c.points[0]].x + P[c.points[1]].x) / 2,
                              (P[c.points[0]].y + P[c.points[1]].y) / 2 + 10 * px);
      }
      const int e = c.entities[0];
      if (sk_.entities[e].type == EntityType::Line) {
        lineMid(e, -(10 + 12 * stack) * px, x, y);
      } else {
        const auto& en = sk_.entities[e];
        x = P[en.center].x - (en.radius + (10 + 12 * stack) * px) * 0.7071;
        y = P[en.center].y + (en.radius + (10 + 12 * stack) * px) * 0.7071;
      }
      return std::make_pair(x, y);
    }
  }
}

// The point a dimension's value is placed relative to.
std::pair<double, double> SketchEditor::dimensionBase(const Constraint& c) const {
  const auto& P = sk_.points;
  auto mid = [](const sketch::Point& a, const sketch::Point& b) { return std::make_pair((a.x + b.x) / 2, (a.y + b.y) / 2); };
  switch (c.type) {
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance: {
      if (c.points.size() == 2) return mid(P[c.points[0]], P[c.points[1]]);
      const auto& e = sk_.entities[c.entities[0]];
      if (c.points.empty()) return mid(P[e.a], P[e.b]);
      // Point to line: halfway between the point and its foot on the line.
      const auto& p = P[c.points[0]];
      const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
      const double t = ((p.x - P[e.a].x) * dx + (p.y - P[e.a].y) * dy) / std::max(dx * dx + dy * dy, 1e-24);
      return std::make_pair((p.x + P[e.a].x + t * dx) / 2, (p.y + P[e.a].y + t * dy) / 2);
    }
    case ConstraintType::Radius:
    case ConstraintType::Diameter: {
      const auto& e = sk_.entities[c.entities[0]];
      return {P[e.center].x, P[e.center].y};
    }
    case ConstraintType::Angle: {
      const auto& e1 = sk_.entities[c.entities[0]];
      const auto& e2 = sk_.entities[c.entities[1]];
      const double ax = P[e1.b].x - P[e1.a].x, ay = P[e1.b].y - P[e1.a].y;
      const double bx = P[e2.b].x - P[e2.a].x, by = P[e2.b].y - P[e2.a].y;
      const double den = ax * by - ay * bx;
      if (std::abs(den) < 1e-12 * std::max(1.0, std::hypot(ax, ay) * std::hypot(bx, by))) {
        const auto m1 = mid(P[e1.a], P[e1.b]), m2 = mid(P[e2.a], P[e2.b]);
        return {(m1.first + m2.first) / 2, (m1.second + m2.second) / 2};
      }
      // Where the two lines (extended) cross.
      const double t = ((P[e2.a].x - P[e1.a].x) * by - (P[e2.a].y - P[e1.a].y) * bx) / den;
      return {P[e1.a].x + t * ax, P[e1.a].y + t * ay};
    }
    default:
      return {0, 0};
  }
}

void SketchEditor::addDimensionGraphics(const Constraint& c, double lx, double ly, const Quantity_Color& colour,
                                        std::vector<Handle(AIS_InteractiveObject)>& out) const {
  if (!view_ || view_->aisContext().IsNull()) return;
  const double px = view_->modelPerPixel();
  const auto& P = sk_.points;
  sketch::Sketch g;   // the dimension's lines, drawn thin
  auto seg = [&](double x1, double y1, double x2, double y2) {
    if (std::hypot(x2 - x1, y2 - y1) > px * 0.5) g.addLine(x1, y1, x2, y2);
  };
  // An arrowhead with its tip at (x, y), pointing along (dx, dy) (unit).
  auto arrow = [&](double x, double y, double dx, double dy) {
    const double l = 9 * px, w = 3.2 * px;
    seg(x, y, x - dx * l - dy * w, y - dy * l + dx * w);
    seg(x, y, x - dx * l + dy * w, y - dy * l - dx * w);
  };
  switch (c.type) {
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance: {
      // The two measured points and the measuring direction.
      double x1, y1, x2, y2;
      if (c.points.size() == 2) {
        x1 = P[c.points[0]].x, y1 = P[c.points[0]].y, x2 = P[c.points[1]].x, y2 = P[c.points[1]].y;
      } else {
        const auto& e = sk_.entities[c.entities[0]];
        if (c.points.empty()) {
          x1 = P[e.a].x, y1 = P[e.a].y, x2 = P[e.b].x, y2 = P[e.b].y;
        } else {   // point to line: the point and its foot
          const auto& p = P[c.points[0]];
          const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
          const double t = ((p.x - P[e.a].x) * dx + (p.y - P[e.a].y) * dy) / std::max(dx * dx + dy * dy, 1e-24);
          x1 = p.x, y1 = p.y, x2 = P[e.a].x + t * dx, y2 = P[e.a].y + t * dy;
          // The line itself, extended to the foot, as a thin reference.
          seg(P[e.a].x, P[e.a].y, x2, y2);
        }
      }
      double dx = x2 - x1, dy = y2 - y1;
      if (c.type == ConstraintType::HorizontalDistance) dx = 1, dy = 0;
      else if (c.type == ConstraintType::VerticalDistance) dx = 0, dy = 1;
      const double n = std::hypot(dx, dy);
      if (n < 1e-12) break;
      dx /= n, dy /= n;
      const double nx = -dy, ny = dx;   // across the measurement
      // The dimension line runs through the value, a little below it.
      double h = (lx - x1) * nx + (ly - y1) * ny;
      // The text is level: beside a steep dimension line it needs half its
      // width of room, above a level one just its half height.
      const double gap = (std::abs(dy) > std::abs(dx) ? 26 : 8) * px;
      if (std::abs(h) > 2 * gap) h -= std::copysign(gap, h);
      const double h1 = h, h2 = h + (x1 - x2) * nx + (y1 - y2) * ny;   // offsets from each point
      const double ax = x1 + nx * h1, ay = y1 + ny * h1;   // dimension line ends
      const double bx = x2 + nx * h2, by = y2 + ny * h2;
      // Extension lines, a small gap off the geometry and a little past the line.
      auto ext = [&](double x, double y, double hh) {
        if (std::abs(hh) < 3 * px) return;
        const double s = hh > 0 ? 1 : -1;
        seg(x + nx * s * 2 * px, y + ny * s * 2 * px, x + nx * (hh + s * 4 * px), y + ny * (hh + s * 4 * px));
      };
      ext(x1, y1, h1);
      ext(x2, y2, h2);
      // Dimension line (out to the value when it sits beyond the ends).
      const double along = ((bx - ax) * dx + (by - ay) * dy);
      const double s = along >= 0 ? 1 : -1;
      const double tv = (lx - ax) * dx + (ly - ay) * dy;   // the value along the line
      const double lo = std::min({0.0, along, tv}), hi = std::max({0.0, along, tv});
      seg(ax + dx * lo, ay + dy * lo, ax + dx * hi, ay + dy * hi);
      arrow(ax, ay, -dx * s, -dy * s);
      arrow(bx, by, dx * s, dy * s);
      break;
    }
    case ConstraintType::Radius:
    case ConstraintType::Diameter: {
      const auto& e = sk_.entities[c.entities[0]];
      const double cx = P[e.center].x, cy = P[e.center].y, r = e.radius;
      double ux = lx - cx, uy = ly - cy;
      const double d = std::hypot(ux, uy);
      if (e.type == EntityType::Ellipse) {   // across the drawn axis, on the value's side
        double nx = -(P[e.a].y - cy), ny = P[e.a].x - cx;
        const double nl = std::max(std::hypot(nx, ny), 1e-12);
        nx /= nl, ny /= nl;
        if (nx * ux + ny * uy < 0) nx = -nx, ny = -ny;
        ux = nx, uy = ny;
      } else if (d < 1e-12) {
        ux = 0.7071, uy = 0.7071;
      } else {
        ux /= d, uy /= d;
      }
      const double qx = cx + ux * r, qy = cy + uy * r;
      if (c.type == ConstraintType::Radius) {
        seg(cx, cy, qx, qy);
        arrow(qx, qy, ux, uy);
      } else {
        seg(cx - ux * r, cy - uy * r, qx, qy);
        arrow(qx, qy, ux, uy);
        arrow(cx - ux * r, cy - uy * r, -ux, -uy);
      }
      if (d > r + 2 * px) seg(qx, qy, cx + ux * (d - 8 * px), cy + uy * (d - 8 * px));   // leader out to the value
      break;
    }
    case ConstraintType::Angle: {
      const auto [ox, oy] = dimensionBase(c);
      const double rho = std::hypot(lx - ox, ly - oy);
      if (rho < 4 * px) break;
      // The two lines' directions; the arc spans the sector the value is in.
      const auto& e1 = sk_.entities[c.entities[0]];
      const auto& e2 = sk_.entities[c.entities[1]];
      const double t1 = std::atan2(P[e1.b].y - P[e1.a].y, P[e1.b].x - P[e1.a].x);
      const double t2 = std::atan2(P[e2.b].y - P[e2.a].y, P[e2.b].x - P[e2.a].x);
      const double tl = std::atan2(ly - oy, lx - ox);
      const double pi = std::numbers::pi;
      auto norm = [&](double a) { return a - 2 * pi * std::floor(a / (2 * pi)); };
      // Of the four rays (each line both ways), the ones either side of tl.
      double lo = -1e9, hi = 1e9;
      for (double ray : {t1, t1 + pi, t2, t2 + pi}) {
        const double d = norm(ray - tl);   // counter-clockwise from tl to the ray
        if (d < norm(hi - tl) || hi > 1e8) hi = tl + d;
        const double back = norm(tl - ray);   // clockwise
        if (back < norm(tl - lo) || lo < -1e8) lo = tl - back;
      }
      const int n = 32;
      double px0 = ox + rho * std::cos(lo), py0 = oy + rho * std::sin(lo);
      for (int k = 1; k <= n; ++k) {
        const double a = lo + (hi - lo) * k / n;
        const double x = ox + rho * std::cos(a), y = oy + rho * std::sin(a);
        seg(px0, py0, x, y);
        px0 = x, py0 = y;
      }
      arrow(ox + rho * std::cos(lo), oy + rho * std::sin(lo), std::sin(lo), -std::cos(lo));
      arrow(ox + rho * std::cos(hi), oy + rho * std::sin(hi), -std::sin(hi), std::cos(hi));
      break;
    }
    default:
      break;
  }
  const TopoDS_Shape gs = sketch::curves(g, frame_, false);
  if (gs.IsNull() || !TopExp_Explorer(gs, TopAbs_EDGE).More()) return;
  Handle(AIS_Shape) a = wire(gs, colour, 1.0, Aspect_TOL_SOLID);
  view_->aisContext()->Display(a, AIS_WireFrame, -1, false);
  view_->aisContext()->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
  out.push_back(a);
}

bool SketchEditor::tangentCircle(double x, double y, double& cx, double& cy, double& r) const {
  // Each line as n.p + d = 0 with n a unit normal.
  struct L { double nx, ny, d; };
  std::vector<L> ls;
  for (int l : tangentLines_) {
    const auto& e = sk_.entities[l];
    const auto& a = sk_.points[e.a];
    const auto& b = sk_.points[e.b];
    const double len = std::hypot(b.x - a.x, b.y - a.y);
    if (len < 1e-12) return false;
    const double nx = -(b.y - a.y) / len, ny = (b.x - a.x) / len;
    ls.push_back({nx, ny, -(nx * a.x + ny * a.y)});
  }
  auto f = [](const L& l, double px, double py) { return l.nx * px + l.ny * py + l.d; };
  if (ls.size() == 2) {
    L a = ls[0], b = ls[1];
    const double cross = a.nx * b.ny - a.ny * b.nx;
    if (std::abs(cross) < 1e-9) {   // parallel: centred between them, the cursor slides it along
      if (a.nx * b.nx + a.ny * b.ny < 0) b = {-b.nx, -b.ny, -b.d};
      const double mid = (a.d + b.d) / 2;
      const double t = a.nx * x + a.ny * y + mid;
      cx = x - a.nx * t, cy = y - a.ny * t;
      r = std::abs(a.d - b.d) / 2;
      return r > 1e-9;
    }
    // In the corner the cursor is in: the centre is on that corner's
    // bisector, where the cursor projects onto it.
    const double s1 = f(a, x, y) >= 0 ? 1 : -1, s2 = f(b, x, y) >= 0 ? 1 : -1;
    const double ox = (a.ny * b.d - b.ny * a.d) / cross, oy = (b.nx * a.d - a.nx * b.d) / cross;   // the crossing
    double dx = -(s1 * a.ny - s2 * b.ny), dy = s1 * a.nx - s2 * b.nx;   // along s1 f1 = s2 f2
    const double n = std::hypot(dx, dy);
    if (n < 1e-12) return false;
    dx /= n, dy /= n;
    const double t = (x - ox) * dx + (y - oy) * dy;
    cx = ox + dx * t, cy = oy + dy * t;
    r = s1 * f(a, cx, cy);
    return r > 1e-9;
  }
  if (ls.size() == 3) {
    // n_i.c + d_i = s_i r for each choice of sides; the circle nearest the
    // clicks (inside the triangle when its sides were clicked).
    double tx = 0, ty = 0;
    for (const auto& [px, py] : tangentClicks_) tx += px / 3, ty += py / 3;
    bool found = false;
    double best = 0;
    for (int m = 0; m < 8; ++m) {
      double A[3][3], B[3];
      for (int i = 0; i < 3; ++i) {
        const double s = (m >> i) & 1 ? -1 : 1;
        A[i][0] = ls[i].nx, A[i][1] = ls[i].ny, A[i][2] = -s, B[i] = -ls[i].d;
      }
      auto det3 = [](double M[3][3]) {
        return M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
               M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
      };
      const double D = det3(A);
      if (std::abs(D) < 1e-12) continue;
      double sol[3];
      for (int k = 0; k < 3; ++k) {   // Cramer's rule
        double M[3][3];
        for (int i = 0; i < 3; ++i)
          for (int j = 0; j < 3; ++j) M[i][j] = j == k ? B[i] : A[i][j];
        sol[k] = det3(M) / D;
      }
      if (sol[2] <= 1e-9) continue;
      const double dist = std::hypot(sol[0] - tx, sol[1] - ty);
      if (!found || dist < best) {
        found = true;
        best = dist;
        cx = sol[0], cy = sol[1], r = sol[2];
      }
    }
    return found;
  }
  return false;
}

std::optional<Constraint> SketchEditor::dimensionCandidate(double x, double y) const {
  if (picks_.empty()) return std::nullopt;
  const auto& P = sk_.points;
  auto isLine = [&](const Hit& h) { return h.kind == Hit::Entity && sk_.entities[h.index].type == EntityType::Line; };
  // Two points measured: horizontal, vertical or aligned, by where the cursor
  // is, as in the familiar sketcher (beside the pair's span: across it).
  auto linear = [&](int a, int b, std::optional<int> line) -> Constraint {
    const auto& p = P[a];
    const auto& q = P[b];
    const double dx = std::abs(q.x - p.x), dy = std::abs(q.y - p.y);
    const bool level = dy <= 1e-9 * (1 + dx), upright = dx <= 1e-9 * (1 + dy);
    const bool inX = x > std::min(p.x, q.x) && x < std::max(p.x, q.x);
    const bool inY = y > std::min(p.y, q.y) && y < std::max(p.y, q.y);
    const bool outX = !inX && !level, outY = !inY && !upright;
    const int left = p.x <= q.x ? a : b, right = left == a ? b : a;
    const int low = p.y <= q.y ? a : b, high = low == a ? b : a;
    if (!line && level) return {ConstraintType::HorizontalDistance, {left, right}};
    if (!line && upright) return {ConstraintType::VerticalDistance, {low, high}};
    if (inX && outY && !level && !upright) return {ConstraintType::HorizontalDistance, {left, right}};
    if (inY && outX && !level && !upright) return {ConstraintType::VerticalDistance, {low, high}};
    if (line) return {ConstraintType::Distance, {}, {*line}};
    return {ConstraintType::Distance, {a, b}};
  };
  const Hit a = picks_[0].hit;
  Constraint c;
  if (picks_.size() == 1) {
    if (a.kind == Hit::Entity && sk_.entities[a.index].type == EntityType::Ellipse) {
      // The half axis the cursor is along: the drawn one (centre to its axis
      // point) or the other (the ellipse's radius).
      const auto& el = sk_.entities[a.index];
      const double ux = P[el.a].x - P[el.center].x, uy = P[el.a].y - P[el.center].y;
      const double along = std::abs((x - P[el.center].x) * ux + (y - P[el.center].y) * uy);
      const double across = std::abs(-(x - P[el.center].x) * uy + (y - P[el.center].y) * ux);
      if (along >= across) c = {ConstraintType::Distance, {el.center, el.a}};
      else c = {ConstraintType::Radius, {}, {a.index}};
    } else if (a.kind == Hit::Entity && sk_.entities[a.index].type == EntityType::Circle) c = {ConstraintType::Diameter, {}, {a.index}};
    else if (a.kind == Hit::Entity && sk_.entities[a.index].type == EntityType::Arc) c = {ConstraintType::Radius, {}, {a.index}};
    else if (isLine(a)) c = linear(sk_.entities[a.index].a, sk_.entities[a.index].b, a.index);
    else return std::nullopt;   // a point: a second pick is needed
  } else {
    const Hit b = picks_[1].hit;
    if (isLine(a) && isLine(b)) c = {ConstraintType::Angle, {}, {a.index, b.index}};
    else if (a.kind == Hit::Point && b.kind == Hit::Point) c = linear(a.index, b.index, std::nullopt);
    else if (a.kind == Hit::Point && isLine(b)) c = {ConstraintType::Distance, {a.index}, {b.index}};
    else if (isLine(a) && b.kind == Hit::Point) c = {ConstraintType::Distance, {b.index}, {a.index}};
    else return std::nullopt;
  }
  const auto [bx, by] = dimensionBase(c);
  c.hasLabel = true;
  c.labelX = x - bx;
  c.labelY = y - by;
  return c;
}

QString SketchEditor::labelText(const Constraint& c) const {
  if (c.driven) {   // a reference dimension: what the geometry measures, in brackets
    Constraint measured = c;
    measured.driven = false;
    measured.expression.clear();
    measured.value = currentValue(c);
    return QStringLiteral("(%1)").arg(labelText(measured));
  }
  switch (c.type) {
    case ConstraintType::Horizontal: return QStringLiteral("H");
    case ConstraintType::Vertical: return QStringLiteral("V");
    case ConstraintType::Parallel: return QStringLiteral("//");
    case ConstraintType::Perpendicular: return QString::fromUtf8("⊥");
    case ConstraintType::Equal: return QStringLiteral("=");
    case ConstraintType::Tangent: return QStringLiteral("T");
    case ConstraintType::Concentric: return QString::fromUtf8("◎");
    case ConstraintType::Fix: return QString::fromUtf8("⌖");
    case ConstraintType::Midpoint: return QStringLiteral("M");
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance:
      return QString::number(fromInternal(std::abs(c.value), unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Radius:
      return QStringLiteral("R") + QString::number(fromInternal(c.value, unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Diameter:
      return QString::fromUtf8("⌀") + QString::number(fromInternal(c.value, unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Angle:
      return QString::number(fromInternal(c.value, Unit::Degree), 'f', 1) + QString::fromUtf8("°");
    default:
      return {};
  }
}

void SketchEditor::setDisplay(const Display& d) {
  display_ = d;
  rebuild();
}

void SketchEditor::rebuild() {
  if (!view_) return;
  const auto& ctx = view_->aisContext();
  if (ctx.IsNull()) return;
  for (auto& o : objects_) ctx->Remove(o, false);
  objects_.clear();

  // Closed regions, lightly shaded (what Extrude can pick after Finish).
  if (display_.profiles) {
    try {
      for (const auto& pr : cachedProfiles(sk_, frame_)) {
        Handle(AIS_Shape) f = new AIS_Shape(pr.face);
        Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
        const Quantity_Color c = rgb(120, 170, 230);
        m.SetDiffuseColor(c);
        m.SetAmbientColor(c);
        m.SetSpecularColor(Quantity_Color(Quantity_NOC_BLACK));
        m.SetEmissiveColor(Quantity_Color(c.Rgb() * 0.3f));
        f->SetMaterial(m);
        f->SetTransparency(0.8);
        f->Attributes()->SetFaceBoundaryDraw(false);
        ctx->Display(f, AIS_Shaded, -1, false);
        objects_.push_back(f);
      }
    } catch (const std::exception&) {
    }
  }

  auto selected = [&](Hit::Kind k, int i) {
    for (const auto& s : selection_)
      if (s.kind == k && s.index == i) return true;
    for (const auto& p : picks_)
      if (p.hit.kind == k && p.hit.index == i) return true;
    if (k == Hit::Entity && std::find(tangentLines_.begin(), tangentLines_.end(), i) != tangentLines_.end()) return true;
    return false;
  };
  auto hovered = [&](Hit::Kind k, int i) { return hover_.kind == k && hover_.index == i; };
  auto colorFor = [&](Hit::Kind k, int i, bool fixed, bool construction) {
    if (selected(k, i)) return kSelected;
    if (hovered(k, i)) return kHover;
    if (construction) return kConstruction;
    return fixed ? fixedColor() : freeColor();
  };

  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const TopoDS_Shape s = sketch::curve(sk_, frame_, i);
    if (s.IsNull()) continue;
    const auto& e = sk_.entities[i];
    if (e.construction && !display_.construction) continue;
    if (e.projected && !display_.projected) continue;
    const bool fixed = res_.ok && i < static_cast<int>(res_.entityFixed.size()) && res_.entityFixed[i];
    const bool hl = selected(Hit::Entity, i) || hovered(Hit::Entity, i);
    const Quantity_Color colour = e.projected && !hl ? rgb(190, 110, 235) : colorFor(Hit::Entity, i, fixed, e.construction);
    Handle(AIS_Shape) a = wire(s, colour, hl ? 3.0 : 2.0, e.construction ? Aspect_TOL_DASH : Aspect_TOL_SOLID);
    ctx->Display(a, AIS_WireFrame, -1, false);
    ctx->SetZLayer(a, Graphic3d_ZLayerId_Topmost);   // never hidden behind bodies
    objects_.push_back(a);
    if (e.type == EntityType::Spline && e.kind != sketch::SplineKind::Fit && e.fit.size() >= 2) {
      // Its frame (control points, or a conic's tangents to the vertex), dashed.
      sketch::Sketch frame;
      frame.points = sk_.points;
      for (size_t k = 1; k < e.fit.size(); ++k) frame.entities.push_back(lineEntity(e.fit[k - 1], e.fit[k]));
      const TopoDS_Shape fs = sketch::curves(frame, frame_, false);
      if (!fs.IsNull()) {
        Handle(AIS_Shape) fa = wire(fs, colour, 1.0, Aspect_TOL_DOT);
        ctx->Display(fa, AIS_WireFrame, -1, false);
        ctx->SetZLayer(fa, Graphic3d_ZLayerId_Topmost);
        objects_.push_back(fa);
      }
    }
  }
  // Tangent handles of selected fit point splines: set ones green, free
  // ones (the curve's own direction) grey.
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    if (!showsHandles(i)) continue;
    for (const auto& h : sketch::splineHandles(sk_, i)) {
      const double ex = h.tx * h.arm, ey = h.ty * h.arm;
      if (std::hypot(ex, ey) < 1e-9) continue;
      const Quantity_Color col = h.set ? rgb(80, 200, 120) : rgb(150, 150, 150);
      sketch::Sketch hs;
      hs.addLine(h.x - ex, h.y - ey, h.x + ex, h.y + ey);
      if (const TopoDS_Shape sh = sketch::curves(hs, frame_, false); !sh.IsNull()) {
        Handle(AIS_Shape) a = wire(sh, col, 1.5, Aspect_TOL_SOLID);
        ctx->Display(a, AIS_WireFrame, -1, false);
        ctx->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
        objects_.push_back(a);
      }
      for (double sg : {-1.0, 1.0}) {
        Handle(AIS_Point) p = new AIS_Point(new Geom_CartesianPoint(sketch::toWorld(frame_, h.x + sg * ex, h.y + sg * ey)));
        p->Attributes()->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_O_POINT, col, 2.0));
        ctx->Display(p, 0, -1, false);
        ctx->SetZLayer(p, Graphic3d_ZLayerId_Topmost);
        objects_.push_back(p);
      }
    }
  }
  for (int i = 0; i < static_cast<int>(sk_.texts.size()); ++i) {
    const TopoDS_Shape ts = sketch::textShape(sk_, frame_, i);
    if (ts.IsNull()) continue;
    const bool fixed = res_.ok && sk_.texts[i].point < static_cast<int>(res_.pointFixed.size()) && res_.pointFixed[sk_.texts[i].point];
    Handle(AIS_Shape) a = wire(ts, fixed ? fixedColor() : freeColor(), 1.5, Aspect_TOL_SOLID);
    ctx->Display(a, AIS_WireFrame, -1, false);
    ctx->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
    objects_.push_back(a);
    if (const auto& t = sk_.texts[i]; t.corner >= 0) {
      // The text box, dashed, in the text's own frame.
      const double c = std::cos(t.angle), sn = std::sin(t.angle);
      const auto& p0 = sk_.points[t.point];
      const auto& p1 = sk_.points[t.corner];
      const double u = (p1.x - p0.x) * c + (p1.y - p0.y) * sn, v = -(p1.x - p0.x) * sn + (p1.y - p0.y) * c;
      auto at = [&](double uu, double vv) { return std::make_pair(p0.x + uu * c - vv * sn, p0.y + uu * sn + vv * c); };
      sketch::Sketch frame;
      const std::pair<double, double> corners[4] = {at(0, 0), at(u, 0), at(u, v), at(0, v)};
      for (int k = 0; k < 4; ++k)
        frame.addLine(corners[k].first, corners[k].second, corners[(k + 1) % 4].first, corners[(k + 1) % 4].second);
      const TopoDS_Shape fs = sketch::curves(frame, frame_, false);
      if (!fs.IsNull()) {
        Handle(AIS_Shape) fa = wire(fs, kConstruction, 1.0, Aspect_TOL_DASH);
        ctx->Display(fa, AIS_WireFrame, -1, false);
        ctx->SetZLayer(fa, Graphic3d_ZLayerId_Topmost);
        objects_.push_back(fa);
      }
    }
  }
  for (int i = 0; i < static_cast<int>(sk_.points.size()); ++i) {
    if (!display_.points && i != 0 && !selected(Hit::Point, i) && !hovered(Hit::Point, i)) continue;
    const bool fixed = res_.ok && i < static_cast<int>(res_.pointFixed.size()) && res_.pointFixed[i];
    // Included 3D geometry: its points stand where they are in space.
    const gp_Pnt at = sketch::toWorld(frame_, sk_.points[i].x, sk_.points[i].y)
                          .Translated(gp_Vec(frame_.Direction()) * sk_.points[i].z);
    Handle(AIS_Point) p = new AIS_Point(new Geom_CartesianPoint(at));
    const Quantity_Color c = i == 0 && !selected(Hit::Point, 0) && !hovered(Hit::Point, 0)
                                 ? rgb(200, 40, 40)
                                 : colorFor(Hit::Point, i, fixed, false);
    const bool big = selected(Hit::Point, i) || hovered(Hit::Point, i);
    p->Attributes()->SetPointAspect(new Prs3d_PointAspect(big ? Aspect_TOM_O_POINT : Aspect_TOM_POINT, c, big ? 2.5 : 4.0));
    ctx->Display(p, 0, -1, false);
    ctx->SetZLayer(p, Graphic3d_ZLayerId_Topmost);
    objects_.push_back(p);
  }
  for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i) {
    const auto anchor = labelAnchor(i);
    if (!anchor) continue;
    const auto& c = sk_.constraints[i];
    if (sketch::isDimension(c.type) ? !display_.dimensions : !display_.constraints) continue;
    if (onlyProjected(c)) continue;
    const Quantity_Color labelColour = selected(Hit::Label, i) ? kSelected
                                       : hovered(Hit::Label, i) ? kHover
                                       : sketch::isDimension(c.type) ? qc(themeColors().sketchLabel)
                                                                     : qc(themeColors().sketchGlyph);
    if (sketch::isDimension(c.type)) addDimensionGraphics(c, anchor->first, anchor->second, labelColour, objects_);
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(ext(labelText(c)));
    t->SetPosition(sketch::toWorld(frame_, anchor->first, anchor->second));
    t->SetHeight(sketch::isDimension(c.type) ? 14 : 12);
    t->SetColor(labelColour);
    t->SetHJustification(Graphic3d_HTA_CENTER);
    t->SetVJustification(Graphic3d_VTA_CENTER);
    ctx->Display(t, 0, -1, false);
    ctx->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
    objects_.push_back(t);
  }
  view_->redraw();
}

void SketchEditor::finishSpline(bool closed) {
  if (steps_.size() < 2) return;
  checkpoint();
  std::vector<int> fit;
  for (const auto& p : steps_) {
    const int i = materialize(p);
    if (fit.empty() || fit.back() != i) fit.push_back(i);
  }
  if (closed && fit.size() >= 3) fit.push_back(fit.front());
  if (fit.size() < 2) {
    undo_.pop_back();
    resetSteps();
    return;
  }
  sk_.addSpline(fit, construction_, tool_ == Tool::ControlSpline ? sketch::SplineKind::Control : sketch::SplineKind::Fit);
  resetSteps();
  solveAndShow();
}

void SketchEditor::commitCurve() {
  if ((tool_ == Tool::Spline || tool_ == Tool::ControlSpline) && steps_.size() >= 2) finishSpline(false);
}

std::vector<std::pair<double, double>> SketchEditor::curveSamples(int entity) const {
  std::vector<std::pair<double, double>> out;
  const TopoDS_Shape s = sketch::curve(sk_, frame_, entity);
  if (s.IsNull()) return out;
  BRepAdaptor_Curve c(TopoDS::Edge(s));
  const int n = 64;
  for (int i = 0; i <= n; ++i) {
    const gp_Pnt p = c.Value(c.FirstParameter() + (c.LastParameter() - c.FirstParameter()) * i / n);
    double x, y;
    sketch::toSketch(frame_, p, x, y);
    out.emplace_back(x, y);
  }
  return out;
}

double SketchEditor::entityDistance(int entity, double x, double y) const {
  if (entity < 0 || entity >= static_cast<int>(sk_.entities.size())) return 1e300;
  const auto& e = sk_.entities[entity];
  if (e.type == EntityType::Line) {
    const auto &a = sk_.points[e.a], &b = sk_.points[e.b];
    return segDistance(x, y, a.x, a.y, b.x, b.y);
  }
  if (sketch::isRound(e.type)) {
    const auto& c = sk_.points[e.center];
    return std::abs(std::hypot(x - c.x, y - c.y) - e.radius);
  }
  const auto pts = curveSamples(entity);
  double best = 1e300;
  for (size_t i = 1; i < pts.size(); ++i)
    best = std::min(best, segDistance(x, y, pts[i - 1].first, pts[i - 1].second, pts[i].first, pts[i].second));
  return best;
}

double SketchEditor::filletRadiusAt(double x, double y) const {
  if (steps_.empty()) return 0;
  // Half the cursor's distance from the corner: a natural feel when dragging out.
  return std::max(std::hypot(x - steps_.front().x, y - steps_.front().y) * 0.5, tolerance() / 4);
}

double SketchEditor::offsetAt(double x, double y, double magnitude) const {
  if (offsetEntity_ < 0) return 0;
  const double m = magnitude > 0 ? magnitude : std::max(entityDistance(offsetEntity_, x, y), tolerance() / 4);
  // Whichever side's copy passes nearer the cursor.
  double best = m, bestD = 1e300;
  for (double d : {m, -m}) {
    sketch::Sketch trial = sk_;
    std::vector<int> made;
    if (!sketch::offsetChain(trial, offsetEntity_, d, &made).empty()) continue;
    double dist = 1e300;
    for (int e : made) {
      const auto& en = trial.entities[e];
      if (en.type == EntityType::Line) {
        const auto &a = trial.points[en.a], &b = trial.points[en.b];
        dist = std::min(dist, segDistance(x, y, a.x, a.y, b.x, b.y));
      } else if (en.type == EntityType::Spline || en.type == EntityType::Ellipse) {
        const TopoDS_Shape sh = sketch::curve(trial, frame_, e);
        if (sh.IsNull()) continue;
        BRepAdaptor_Curve c(TopoDS::Edge(sh));
        double px = 0, py = 0;
        for (int k = 0; k <= 48; ++k) {
          double qx, qy;
          sketch::toSketch(frame_, c.Value(c.FirstParameter() + (c.LastParameter() - c.FirstParameter()) * k / 48), qx, qy);
          if (k > 0) dist = std::min(dist, segDistance(x, y, px, py, qx, qy));
          px = qx;
          py = qy;
        }
      } else {
        const auto& c = trial.points[en.center];
        dist = std::min(dist, std::abs(std::hypot(x - c.x, y - c.y) - en.radius));
      }
    }
    if (dist < bestD) {
      bestD = dist;
      best = d;
    }
  }
  return best;
}

void SketchEditor::clearPreview() {
  if (!view_) return;
  const auto& ctx = view_->aisContext();
  if (!ctx.IsNull())
    for (auto& o : preview_) ctx->Remove(o, false);
  preview_.clear();
}

void SketchEditor::updatePreview(double x, double y) {
  clearPreview();
  if (tool_ == Tool::Dimension && view_ && !view_->aisContext().IsNull()) {
    if (const auto c = dimensionCandidate(x, y)) {
      addDimensionGraphics(*c, x, y, kPreview, preview_);
      Handle(AIS_TextLabel) t = new AIS_TextLabel();
      Constraint shown = *c;
      shown.value = currentValue(*c);
      t->SetText(ext(labelText(shown)));
      t->SetPosition(sketch::toWorld(frame_, x, y));
      t->SetHeight(14);
      t->SetColor(kPreview);
      t->SetHJustification(Graphic3d_HTA_CENTER);
      t->SetVJustification(Graphic3d_VTA_CENTER);
      view_->aisContext()->Display(t, 0, -1, false);
      view_->aisContext()->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
      preview_.push_back(t);
    }
    view_->redraw();
    return;
  }
  const bool drawing = tool_ == Tool::Line || tool_ == Tool::Rectangle || tool_ == Tool::CenterRectangle ||
                       tool_ == Tool::Circle || tool_ == Tool::Arc || tool_ == Tool::Point || tool_ == Tool::Polygon ||
                       tool_ == Tool::Slot || tool_ == Tool::Spline || tool_ == Tool::ThreePointRectangle ||
                       tool_ == Tool::TwoPointCircle || tool_ == Tool::ThreePointCircle || tool_ == Tool::ThreePointArc ||
                       tool_ == Tool::TangentArc || tool_ == Tool::ControlSpline || tool_ == Tool::Conic ||
                       tool_ == Tool::OverallSlot || tool_ == Tool::ArcSlot || tool_ == Tool::Ellipse;
  if (view_ && drawing && !(hudTool() && !steps_.empty() && hudAnyLocked())) showSnap(snapAt(x, y));
  if (view_ && tool_ == Tool::TwoTangentCircle && tangentLines_.size() == 2) {
    double cx, cy, r;
    if (tangentCircle(x, y, cx, cy, r)) {
      sketch::Sketch t;
      t.addCircle(cx, cy, r);
      const TopoDS_Shape s = sketch::curves(t, frame_, false);
      if (!s.IsNull() && !view_->aisContext().IsNull()) {
        Handle(AIS_Shape) w = wire(s, kPreview, 1.5, Aspect_TOL_DASH);
        view_->aisContext()->Display(w, AIS_WireFrame, -1, false);
        view_->aisContext()->SetZLayer(w, Graphic3d_ZLayerId_Topmost);
        preview_.push_back(w);
      }
    }
    view_->redraw();
    return;
  }
  if (!view_ || steps_.empty()) {
    if (view_) view_->redraw();
    return;
  }
  if (hudTool()) {
    ensureHud();
    std::tie(x, y) = hudTarget(x, y);
    if (!hudAnyLocked() && tool_ != Tool::Fillet && tool_ != Tool::Chamfer && tool_ != Tool::Offset) {
      const Pick snap = pickPoint(x, y);
      x = snap.x;
      y = snap.y;
    }
    updateHud(x, y);
  } else {
    const Pick snap = pickPoint(x, y);
    x = snap.x;
    y = snap.y;
  }
  sketch::Sketch tmp;
  const auto& a = steps_.front();
  TopoDS_Shape special;   // preview made from a trial copy of the sketch
  auto trialCurves = [&](const sketch::Sketch& trial, const std::vector<int>& ents) {
    TopoDS_Compound c;
    BRep_Builder bb;
    bb.MakeCompound(c);
    for (int e : ents)
      if (const TopoDS_Shape sh = sketch::curve(trial, frame_, e); !sh.IsNull()) bb.Add(c, sh);
    special = c;
  };
  switch (tool_) {
    case Tool::ControlSpline:
    case Tool::Spline: {
      std::vector<int> fit;
      for (const auto& p : steps_) fit.push_back(tmp.addPoint(p.x, p.y));
      if (std::hypot(x - steps_.back().x, y - steps_.back().y) > 1e-9) fit.push_back(tmp.addPoint(x, y));
      if (fit.size() >= 2) {
        tmp.addSpline(fit, false, tool_ == Tool::ControlSpline ? sketch::SplineKind::Control : sketch::SplineKind::Fit);
        if (tool_ == Tool::ControlSpline)   // the frame too
          for (size_t i = 1; i < fit.size(); ++i) tmp.entities.push_back(lineEntity(fit[i - 1], fit[i]));
      }
      break;
    }
    case Tool::Conic: {
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
        break;
      }
      const int ps = tmp.addPoint(a.x, a.y), pe = tmp.addPoint(steps_[1].x, steps_[1].y), pv = tmp.addPoint(x, y);
      const double cross = (steps_[1].x - a.x) * (y - a.y) - (steps_[1].y - a.y) * (x - a.x);
      if (std::abs(cross) > 1e-9) {
        tmp.addConic(ps, pv, pe, 0.5);
        tmp.entities.push_back(lineEntity(ps, pv));
        tmp.entities.push_back(lineEntity(pv, pe));
      } else {
        tmp.entities.push_back(lineEntity(ps, pe));
      }
      break;
    }
    case Tool::Fillet: {
      sketch::Sketch trial = sk_;
      int arc = -1;
      const double r = hudLocked(0) ? hudValue(0) : filletRadiusAt(x, y);
      if (filletLines_.first >= 0 && sketch::filletCorner(trial, filletLines_.first, filletLines_.second, r, &arc).empty())
        trialCurves(trial, {arc, filletLines_.first, filletLines_.second});
      break;
    }
    case Tool::Chamfer: {
      sketch::Sketch trial = sk_;
      int line = -1;
      const double d = hudLocked(0) ? hudValue(0) : filletRadiusAt(x, y);
      if (filletLines_.first >= 0 && sketch::chamferCorner(trial, filletLines_.first, filletLines_.second, d, &line).empty())
        trialCurves(trial, {line, filletLines_.first, filletLines_.second});
      break;
    }
    case Tool::Offset: {
      sketch::Sketch trial = sk_;
      std::vector<int> made;
      const double d = offsetAt(x, y, hudLocked(0) ? hudValue(0) : 0);
      if (offsetEntity_ >= 0 && std::abs(d) > 1e-9 && sketch::offsetChain(trial, offsetEntity_, d, &made).empty())
        trialCurves(trial, made);
      break;
    }
    case Tool::CenterRectangle: {
      const double hx = std::abs(x - a.x), hy = std::abs(y - a.y);
      if (hx > 1e-9 && hy > 1e-9) {
        tmp.addLine(a.x - hx, a.y - hy, a.x + hx, a.y - hy);
        tmp.addLine(a.x + hx, a.y - hy, a.x + hx, a.y + hy);
        tmp.addLine(a.x + hx, a.y + hy, a.x - hx, a.y + hy);
        tmp.addLine(a.x - hx, a.y + hy, a.x - hx, a.y - hy);
      }
      break;
    }
    case Tool::Polygon: {
      const double r = std::hypot(x - a.x, y - a.y);
      const int n = polygonSides();
      const double a0 = std::atan2(y - a.y, x - a.x);
      if (r > 1e-9)
        for (int i = 0; i < n; ++i) {
          const double t0 = a0 + 2 * kPi * i / n, t1 = a0 + 2 * kPi * (i + 1) / n;
          tmp.addLine(a.x + r * std::cos(t0), a.y + r * std::sin(t0), a.x + r * std::cos(t1), a.y + r * std::sin(t1));
        }
      break;
    }
    case Tool::Slot: {
      const double len = std::hypot(x - a.x, y - a.y);
      if (len > 1e-9) {
        const double r = (hudLocked(1) ? hudValue(1) : len / 3) / 2;
        const double ux = (x - a.x) / len, uy = (y - a.y) / len, nx = -uy, ny = ux;
        tmp.addLine(a.x + nx * r, a.y + ny * r, x + nx * r, y + ny * r);
        tmp.addLine(a.x - nx * r, a.y - ny * r, x - nx * r, y - ny * r);
        const int c2 = tmp.addPoint(x, y), s2 = tmp.addPoint(x - nx * r, y - ny * r), e2 = tmp.addPoint(x + nx * r, y + ny * r);
        tmp.addArc(c2, s2, e2);
        const int c1 = tmp.addPoint(a.x, a.y), s1 = tmp.addPoint(a.x + nx * r, a.y + ny * r), e1 = tmp.addPoint(a.x - nx * r, a.y - ny * r);
        tmp.addArc(c1, s1, e1);
      }
      break;
    }
    case Tool::Line: {
      const auto& b = steps_.back();
      if (std::hypot(x - b.x, y - b.y) > 1e-9) tmp.addLine(b.x, b.y, x, y);
      break;
    }
    case Tool::Rectangle:
      if (std::abs(x - a.x) > 1e-9 && std::abs(y - a.y) > 1e-9) {
        tmp.addLine(a.x, a.y, x, a.y);
        tmp.addLine(x, a.y, x, y);
        tmp.addLine(x, y, a.x, y);
        tmp.addLine(a.x, y, a.x, a.y);
      }
      break;
    case Tool::Circle: {
      const double r = std::hypot(x - a.x, y - a.y);
      if (r > 1e-9) tmp.addCircle(a.x, a.y, r);
      break;
    }
    case Tool::TwoPointCircle: {
      const double r = std::hypot(x - a.x, y - a.y) / 2;
      if (r > 1e-9) tmp.addCircle((a.x + x) / 2, (a.y + y) / 2, r);
      break;
    }
    case Tool::ThreePointCircle: {
      double cx, cy, r;
      if (steps_.size() == 1) tmp.addLine(a.x, a.y, x, y);
      else if (circumcircle(a.x, a.y, steps_[1].x, steps_[1].y, x, y, cx, cy, r)) tmp.addCircle(cx, cy, r);
      break;
    }
    case Tool::Text: {
      if (std::abs(x - a.x) > 1e-9 && std::abs(y - a.y) > 1e-9) {
        tmp.addLine(a.x, a.y, x, a.y);
        tmp.addLine(x, a.y, x, y);
        tmp.addLine(x, y, a.x, y);
        tmp.addLine(a.x, y, a.x, a.y);
      }
      break;
    }
    case Tool::TangentArc: {
      double cx, cy, r;
      bool ccw;
      if (tangentArc(x, y, cx, cy, r, ccw)) {
        const int c = tmp.addPoint(cx, cy), ps = tmp.addPoint(a.x, a.y), pe = tmp.addPoint(x, y);
        if (ccw) tmp.addArc(c, ps, pe);
        else tmp.addArc(c, pe, ps);
      }
      break;
    }
    case Tool::ThreePointArc: {
      double cx, cy, r;
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
      } else if (circumcircle(a.x, a.y, steps_[1].x, steps_[1].y, x, y, cx, cy, r)) {
        const int c = tmp.addPoint(cx, cy), ps = tmp.addPoint(a.x, a.y), pe = tmp.addPoint(steps_[1].x, steps_[1].y);
        const double as = std::atan2(a.y - cy, a.x - cx), ae = std::atan2(steps_[1].y - cy, steps_[1].x - cx);
        if (ccwContains(as, ae, std::atan2(y - cy, x - cx))) tmp.addArc(c, ps, pe);
        else tmp.addArc(c, pe, ps);
      } else {
        tmp.addLine(a.x, a.y, steps_[1].x, steps_[1].y);
      }
      break;
    }
    case Tool::Ellipse: {
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
        break;
      }
      const auto& e = steps_[1];
      const double A = std::hypot(e.x - a.x, e.y - a.y);
      const double B = A > 1e-12 ? std::abs((x - a.x) * -(e.y - a.y) / A + (y - a.y) * (e.x - a.x) / A) : 0;
      if (B > 1e-9) tmp.addEllipse(tmp.addPoint(a.x, a.y), tmp.addPoint(e.x, e.y), B);
      else tmp.addLine(a.x, a.y, e.x, e.y);
      break;
    }
    case Tool::OverallSlot: {
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
        break;
      }
      const auto& b = steps_[1];
      const double len = std::hypot(b.x - a.x, b.y - a.y);
      if (len < 1e-12) break;
      const double ux = (b.x - a.x) / len, uy = (b.y - a.y) / len, nx = -uy, ny = ux;
      const double r = std::abs((x - a.x) * nx + (y - a.y) * ny);
      if (r < 1e-9 || 2 * r >= len) {
        tmp.addLine(a.x, a.y, b.x, b.y);
        break;
      }
      const double x1 = a.x + ux * r, y1 = a.y + uy * r, x2 = b.x - ux * r, y2 = b.y - uy * r;
      tmp.addLine(x1 + nx * r, y1 + ny * r, x2 + nx * r, y2 + ny * r);
      tmp.addLine(x1 - nx * r, y1 - ny * r, x2 - nx * r, y2 - ny * r);
      const int c2 = tmp.addPoint(x2, y2), c1 = tmp.addPoint(x1, y1);
      tmp.addArc(c2, tmp.addPoint(x2 - nx * r, y2 - ny * r), tmp.addPoint(x2 + nx * r, y2 + ny * r));
      tmp.addArc(c1, tmp.addPoint(x1 + nx * r, y1 + ny * r), tmp.addPoint(x1 - nx * r, y1 - ny * r));
      break;
    }
    case Tool::ArcSlot: {
      const double R = steps_.size() >= 2 ? std::hypot(steps_[1].x - a.x, steps_[1].y - a.y) : std::hypot(x - a.x, y - a.y);
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
        break;
      }
      const double as = std::atan2(steps_[1].y - a.y, steps_[1].x - a.x);
      const double ae = std::atan2((steps_.size() >= 3 ? steps_[2].y : y) - a.y, (steps_.size() >= 3 ? steps_[2].x : x) - a.x);
      const double w2 = steps_.size() >= 3 ? std::abs(std::hypot(x - a.x, y - a.y) - R) : 0;
      const int c = tmp.addPoint(a.x, a.y);
      auto at = [&](double rad, double ang) { return tmp.addPoint(a.x + rad * std::cos(ang), a.y + rad * std::sin(ang)); };
      if (w2 < 1e-9 || w2 >= R) {
        tmp.addArc(c, at(R, as), at(R, ae));
        break;
      }
      tmp.addArc(c, at(R + w2, as), at(R + w2, ae));
      tmp.addArc(c, at(R - w2, as), at(R - w2, ae));
      tmp.addArc(at(R, as), at(R - w2, as), at(R + w2, as));
      tmp.addArc(at(R, ae), at(R + w2, ae), at(R - w2, ae));
      break;
    }
    case Tool::ThreePointRectangle: {
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
        break;
      }
      const auto& b = steps_[1];
      const double len = std::hypot(b.x - a.x, b.y - a.y);
      if (len < 1e-12) break;
      const double nx = -(b.y - a.y) / len, ny = (b.x - a.x) / len;
      const double h = (x - a.x) * nx + (y - a.y) * ny;
      tmp.addLine(a.x, a.y, b.x, b.y);
      tmp.addLine(b.x, b.y, b.x + nx * h, b.y + ny * h);
      tmp.addLine(b.x + nx * h, b.y + ny * h, a.x + nx * h, a.y + ny * h);
      tmp.addLine(a.x + nx * h, a.y + ny * h, a.x, a.y);
      break;
    }
    case Tool::Arc:
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
      } else {
        const auto& s = steps_[1];
        const double r = std::hypot(s.x - a.x, s.y - a.y);
        const double ang = std::atan2(y - a.y, x - a.x);
        const int c = tmp.addPoint(a.x, a.y);
        const int ps = tmp.addPoint(s.x, s.y);
        const int pe = tmp.addPoint(a.x + r * std::cos(ang), a.y + r * std::sin(ang));
        if (r > 1e-9) tmp.addArc(c, ps, pe);
      }
      break;
    default:
      break;
  }
  const TopoDS_Shape s = special.IsNull() ? sketch::curves(tmp, frame_, false) : special;
  const auto& ctx = view_->aisContext();
  if (!s.IsNull() && !ctx.IsNull()) {
    Handle(AIS_Shape) w = wire(s, kPreview, 1.5, Aspect_TOL_DASH);
    ctx->Display(w, AIS_WireFrame, -1, false);
    ctx->SetZLayer(w, Graphic3d_ZLayerId_Topmost);
    preview_.push_back(w);
    // Rectangles: dimension lines with extension lines and arrowheads for
    // width (above) and height (left), where the size boxes sit.
    if (tool_ == Tool::Rectangle || tool_ == Tool::CenterRectangle) {
      const bool centred = tool_ == Tool::CenterRectangle;
      const double hx = std::abs(x - a.x), hy = std::abs(y - a.y);
      const double x0 = centred ? a.x - hx : std::min(a.x, x), x1 = centred ? a.x + hx : std::max(a.x, x);
      const double y0 = centred ? a.y - hy : std::min(a.y, y), y1 = centred ? a.y + hy : std::max(a.y, y);
      const double off = view_->modelPerPixel() * 22 * 1.6, ext = off * 1.25, h = off * 0.28;
      sketch::Sketch dims;
      dims.addLine(x0, y1, x0, y1 + ext);
      dims.addLine(x1, y1, x1, y1 + ext);
      dims.addLine(x0, y1 + off, x1, y1 + off);
      dims.addLine(x0, y1 + off, x0 + h, y1 + off + h * 0.45);
      dims.addLine(x0, y1 + off, x0 + h, y1 + off - h * 0.45);
      dims.addLine(x1, y1 + off, x1 - h, y1 + off + h * 0.45);
      dims.addLine(x1, y1 + off, x1 - h, y1 + off - h * 0.45);
      dims.addLine(x0, y0, x0 - ext, y0);
      dims.addLine(x0, y1, x0 - ext, y1);
      dims.addLine(x0 - off, y0, x0 - off, y1);
      dims.addLine(x0 - off, y0, x0 - off + h * 0.45, y0 + h);
      dims.addLine(x0 - off, y0, x0 - off - h * 0.45, y0 + h);
      dims.addLine(x0 - off, y1, x0 - off + h * 0.45, y1 - h);
      dims.addLine(x0 - off, y1, x0 - off - h * 0.45, y1 - h);
      const TopoDS_Shape ds = hx > 1e-9 && hy > 1e-9 ? sketch::curves(dims, frame_, false) : TopoDS_Shape();
      if (!ds.IsNull()) {
        Handle(AIS_Shape) d = wire(ds, Quantity_Color(0.55, 0.85, 0.22, Quantity_TOC_sRGB), 1.2, Aspect_TOL_SOLID);
        ctx->Display(d, AIS_WireFrame, -1, false);
        ctx->SetZLayer(d, Graphic3d_ZLayerId_Topmost);
        preview_.push_back(d);
      }
    }
    // Tools with size boxes show their sizes there; the rest get a label.
    QString text;
    double lx = x, ly = y;
    switch (tool_) {
      case Tool::Line: {
        const auto& b = steps_.back();
        text = lengthText(std::hypot(x - b.x, y - b.y));
        const double ang = std::atan2(y - b.y, x - b.x) * 180.0 / kPi;
        text += QStringLiteral("   %1\u00B0").arg(ang, 0, 'f', 1);
        lx = (x + b.x) / 2;
        ly = (y + b.y) / 2;
        break;
      }
      case Tool::Rectangle:
        text = lengthText(std::abs(x - a.x)) + QStringLiteral(" \u00D7 ") + lengthText(std::abs(y - a.y));
        lx = (x + a.x) / 2;
        ly = (y + a.y) / 2;
        break;
      case Tool::Circle:
        text = QString::fromUtf8("\u2300 ") + lengthText(2 * std::hypot(x - a.x, y - a.y));
        break;
      case Tool::Arc:
        if (steps_.size() > 1) text = QStringLiteral("R ") + lengthText(std::hypot(steps_[1].x - a.x, steps_[1].y - a.y));
        break;
      default:
        break;
    }
    if (hudTool()) text.clear();   // sizes are shown in the boxes
    if (!text.isEmpty()) {
      Handle(AIS_TextLabel) t = new AIS_TextLabel();
      t->SetText(ext(text));
      t->SetPosition(sketch::toWorld(frame_, lx, ly));
      t->SetHeight(14);
      t->SetColor(qc(themeColors().sketchLabel));
      t->SetHJustification(Graphic3d_HTA_CENTER);
      t->SetVJustification(Graphic3d_VTA_BOTTOM);
      ctx->Display(t, 0, -1, false);
      ctx->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
      preview_.push_back(t);
    }
  }
  view_->redraw();
}

} // namespace tsr::app
