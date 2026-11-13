#!/usr/bin/env bash
# Build Tessera from this source tree and install it.
#
#   ./install.sh                 build and install to /usr/local (asks for sudo only for the copy step)
#   ./install.sh --user          install to ~/.local instead (no sudo at all)
#   ./install.sh --deps          also apt-install missing build dependencies first
#
# Run it as your normal user, not with sudo: the build happens in your account and
# sudo is used only where the install location needs it. Remove with ./uninstall.sh.
set -euo pipefail

SRC="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PREFIX=/usr/local
BUILD_DIR="$SRC/build-release"
RUN_TESTS=0   # the tests run in development builds (scripts/build.sh), not here
INSTALL_DEPS=0
JOBS="$(nproc 2>/dev/null || echo 2)"

DEPS=(build-essential cmake ninja-build qt6-base-dev
      libocct-foundation-dev libocct-modeling-data-dev libocct-modeling-algorithms-dev
      libocct-ocaf-dev libocct-visualization-dev libocct-data-exchange-dev
      pybind11-dev python3-dev nlohmann-json3-dev libeigen3-dev libtbb-dev)

usage() {
  cat <<EOF
Usage: ./install.sh [options]

  --prefix DIR     install location (default: /usr/local)
  --user           install to ~/.local (same as --prefix ~/.local, no sudo needed)
  --deps           apt-install any missing build dependencies first (uses sudo)
  --tests          also build and run the test suite before installing
                   (development builds run it: scripts/build.sh)
  --build-dir DIR  build directory (default: build-release in the source tree)
  --jobs N         parallel build jobs (default: $JOBS)
  -h, --help       show this help

Environment:
  APT_PROXY        proxy for --deps, e.g. socks5h://127.0.0.1:1080 for a machine
                   without direct internet access
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --prefix)    PREFIX="${2:?--prefix needs a directory}"; shift 2 ;;
    --prefix=*)  PREFIX="${1#*=}"; shift ;;
    --user)      PREFIX="$HOME/.local"; shift ;;
    --deps)      INSTALL_DEPS=1; shift ;;
    --tests)     RUN_TESTS=1; shift ;;
    --no-tests)  RUN_TESTS=0; shift ;;   # the default; kept for old scripts
    --build-dir) BUILD_DIR="${2:?--build-dir needs a directory}"; shift 2 ;;
    --jobs)      JOBS="${2:?--jobs needs a number}"; shift 2 ;;
    -h|--help)   usage; exit 0 ;;
    *) echo "install.sh: unknown option '$1'" >&2; usage >&2; exit 2 ;;
  esac
done

step() { printf '\n\033[1;34m==>\033[0m \033[1m%s\033[0m\n' "$*"; }
die()  { printf '\033[1;31merror:\033[0m %s\n' "$*" >&2; exit 1; }

if [[ $EUID -eq 0 ]]; then
  die "run ./install.sh as your normal user, not as root or with sudo.
       It asks for sudo itself, and only for the step that needs it."
fi
[[ -f "$SRC/CMakeLists.txt" && -d "$SRC/modules" ]] || die "run this from a Tessera source checkout"
PREFIX="$(realpath -m "$PREFIX")"

# --- dependencies -----------------------------------------------------------
step "Checking build dependencies"
missing=()
for p in "${DEPS[@]}"; do
  dpkg-query -W -f='${Status}' "$p" 2>/dev/null | grep -q "install ok installed" || missing+=("$p")
done
if [[ ${#missing[@]} -eq 0 ]]; then
  echo "all ${#DEPS[@]} packages are installed"
elif [[ $INSTALL_DEPS -eq 1 ]]; then
  echo "installing: ${missing[*]}"
  apt_opts=()
  if [[ -n "${APT_PROXY:-}" ]]; then
    apt_opts=(-o "Acquire::http::Proxy=$APT_PROXY" -o "Acquire::https::Proxy=$APT_PROXY")
  fi
  sudo apt-get "${apt_opts[@]}" update
  sudo apt-get "${apt_opts[@]}" install -y "${missing[@]}"
else
  die "missing packages: ${missing[*]}
       Install them with:  sudo apt install ${missing[*]}
       or rerun with:      ./install.sh --deps"
fi

# --- build ------------------------------------------------------------------
step "Configuring (Release, prefix $PREFIX)"
cmake -S "$SRC" -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PREFIX" \
  -DTSR_BUILD_TESTS="$([[ $RUN_TESTS -eq 1 ]] && echo ON || echo OFF)"

step "Building with $JOBS jobs"
cmake --build "$BUILD_DIR" --parallel "$JOBS"

if [[ $RUN_TESTS -eq 1 ]]; then
  step "Running tests"
  ctest --test-dir "$BUILD_DIR" --output-on-failure
fi

# --- install ----------------------------------------------------------------
# Use sudo only when the prefix is not writable by this user.
probe="$PREFIX"
while [[ ! -e "$probe" ]]; do probe="$(dirname "$probe")"; done
SUDO=()
if [[ ! -w "$probe" ]]; then
  SUDO=(sudo)
  echo
  echo "$PREFIX is not writable by $USER; sudo is needed to copy the files there."
fi

step "Installing to $PREFIX"
"${SUDO[@]}" cmake --install "$BUILD_DIR"
# cmake --install under sudo leaves a root-owned manifest in the build dir; hand it back.
[[ ${#SUDO[@]} -eq 0 ]] || sudo chown "$(id -u):$(id -g)" "$BUILD_DIR/install_manifest.txt"

# Keep the list of installed files next to the install so ./uninstall.sh works
# even after the source tree or build directory is gone.
MANIFEST_DIR="$PREFIX/share/tessera"
"${SUDO[@]}" mkdir -p "$MANIFEST_DIR"
{ cat "$BUILD_DIR/install_manifest.txt"; echo; echo "$MANIFEST_DIR/install-manifest.txt"; } \
  | sed '/^$/d' | "${SUDO[@]}" tee "$MANIFEST_DIR/install-manifest.txt" >/dev/null

step "Refreshing desktop caches"
refresh() { command -v "$1" >/dev/null 2>&1 && "${SUDO[@]}" "$@" >/dev/null 2>&1 || true; }
refresh update-mime-database "$PREFIX/share/mime"
refresh update-desktop-database "$PREFIX/share/applications"
refresh gtk-update-icon-cache -f -t "$PREFIX/share/icons/hicolor"
command -v kbuildsycoca6 >/dev/null 2>&1 && kbuildsycoca6 >/dev/null 2>&1 || true

step "Done"
echo "Installed $(wc -l < "$MANIFEST_DIR/install-manifest.txt") files under $PREFIX:"
echo "  $PREFIX/bin/tessera        the application (also in the KDE menu under Graphics)"
echo "  $PREFIX/bin/tessera-cli    headless scripting runner"
case ":$PATH:" in
  *":$PREFIX/bin:"*) ;;
  *) echo
     echo "Note: $PREFIX/bin is not on your PATH. Add it with:"
     echo "  echo 'export PATH=\"$PREFIX/bin:\$PATH\"' >> ~/.bashrc" ;;
esac
echo
echo "To remove it again: ./uninstall.sh$([[ "$PREFIX" == "$HOME/.local" ]] && echo ' --user')"
