#include "tsr/core/Units.h"

#include <cctype>
#include <charconv>
#include <cmath>
#include <numbers>
#include <sstream>

namespace tsr {

namespace {
// Factor to multiply a value in unit u by to get internal units.
double factor(Unit u) {
  switch (u) {
    case Unit::Millimeter: return 0.1;
    case Unit::Centimeter: return 1.0;
    case Unit::Meter:      return 100.0;
    case Unit::Inch:       return 2.54;
    case Unit::Foot:       return 30.48;
    case Unit::Degree:     return std::numbers::pi / 180.0;
    case Unit::Radian:     return 1.0;
    case Unit::None:       return 1.0;
  }
  return 1.0;
}

std::string_view trim(std::string_view s) {
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.remove_suffix(1);
  return s;
}
} // namespace

Dimension dimensionOf(Unit u) {
  switch (u) {
    case Unit::Millimeter: case Unit::Centimeter: case Unit::Meter:
    case Unit::Inch: case Unit::Foot: return Dimension::Length;
    case Unit::Degree: case Unit::Radian: return Dimension::Angle;
    case Unit::None: return Dimension::Unitless;
  }
  return Dimension::Unitless;
}

std::string_view unitSymbol(Unit u) {
  switch (u) {
    case Unit::Millimeter: return "mm";
    case Unit::Centimeter: return "cm";
    case Unit::Meter:      return "m";
    case Unit::Inch:       return "in";
    case Unit::Foot:       return "ft";
    case Unit::Degree:     return "deg";
    case Unit::Radian:     return "rad";
    case Unit::None:       return "";
  }
  return "";
}

std::optional<Unit> parseUnit(std::string_view s) {
  s = trim(s);
  if (s.empty()) return Unit::None;
  if (s == "mm") return Unit::Millimeter;
  if (s == "cm") return Unit::Centimeter;
  if (s == "m") return Unit::Meter;
  if (s == "in" || s == "\"") return Unit::Inch;
  if (s == "ft" || s == "'") return Unit::Foot;
  if (s == "deg" || s == "\xC2\xB0") return Unit::Degree; // UTF-8 degree sign
  if (s == "rad") return Unit::Radian;
  return std::nullopt;
}

double toInternal(double value, Unit u) { return value * factor(u); }
double fromInternal(double value, Unit u) { return value / factor(u); }

std::optional<double> parseQuantity(std::string_view text, Unit defaultUnit) {
  text = trim(text);
  if (text.empty()) return std::nullopt;
  double number = 0.0;
  const char* begin = text.data();
  const char* end = text.data() + text.size();
  if (*begin == '+') ++begin; // from_chars rejects a leading '+'
  auto [ptr, ec] = std::from_chars(begin, end, number);
  if (ec != std::errc{} || !std::isfinite(number)) return std::nullopt;
  auto unit = parseUnit(std::string_view(ptr, static_cast<size_t>(end - ptr)));
  if (!unit) return std::nullopt;
  Unit u = (*unit == Unit::None) ? defaultUnit : *unit;
  if (dimensionOf(u) != dimensionOf(defaultUnit)) return std::nullopt;
  return toInternal(number, u);
}

std::string formatQuantity(double internalValue, Unit u) {
  std::ostringstream os;
  os.precision(12);
  os << fromInternal(internalValue, u);
  if (u != Unit::None) os << ' ' << unitSymbol(u);
  return os.str();
}

} // namespace tsr
