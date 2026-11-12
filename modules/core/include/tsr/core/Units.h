#pragma once
#include <optional>
#include <string>
#include <string_view>

namespace tsr {

// Internal units match the adsk API: length in cm, angle in radians.
enum class Unit { None, Millimeter, Centimeter, Meter, Inch, Foot, Degree, Radian };

enum class Dimension { Unitless, Length, Angle };

Dimension dimensionOf(Unit u);
std::string_view unitSymbol(Unit u);               // "mm", "deg", "" ...
std::optional<Unit> parseUnit(std::string_view s); // "mm", "in", "deg", "rad", "" ...

double toInternal(double value, Unit u);   // 10 mm -> 1.0 (cm)
double fromInternal(double value, Unit u); // 1.0 (cm) -> 10 mm

// Parse "10", "10 mm", "2.5in", "-45 deg". A bare number uses defaultUnit.
// Returns the value in internal units, or nullopt if the text does not parse
// or its unit's dimension differs from defaultUnit's.
// P0 limitation: no arithmetic, functions or parameter references
// (docs/KNOWN_GAPS.md, P0-1).
std::optional<double> parseQuantity(std::string_view text, Unit defaultUnit);

// "10 mm" style text for an internal value shown in unit u.
std::string formatQuantity(double internalValue, Unit u);

} // namespace tsr
