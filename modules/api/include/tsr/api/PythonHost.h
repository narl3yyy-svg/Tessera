#pragma once
#include "tsr/doc/Session.h"

#include <filesystem>
#include <string>

namespace tsr::api {

// Embedded CPython with the adsk.* shim and the tessera-specific `tsr`
// module bound to one Session. One host per process (CPython limitation).
class PythonHost {
public:
  explicit PythonHost(doc::Session& session);
  ~PythonHost();
  PythonHost(const PythonHost&) = delete;
  PythonHost& operator=(const PythonHost&) = delete;

  struct Result {
    bool ok = false;
    std::string output; // captured stdout + stderr
    std::string error;  // formatted Python exception, if any
  };

  // Fusion-style script: execute the file as __main__, then call
  // run(context) if the file defines it.
  Result runScript(const std::filesystem::path& path);
  // Execute a code string in a persistent __main__ namespace.
  Result exec(const std::string& code);
};

// Used by the bindings; valid while a PythonHost exists.
doc::Session& activeSession();

} // namespace tsr::api
