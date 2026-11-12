#!/bin/bash
# Live GUI test on a virtual X display (Xvfb, software OpenGL): runs the real
# app, drives it with real X11 input (scripts/xdrive.py), saves the
# design on exit and, if given, checks it with a Python script.
#
#   scripts/live-test.sh DRIVE_SCRIPT [SETUP.py] [CHECK.py]
#
# Screenshots named in the drive script land where its `shot` lines say.
set -u
here="$(cd "$(dirname "$0")/.." && pwd)"
build="${TSR_BUILD_DIR:-$here/build}"
drive="$(realpath "$1")"
setup="${2:+$(realpath "$2")}"
check="${3:+$(realpath "$3")}"
work="$(mktemp -d)"
cat > "$work/session.sh" <<INNER
#!/bin/bash
cd "$here"
export QT_QPA_PLATFORM=xcb TSR_THEME=dark LIBGL_ALWAYS_SOFTWARE=1
"$build/modules/app/tessera" --live-geometry "$work/geom.json" --save-on-exit "$work/out.tsr" \
    ${setup:+--script "$setup"} --quit-after 120000 > "$work/app.log" 2>&1 &
app=\$!
python3 "$here/scripts/xdrive.py" "$work/geom.json" "$drive" > "$work/drive.log" 2>&1
echo \$? > "$work/drive.status"
wait \$app
INNER
chmod +x "$work/session.sh"
timeout 180 xvfb-run -a -s "-screen 0 1600x1000x24" "$work/session.sh" > /dev/null 2>&1
cat "$work/drive.log";
status="$(cat "$work/drive.status" 2>/dev/null || echo 99)"
if [ "$status" != 0 ]; then
  echo "live-test: driver failed ($status); app log:"; tail -20 "$work/app.log"; exit 1
fi
if [ -n "$check" ]; then
  "$build/modules/api/tessera-cli" --open "$work/out.tsr" --script "$check" || { echo "live-test: check failed"; exit 1; }
fi
echo "live-test: PASS"
