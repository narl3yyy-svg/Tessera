#include "TestFramework.h"
#include "tsr/core/Units.h"

#include <numbers>

using namespace tsr;

TEST(units_internal_is_cm_and_rad) {
  CHECK_NEAR(toInternal(10, Unit::Millimeter), 1.0, 1e-12);
  CHECK_NEAR(toInternal(1, Unit::Inch), 2.54, 1e-12);
  CHECK_NEAR(toInternal(180, Unit::Degree), std::numbers::pi, 1e-12);
  CHECK_NEAR(fromInternal(1.0, Unit::Millimeter), 10.0, 1e-12);
}

TEST(units_parse_quantity) {
  CHECK_NEAR(*parseQuantity("10", Unit::Millimeter), 1.0, 1e-12);
  CHECK_NEAR(*parseQuantity("10 mm", Unit::Millimeter), 1.0, 1e-12);
  CHECK_NEAR(*parseQuantity(" 2.5in ", Unit::Millimeter), 6.35, 1e-12);
  CHECK_NEAR(*parseQuantity("+3 cm", Unit::Millimeter), 3.0, 1e-12);
  CHECK_NEAR(*parseQuantity("-90 deg", Unit::Radian), -std::numbers::pi / 2, 1e-12);
  CHECK_NEAR(*parseQuantity("7", Unit::None), 7.0, 1e-12);
}

TEST(units_parse_quantity_rejects) {
  CHECK(!parseQuantity("", Unit::Millimeter));
  CHECK(!parseQuantity("abc", Unit::Millimeter));
  CHECK(!parseQuantity("10 furlongs", Unit::Millimeter));
  CHECK(!parseQuantity("10 deg", Unit::Millimeter)); // angle where a length is expected
  CHECK(!parseQuantity("10 mm", Unit::None));        // unit given for a unitless value
  CHECK(!parseQuantity("1e999", Unit::Millimeter));  // not finite
}

TEST(units_format_round_trips) {
  CHECK_EQ(formatQuantity(1.0, Unit::Millimeter), std::string("10 mm"));
  CHECK_NEAR(*parseQuantity(formatQuantity(0.123456789, Unit::Inch), Unit::Inch), 0.123456789, 1e-12);
}
