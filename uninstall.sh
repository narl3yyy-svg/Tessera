#!/usr/bin/env bash
# Remove a Tessera installation made by ./install.sh.
#
#   ./uninstall.sh               remove the /usr/local install (asks for sudo if needed)
#   ./uninstall.sh --user        remove the ~/.local install
#   ./uninstall.sh --dry-run     only list what would be removed
#
# Only the files install.sh recorded are removed. Your .tsr designs are never touched.
set -euo pipefail

SRC="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PREFIX=""
DRY_RUN=0
CLEAN_BUILD=0

usage() {
  cat <<EOF
Usage: ./uninstall.sh [options]

  --prefix DIR   the prefix Tessera was installed to (default: found automatically,
                 checking /usr/local and ~/.local)
  --user         same as --prefix ~/.local
  --dry-run      list the files that would be removed, change nothing
  --clean-build  also delete the build-release directory in this source tree
  -h, --help     show this help
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --prefix)      PREFIX="${2:?--prefix needs a directory}"; shift 2 ;;
    --prefix=*)    PREFIX="${1#*=}"; shift ;;
    --user)        PREFIX="$HOME/.local"; shift ;;
    --dry-run)     DRY_RUN=1; shift ;;
    --clean-build) CLEAN_BUILD=1; shift ;;
    -h|--help)     usage; exit 0 ;;
    *) echo "uninstall.sh: unknown option '$1'" >&2; usage >&2; exit 2 ;;
  esac
done

step() { printf '\n\033[1;34m==>\033[0m \033[1m%s\033[0m\n' "$*"; }
die()  { printf '\033[1;31merror:\033[0m %s\n' "$*" >&2; exit 1; }

manifest_for() { echo "$1/share/tessera/install-manifest.txt"; }

if [[ -z "$PREFIX" ]]; then
  found=()
  for p in /usr/local "$HOME/.local"; do [[ -f "$(manifest_for "$p")" ]] && found+=("$p"); done
  case ${#found[@]} in
    0) die "no Tessera installation found in /usr/local or ~/.local.
       If you installed somewhere else, pass --prefix DIR." ;;
    1) PREFIX="${found[0]}" ;;
    *) die "Tessera is installed in both ${found[*]}.
       Choose one: ./uninstall.sh --prefix /usr/local   or   ./uninstall.sh --user" ;;
  esac
fi
PREFIX="$(realpath -m "$PREFIX")"
MANIFEST="$(manifest_for "$PREFIX")"
[[ -f "$MANIFEST" ]] || die "no install manifest at $MANIFEST; is Tessera installed under $PREFIX?"

# Read the list, and refuse anything outside the prefix so a damaged manifest
# can never delete unrelated files.
mapfile -t files < <(sed '/^[[:space:]]*$/d' "$MANIFEST")
for f in "${files[@]}"; do
  case "$(realpath -m "$f")" in
    "$PREFIX"/*) ;;
    *) die "manifest lists '$f', which is outside $PREFIX; refusing to continue" ;;
  esac
done

SUDO=()
if [[ ! -w "$PREFIX/share/tessera" ]]; then
  [[ $DRY_RUN -eq 1 ]] || SUDO=(sudo)
fi

step "Removing Tessera from $PREFIX"
removed=0
for f in "${files[@]}"; do
  if [[ -e "$f" || -L "$f" ]]; then
    echo "  rm $f"
    [[ $DRY_RUN -eq 1 ]] || "${SUDO[@]}" rm -f -- "$f"
    removed=$((removed + 1))
  fi
done

# Remove directories only if they are now empty (never system directories that
# still hold other software). share/mime/packages stays: update-mime-database
# refuses to rebuild without it, which would leave the .tsr type registered.
dirs=(share/tessera share/icons/hicolor/scalable/apps)
if [[ $DRY_RUN -eq 0 ]]; then
  for d in "${dirs[@]}"; do "${SUDO[@]}" rmdir --ignore-fail-on-non-empty -- "$PREFIX/$d" 2>/dev/null || true; done

  step "Refreshing desktop caches"
  refresh() { command -v "$1" >/dev/null 2>&1 && "${SUDO[@]}" "$@" >/dev/null 2>&1 || true; }
  refresh update-mime-database "$PREFIX/share/mime"
  refresh update-desktop-database "$PREFIX/share/applications"
  refresh gtk-update-icon-cache -f -t "$PREFIX/share/icons/hicolor"
  command -v kbuildsycoca6 >/dev/null 2>&1 && kbuildsycoca6 >/dev/null 2>&1 || true
fi

if [[ $CLEAN_BUILD -eq 1 && -d "$SRC/build-release" ]]; then
  echo "  rm -r $SRC/build-release"
  [[ $DRY_RUN -eq 1 ]] || rm -rf -- "$SRC/build-release"
fi

step "Done"
if [[ $DRY_RUN -eq 1 ]]; then
  echo "Dry run: $removed files would be removed. Nothing was changed."
else
  echo "Removed $removed files. Your .tsr design files were not touched."
fi
