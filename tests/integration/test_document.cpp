#include "TestFramework.h"
#include "tsr/doc/DocCommands.h"
#include "tsr/doc/Session.h"
#include "tsr/kernel/Kernel.h"

#include <filesystem>
#include <fstream>

using namespace tsr;
namespace fs = std::filesystem;

namespace {
Inputs param(const std::string& name, const std::string& expr, const std::string& unit = "mm") {
  return {{"name", name}, {"expression", expr}, {"unit", unit}, {"comment", std::string("c")}};
}
fs::path tmp(const char* name) { return fs::temp_directory_path() / name; }
} // namespace

TEST(kernel_box_metrics) {
  const auto s = kernel::makeBox(1, 2, 3);
  CHECK(kernel::isValid(s));
  const auto m = kernel::massProperties(s);
  CHECK_NEAR(m.volume, 6.0, 1e-9);
  CHECK_NEAR(m.area, 22.0, 1e-9);
  CHECK_NEAR(m.centerOfMass.z, 1.5, 1e-9);
  const auto t = kernel::topologyCounts(s);
  CHECK_EQ(t.faces, 6);
  CHECK_EQ(t.edges, 12);
  CHECK_EQ(t.vertices, 8);
  CHECK_THROWS(kernel::makeBox(0, 1, 1));
}

TEST(doc_add_parameter_undo_redo) {
  doc::Session s;
  CHECK_EQ(s.run(doc::kCmdAddUserParameter, param("width", "25 mm")), std::string());
  CHECK_EQ(s.run(doc::kCmdAddUserParameter, param("angle", "45", "deg")), std::string());
  auto& d = s.document();
  CHECK_EQ(d.userParameters().size(), size_t(2));
  CHECK_NEAR(d.userParameter("width")->value, 2.5, 1e-12);
  CHECK(d.isModified());

  CHECK(s.undo());
  CHECK_EQ(d.userParameters().size(), size_t(1));
  CHECK(s.undo());
  CHECK(d.userParameters().empty());
  CHECK(!s.undo());
  CHECK(s.redo());
  CHECK(s.redo());
  CHECK_EQ(d.userParameters().size(), size_t(2));
  CHECK_EQ(d.userParameter("angle")->unit, std::string("deg"));
}

TEST(doc_parameter_validation) {
  doc::Session s;
  CHECK_EQ(s.run(doc::kCmdAddUserParameter, param("w", "1")), std::string());
  CHECK(!s.run(doc::kCmdAddUserParameter, param("w", "2")).empty());       // duplicate
  CHECK(!s.run(doc::kCmdAddUserParameter, param("2w", "2")).empty());      // bad identifier
  CHECK(!s.run(doc::kCmdAddUserParameter, param("mm", "2")).empty());      // unit name
  CHECK(!s.run(doc::kCmdAddUserParameter, param("x", "2 deg")).empty());   // wrong dimension
  CHECK(!s.run(doc::kCmdAddUserParameter, param("x", "2", "furlong")).empty());
  CHECK_EQ(s.document().userParameters().size(), size_t(1));
  CHECK(!s.document().hasOpenTransaction());
}

TEST(doc_box_preview_cancel_and_execute) {
  doc::Session s;
  {
    auto cmd = s.begin(doc::kCmdBox);
    CHECK(cmd != nullptr);
    CHECK_EQ(cmd->preview(), std::string());
    CHECK_EQ(s.document().bodies().size(), size_t(1));
    cmd->cancel();
  }
  CHECK(s.document().bodies().empty());
  CHECK(!s.document().canUndo()); // a cancelled preview is not an undo step

  CHECK_EQ(s.run(doc::kCmdBox, {{"length", 2.0}, {"width", 3.0}, {"height", 4.0}}), std::string());
  const auto bodies = s.document().bodies();
  CHECK_EQ(bodies.size(), size_t(1));
  CHECK_EQ(bodies[0].name, std::string("Body1"));
  CHECK_NEAR(kernel::massProperties(bodies[0].shape).volume, 24.0, 1e-9);
  CHECK(!s.run(doc::kCmdBox, {{"length", 0.0}}).empty());
}

TEST(doc_tsr_round_trip) {
  const auto path = tmp("tsr_round_trip.tsr");
  {
    doc::Session s;
    CHECK_EQ(s.run(doc::kCmdAddUserParameter, param("width", "25 mm")), std::string());
    CHECK_EQ(s.run(doc::kCmdBox, {{"length", 2.0}, {"width", 3.0}, {"height", 4.0}}), std::string());
    s.save(path);
    CHECK(!s.document().isModified());
  }
  doc::Session s;
  s.open(path);
  auto& d = s.document();
  CHECK_EQ(d.userParameters().size(), size_t(1));
  const auto p = *d.userParameter("width");
  CHECK_EQ(p.expression, std::string("25 mm"));
  CHECK_EQ(p.comment, std::string("c"));
  CHECK_NEAR(p.value, 2.5, 1e-12);
  const auto bodies = d.bodies();
  CHECK_EQ(bodies.size(), size_t(1));
  CHECK(kernel::isValid(bodies[0].shape));
  CHECK_NEAR(kernel::massProperties(bodies[0].shape).volume, 24.0, 1e-9);
  CHECK_EQ(kernel::topologyCounts(bodies[0].shape).faces, 6);

  // The reopened document is editable and undoable.
  CHECK_EQ(s.run(doc::kCmdAddUserParameter, param("depth", "5")), std::string());
  CHECK(s.undo());
  CHECK_EQ(d.userParameters().size(), size_t(1));
  fs::remove(path);
}

TEST(doc_load_rejects_garbage) {
  const auto path = tmp("tsr_garbage.tsr");
  { std::ofstream(path) << "not a zip"; }
  doc::Session s;
  CHECK_THROWS(s.open(path));
  CHECK(s.document().userParameters().empty()); // previous document kept
  fs::remove(path);
}
