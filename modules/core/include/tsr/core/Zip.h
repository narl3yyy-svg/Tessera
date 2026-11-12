#pragma once
#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace tsr::zip {

struct Entry {
  std::string name; // forward slashes, no leading slash
  std::string data; // raw bytes
};

class ZipError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

std::uint32_t crc32(const void* data, std::size_t size);

// Writes a ZIP archive with every member STORED (method 0) and fixed
// timestamps, so the same content always produces the same bytes.
// Writes to <path>.tmp then renames, so a crash never leaves a torn file.
// P0 limitation: no deflate (docs/KNOWN_GAPS.md, P0-3).
void write(const std::filesystem::path& path, const std::vector<Entry>& entries);

// Reads a ZIP archive. Supports STORED members only; throws ZipError for
// deflated members, ZIP64, encryption, or CRC mismatch.
std::vector<Entry> read(const std::filesystem::path& path);

} // namespace tsr::zip
