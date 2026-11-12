#!/usr/bin/env python3
"""Live GUI driver for Tessera: injects real X11 mouse and keyboard events
(XTest) into a running `tessera --live-geometry FILE` and reads where its
widgets and the sketch are from FILE.

Runs on an X display (e.g. XWayland inside `kwin_wayland --virtual`).
Usage: xdrive.py GEOMETRY_FILE SCRIPT_FILE

Script lines (blank lines and # comments ignored):
  wait MS                    pause
  waitfor NAME [MS]          until a widget named NAME is visible
  click NAME                 left click the centre of widget NAME
  dclick NAME                double click it
  vclick FX FY               click the canvas at fractions of its width/height
  plane XY|XZ|YZ             click that origin plane (while Create Sketch asks for one)
  sclick X Y                 click sketch coordinates (mm) of the open sketch
  smove X Y                  move the pointer there (hover)
  sdrag X1 Y1 X2 Y2          press at one sketch point, drag to another, release
  spress X Y / srelease      press (and hold) / release the left button at a sketch point
  vdrag FX1 FY1 FX2 FY2      the same in canvas fractions
  wdrag NAME DX DY           press on widget NAME, drag by DX, DY pixels, release
  adrag DX DY                drag the in-canvas arrow by DX, DY pixels
  key KEY                    press a key: Tab, Return, Escape, a, ctrl+z, shift+Tab ...
  type TEXT                  type text (rest of the line)
  shot FILE                  ask the app to save a screenshot to FILE
  expect NAME                fail unless widget NAME is visible
  expectnot NAME             fail if widget NAME is visible
"""
import ctypes
import json
import os
import sys
import time

x11 = ctypes.CDLL("libX11.so.6")
xtst = ctypes.CDLL("libXtst.so.6")
x11.XOpenDisplay.restype = ctypes.c_void_p
x11.XOpenDisplay.argtypes = [ctypes.c_char_p]
x11.XStringToKeysym.restype = ctypes.c_ulong
x11.XStringToKeysym.argtypes = [ctypes.c_char_p]
x11.XKeysymToKeycode.restype = ctypes.c_ubyte
x11.XKeysymToKeycode.argtypes = [ctypes.c_void_p, ctypes.c_ulong]
x11.XFlush.argtypes = [ctypes.c_void_p]
x11.XSync.argtypes = [ctypes.c_void_p, ctypes.c_int]
xtst.XTestFakeMotionEvent.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_ulong]
xtst.XTestFakeButtonEvent.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_int, ctypes.c_ulong]
xtst.XTestFakeKeyEvent.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_int, ctypes.c_ulong]

dpy = x11.XOpenDisplay(None)
if not dpy:
    sys.exit("xdrive: cannot open the X display (is DISPLAY set?)")

GEOM = sys.argv[1]


def geometry(timeout=5.0):
    end = time.time() + timeout
    while True:
        try:
            with open(GEOM) as f:
                return json.load(f)
        except (OSError, ValueError):
            if time.time() > end:
                sys.exit("xdrive: no geometry from the app in " + GEOM)
            time.sleep(0.1)


def flush():
    x11.XSync(dpy, 0)


def move(x, y):
    xtst.XTestFakeMotionEvent(dpy, -1, int(round(x)), int(round(y)), 0)
    flush()
    time.sleep(0.03)


def button(down, which=1):
    xtst.XTestFakeButtonEvent(dpy, which, 1 if down else 0, 0)
    flush()
    time.sleep(0.04)


def click(x, y, times=1):
    move(x, y)
    for _ in range(times):
        button(True)
        button(False)
    time.sleep(0.15)


def drag(x1, y1, x2, y2, steps=20):
    move(x1, y1)
    button(True)
    for i in range(1, steps + 1):
        move(x1 + (x2 - x1) * i / steps, y1 + (y2 - y1) * i / steps)
    button(False)
    time.sleep(0.2)


def keycode(name):
    sym = x11.XStringToKeysym(name.encode())
    if not sym:
        sys.exit("xdrive: unknown key " + name)
    return x11.XKeysymToKeycode(dpy, sym)


MODS = {"ctrl": "Control_L", "shift": "Shift_L", "alt": "Alt_L"}


def key(spec):
    parts = spec.split("+")
    mods = [keycode(MODS[p]) for p in parts[:-1]]
    k = keycode(parts[-1])
    for m in mods:
        xtst.XTestFakeKeyEvent(dpy, m, 1, 0)
    xtst.XTestFakeKeyEvent(dpy, k, 1, 0)
    xtst.XTestFakeKeyEvent(dpy, k, 0, 0)
    for m in reversed(mods):
        xtst.XTestFakeKeyEvent(dpy, m, 0, 0)
    flush()
    time.sleep(0.05)


CHARS = {" ": "space", ".": "period", "-": "minus", "/": "slash", "*": "asterisk", "+": "plus",
         "(": "parenleft", ")": "parenright", ",": "comma", "_": "underscore", "^": "asciicircum"}
SHIFTED = set("*+()_^") | set("ABCDEFGHIJKLMNOPQRSTUVWXYZ")


def type_text(text):
    for ch in text:
        name = CHARS.get(ch, ch)
        key(("shift+" if ch in SHIFTED else "") + name)


def widget(name, g=None):
    g = g or geometry()
    r = g["widgets"].get(name)
    if r is None:
        sys.exit("xdrive: no visible widget named '%s'" % name)
    return r[0] + r[2] / 2, r[1] + r[3] / 2


def canvas(fx, fy):
    v = geometry()["viewport"]
    return v[0] + v[2] * fx, v[1] + v[3] * fy


def sketch_point(x_mm, y_mm):
    g = geometry()
    s = g.get("sketch")
    if not s:
        sys.exit("xdrive: no sketch is open")
    o, ax, ay = s["o"], s["x"], s["y"]   # screen positions of (0,0), (10,0), (0,10) mm
    return (o[0] + (ax[0] - o[0]) * x_mm / 10 + (ay[0] - o[0]) * y_mm / 10,
            o[1] + (ax[1] - o[1]) * x_mm / 10 + (ay[1] - o[1]) * y_mm / 10)


def main():
    with open(sys.argv[2]) as f:
        lines = f.read().splitlines()
    for n, raw in enumerate(lines, 1):
        line = raw.split("#", 1)[0].strip() if not raw.strip().startswith("type ") else raw.strip()
        if not line:
            continue
        cmd, _, rest = line.partition(" ")
        a = rest.split()
        print("xdrive:", n, line, flush=True)
        if cmd == "wait":
            time.sleep(float(a[0]) / 1000)
        elif cmd == "waitfor":
            end = time.time() + (float(a[1]) / 1000 if len(a) > 1 else 5)
            while a[0] not in geometry()["widgets"]:
                if time.time() > end:
                    sys.exit("xdrive: line %d: '%s' did not appear" % (n, a[0]))
                time.sleep(0.1)
        elif cmd == "click":
            click(*widget(a[0]))
        elif cmd == "dclick":
            click(*widget(a[0]), times=2)
        elif cmd == "vclick":
            click(*canvas(float(a[0]), float(a[1])))
        elif cmd == "plane":
            end = time.time() + 5
            while a[0] not in geometry().get("planes", {}):
                if time.time() > end:
                    sys.exit("xdrive: line %d: no origin planes to pick" % n)
                time.sleep(0.1)
            p = geometry()["planes"][a[0]]
            click(p[0], p[1])
        elif cmd == "sclick":
            click(*sketch_point(float(a[0]), float(a[1])))
        elif cmd == "smove":
            move(*sketch_point(float(a[0]), float(a[1])))
            time.sleep(0.15)
        elif cmd == "sdrag":
            p, q = sketch_point(float(a[0]), float(a[1])), sketch_point(float(a[2]), float(a[3]))
            drag(p[0], p[1], q[0], q[1])
        elif cmd == "spress":
            move(*sketch_point(float(a[0]), float(a[1])))
            button(True)
        elif cmd == "srelease":
            move(*sketch_point(float(a[0]), float(a[1])))
            button(False)
            time.sleep(0.2)
        elif cmd == "vdrag":
            p, q = canvas(float(a[0]), float(a[1])), canvas(float(a[2]), float(a[3]))
            drag(p[0], p[1], q[0], q[1])
        elif cmd == "wdrag":
            x, y = widget(a[0])
            drag(x, y, x + float(a[1]), y + float(a[2]))
        elif cmd == "adrag":
            end = time.time() + 5
            while "arrow" not in geometry():
                if time.time() > end:
                    sys.exit("xdrive: line %d: no drag arrow" % n)
                time.sleep(0.1)
            x, y = geometry()["arrow"]
            drag(x, y, x + float(a[0]), y + float(a[1]), steps=30)
        elif cmd == "key":
            key(a[0])
        elif cmd == "type":
            type_text(rest)
        elif cmd == "shot":
            path = os.path.abspath(a[0])
            with open(GEOM + ".shot", "w") as f:
                f.write(path)
            end = time.time() + 5
            while os.path.exists(GEOM + ".shot"):
                if time.time() > end:
                    sys.exit("xdrive: the app did not take the screenshot")
                time.sleep(0.1)
        elif cmd == "expect":
            if a[0] not in geometry()["widgets"]:
                sys.exit("xdrive: line %d: expected '%s' to be visible" % (n, a[0]))
        elif cmd == "expectnot":
            if a[0] in geometry()["widgets"]:
                sys.exit("xdrive: line %d: expected '%s' not to be visible" % (n, a[0]))
        else:
            sys.exit("xdrive: line %d: unknown command '%s'" % (n, cmd))
    print("xdrive: OK", flush=True)


try:
    main()
finally:
    open(GEOM + ".quit", "w").close()   # the app saves (--save-on-exit) and quits
