#pragma once
#include <functional>
#include <string>

namespace tsr::log {

enum class Level { Debug, Info, Warning, Error };

void write(Level level, const std::string& message);
inline void debug(const std::string& m) { write(Level::Debug, m); }
inline void info(const std::string& m) { write(Level::Info, m); }
inline void warning(const std::string& m) { write(Level::Warning, m); }
inline void error(const std::string& m) { write(Level::Error, m); }

// Replace the sink (default: stderr, Info and above). Pass nullptr to restore.
using Sink = std::function<void(Level, const std::string&)>;
void setSink(Sink sink);

} // namespace tsr::log
