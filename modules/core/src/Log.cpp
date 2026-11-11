#include "tsr/core/Log.h"

#include <cstdio>
#include <mutex>

namespace tsr::log {

namespace {
std::mutex g_mutex;
Sink g_sink;

const char* name(Level l) {
  switch (l) {
    case Level::Debug: return "debug";
    case Level::Info: return "info";
    case Level::Warning: return "warning";
    case Level::Error: return "error";
  }
  return "?";
}
} // namespace

void write(Level level, const std::string& message) {
  std::lock_guard lock(g_mutex);
  if (g_sink) {
    g_sink(level, message);
  } else if (level >= Level::Info) {
    std::fprintf(stderr, "tessera [%s] %s\n", name(level), message.c_str());
  }
}

void setSink(Sink sink) {
  std::lock_guard lock(g_mutex);
  g_sink = std::move(sink);
}

} // namespace tsr::log
