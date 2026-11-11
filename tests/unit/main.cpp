#include "TestFramework.h"

#include <cstdio>
#include <cstring>

// Usage: <binary> [substring-filter]
int main(int argc, char** argv) {
  int passed = 0, failed = 0;
  for (const auto& c : tsrtest::registry()) {
    if (argc > 1 && !std::strstr(c.name, argv[1])) continue;
    try {
      c.fn();
      ++passed;
      std::printf("  ok    %s\n", c.name);
    } catch (const std::exception& e) {
      ++failed;
      std::printf("  FAIL  %s\n        %s\n", c.name, e.what());
    }
  }
  std::printf("%d passed, %d failed\n", passed, failed);
  return failed == 0 && passed > 0 ? 0 : 1;
}
