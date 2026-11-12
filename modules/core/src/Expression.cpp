#include "tsr/core/Expression.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cmath>
#include <numbers>

namespace tsr {

namespace {

constexpr const char* kFunctions[] = {"sin",  "cos",  "tan", "asin", "acos", "atan", "atan2", "sqrt", "abs",
                                      "floor", "ceil", "round", "sign", "min", "max",  "exp",  "ln",    "log",
                                      "pow"};

bool isFunctionName(std::string_view s) {
  return std::any_of(std::begin(kFunctions), std::end(kFunctions), [&](const char* f) { return s == f; });
}
bool isConstantName(std::string_view s) { return s == "pi" || s == "PI" || s == "e" || s == "E"; }

bool isIdentStart(char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '_'; }
bool isIdentChar(char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; }

std::string describe(const Quantity& q) {
  if (q.unitless()) return "a unitless number";
  if (q.angle == 0) {
    if (q.length == 1) return "a length";
    if (q.length == 2) return "an area";
    if (q.length == 3) return "a volume";
  }
  if (q.length == 0 && q.angle == 1) return "an angle";
  return "a value with mixed units";
}

bool sameDims(const Quantity& a, const Quantity& b) { return a.length == b.length && a.angle == b.angle; }

class Parser {
public:
  Parser(std::string_view text, const ExpressionEnv* env, Unit len, Unit ang, std::vector<std::string>* refs)
      : s_(text), env_(env), len_(len), ang_(ang), refs_(refs) {}

  Quantity parseAll() {
    skip();
    if (pos_ >= s_.size()) throw ExpressionError("empty expression");
    Quantity q = expr();
    skip();
    if (pos_ < s_.size()) unexpected();
    return q;
  }

private:
  // In reference-collecting mode (no env) names evaluate to 1 and dimension
  // checks are skipped, so only syntax errors are reported.
  bool lenient() const { return env_ == nullptr; }

  [[noreturn]] void fail(const std::string& msg) const { throw ExpressionError(msg); }
  [[noreturn]] void unexpected() const {
    if (pos_ >= s_.size()) fail("unexpected end of expression");
    size_t n = 1;
    if (isIdentStart(s_[pos_]))
      while (pos_ + n < s_.size() && isIdentChar(s_[pos_ + n])) ++n;
    fail("unexpected '" + std::string(s_.substr(pos_, n)) + "' at position " + std::to_string(pos_ + 1));
  }

  void skip() {
    while (pos_ < s_.size() && std::isspace(static_cast<unsigned char>(s_[pos_]))) ++pos_;
  }
  bool eat(char c) {
    skip();
    if (pos_ < s_.size() && s_[pos_] == c) {
      ++pos_;
      return true;
    }
    return false;
  }

  // A bare number promoted to the dimension it is combined with.
  Quantity promote(const Quantity& bare, const Quantity& like) const {
    if (like.length == 1 && like.angle == 0) return quantityOf(toInternal(bare.value, len_), Unit::Centimeter);
    if (like.length == 0 && like.angle == 1) return quantityOf(toInternal(bare.value, ang_), Unit::Radian);
    return bare;
  }

  void unify(Quantity& a, Quantity& b, const char* verb) const {
    if (sameDims(a, b)) return;
    if (a.unitless()) a = promote(a, b);
    else if (b.unitless()) b = promote(b, a);
    if (!sameDims(a, b) && !lenient())
      fail(std::string("cannot ") + verb + " " + describe(a) + " and " + describe(b));
  }

  Quantity expr() {
    Quantity a = term();
    for (;;) {
      if (eat('+')) {
        Quantity b = term();
        unify(a, b, "add");
        a.value += b.value;
      } else if (eat('-')) {
        Quantity b = term();
        unify(a, b, "subtract");
        a.value -= b.value;
      } else {
        return a;
      }
    }
  }

  Quantity term() {
    Quantity a = unary();
    for (;;) {
      if (eat('*')) {
        const Quantity b = unary();
        a = {a.value * b.value, a.length + b.length, a.angle + b.angle};
      } else if (eat('/')) {
        const Quantity b = unary();
        if (b.value == 0 && !lenient()) fail("division by zero");
        a = {b.value == 0 ? 0 : a.value / b.value, a.length - b.length, a.angle - b.angle};
      } else {
        return a;
      }
    }
  }

  Quantity unary() {
    if (eat('-')) {
      Quantity q = unary();
      q.value = -q.value;
      return q;
    }
    if (eat('+')) return unary();
    return power();
  }

  Quantity raise(const Quantity& base, const Quantity& ex) const {
    if (!ex.unitless() && !lenient()) fail("an exponent must be a unitless number, not " + describe(ex));
    Quantity out{std::pow(base.value, ex.value), 0, 0};
    if (!base.unitless()) {
      const double n = std::round(ex.value);
      if (std::abs(n - ex.value) > 1e-9 && !lenient())
        fail("only whole powers of " + describe(base) + " are allowed");
      out.length = base.length * static_cast<int>(n);
      out.angle = base.angle * static_cast<int>(n);
    }
    return out;
  }

  Quantity power() {
    const Quantity base = primary();
    if (eat('^')) return raise(base, unary());
    return base;
  }

  std::string identifier() {
    const size_t start = pos_;
    while (pos_ < s_.size() && isIdentChar(s_[pos_])) ++pos_;
    return std::string(s_.substr(start, pos_ - start));
  }

  // Optional unit right after a number: "10 mm", "2in", "45°", "3\"".
  std::optional<Unit> unitSuffix() {
    skip();
    if (pos_ >= s_.size()) return std::nullopt;
    if (s_[pos_] == '"') { ++pos_; return Unit::Inch; }
    if (s_[pos_] == '\'') { ++pos_; return Unit::Foot; }
    if (s_.substr(pos_, 2) == "\xC2\xB0") { pos_ += 2; return Unit::Degree; }
    if (!isIdentStart(s_[pos_])) return std::nullopt;
    const size_t save = pos_;
    const std::string word = identifier();
    if (auto u = parseUnit(word); u && *u != Unit::None) return u;
    pos_ = save;
    return std::nullopt;
  }

  Quantity number() {
    double v = 0;
    const char* begin = s_.data() + pos_;
    const char* end = s_.data() + s_.size();
    auto [ptr, ec] = std::from_chars(begin, end, v);
    if (ec != std::errc{}) unexpected();
    pos_ += static_cast<size_t>(ptr - begin);
    if (!std::isfinite(v)) fail("number out of range");
    if (auto u = unitSuffix()) return quantityOf(toInternal(v, *u), *u);
    return {v, 0, 0};
  }

  std::vector<Quantity> arguments(const std::string& fn) {
    std::vector<Quantity> args;
    if (!eat('(')) fail("'" + fn + "' needs arguments in parentheses");
    if (eat(')')) return args;
    do args.push_back(expr());
    while (eat(','));
    if (!eat(')')) fail("missing ')' after the arguments of '" + fn + "'");
    return args;
  }

  double radians(const Quantity& q, const std::string& fn) const {
    if (q.length == 0 && q.angle == 1) return q.value;
    if (q.unitless()) return toInternal(q.value, ang_);
    if (!lenient()) fail("'" + fn + "' takes an angle, not " + describe(q));
    return q.value;
  }

  // Applies a rounding-style function in display units.
  Quantity rounded(const Quantity& q, double (*f)(double), const std::string& fn) const {
    Unit u = Unit::None;
    if (q.length == 1 && q.angle == 0) u = len_;
    else if (q.length == 0 && q.angle == 1) u = ang_;
    else if (!q.unitless() && !lenient()) fail("'" + fn + "' cannot round " + describe(q));
    Quantity out = q;
    out.value = toInternal(f(fromInternal(q.value, u)), u);
    return out;
  }

  Quantity call(const std::string& fn) {
    std::vector<Quantity> a = arguments(fn);
    auto need = [&](size_t n) {
      if (a.size() != n)
        fail("'" + fn + "' takes " + std::to_string(n) + " argument" + (n == 1 ? "" : "s"));
    };
    auto unitlessArg = [&](const Quantity& q) {
      if (!q.unitless() && !lenient()) fail("'" + fn + "' takes a unitless number, not " + describe(q));
      return q.value;
    };
    auto angle = [](double rad) { return Quantity{rad, 0, 1}; };
    if (fn == "sin") { need(1); return {std::sin(radians(a[0], fn)), 0, 0}; }
    if (fn == "cos") { need(1); return {std::cos(radians(a[0], fn)), 0, 0}; }
    if (fn == "tan") { need(1); return {std::tan(radians(a[0], fn)), 0, 0}; }
    if (fn == "asin") { need(1); return angle(std::asin(unitlessArg(a[0]))); }
    if (fn == "acos") { need(1); return angle(std::acos(unitlessArg(a[0]))); }
    if (fn == "atan") { need(1); return angle(std::atan(unitlessArg(a[0]))); }
    if (fn == "atan2") {
      need(2);
      unify(a[0], a[1], "compare");
      return angle(std::atan2(a[0].value, a[1].value));
    }
    if (fn == "sqrt") {
      need(1);
      if (((a[0].length % 2) != 0 || (a[0].angle % 2) != 0) && !lenient())
        fail("cannot take the square root of " + describe(a[0]));
      if (a[0].value < 0 && !lenient()) fail("square root of a negative value");
      return {std::sqrt(std::max(0.0, a[0].value)), a[0].length / 2, a[0].angle / 2};
    }
    if (fn == "abs") { need(1); return {std::abs(a[0].value), a[0].length, a[0].angle}; }
    if (fn == "sign") { need(1); return {a[0].value > 0 ? 1.0 : a[0].value < 0 ? -1.0 : 0.0, 0, 0}; }
    if (fn == "floor") { need(1); return rounded(a[0], [](double x) { return std::floor(x); }, fn); }
    if (fn == "ceil") { need(1); return rounded(a[0], [](double x) { return std::ceil(x); }, fn); }
    if (fn == "round") { need(1); return rounded(a[0], [](double x) { return std::round(x); }, fn); }
    if (fn == "min" || fn == "max") {
      if (a.empty()) fail("'" + fn + "' needs at least one argument");
      Quantity best = a[0];
      for (size_t i = 1; i < a.size(); ++i) {
        Quantity x = a[i];
        unify(best, x, "compare");
        if (fn == "min" ? x.value < best.value : x.value > best.value) best = x;
      }
      return best;
    }
    if (fn == "exp") { need(1); return {std::exp(unitlessArg(a[0])), 0, 0}; }
    if (fn == "ln") { need(1); return {std::log(unitlessArg(a[0])), 0, 0}; }
    if (fn == "log") { need(1); return {std::log10(unitlessArg(a[0])), 0, 0}; }
    if (fn == "pow") { need(2); return raise(a[0], a[1]); }
    fail("unknown function '" + fn + "'");
  }

  Quantity primary() {
    skip();
    if (pos_ >= s_.size()) unexpected();
    const char c = s_[pos_];
    if (c == '(') {
      ++pos_;
      Quantity q = expr();
      if (!eat(')')) fail("missing ')'");
      return q;
    }
    if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') return number();
    if (!isIdentStart(c)) unexpected();
    const std::string name = identifier();
    skip();
    if (pos_ < s_.size() && s_[pos_] == '(') {
      if (!isFunctionName(name)) fail("unknown function '" + name + "'");
      return call(name);
    }
    if (name == "pi" || name == "PI") return {std::numbers::pi, 0, 0};
    if (name == "e" || name == "E") return {std::numbers::e, 0, 0};
    if (isFunctionName(name)) fail("'" + name + "' is a function and needs arguments in parentheses");
    if (parseUnit(name)) fail("unit '" + name + "' must follow a number");
    if (refs_ && std::find(refs_->begin(), refs_->end(), name) == refs_->end()) refs_->push_back(name);
    if (lenient()) return {1, 0, 0};
    std::optional<Quantity> q = env_->lookup ? env_->lookup(name) : std::nullopt;
    if (!q) fail("unknown parameter '" + name + "'");
    return *q;
  }

  std::string_view s_;
  size_t pos_ = 0;
  const ExpressionEnv* env_;
  Unit len_;
  Unit ang_;
  std::vector<std::string>* refs_;
};

} // namespace

Quantity quantityOf(double internalValue, Unit u) {
  switch (dimensionOf(u)) {
    case Dimension::Length: return {internalValue, 1, 0};
    case Dimension::Angle: return {internalValue, 0, 1};
    case Dimension::Unitless: break;
  }
  return {internalValue, 0, 0};
}

Quantity evaluateQuantity(std::string_view text, const ExpressionEnv& env) {
  Quantity q = Parser(text, &env, env.lengthUnit, Unit::Degree, nullptr).parseAll();
  if (!std::isfinite(q.value)) throw ExpressionError("the result is not a finite number");
  return q;
}

double evaluateExpression(std::string_view text, Unit expected, const ExpressionEnv& env) {
  const Dimension dim = dimensionOf(expected);
  const Unit len = dim == Dimension::Length ? expected : env.lengthUnit;
  const Unit ang = dim == Dimension::Angle ? expected : Unit::Degree;
  const Quantity q = Parser(text, &env, len, ang, nullptr).parseAll();
  if (!std::isfinite(q.value)) throw ExpressionError("the result is not a finite number");
  const Quantity want = quantityOf(0, expected);
  if (sameDims(q, want)) return q.value;
  if (q.unitless()) return toInternal(q.value, expected);
  throw ExpressionError("expected " + describe(want) + ", got " + describe(q));
}

std::vector<std::string> expressionReferences(std::string_view text) {
  std::vector<std::string> refs;
  (void)Parser(text, nullptr, Unit::Millimeter, Unit::Degree, &refs).parseAll();
  return refs;
}

bool isPlainQuantity(std::string_view text) {
  // A bare number or a number followed by a unit: parseQuantity with any
  // matching default unit takes it.
  for (Unit u : {Unit::None, Unit::Millimeter, Unit::Degree})
    if (parseQuantity(text, u)) return true;
  return false;
}

bool isValidParameterName(std::string_view name) {
  if (name.empty() || !isIdentStart(name[0])) return false;
  if (!std::all_of(name.begin(), name.end(), isIdentChar)) return false;
  return !parseUnit(name) && !isFunctionName(name) && !isConstantName(name);
}

} // namespace tsr
