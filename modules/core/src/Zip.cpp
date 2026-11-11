#include "tsr/core/Zip.h"

#include <array>
#include <fstream>
#include <iterator>
#include <limits>

namespace tsr::zip {

namespace {
constexpr std::uint32_t kLocalSig = 0x04034b50;
constexpr std::uint32_t kCentralSig = 0x02014b50;
constexpr std::uint32_t kEndSig = 0x06054b50;
constexpr std::uint16_t kFlagUtf8 = 0x0800;
constexpr std::uint16_t kDosTime = 0;      // 00:00:00
constexpr std::uint16_t kDosDate = 0x0021; // 1980-01-01

const std::array<std::uint32_t, 256>& crcTable() {
  static const auto table = [] {
    std::array<std::uint32_t, 256> t{};
    for (std::uint32_t i = 0; i < 256; ++i) {
      std::uint32_t c = i;
      for (int k = 0; k < 8; ++k) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
      t[i] = c;
    }
    return t;
  }();
  return table;
}

void put16(std::string& b, std::uint16_t v) {
  b.push_back(static_cast<char>(v & 0xff));
  b.push_back(static_cast<char>(v >> 8));
}
void put32(std::string& b, std::uint32_t v) {
  for (int i = 0; i < 4; ++i) b.push_back(static_cast<char>((v >> (8 * i)) & 0xff));
}
std::uint16_t get16(const std::string& b, std::size_t off) {
  if (off + 2 > b.size()) throw ZipError("truncated archive");
  return static_cast<std::uint16_t>(static_cast<unsigned char>(b[off]) |
                                    (static_cast<unsigned char>(b[off + 1]) << 8));
}
std::uint32_t get32(const std::string& b, std::size_t off) {
  if (off + 4 > b.size()) throw ZipError("truncated archive");
  std::uint32_t v = 0;
  for (int i = 3; i >= 0; --i) v = (v << 8) | static_cast<unsigned char>(b[off + static_cast<std::size_t>(i)]);
  return v;
}
} // namespace

std::uint32_t crc32(const void* data, std::size_t size) {
  const auto& t = crcTable();
  std::uint32_t c = 0xFFFFFFFFu;
  auto p = static_cast<const unsigned char*>(data);
  for (std::size_t i = 0; i < size; ++i) c = t[(c ^ p[i]) & 0xff] ^ (c >> 8);
  return c ^ 0xFFFFFFFFu;
}

void write(const std::filesystem::path& path, const std::vector<Entry>& entries) {
  constexpr auto kMax = std::numeric_limits<std::uint32_t>::max();
  if (entries.size() >= 0xFFFF) throw ZipError("too many entries (ZIP64 not supported)");
  std::string out, central;
  for (const auto& e : entries) {
    if (e.name.empty() || e.name.size() > 0xFFFF || e.name.front() == '/')
      throw ZipError("invalid entry name '" + e.name + "'");
    if (e.data.size() >= kMax || out.size() >= kMax) throw ZipError("archive too large (ZIP64 not supported)");
    const auto crc = crc32(e.data.data(), e.data.size());
    const auto size = static_cast<std::uint32_t>(e.data.size());
    const auto offset = static_cast<std::uint32_t>(out.size());
    const auto nameLen = static_cast<std::uint16_t>(e.name.size());

    put32(out, kLocalSig); put16(out, 20); put16(out, kFlagUtf8); put16(out, 0);
    put16(out, kDosTime); put16(out, kDosDate);
    put32(out, crc); put32(out, size); put32(out, size);
    put16(out, nameLen); put16(out, 0);
    out += e.name; out += e.data;

    put32(central, kCentralSig); put16(central, 20); put16(central, 20);
    put16(central, kFlagUtf8); put16(central, 0); put16(central, kDosTime); put16(central, kDosDate);
    put32(central, crc); put32(central, size); put32(central, size);
    put16(central, nameLen); put16(central, 0); put16(central, 0);
    put16(central, 0); put16(central, 0); put32(central, 0); put32(central, offset);
    central += e.name;
  }
  if (out.size() + central.size() >= kMax) throw ZipError("archive too large (ZIP64 not supported)");
  const auto cdOffset = static_cast<std::uint32_t>(out.size());
  const auto n = static_cast<std::uint16_t>(entries.size());
  out += central;
  put32(out, kEndSig); put16(out, 0); put16(out, 0); put16(out, n); put16(out, n);
  put32(out, static_cast<std::uint32_t>(central.size())); put32(out, cdOffset); put16(out, 0);

  auto tmp = path;
  tmp += ".tmp";
  {
    std::ofstream f(tmp, std::ios::binary | std::ios::trunc);
    if (!f) throw ZipError("cannot write " + tmp.string());
    f.write(out.data(), static_cast<std::streamsize>(out.size()));
    if (!f) throw ZipError("write failed: " + tmp.string());
  }
  std::filesystem::rename(tmp, path);
}

std::vector<Entry> read(const std::filesystem::path& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) throw ZipError("cannot open " + path.string());
  const std::string b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

  // End-of-central-directory record: 22 bytes + up to 64 KiB comment.
  if (b.size() < 22) throw ZipError("not a zip archive");
  std::size_t eocd = std::string::npos;
  const std::size_t stop = b.size() > 22 + 0xFFFF ? b.size() - 22 - 0xFFFF : 0;
  for (std::size_t i = b.size() - 22 + 1; i-- > stop;)
    if (get32(b, i) == kEndSig) { eocd = i; break; }
  if (eocd == std::string::npos) throw ZipError("not a zip archive (no end record)");

  const std::uint16_t count = get16(b, eocd + 10);
  std::size_t p = get32(b, eocd + 16);
  if (count == 0xFFFF || p == 0xFFFFFFFFu) throw ZipError("ZIP64 not supported");

  std::vector<Entry> entries;
  entries.reserve(count);
  for (std::uint16_t i = 0; i < count; ++i) {
    if (get32(b, p) != kCentralSig) throw ZipError("corrupt central directory");
    const std::uint16_t flags = get16(b, p + 8);
    const std::uint16_t method = get16(b, p + 10);
    const std::uint32_t crc = get32(b, p + 16);
    const std::uint32_t csize = get32(b, p + 20);
    const std::uint32_t usize = get32(b, p + 24);
    const std::uint16_t nlen = get16(b, p + 28), xlen = get16(b, p + 30), clen = get16(b, p + 32);
    const std::uint32_t local = get32(b, p + 42);
    if (p + 46 + nlen > b.size()) throw ZipError("truncated archive");
    Entry e;
    e.name = b.substr(p + 46, nlen);
    p += 46u + nlen + xlen + clen;

    if (flags & 0x0001) throw ZipError(e.name + ": encrypted members not supported");
    if (method != 0) throw ZipError(e.name + ": compression method " + std::to_string(method) + " not supported");
    if (csize != usize) throw ZipError(e.name + ": size mismatch");
    if (get32(b, local) != kLocalSig) throw ZipError(e.name + ": bad local header");
    const std::size_t data = local + 30u + get16(b, local + 26) + get16(b, local + 28);
    if (data + csize > b.size()) throw ZipError(e.name + ": truncated data");
    e.data = b.substr(data, csize);
    if (crc32(e.data.data(), e.data.size()) != crc) throw ZipError(e.name + ": CRC mismatch");
    entries.push_back(std::move(e));
  }
  return entries;
}

} // namespace tsr::zip
