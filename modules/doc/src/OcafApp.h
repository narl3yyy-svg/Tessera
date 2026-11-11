#pragma once
#include <BinDrivers.hxx>
#include <TDocStd_Application.hxx>

namespace tsr::doc {

// OCAF binary format with B-rep (TNaming) support.
inline constexpr const char* kOcafFormat = "BinOcaf";

// One OCAF application per process, as OCCT expects.
inline const Handle(TDocStd_Application)& ocafApplication() {
  static const Handle(TDocStd_Application) app = [] {
    Handle(TDocStd_Application) a = new TDocStd_Application();
    BinDrivers::DefineFormat(a);
    return a;
  }();
  return app;
}

} // namespace tsr::doc
