// Insert SVG: an SVG drawing as sketch geometry. Lines stay lines, Bezier
// curves become control point splines (a cubic Bezier is exactly a clamped
// cubic B-spline on its four points), arcs are turned into Beziers, and
// circles stay circles while the transform keeps them round.
#include "tsr/sketch/SketchGeometry.h"

#include <array>
#include <cctype>
#include <cmath>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

namespace tsr::sketch {

namespace {

constexpr double kPi = 3.14159265358979323846;

// x' = a x + c y + e, y' = b x + d y + f (the SVG matrix order).
struct Affine {
  double a = 1, b = 0, c = 0, d = 1, e = 0, f = 0;
  Affine then(const Affine& m) const {   // this, then m on top (m * this)
    return {m.a * a + m.c * b, m.b * a + m.d * b, m.a * c + m.c * d, m.b * c + m.d * d, m.a * e + m.c * f + m.e,
            m.b * e + m.d * f + m.f};
  }
  std::pair<double, double> map(double x, double y) const { return {a * x + c * y + e, b * x + d * y + f}; }
  // Keeps circles round: equal scale both ways, no shear.
  bool similar() const {
    const double sx = std::hypot(a, b), sy = std::hypot(c, d);
    return std::abs(sx - sy) < 1e-9 * std::max(sx, 1.0) && std::abs(a * c + b * d) < 1e-9 * std::max(sx * sy, 1.0);
  }
  double scale() const { return std::sqrt(std::abs(a * d - b * c)); }
};

std::vector<double> numbers(const std::string& s) {
  std::vector<double> out;
  static const std::regex num(R"([-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?)");
  for (std::sregex_iterator it(s.begin(), s.end(), num), end; it != end; ++it) out.push_back(std::stod(it->str()));
  return out;
}

Affine parseTransform(const std::string& t) {
  Affine m;
  static const std::regex fn(R"((matrix|translate|scale|rotate|skewX|skewY)\s*\(([^)]*)\))");
  for (std::sregex_iterator it(t.begin(), t.end(), fn), end; it != end; ++it) {
    const std::string name = (*it)[1];
    const auto v = numbers((*it)[2]);
    Affine x;
    if (name == "matrix" && v.size() >= 6) x = {v[0], v[1], v[2], v[3], v[4], v[5]};
    else if (name == "translate" && !v.empty()) x = {1, 0, 0, 1, v[0], v.size() > 1 ? v[1] : 0};
    else if (name == "scale" && !v.empty()) x = {v[0], 0, 0, v.size() > 1 ? v[1] : v[0], 0, 0};
    else if (name == "rotate" && !v.empty()) {
      const double r = v[0] * kPi / 180, cs = std::cos(r), sn = std::sin(r);
      const double cx = v.size() > 2 ? v[1] : 0, cy = v.size() > 2 ? v[2] : 0;
      x = {cs, sn, -sn, cs, cx - cs * cx + sn * cy, cy - sn * cx - cs * cy};
    } else if (name == "skewX" && !v.empty()) x = {1, 0, std::tan(v[0] * kPi / 180), 1, 0, 0};
    else if (name == "skewY" && !v.empty()) x = {1, std::tan(v[0] * kPi / 180), 0, 1, 0, 0};
    // Functions apply right to left: the last one acts on the point first.
    m = x.then(m);
  }
  return m;
}

// A length with an optional unit, in millimetres per user unit at 96 dpi.
double lengthMm(const std::string& s, bool* hadUnit = nullptr) {
  const auto v = numbers(s);
  if (v.empty()) return 0;
  std::string unit;
  for (char ch : s)
    if (std::isalpha(static_cast<unsigned char>(ch)) && ch != 'e' && ch != 'E') unit += ch;
  if (hadUnit) *hadUnit = !unit.empty() && unit != "px";
  if (unit == "mm") return v[0];
  if (unit == "cm") return v[0] * 10;
  if (unit == "in") return v[0] * 25.4;
  if (unit == "pt") return v[0] * 25.4 / 72;
  if (unit == "pc") return v[0] * 25.4 / 6;
  return v[0] * 25.4 / 96;   // px and plain numbers
}

class Builder {
public:
  explicit Builder(double cmPerUnit) : k_(cmPerUnit) {}
  Sketch sketch;

  int point(const Affine& m, double x, double y) {
    auto [u, v] = m.map(x, y);
    u *= k_;
    v *= -k_;   // SVG's y runs down
    const auto key = std::make_pair(std::llround(u * 1e6), std::llround(v * 1e6));
    if (auto it = byPlace_.find(key); it != byPlace_.end()) return it->second;
    return byPlace_[key] = sketch.addPoint(u, v);
  }
  int freePoint(const Affine& m, double x, double y) {
    auto [u, v] = m.map(x, y);
    return sketch.addPoint(u * k_, -v * k_);
  }
  void line(const Affine& m, double x0, double y0, double x1, double y1) {
    const int a = point(m, x0, y0), b = point(m, x1, y1);
    if (a != b) sketch.addLine(a, b);
  }
  void cubic(const Affine& m, const std::array<double, 8>& p) {
    // Straight (all four in line): a line.
    const double dx = p[6] - p[0], dy = p[7] - p[1];
    const double l = std::hypot(dx, dy);
    auto off = [&](double x, double y) { return l > 0 ? std::abs((x - p[0]) * dy - (y - p[1]) * dx) / l : std::hypot(x - p[0], y - p[1]); };
    if (off(p[2], p[3]) < 1e-9 && off(p[4], p[5]) < 1e-9) {
      line(m, p[0], p[1], p[6], p[7]);
      return;
    }
    const int a = point(m, p[0], p[1]), b = point(m, p[6], p[7]);
    const int c1 = freePoint(m, p[2], p[3]), c2 = freePoint(m, p[4], p[5]);
    std::vector<int> fit = {a, c1, c2, b};
    if (a == b) {
      // A closed single Bezier: keep both ends apart in the frame (a control
      // spline cannot share its end points).
      fit.back() = freePoint(m, p[6], p[7]);
    }
    sketch.addSpline(fit, false, SplineKind::Control);
  }
  void circle(const Affine& m, double cx, double cy, double rx, double ry) {
    if (rx <= 0 || ry <= 0) return;
    if (std::abs(rx - ry) < 1e-12 && m.similar()) {
      auto [u, v] = m.map(cx, cy);
      sketch.addCircle(u * k_, -v * k_, rx * m.scale() * k_);
      return;
    }
    // Otherwise four quarter arcs as Beziers (exact enough: 0.03% of the radius).
    const double kk = 0.5522847498307936;
    const std::array<std::array<double, 2>, 4> q = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
    for (int i = 0; i < 4; ++i) {
      const auto& s0 = q[i];
      const auto& s1 = q[(i + 1) % 4];
      cubic(m, {cx + rx * s0[0], cy + ry * s0[1], cx + rx * (s0[0] - kk * s0[1]), cy + ry * (s0[1] + kk * s0[0]),
                cx + rx * (s1[0] + kk * s1[1]), cy + ry * (s1[1] - kk * s1[0]), cx + rx * s1[0], cy + ry * s1[1]});
    }
  }
  // Endpoint-form elliptical arc (SVG "A") as cubic Beziers of at most 90 degrees.
  void arc(const Affine& m, double x0, double y0, double rx, double ry, double phiDeg, bool large, bool sweep, double x1,
           double y1) {
    if (std::abs(x0 - x1) < 1e-12 && std::abs(y0 - y1) < 1e-12) return;
    rx = std::abs(rx);
    ry = std::abs(ry);
    if (rx < 1e-12 || ry < 1e-12) {
      line(m, x0, y0, x1, y1);
      return;
    }
    const double phi = phiDeg * kPi / 180, cs = std::cos(phi), sn = std::sin(phi);
    const double dx = (x0 - x1) / 2, dy = (y0 - y1) / 2;
    const double x1p = cs * dx + sn * dy, y1p = -sn * dx + cs * dy;
    const double lam = x1p * x1p / (rx * rx) + y1p * y1p / (ry * ry);
    if (lam > 1) {
      rx *= std::sqrt(lam);
      ry *= std::sqrt(lam);
    }
    double num = rx * rx * ry * ry - rx * rx * y1p * y1p - ry * ry * x1p * x1p;
    const double den = rx * rx * y1p * y1p + ry * ry * x1p * x1p;
    double co = den > 0 ? std::sqrt(std::max(0.0, num / den)) : 0;
    if (large == sweep) co = -co;
    const double cxp = co * rx * y1p / ry, cyp = -co * ry * x1p / rx;
    const double cx = cs * cxp - sn * cyp + (x0 + x1) / 2, cy = sn * cxp + cs * cyp + (y0 + y1) / 2;
    auto ang = [](double ux, double uy, double vx, double vy) {
      return std::atan2(ux * vy - uy * vx, ux * vx + uy * vy);
    };
    const double t1 = ang(1, 0, (x1p - cxp) / rx, (y1p - cyp) / ry);
    double dt = ang((x1p - cxp) / rx, (y1p - cyp) / ry, (-x1p - cxp) / rx, (-y1p - cyp) / ry);
    if (!sweep && dt > 0) dt -= 2 * kPi;
    if (sweep && dt < 0) dt += 2 * kPi;
    const int n = std::max(1, static_cast<int>(std::ceil(std::abs(dt) / (kPi / 2) - 1e-9)));
    const double step = dt / n, alpha = 4.0 / 3 * std::tan(step / 4);
    auto at = [&](double t, double& x, double& y, double& tx, double& ty) {
      const double ex = rx * std::cos(t), ey = ry * std::sin(t);
      x = cs * ex - sn * ey + cx;
      y = sn * ex + cs * ey + cy;
      const double dex = -rx * std::sin(t), dey = ry * std::cos(t);
      tx = cs * dex - sn * dey;
      ty = sn * dex + cs * dey;
    };
    double px = x0, py = y0;
    for (int i = 0; i < n; ++i) {
      double ax, ay, atx, aty, bx, by, btx, bty;
      at(t1 + step * i, ax, ay, atx, aty);
      at(t1 + step * (i + 1), bx, by, btx, bty);
      if (i == n - 1) bx = x1, by = y1;
      cubic(m, {px, py, ax + alpha * atx, ay + alpha * aty, bx - alpha * btx, by - alpha * bty, bx, by});
      px = bx;
      py = by;
    }
  }

  // Path data.
  void path(const Affine& m, const std::string& d) {
    static const std::regex tok(R"([MmLlHhVvCcSsQqTtAaZz]|[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?)");
    std::vector<std::string> t;
    for (std::sregex_iterator it(d.begin(), d.end(), tok), end; it != end; ++it) t.push_back(it->str());
    size_t i = 0;
    char cmd = 0;
    double x = 0, y = 0, sx = 0, sy = 0, lcx = 0, lcy = 0;   // current, subpath start, last control
    char last = 0;
    auto isCmd = [](const std::string& s) { return s.size() == 1 && std::isalpha(static_cast<unsigned char>(s[0])); };
    auto num = [&]() {
      if (i >= t.size() || isCmd(t[i])) throw SketchError("SVG path: a number is missing");
      return std::stod(t[i++]);
    };
    // Arc flags may be written together ("a1 1 0 01 2 2"): one digit each.
    auto flag = [&]() {
      if (i >= t.size()) throw SketchError("SVG path: an arc flag is missing");
      std::string& s = t[i];
      const bool f = s[0] == '1';
      if (s.size() > 1) s.erase(0, 1);
      else ++i;
      return f;
    };
    while (i < t.size()) {
      if (isCmd(t[i])) cmd = t[i++][0];
      else if (!cmd) throw SketchError("SVG path: data must start with a command");
      const bool rel = std::islower(static_cast<unsigned char>(cmd));
      const char up = static_cast<char>(std::toupper(static_cast<unsigned char>(cmd)));
      const double ox = rel ? x : 0, oy = rel ? y : 0;
      switch (up) {
        case 'M': {
          x = ox + num();
          y = oy + num();
          sx = x;
          sy = y;
          cmd = rel ? 'l' : 'L';   // further pairs are lines
          break;
        }
        case 'L': {
          const double nx = ox + num(), ny = oy + num();
          line(m, x, y, nx, ny);
          x = nx;
          y = ny;
          break;
        }
        case 'H': {
          const double nx = (rel ? x : 0) + num();
          line(m, x, y, nx, y);
          x = nx;
          break;
        }
        case 'V': {
          const double ny = (rel ? y : 0) + num();
          line(m, x, y, x, ny);
          y = ny;
          break;
        }
        case 'C': {
          const double a = ox + num(), b = oy + num(), c = ox + num(), dd = oy + num(), e = ox + num(), f = oy + num();
          cubic(m, {x, y, a, b, c, dd, e, f});
          lcx = c;
          lcy = dd;
          x = e;
          y = f;
          break;
        }
        case 'S': {
          const bool smooth = last == 'C' || last == 'S';
          const double a = smooth ? 2 * x - lcx : x, b = smooth ? 2 * y - lcy : y;
          const double c = ox + num(), dd = oy + num(), e = ox + num(), f = oy + num();
          cubic(m, {x, y, a, b, c, dd, e, f});
          lcx = c;
          lcy = dd;
          x = e;
          y = f;
          break;
        }
        case 'Q':
        case 'T': {
          double qx, qy;
          if (up == 'Q') {
            qx = ox + num();
            qy = oy + num();
          } else {
            const bool smooth = last == 'Q' || last == 'T';
            qx = smooth ? 2 * x - lcx : x;
            qy = smooth ? 2 * y - lcy : y;
          }
          const double e = ox + num(), f = oy + num();
          // A quadratic raised to a cubic: controls two thirds toward Q.
          cubic(m, {x, y, x + 2.0 / 3 * (qx - x), y + 2.0 / 3 * (qy - y), e + 2.0 / 3 * (qx - e), f + 2.0 / 3 * (qy - f), e, f});
          lcx = qx;
          lcy = qy;
          x = e;
          y = f;
          break;
        }
        case 'A': {
          const double rx = num(), ry = num(), rot = num();
          const bool large = flag(), sweep = flag();
          const double nx = ox + num(), ny = oy + num();
          arc(m, x, y, rx, ry, rot, large, sweep, nx, ny);
          x = nx;
          y = ny;
          break;
        }
        case 'Z':
          line(m, x, y, sx, sy);
          x = sx;
          y = sy;
          break;
        default: throw SketchError(std::string("SVG path: unknown command '") + cmd + "'");
      }
      last = up;
    }
  }

private:
  double k_;
  std::map<std::pair<long long, long long>, int> byPlace_;
};

} // namespace

Sketch fromSvg(const std::string& text, double scale) {
  static const std::regex attr(R"re(([\w:-]+)\s*=\s*(?:"([^"]*)"|'([^']*)'))re");
  // Millimetres per user unit: from the root's width and viewBox, else 96 dpi.
  double mmPerUnit = 25.4 / 96;
  std::vector<Affine> stack = {Affine{}};
  int skipDepth = 0;   // inside defs, clip paths, masks, symbols, text
  Builder* b = nullptr;
  std::unique_ptr<Builder> owner;
  size_t pos = 0;
  while ((pos = text.find('<', pos)) != std::string::npos) {
    if (text.compare(pos, 4, "<!--") == 0) {
      pos = text.find("-->", pos);
      if (pos == std::string::npos) break;
      continue;
    }
    const size_t end = text.find('>', pos);
    if (end == std::string::npos) break;
    std::string tag = text.substr(pos + 1, end - pos - 1);
    pos = end + 1;
    if (tag.empty() || tag[0] == '?' || tag[0] == '!') continue;
    const bool closing = tag[0] == '/';
    const bool selfClosing = !closing && tag.back() == '/';
    if (selfClosing) tag.pop_back();
    size_t n = closing ? 1 : 0;
    while (n < tag.size() && !std::isspace(static_cast<unsigned char>(tag[n]))) ++n;
    std::string name = tag.substr(closing ? 1 : 0, n - (closing ? 1 : 0));
    if (const size_t colon = name.find(':'); colon != std::string::npos) name = name.substr(colon + 1);
    const bool container = name == "g" || name == "svg" || name == "a" || name == "switch";
    const bool skipped = name == "defs" || name == "clipPath" || name == "mask" || name == "symbol" || name == "text" ||
                         name == "pattern" || name == "marker" || name == "style" || name == "title" || name == "metadata";
    if (closing) {
      if (skipped && skipDepth > 0) --skipDepth;
      else if (container && stack.size() > 1 && skipDepth == 0) stack.pop_back();
      continue;
    }
    if (skipped) {
      if (!selfClosing) ++skipDepth;
      continue;
    }
    if (skipDepth > 0) continue;
    std::map<std::string, std::string> at;
    for (std::sregex_iterator it(tag.begin() + static_cast<long>(n), tag.end(), attr), e; it != e; ++it)
      at[(*it)[1]] = (*it)[2].matched ? (*it)[2].str() : (*it)[3].str();
    auto num = [&](const char* key) {
      const auto it = at.find(key);
      if (it == at.end()) return 0.0;
      const auto v = numbers(it->second);
      return v.empty() ? 0.0 : v[0];
    };
    Affine m = stack.back();
    if (const auto it = at.find("transform"); it != at.end()) m = parseTransform(it->second).then(m);
    if (name == "svg" && !b) {
      // Units: width with a unit and a viewBox give the user unit's size.
      const auto vb = at.count("viewBox") ? numbers(at["viewBox"]) : std::vector<double>{};
      bool unit = false;
      const double wmm = at.count("width") ? lengthMm(at["width"], &unit) : 0;
      if (vb.size() == 4 && vb[2] > 0 && wmm > 0) mmPerUnit = wmm / vb[2];
      else if (vb.size() == 4 && vb[2] > 0 && !at.count("width")) mmPerUnit = 25.4 / 96;
      if (vb.size() == 4) m = Affine{1, 0, 0, 1, -vb[0], -vb[1]}.then(m);
      owner = std::make_unique<Builder>(mmPerUnit / 10 * scale);
      b = owner.get();
    }
    if (!b) {
      owner = std::make_unique<Builder>(mmPerUnit / 10 * scale);
      b = owner.get();
    }
    if (container) {
      if (!selfClosing) stack.push_back(m);
      continue;
    }
    if (name == "path" && at.count("d")) {
      b->path(m, at["d"]);
    } else if (name == "line") {
      b->line(m, num("x1"), num("y1"), num("x2"), num("y2"));
    } else if (name == "rect") {
      const double x = num("x"), y = num("y"), w = num("width"), h = num("height");
      double rx = num("rx"), ry = num("ry");
      if (at.count("rx") && !at.count("ry")) ry = rx;
      if (at.count("ry") && !at.count("rx")) rx = ry;
      rx = std::min(rx, w / 2);
      ry = std::min(ry, h / 2);
      if (w <= 0 || h <= 0) continue;
      if (rx <= 0 || ry <= 0) {
        b->line(m, x, y, x + w, y);
        b->line(m, x + w, y, x + w, y + h);
        b->line(m, x + w, y + h, x, y + h);
        b->line(m, x, y + h, x, y);
      } else {
        // Rounded corners as quarter arcs.
        b->line(m, x + rx, y, x + w - rx, y);
        b->arc(m, x + w - rx, y, rx, ry, 0, false, true, x + w, y + ry);
        b->line(m, x + w, y + ry, x + w, y + h - ry);
        b->arc(m, x + w, y + h - ry, rx, ry, 0, false, true, x + w - rx, y + h);
        b->line(m, x + w - rx, y + h, x + rx, y + h);
        b->arc(m, x + rx, y + h, rx, ry, 0, false, true, x, y + h - ry);
        b->line(m, x, y + h - ry, x, y + ry);
        b->arc(m, x, y + ry, rx, ry, 0, false, true, x + rx, y);
      }
    } else if (name == "circle") {
      b->circle(m, num("cx"), num("cy"), num("r"), num("r"));
    } else if (name == "ellipse") {
      b->circle(m, num("cx"), num("cy"), num("rx"), num("ry"));
    } else if ((name == "polyline" || name == "polygon") && at.count("points")) {
      const auto v = numbers(at["points"]);
      for (size_t i = 0; i + 3 < v.size(); i += 2) b->line(m, v[i], v[i + 1], v[i + 2], v[i + 3]);
      if (name == "polygon" && v.size() >= 6) b->line(m, v[v.size() - 2], v[v.size() - 1], v[0], v[1]);
    }
  }
  if (!b || b->sketch.entities.empty())
    throw SketchError("nothing in that SVG file could be read (paths, lines, rectangles, circles, ellipses, polygons)");
  return std::move(b->sketch);
}

} // namespace tsr::sketch
