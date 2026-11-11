#pragma once
#include <cstdint>
#include <string>
#include <variant>

namespace tsr {

// The value carried by a command input. Real values are always in internal
// units (cm, rad) — the same convention as the adsk API — and are converted
// to display units only at the UI edge.
using Value = std::variant<std::monostate, bool, std::int64_t, double, std::string>;

inline bool isEmpty(const Value& v) { return std::holds_alternative<std::monostate>(v); }

} // namespace tsr
