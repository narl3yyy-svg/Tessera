#pragma once
// Minimal self-registering test harness (no third-party dependency).
#include <cmath>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace tsrtest {

struct Case {
  const char* name;
  std::function<void()> fn;
};

inline std::vector<Case>& registry() {
  static std::vector<Case> r;
  return r;
}

struct Register {
  Register(const char* name, std::function<void()> fn) { registry().push_back({name, std::move(fn)}); }
};

struct Failure : std::runtime_error {
  using std::runtime_error::runtime_error;
};

inline void fail(const char* file, int line, const std::string& msg) {
  std::ostringstream os;
  os << file << ':' << line << ": " << msg;
  throw Failure(os.str());
}

} // namespace tsrtest

#define TSR_CAT2(a, b) a##b
#define TSR_CAT(a, b) TSR_CAT2(a, b)
#define TEST(name)                                                                      \
  static void TSR_CAT(test_, name)();                                                   \
  static ::tsrtest::Register TSR_CAT(reg_, name)(#name, &TSR_CAT(test_, name));         \
  static void TSR_CAT(test_, name)()

#define CHECK(cond) \
  do { if (!(cond)) ::tsrtest::fail(__FILE__, __LINE__, "CHECK(" #cond ")"); } while (0)

#define CHECK_EQ(a, b)                                                                   \
  do {                                                                                   \
    /* copies: (a) may be a member of a temporary that dies with the statement */        \
    const auto va_ = (a); const auto vb_ = (b);                                          \
    if (!(va_ == vb_)) {                                                                 \
      std::ostringstream os_; os_ << "CHECK_EQ(" #a ", " #b "): " << va_ << " != " << vb_; \
      ::tsrtest::fail(__FILE__, __LINE__, os_.str());                                   \
    }                                                                                    \
  } while (0)

#define CHECK_NEAR(a, b, tol)                                                             \
  do {                                                                                    \
    const double va_ = (a), vb_ = (b);                                                    \
    if (!(std::abs(va_ - vb_) <= (tol))) {                                                \
      std::ostringstream os_; os_.precision(15);                                          \
      os_ << "CHECK_NEAR(" #a ", " #b "): " << va_ << " vs " << vb_;                      \
      ::tsrtest::fail(__FILE__, __LINE__, os_.str());                                    \
    }                                                                                     \
  } while (0)

#define CHECK_THROWS(expr)                                                                 \
  do {                                                                                     \
    bool threw_ = false;                                                                   \
    try { (void)(expr); } catch (...) { threw_ = true; }                                   \
    if (!threw_) ::tsrtest::fail(__FILE__, __LINE__, "expected exception: " #expr);       \
  } while (0)
