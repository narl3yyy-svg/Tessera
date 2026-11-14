#include "ProfileCache.h"

#include <cstdio>
#include <list>
#include <string>
#include <utility>

namespace tsr::app {

namespace {

// What profiles depend on: the plane and the curves (not constraints, which
// only say how the curves got where they are).
std::string keyOf(const sketch::Sketch& s, const gp_Ax3& f) {
  char buf[256];
  const gp_Pnt o = f.Location();
  const gp_Dir n = f.Direction(), x = f.XDirection();
  std::snprintf(buf, sizeof buf, "%.17g %.17g %.17g %.17g %.17g %.17g %.17g %.17g %.17g|", o.X(), o.Y(), o.Z(), n.X(),
                n.Y(), n.Z(), x.X(), x.Y(), x.Z());
  sketch::Sketch g;
  g.points = s.points;
  g.entities = s.entities;
  g.texts = s.texts;
  return buf + g.toJson();
}

constexpr size_t kCapacity = 24;   // a few visible sketches and the one being edited, with undo steps

} // namespace

std::vector<sketch::Profile> cachedProfiles(const sketch::Sketch& s, const gp_Ax3& frame) {
  static std::list<std::pair<std::string, std::vector<sketch::Profile>>> cache;   // most recent first
  std::string key = keyOf(s, frame);
  for (auto it = cache.begin(); it != cache.end(); ++it)
    if (it->first == key) {
      cache.splice(cache.begin(), cache, it);
      return cache.front().second;
    }
  auto profiles = sketch::profiles(s, frame);
  cache.emplace_front(std::move(key), profiles);
  if (cache.size() > kCapacity) cache.pop_back();
  return profiles;
}

} // namespace tsr::app
