#include "TestFramework.h"
#include "tsr/core/Expression.h"

#include <map>
#include <numbers>

using namespace tsr;

namespace {
ExpressionEnv env() {
  ExpressionEnv e;
  e.lengthUnit = Unit::Millimeter;
  static const std::map<std::string, Quantity> params = {
      {"width", quantityOf(5.0, Unit::Centimeter)},   // 50 mm
      {"angle", quantityOf(std::numbers::pi / 6, Unit::Radian)},
      {"count", {4, 0, 0}},
  };
  e.lookup = [](const std::string& n) -> std::optional<Quantity> {
    auto it = params.find(n);
    if (it == params.end()) return std::nullopt;
    return it->second;
  };
  return e;
}
double mm(const char* text) { return evaluateExpression(text, Unit::Millimeter, env()); }
} // namespace

TEST(expression_arithmetic_and_units) {
  CHECK_NEAR(mm("10"), 1.0, 1e-12);
  CHECK_NEAR(mm("10 mm + 1 cm"), 2.0, 1e-12);
  CHECK_NEAR(mm("2 * (3 + 4)"), 1.4, 1e-12);      // 14 mm
  CHECK_NEAR(mm("1in"), 2.54, 1e-12);
  CHECK_NEAR(mm("-2^2"), -0.4, 1e-12);            // -(2^2) mm
  CHECK_NEAR(mm("2^3^2"), 51.2, 1e-9);            // right associative: 512 mm
  CHECK_NEAR(evaluateExpression("10", Unit::Inch, env()), 25.4, 1e-12);
}

TEST(expression_parameters) {
  CHECK_NEAR(mm("width"), 5.0, 1e-12);
  CHECK_NEAR(mm("width / 2 + 3"), 2.8, 1e-12);    // 25 + 3 mm
  CHECK_NEAR(mm("width * count"), 20.0, 1e-12);
  CHECK_NEAR(mm("sqrt(width^2 + width^2)"), 5.0 * std::numbers::sqrt2, 1e-12);
  CHECK_NEAR(evaluateExpression("angle * 2", Unit::Degree, env()), std::numbers::pi / 3, 1e-12);
  CHECK_NEAR(evaluateExpression("count + 1", Unit::None, env()), 5.0, 1e-12);
}

TEST(expression_functions) {
  CHECK_NEAR(evaluateExpression("sin(30 deg)", Unit::None, env()), 0.5, 1e-12);
  CHECK_NEAR(evaluateExpression("cos(60)", Unit::None, env()), 0.5, 1e-12);   // bare: degrees
  CHECK_NEAR(evaluateExpression("atan(1)", Unit::Degree, env()), std::numbers::pi / 4, 1e-12);
  CHECK_NEAR(evaluateExpression("acos(0.5)", Unit::Degree, env()), std::numbers::pi / 3, 1e-12);
  CHECK_NEAR(mm("max(3, width / 10, 4 mm)"), 0.5, 1e-12);
  CHECK_NEAR(mm("floor(12.7)"), 1.2, 1e-12);
  CHECK_NEAR(mm("2 * pi * 10"), 2 * std::numbers::pi, 1e-12);
  CHECK_NEAR(mm("abs(-3)"), 0.3, 1e-12);
}

TEST(expression_errors) {
  CHECK_THROWS(mm("width +"));
  CHECK_THROWS(mm("nope * 2"));
  CHECK_THROWS(mm("10 deg"));              // angle where a length is expected
  CHECK_THROWS(mm("width * width"));       // an area
  CHECK_THROWS(mm("width + 10 deg"));
  CHECK_THROWS(mm("1 / 0"));
  CHECK_THROWS(mm("sqrt(width)"));
  CHECK_THROWS(mm("(1 + 2"));
  CHECK_THROWS(mm("frob(2)"));
  CHECK_THROWS(evaluateExpression("width", Unit::None, env()));
}

TEST(expression_references_and_names) {
  const auto refs = expressionReferences("width / 2 + sin(angle) * width + 3 mm + pi");
  CHECK_EQ(refs.size(), size_t(2));
  CHECK_EQ(refs[0], std::string("width"));
  CHECK_EQ(refs[1], std::string("angle"));
  CHECK_THROWS(expressionReferences("width +"));
  CHECK(isPlainQuantity("10"));
  CHECK(isPlainQuantity("2.5 in"));
  CHECK(isPlainQuantity("45 deg"));
  CHECK(!isPlainQuantity("width / 2"));
  CHECK(isValidParameterName("width_2"));
  CHECK(!isValidParameterName("mm"));
  CHECK(!isValidParameterName("sin"));
  CHECK(!isValidParameterName("pi"));
  CHECK(!isValidParameterName("2x"));
}
