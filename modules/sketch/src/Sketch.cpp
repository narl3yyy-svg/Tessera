#include "tsr/sketch/Sketch.h"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <cmath>
#include <map>
#include <set>

namespace tsr::sketch {

namespace {
struct TypeName {
  ConstraintType type;
  const char* name;
};
constexpr TypeName kTypeNames[] = {
    {ConstraintType::Coincident, "coincident"},
    {ConstraintType::Horizontal, "horizontal"},
    {ConstraintType::Vertical, "vertical"},
    {ConstraintType::Parallel, "parallel"},
    {ConstraintType::Perpendicular, "perpendicular"},
    {ConstraintType::Equal, "equal"},
    {ConstraintType::Tangent, "tangent"},
    {ConstraintType::PointOnEntity, "pointOnEntity"},
    {ConstraintType::Midpoint, "midpoint"},
    {ConstraintType::Concentric, "concentric"},
    {ConstraintType::Fix, "fix"},
    {ConstraintType::Collinear, "collinear"},
    {ConstraintType::Symmetry, "symmetry"},
    {ConstraintType::Distance, "distance"},
    {ConstraintType::HorizontalDistance, "horizontalDistance"},
    {ConstraintType::VerticalDistance, "verticalDistance"},
    {ConstraintType::Radius, "radius"},
    {ConstraintType::Diameter, "diameter"},
    {ConstraintType::Angle, "angle"},
};

const char* entityTypeName(EntityType t) {
  switch (t) {
    case EntityType::Line: return "line";
    case EntityType::Circle: return "circle";
    case EntityType::Arc: return "arc";
    case EntityType::Spline: return "spline";
    case EntityType::Ellipse: return "ellipse";
  }
  return "?";
}
} // namespace

bool isDimension(ConstraintType t) {
  switch (t) {
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance:
    case ConstraintType::Radius:
    case ConstraintType::Diameter:
    case ConstraintType::Angle:
      return true;
    default:
      return false;
  }
}

const char* typeName(ConstraintType t) {
  for (const auto& tn : kTypeNames)
    if (tn.type == t) return tn.name;
  return "?";
}

Sketch::Sketch() { points.push_back({0, 0}); }

int Sketch::addPoint(double x, double y) {
  points.push_back({x, y});
  return static_cast<int>(points.size()) - 1;
}

int Sketch::addLine(int a, int b, bool construction) {
  Entity e;
  e.type = EntityType::Line;
  e.a = a;
  e.b = b;
  e.construction = construction;
  entities.push_back(e);
  return static_cast<int>(entities.size()) - 1;
}

int Sketch::addLine(double x1, double y1, double x2, double y2, bool construction) {
  const int a = addPoint(x1, y1);
  const int b = addPoint(x2, y2);
  return addLine(a, b, construction);
}

int Sketch::addCircleAt(int center, double radius, bool construction) {
  Entity e;
  e.type = EntityType::Circle;
  e.center = center;
  e.radius = radius;
  e.construction = construction;
  entities.push_back(e);
  return static_cast<int>(entities.size()) - 1;
}

int Sketch::addCircle(double cx, double cy, double radius, bool construction) {
  return addCircleAt(addPoint(cx, cy), radius, construction);
}

int Sketch::addArc(int center, int start, int end, bool construction) {
  Entity e;
  e.type = EntityType::Arc;
  e.center = center;
  e.a = start;
  e.b = end;
  const Point& c = points.at(center);
  const Point& s = points.at(start);
  e.radius = std::hypot(s.x - c.x, s.y - c.y);
  e.construction = construction;
  entities.push_back(e);
  return static_cast<int>(entities.size()) - 1;
}

int Sketch::addSpline(const std::vector<int>& fitPoints, bool construction, SplineKind kind) {
  if (fitPoints.size() < 2) throw SketchError("a spline needs at least two points");
  Entity e;
  e.type = EntityType::Spline;
  e.kind = kind;
  e.fit = fitPoints;
  e.a = fitPoints.front();
  e.b = fitPoints.back();
  e.construction = construction;
  entities.push_back(e);
  return static_cast<int>(entities.size()) - 1;
}

int Sketch::addConic(int start, int vertex, int end, double rho, bool construction) {
  if (!(rho > 0 && rho < 1)) throw SketchError("a conic's rho must be between 0 and 1");
  const int id = addSpline({start, vertex, end}, construction, SplineKind::Conic);
  entities[id].radius = rho;
  return id;
}

int Sketch::addEllipse(int center, int axisEnd, double otherRadius, bool construction) {
  Entity e;
  e.type = EntityType::Ellipse;
  e.center = center;
  e.a = axisEnd;
  e.b = -1;
  e.radius = otherRadius;
  e.construction = construction;
  entities.push_back(e);
  return static_cast<int>(entities.size()) - 1;
}

int Sketch::addEllipticalArc(int center, int axisEnd, double otherRadius, int start, int end, bool construction) {
  const int id = addEllipse(center, axisEnd, otherRadius, construction);
  entities[id].fit = {start, end};
  return id;
}

int Sketch::addText(int point, const std::string& text, double height, double angle, const std::string& font) {
  Text t;
  t.point = point;
  t.text = text;
  t.height = height;
  t.angle = angle;
  t.font = font;
  texts.push_back(t);
  return static_cast<int>(texts.size()) - 1;
}

int Sketch::addConstraint(Constraint c) {
  constraints.push_back(std::move(c));
  return static_cast<int>(constraints.size()) - 1;
}

std::vector<int> Sketch::entityPoints(int id) const {
  const Entity& e = entities.at(id);
  switch (e.type) {
    case EntityType::Line: return {e.a, e.b};
    case EntityType::Circle: return {e.center};
    case EntityType::Arc: return {e.center, e.a, e.b};
    case EntityType::Spline: return e.fit;
    case EntityType::Ellipse: {
      std::vector<int> v = {e.center, e.a};
      v.insert(v.end(), e.fit.begin(), e.fit.end());
      return v;
    }
  }
  return {};
}

void Sketch::removeConstraint(int index) {
  if (index < 0 || index >= static_cast<int>(constraints.size())) return;
  constraints.erase(constraints.begin() + index);
}

void Sketch::removeEntities(std::vector<int> ids) { removeImpl(std::set<int>(ids.begin(), ids.end()), {}); }

void Sketch::removePoints(std::vector<int> ids) { removeItems({}, ids); }

void Sketch::removeItems(const std::vector<int>& entityIds, const std::vector<int>& pointIds) {
  std::set<int> pts;
  for (int p : pointIds)
    if (p > 0 && p < static_cast<int>(points.size())) pts.insert(p);
  std::set<int> ents;
  for (int e : entityIds)
    if (e >= 0 && e < static_cast<int>(entities.size())) ents.insert(e);
  for (int i = 0; i < static_cast<int>(entities.size()); ++i)
    for (int p : entityPoints(i))
      if (pts.count(p)) ents.insert(i);
  removeImpl(ents, pts);
}

void Sketch::removeImpl(const std::set<int>& gone, const std::set<int>& forcePoints) {
  std::map<int, int> entityMap;
  std::vector<Entity> keptE;
  std::set<int> candidates = forcePoints;   // points that may go
  for (int i = 0; i < static_cast<int>(entities.size()); ++i) {
    if (gone.count(i)) {
      for (int p : entityPoints(i)) candidates.insert(p);
    } else {
      entityMap[i] = static_cast<int>(keptE.size());
      keptE.push_back(entities[i]);
    }
  }
  std::set<int> used = {0};
  for (const auto& t : texts) {
    if (!forcePoints.count(t.point)) used.insert(t.point);
    if (t.corner >= 0 && !forcePoints.count(t.corner)) used.insert(t.corner);
  }
  for (const auto& e : keptE) {
    for (int p : {e.a, e.b, e.center})
      if (p >= 0) used.insert(p);
    for (int p : e.fit) used.insert(p);
  }
  std::set<int> dropP;
  for (int p : candidates)
    if (!used.count(p)) dropP.insert(p);

  // Constraints referencing anything removed go too.
  std::vector<Constraint> keptC;
  for (const auto& c : constraints) {
    bool ok = true;
    for (int e : c.entities) ok = ok && !gone.count(e);
    for (int p : c.points) ok = ok && !dropP.count(p);
    if (ok) keptC.push_back(c);
  }
  std::map<int, int> pointMap;
  std::vector<Point> keptP;
  for (int i = 0; i < static_cast<int>(points.size()); ++i)
    if (!dropP.count(i)) {
      pointMap[i] = static_cast<int>(keptP.size());
      keptP.push_back(points[i]);
    }
  for (auto& e : keptE) {
    for (int* p : {&e.a, &e.b, &e.center})
      if (*p >= 0) *p = pointMap.at(*p);
    for (int& p : e.fit) p = pointMap.at(p);
  }
  for (auto& c : keptC) {
    for (int& p : c.points) p = pointMap.at(p);
    for (int& e : c.entities) e = entityMap.at(e);
  }
  std::vector<Text> keptT;
  for (const auto& t : texts)
    if (!dropP.count(t.point) && !(t.corner >= 0 && dropP.count(t.corner)) && !(t.path >= 0 && gone.count(t.path))) {
      keptT.push_back(t);
      keptT.back().point = pointMap.at(t.point);
      if (t.corner >= 0) keptT.back().corner = pointMap.at(t.corner);
      if (t.path >= 0) keptT.back().path = entityMap.at(t.path);
    }
  points = std::move(keptP);
  entities = std::move(keptE);
  constraints = std::move(keptC);
  texts = std::move(keptT);
}

void Sketch::checkIndices() const {
  const int np = static_cast<int>(points.size());
  const int ne = static_cast<int>(entities.size());
  if (np < 1) throw SketchError("sketch has no origin point");
  auto pt = [&](int p, bool required) {
    if (p == -1 && !required) return;
    if (p < 0 || p >= np) throw SketchError("sketch references a missing point");
  };
  for (const auto& t : texts) {
    pt(t.point, true);
    pt(t.corner, false);
    if (t.path != -1 && (t.path < 0 || t.path >= ne)) throw SketchError("text on a missing path");
    if (!(t.height > 0)) throw SketchError("text with no height");
  }
  for (const auto& e : entities) {
    switch (e.type) {
      case EntityType::Line: pt(e.a, true); pt(e.b, true); if (e.a == e.b) throw SketchError("line with one point"); break;
      case EntityType::Circle: pt(e.center, true); break;
      case EntityType::Arc: pt(e.center, true); pt(e.a, true); pt(e.b, true); break;
      case EntityType::Spline:
        if (e.fit.size() < 2) throw SketchError("spline with fewer than two points");
        if (e.kind == SplineKind::Conic && (e.fit.size() != 3 || !(e.radius > 0 && e.radius < 1)))
          throw SketchError("a conic needs a start, a vertex and an end, and rho between 0 and 1");
        for (int p : e.fit) pt(p, true);
        break;
      case EntityType::Ellipse:
        pt(e.center, true);
        pt(e.a, true);
        if (!e.fit.empty() && e.fit.size() != 2) throw SketchError("an elliptical arc needs a start and an end");
        for (int p : e.fit) pt(p, true);
        break;
    }
    if (!e.handles.empty() && e.handles.size() != e.fit.size()) throw SketchError("spline handles do not match its points");
  }
  for (const auto& c : constraints) {
    for (int p : c.points) pt(p, true);
    for (int e : c.entities)
      if (e < 0 || e >= ne) throw SketchError("constraint references a missing entity");
  }
}

std::string Sketch::toJson() const {
  nlohmann::json j;
  auto& pts = j["points"] = nlohmann::json::array();
  for (const auto& p : points) {
    if (p.z != 0) pts.push_back({p.x, p.y, p.z});
    else pts.push_back({p.x, p.y});
  }
  auto& ents = j["entities"] = nlohmann::json::array();
  for (const auto& e : entities) {
    nlohmann::json je;
    je["type"] = entityTypeName(e.type);
    if (e.projected) je["projected"] = true;
    if (e.included) je["included"] = true;
    if (e.type == EntityType::Spline) {
      je["fit"] = e.fit;
      if (!e.handles.empty()) {
        auto& hs = je["handles"] = nlohmann::json::array();
        for (const auto& h : e.handles) hs.push_back({h.x, h.y});
      }
      if (e.kind == SplineKind::Control) je["kind"] = "control";
      if (e.kind == SplineKind::Conic) {
        je["kind"] = "conic";
        je["rho"] = e.radius;
      }
      if (e.construction) je["construction"] = true;
      ents.push_back(je);
      continue;
    }
    if (e.type != EntityType::Circle) je["p"] = {e.a, e.b};
    if (e.type != EntityType::Line) {
      je["c"] = e.center;
      je["r"] = e.radius;
    }
    if (e.isEllipticalArc()) je["ends"] = e.fit;
    if (e.construction) je["construction"] = true;
    ents.push_back(je);
  }
  if (!texts.empty()) {
    auto& tx = j["texts"] = nlohmann::json::array();
    for (const auto& t : texts) {
      nlohmann::json jt;
      jt["p"] = t.point;
      jt["text"] = t.text;
      jt["h"] = t.height;
      if (t.angle != 0) jt["a"] = t.angle;
      if (!t.font.empty()) jt["font"] = t.font;
      if (t.corner >= 0) jt["corner"] = t.corner;
      if (t.path >= 0) jt["path"] = t.path;
      if (t.flip) jt["flip"] = true;
      if (t.hAlign != "left") jt["halign"] = t.hAlign;
      if (t.vAlign != "bottom") jt["valign"] = t.vAlign;
      tx.push_back(jt);
    }
  }
  auto& cons = j["constraints"] = nlohmann::json::array();
  for (const auto& c : constraints) {
    nlohmann::json jc;
    jc["type"] = typeName(c.type);
    if (!c.points.empty()) jc["p"] = c.points;
    if (!c.entities.empty()) jc["e"] = c.entities;
    if (c.value != 0) jc["v"] = c.value;
    if (c.value2 != 0) jc["v2"] = c.value2;
    if (!c.expression.empty()) jc["expr"] = c.expression;
    if (c.hasLabel) {
      jc["lx"] = c.labelX;
      jc["ly"] = c.labelY;
    }
    if (c.driven) jc["driven"] = true;
    if (!c.name.empty()) jc["name"] = c.name;
    cons.push_back(jc);
  }
  return j.dump();
}

Sketch Sketch::fromJson(const std::string& text) {
  Sketch s;
  if (text.empty() || text == "{}") return s;
  const auto j = nlohmann::json::parse(text, nullptr, /*allow_exceptions=*/false);
  if (!j.is_object()) throw SketchError("sketch data is not valid JSON");
  try {
    s.points.clear();
    for (const auto& p : j.value("points", nlohmann::json::array())) s.points.push_back({p.at(0).get<double>(), p.at(1).get<double>(), p.size() > 2 ? p.at(2).get<double>() : 0.0});
    if (s.points.empty()) s.points.push_back({0, 0});
    s.points[0] = {0, 0, 0}; // the origin never moves
    for (const auto& je : j.value("entities", nlohmann::json::array())) {
      Entity e;
      const std::string t = je.at("type").get<std::string>();
      if (t == "line") e.type = EntityType::Line;
      else if (t == "circle") e.type = EntityType::Circle;
      else if (t == "arc") e.type = EntityType::Arc;
      else if (t == "ellipse") e.type = EntityType::Ellipse;
      else if (t == "spline") {
        e.type = EntityType::Spline;
        e.fit = je.at("fit").get<std::vector<int>>();
        if (e.fit.size() < 2) throw SketchError("spline with fewer than two points");
        e.a = e.fit.front();
        e.b = e.fit.back();
        const std::string kind = je.value("kind", std::string("fit"));
        e.kind = kind == "control" ? SplineKind::Control : kind == "conic" ? SplineKind::Conic : SplineKind::Fit;
      }
      else throw SketchError("unknown sketch entity type '" + t + "'");
      if (je.contains("p")) {
        e.a = je["p"].at(0).get<int>();
        e.b = je["p"].at(1).get<int>();
      }
      e.center = je.value("c", -1);
      e.radius = je.value("r", je.value("rho", 0.0));
      e.construction = je.value("construction", false);
      e.projected = je.value("projected", false);
      e.included = je.value("included", false);
      if (e.type == EntityType::Ellipse && je.contains("ends")) e.fit = je["ends"].get<std::vector<int>>();
      if (e.type == EntityType::Spline && je.contains("handles"))
        for (const auto& h : je["handles"]) e.handles.push_back({h.at(0).get<double>(), h.at(1).get<double>()});
      s.entities.push_back(e);
    }
    for (const auto& jt : j.value("texts", nlohmann::json::array())) {
      Text t;
      t.point = jt.at("p").get<int>();
      t.text = jt.value("text", std::string{});
      t.height = jt.value("h", 0.5);
      t.angle = jt.value("a", 0.0);
      t.font = jt.value("font", std::string{});
      t.corner = jt.value("corner", -1);
      t.path = jt.value("path", -1);
      t.flip = jt.value("flip", false);
      t.hAlign = jt.value("halign", std::string("left"));
      t.vAlign = jt.value("valign", std::string("bottom"));
      s.texts.push_back(t);
    }
    for (const auto& jc : j.value("constraints", nlohmann::json::array())) {
      Constraint c;
      const std::string t = jc.at("type").get<std::string>();
      bool found = false;
      for (const auto& tn : kTypeNames)
        if (t == tn.name) {
          c.type = tn.type;
          found = true;
        }
      if (!found) throw SketchError("unknown sketch constraint type '" + t + "'");
      c.points = jc.value("p", std::vector<int>{});
      c.entities = jc.value("e", std::vector<int>{});
      c.value = jc.value("v", 0.0);
      c.value2 = jc.value("v2", 0.0);
      c.expression = jc.value("expr", std::string{});
      c.driven = jc.value("driven", false);
      c.name = jc.value("name", std::string{});
      if (jc.contains("lx") && jc.contains("ly")) {
        c.hasLabel = true;
        c.labelX = jc["lx"].get<double>();
        c.labelY = jc["ly"].get<double>();
      }
      s.constraints.push_back(c);
    }
  } catch (const nlohmann::json::exception& e) {
    throw SketchError(std::string("malformed sketch data: ") + e.what());
  }
  s.checkIndices();
  return s;
}

} // namespace tsr::sketch
