#!/usr/bin/env bash
# Configure, build and test. Usage: scripts/build.sh [build-dir] [extra cmake args...]
set -euo pipefail
cd "$(dirname "$0")/.."
BUILD="${1:-build}"
shift || true
cmake -S . -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo "$@"
cmake --build "$BUILD" --parallel "$(nproc)"
ctest --test-dir "$BUILD" --output-on-failure
