#include "TestFramework.h"
#include "tsr/core/Zip.h"

#include <filesystem>
#include <fstream>
#include <iterator>

using namespace tsr;
namespace fs = std::filesystem;

namespace {
fs::path tmp(const char* name) { return fs::temp_directory_path() / name; }

std::string slurp(const fs::path& p) {
  std::ifstream f(p, std::ios::binary);
  return {std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()};
}
} // namespace

TEST(zip_crc32_known_value) {
  const char s[] = "123456789";
  CHECK_EQ(zip::crc32(s, 9), 0xCBF43926u);
}

TEST(zip_round_trip) {
  std::string binary;
  for (int i = 0; i < 1000; ++i) binary.push_back(static_cast<char>(i & 0xff));
  const std::vector<zip::Entry> in = {{"manifest.json", "{}"}, {"document/ocaf.xbf", binary}, {"empty", ""}};
  const auto p = tmp("tsr_zip_round_trip.zip");
  zip::write(p, in);
  const auto out = zip::read(p);
  CHECK_EQ(out.size(), in.size());
  for (size_t i = 0; i < in.size(); ++i) {
    CHECK_EQ(out[i].name, in[i].name);
    CHECK(out[i].data == in[i].data);
  }
  CHECK(!fs::exists(fs::path(p.string() + ".tmp")));
  fs::remove(p);
}

TEST(zip_is_deterministic) {
  const std::vector<zip::Entry> in = {{"a", "hello"}, {"b/c", "world"}};
  const auto p1 = tmp("tsr_zip_det1.zip"), p2 = tmp("tsr_zip_det2.zip");
  zip::write(p1, in);
  zip::write(p2, in);
  CHECK(slurp(p1) == slurp(p2));
  fs::remove(p1);
  fs::remove(p2);
}

TEST(zip_detects_corruption) {
  const auto p = tmp("tsr_zip_corrupt.zip");
  zip::write(p, {{"a", "hello world"}});
  {
    std::fstream f(p, std::ios::in | std::ios::out | std::ios::binary);
    f.seekp(30 + 1 + 3); // local header + name "a" + 3 bytes into the data
    f.put('X');
  }
  CHECK_THROWS(zip::read(p));
  fs::remove(p);
  CHECK_THROWS(zip::read(tmp("tsr_zip_does_not_exist.zip")));
}

TEST(zip_rejects_bad_names) {
  CHECK_THROWS(zip::write(tmp("tsr_zip_bad.zip"), {{"/abs", "x"}}));
  CHECK_THROWS(zip::write(tmp("tsr_zip_bad.zip"), {{"", "x"}}));
}
