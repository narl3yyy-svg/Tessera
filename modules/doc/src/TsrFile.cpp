// .tsr container (plan §4.6):
//   manifest.json        schema, version, units, app version, member list
//   document/ocaf.xbf    OCAF binary — the source of truth
//   params.json          user parameters, a readable mirror of the OCAF data
//   preview/*.png        thumbnails (written by the GUI; absent from headless saves)
#include "tsr/doc/Document.h"
#include "OcafApp.h"

#include "tsr/core/Zip.h"

#include <nlohmann/json.hpp>

#include <sstream>

namespace tsr::doc {

namespace {
constexpr const char* kSchema = "org.tessera.tsr";
constexpr int kSchemaVersion = 1;
constexpr const char* kManifest = "manifest.json";
constexpr const char* kOcaf = "document/ocaf.xbf";
constexpr const char* kParams = "params.json";
} // namespace

void Document::save(const std::filesystem::path& path) {
  if (doc_->HasOpenCommand()) throw DocumentError("cannot save while a command is in progress");

  nlohmann::json params = nlohmann::json::array();
  for (const auto& p : userParameters())
    params.push_back({{"name", p.name}, {"expression", p.expression}, {"unit", p.unit},
                      {"comment", p.comment}, {"value", p.value}});

  std::vector<zip::Entry> entries;
  entries.push_back({kManifest, ""}); // filled below, kept first
  entries.push_back({kOcaf, ocafBytes()});
  entries.push_back({kParams, nlohmann::json{{"userParameters", params}}.dump(2)});

  nlohmann::json members = nlohmann::json::array();
  for (const auto& e : entries) members.push_back(e.name);
  const nlohmann::json manifest = {
      {"schema", kSchema},
      {"schemaVersion", kSchemaVersion},
      {"appVersion", TSR_VERSION_STRING},
      {"units", {{"internalLength", "cm"}, {"internalAngle", "rad"}, {"defaultLength", defaultLengthUnit()}}},
      {"members", members},
  };
  entries[0].data = manifest.dump(2);

  try {
    zip::write(path, entries);
  } catch (const std::exception& e) {
    throw DocumentError("save failed: " + std::string(e.what()));
  }
  modified_ = false;
}

std::unique_ptr<Document> Document::load(const std::filesystem::path& path) {
  std::vector<zip::Entry> entries;
  try {
    entries = zip::read(path);
  } catch (const std::exception& e) {
    throw DocumentError(path.string() + ": " + e.what());
  }
  auto member = [&](const char* name) -> const std::string& {
    for (const auto& e : entries)
      if (e.name == name) return e.data;
    throw DocumentError(path.string() + ": missing " + name);
  };

  nlohmann::json manifest;
  try {
    manifest = nlohmann::json::parse(member(kManifest));
  } catch (const nlohmann::json::exception& e) {
    throw DocumentError(path.string() + ": bad manifest: " + e.what());
  }
  if (manifest.value("schema", "") != kSchema) throw DocumentError(path.string() + ": not a Tessera document");
  const int version = manifest.value("schemaVersion", 0);
  if (version < 1 || version > kSchemaVersion)
    throw DocumentError(path.string() + ": unsupported schema version " + std::to_string(version));

  std::istringstream is(member(kOcaf), std::ios::binary);
  Handle(TDocStd_Document) doc;
  const PCDM_ReaderStatus st = ocafApplication()->Open(is, doc);
  if (st != PCDM_RS_OK || doc.IsNull())
    throw DocumentError(path.string() + ": OCAF read failed (PCDM_ReaderStatus " + std::to_string(st) + ")");
  return std::unique_ptr<Document>(new Document(FromOcaf{}, doc));
}

} // namespace tsr::doc
