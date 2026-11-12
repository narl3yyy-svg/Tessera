#pragma once
// Expressions typed into any numeric input or parameter, the way Fusion takes
// them: "width / 2 + 3 mm", "sqrt(a^2 + b^2)", "atan(h / w)", "2 * pi * r".
//
// Values carry dimensions (powers of length and angle) and are kept in
// internal units (cm, rad). A bare number takes the unit of whatever it meets:
// added to a length it is a length in the expression's default length unit;
// the whole result, if unitless where a length or angle is expected, takes the
// expected unit. Trig functions take radians when given an angle and degrees
// when given a bare number.
#include "tsr/core/Units.h"

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace tsr {

struct Quantity {
  double value = 0;  // internal units
  int length = 0;    // power of length
  int angle = 0;     // power of angle
  bool unitless() const { return length == 0 && angle == 0; }
};

class ExpressionError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

struct ExpressionEnv {
  // Unit a bare number gets when it meets a length (e.g. "width + 3").
  Unit lengthUnit = Unit::Millimeter;
  // Resolves a parameter name; nullopt means "unknown parameter".
  std::function<std::optional<Quantity>(const std::string&)> lookup;
};

// The quantity a value in unit u stands for (10 mm -> {1.0, length 1}).
Quantity quantityOf(double internalValue, Unit u);

// Evaluates without converting the result. Throws ExpressionError.
Quantity evaluateQuantity(std::string_view text, const ExpressionEnv& env);

// Evaluates for an input that expects `expected`'s dimension and returns the
// value in internal units. Bare numbers take `expected` when it is a length
// or angle unit. Throws ExpressionError (syntax, unknown name, wrong
// dimension, not finite).
double evaluateExpression(std::string_view text, Unit expected, const ExpressionEnv& env);

// Parameter names an expression refers to, in order of first use, without
// evaluating it. Throws ExpressionError on a syntax error.
std::vector<std::string> expressionReferences(std::string_view text);

// True if the text is just a number with an optional unit ("10", "2.5 in"),
// i.e. something parseQuantity takes and that needs no expression to be kept.
bool isPlainQuantity(std::string_view text);

// True for names a parameter may use: an identifier that is not a unit,
// function or constant name.
bool isValidParameterName(std::string_view name);

} // namespace tsr
