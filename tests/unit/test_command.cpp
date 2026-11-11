#include "TestFramework.h"
#include "tsr/core/CommandRegistry.h"

#include <memory>
#include <vector>

using namespace tsr;

namespace {

// A document that is just a list of numbers, with transactions as snapshots.
struct FakeDoc : CommandContext {
  std::vector<double> items;
  std::vector<double> snapshot;
  bool open = false;
  int commits = 0, aborts = 0;

  void openTransaction(const std::string&) override {
    if (open) throw std::logic_error("nested transaction");
    snapshot = items;
    open = true;
  }
  void commitTransaction() override { open = false; ++commits; }
  void abortTransaction() override { items = snapshot; open = false; ++aborts; }
  bool hasOpenTransaction() const override { return open; }
};

struct Push : Command {
  CommandDef d;
  Push() {
    d.id = "test.push";
    d.name = "Push";
    d.inputs = {InputDef{.id = "x", .label = "X", .tooltip = {}, .type = InputType::Real, .defaultValue = 1.0,
                         .unit = Unit::Millimeter, .min = 0.0, .max = 10.0, .minExclusive = true}};
  }
  const CommandDef& def() const override { return d; }
  std::string validate(const Inputs& in, CommandContext&) const override {
    return getReal(in, "x") == 5.0 ? "five is forbidden" : "";
  }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    if (getReal(in, "x") == 7.0) throw CommandError("kernel failure");
    static_cast<FakeDoc&>(ctx).items.push_back(getReal(in, "x"));
  }
};

} // namespace

TEST(command_defaults_and_execute) {
  FakeDoc doc;
  Push cmd;
  CommandSession s(cmd, doc);
  CHECK_EQ(getReal(s.inputs(), "x"), 1.0);
  CHECK_EQ(s.execute(), std::string());
  CHECK_EQ(doc.items.size(), size_t(1));
  CHECK_EQ(doc.commits, 1);
  CHECK(!doc.open);
}

TEST(command_range_checks) {
  FakeDoc doc;
  Push cmd;
  CommandSession s(cmd, doc);
  CHECK(!s.setInput("x", 0.0).empty());     // exclusive minimum
  CHECK(!s.setInput("x", 10.5).empty());    // above max
  CHECK(!s.setInput("x", std::string("a")).empty());
  CHECK(!s.setInput("nope", 1.0).empty());
  CHECK(s.setInput("x", std::int64_t{3}).empty()); // integers accepted for reals
  CHECK_EQ(getReal(s.inputs(), "x"), 3.0);
}

TEST(command_preview_is_rolled_back) {
  FakeDoc doc;
  Push cmd;
  {
    CommandSession s(cmd, doc);
    CHECK_EQ(s.preview(), std::string());
    CHECK(s.previewActive());
    CHECK_EQ(doc.items.size(), size_t(1));
    CHECK(s.setInput("x", 2.0).empty()); // change drops the preview
    CHECK(!s.previewActive());
    CHECK(doc.items.empty());
    CHECK_EQ(s.preview(), std::string());
    s.cancel();
    CHECK(doc.items.empty());
    CHECK(!doc.open);
  }
  {
    CommandSession s(cmd, doc);
    CHECK_EQ(s.preview(), std::string());
  } // destructor cancels
  CHECK(doc.items.empty());
  CHECK(!doc.open);
}

TEST(command_preview_then_execute_applies_once) {
  FakeDoc doc;
  Push cmd;
  CommandSession s(cmd, doc);
  CHECK_EQ(s.preview(), std::string());
  CHECK_EQ(s.execute(), std::string());
  CHECK_EQ(doc.items.size(), size_t(1));
  CHECK(s.finished());
  CHECK(!s.execute().empty()); // cannot run twice
}

TEST(command_validation_and_apply_failures_leave_no_trace) {
  FakeDoc doc;
  Push cmd;
  CommandSession a(cmd, doc);
  CHECK(a.setInput("x", 5.0).empty());
  CHECK_EQ(a.execute(), std::string("five is forbidden"));
  CommandSession b(cmd, doc);
  CHECK(b.setInput("x", 7.0).empty());
  CHECK_EQ(b.preview(), std::string("kernel failure"));
  CHECK_EQ(b.execute(), std::string("kernel failure"));
  CHECK(doc.items.empty());
  CHECK(!doc.open);
}

TEST(registry_run_and_lookup) {
  CommandRegistry reg;
  reg.add(std::make_unique<Push>());
  CHECK_THROWS(reg.add(std::make_unique<Push>()));
  CHECK(reg.find("test.push") != nullptr);
  CHECK(reg.find("missing") == nullptr);
  FakeDoc doc;
  CHECK_EQ(reg.run("test.push", {{"x", 4.0}}, doc), std::string());
  CHECK_EQ(doc.items.back(), 4.0);
  CHECK(!reg.run("missing", {}, doc).empty());
  CHECK(!reg.run("test.push", {{"x", 11.0}}, doc).empty());
}
