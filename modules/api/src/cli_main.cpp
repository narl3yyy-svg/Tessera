// tessera-cli: headless driver for scripted tests and the parity harness.
//
//   tessera-cli [--open IN.tsr] [--script S.py]... [--exec CODE]... [--save OUT.tsr] [--list-commands]
//
// Steps run in argument order. Exit code 0 on success, 1 on any failure.
#include "tsr/api/PythonHost.h"

#include <nlohmann/json.hpp>

#include <cstdio>
#include <iostream>
#include <string>

namespace {
int usage() {
  std::cerr << "usage: tessera-cli [--open IN.tsr] [--script S.py]... [--exec CODE]... "
               "[--save OUT.tsr] [--list-commands]\n";
  return 2;
}

void listCommands(const tsr::doc::Session& s) {
  nlohmann::json out = nlohmann::json::array();
  for (const tsr::Command* c : s.commands().all()) {
    nlohmann::json inputs = nlohmann::json::array();
    for (const auto& i : c->def().inputs)
      inputs.push_back({{"id", i.id}, {"label", i.label}, {"unit", std::string(tsr::unitSymbol(i.unit))}});
    out.push_back({{"id", c->def().id}, {"name", c->def().name}, {"tab", c->def().tab},
                   {"panel", c->def().panel}, {"inputs", inputs}});
  }
  std::cout << out.dump(2) << '\n';
}
} // namespace

int main(int argc, char** argv) {
  if (argc < 2) return usage();
  tsr::doc::Session session;
  tsr::api::PythonHost host(session);

  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    const bool hasValue = i + 1 < argc;
    try {
      if (a == "--list-commands") {
        listCommands(session);
      } else if (a == "--open" && hasValue) {
        session.open(argv[++i]);
      } else if (a == "--save" && hasValue) {
        session.save(argv[++i]);
      } else if ((a == "--script" || a == "--exec") && hasValue) {
        const std::string v = argv[++i];
        auto r = (a == "--script") ? host.runScript(v) : host.exec(v);
        std::cout << r.output;
        if (!r.ok) {
          std::cerr << "error: " << r.error << '\n';
          return 1;
        }
      } else {
        return usage();
      }
    } catch (const std::exception& e) {
      std::cerr << "error: " << e.what() << '\n';
      return 1;
    }
  }
  return 0;
}
