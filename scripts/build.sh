#!/usr/bin/env bash
# Development build: configure, build and run every test (unit, API, reference
# parts and the live GUI tests). A build is only good when all of them pass.
# Usage: scripts/build.sh [build-dir] [extra cmake args...]
set -euo pipefail
cd "$(dirname "$0")/.."
BUILD="${1:-build}"
shift || true
cmake -S . -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo "$@"
cmake --build "$BUILD" --parallel "$(nproc)"
ctest --test-dir "$BUILD" --output-on-failure
