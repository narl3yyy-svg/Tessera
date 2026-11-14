# A sketch saved as DXF (R12, millimetres): lines, circles and arcs as
# themselves, splines as polylines, construction only when asked.
import json
import os
import tempfile
import tsr

sk = {"points": [[0, 0], [0, 0], [4, 0], [2, 2], [6, 0], [7, 1], [8, 0], [1, 0], [0, 1], [5, 3], [6, 3]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "circle", "c": 3, "r": 0.5},
                   {"type": "spline", "fit": [4, 5, 6]}, {"type": "arc", "c": 1, "p": [7, 8], "r": 1.0},
                   {"type": "line", "p": [9, 10], "construction": True}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(sk))
path = os.path.join(tempfile.mkdtemp(), "s.dxf")
tsr.export_sketch_dxf("Sketch1", path)
lines = open(path).read().split("\n")
pairs = list(zip(lines[0::2], lines[1::2]))
kinds = [v for c, v in pairs if c.strip() == "0"]
assert kinds.count("LINE") == 1 and kinds.count("CIRCLE") == 1 and kinds.count("ARC") == 1, kinds
assert kinds.count("POLYLINE") == 1 and kinds[-1] == "EOF", kinds
i = kinds.index("LINE")
vals = {}
# The line's end: 40 mm along X.
for k, (c, v) in enumerate(pairs):
    if c.strip() == "0" and v == "LINE":
        vals = dict((cc.strip(), vv) for cc, vv in pairs[k + 1:k + 9])
        break
assert abs(float(vals["11"]) - 40.0) < 1e-9, vals
for k, (c, v) in enumerate(pairs):
    if c.strip() == "0" and v == "ARC":
        arc = dict((cc.strip(), vv) for cc, vv in pairs[k + 1:k + 8])
assert abs(float(arc["40"]) - 10.0) < 1e-9 and abs(float(arc["50"])) < 1e-9 and abs(float(arc["51"]) - 90) < 1e-9, arc
tsr.export_sketch_dxf("Sketch1", path, construction=True)
assert "CONSTRUCTION" in open(path).read()
print("sketch dxf: OK")

# --- Insert DXF: a 40 x 30 mm rectangle with a 10 mm circle, saved and read back.
import adsk.core
import adsk.fusion
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
tsr.new_document()
rect = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3], [2, 1.5]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 4]},
                     {"type": "line", "p": [4, 1]}, {"type": "circle", "c": 5, "r": 0.5}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(rect))
tsr.export_sketch_dxf("Sketch1", path)
tsr.new_document()
tsr.insert_dxf(path, "XY")
tsr.run_command("tsr.feature.extrude", distance=1.0)
import math
# Both regions (the ring and the disc) are extruded: the whole 40 x 30 block,
# and the circle came back as a circle (two regions, not one).
assert abs(root.bRepBodies.item(0).volume - 12) < 1e-6, root.bRepBodies.item(0).volume
assert sum(1 for e in json.loads(tsr.sketch_data("Sketch1"))["entities"] if e["type"] == "circle") == 1

# A hand-written LWPOLYLINE in inches: a 1 x 1 inch square whose top side is
# a half circle bulging out (bulge 1): area 1 + pi / 8 square inches.
lw = "\n".join(["0", "SECTION", "2", "HEADER", "9", "$INSUNITS", "70", "1", "0", "ENDSEC",
                "0", "SECTION", "2", "ENTITIES", "0", "LWPOLYLINE", "8", "0", "90", "4", "70", "1",
                "10", "0", "20", "0", "10", "1", "20", "0", "10", "1", "20", "1", "42", "1", "10", "0", "20", "1",
                "0", "ENDSEC", "0", "EOF", ""])
lpath = os.path.join(tempfile.mkdtemp(), "lw.dxf")
open(lpath, "w").write(lw)
tsr.new_document()
tsr.insert_dxf(lpath, "XY")
tsr.run_command("tsr.feature.extrude", distance=1.0)
inch2 = 2.54 * 2.54
assert abs(root.bRepBodies.item(0).volume - (1 + math.pi / 8) * inch2) < 1e-6, root.bRepBodies.item(0).volume
try:
    bad = os.path.join(tempfile.mkdtemp(), "bad.dxf")
    open(bad, "w").write("0\nSECTION\n2\nENTITIES\n0\nENDSEC\n0\nEOF\n")
    tsr.insert_dxf(bad)
    raise AssertionError("an empty DXF was accepted")
except RuntimeError as e:
    assert "nothing" in str(e), e
print("insert dxf: OK")

# --- Insert SVG (100 x 50 mm page, viewBox in mm): a 40 x 20 rectangle with
# 5 mm round corners, a circle of r 5, and a path with a cubic and an arc.
svg = """<?xml version="1.0"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100mm" height="50mm" viewBox="0 0 100 50">
  <!-- a comment <rect> that must be ignored -->
  <defs><rect id="hidden" width="99" height="99"/></defs>
  <g transform="translate(10,10)">
    <rect x="0" y="0" width="40" height="20" rx="5"/>
    <circle cx="60" cy="10" r="5"/>
  </g>
  <path d="M 10 40 C 20 30, 30 30, 40 40 A 15 15 0 0 1 10 40 Z"/>
  <text x="0" y="0">ignored</text>
</svg>
"""
spath = os.path.join(tempfile.mkdtemp(), "d.svg")
open(spath, "w").write(svg)
tsr.new_document()
tsr.insert_dxf(spath, "XY")
sk = json.loads(tsr.sketch_data("Sketch1"))
kinds = [e["type"] for e in sk["entities"]]
assert kinds.count("circle") == 1 and kinds.count("line") == 4, kinds
circle = [e for e in sk["entities"] if e["type"] == "circle"][0]
assert abs(circle["r"] - 0.5) < 1e-9, circle
c = sk["points"][circle["c"]]
assert abs(c[0] - 7.0) < 1e-9 and abs(c[1] + 2.0) < 1e-9, c          # (70, -20) mm: y turned up
tsr.run_command("tsr.feature.extrude", distance=1.0)
vols = sorted(root.bRepBodies.item(i).volume for i in range(root.bRepBodies.count))
rounded = 4 * 2 - (4 - math.pi) * 0.25                                   # 40 x 20 less the four corners
disc = math.pi * 0.25
# The path: a cubic bump of 150 mm^2 over its 30 mm chord and a half circle of
# r 15 mm below it. Arcs become Beziers (within 0.03%); the circle stays exact.
shape = (150 + math.pi * 15 * 15 / 2) / 100
assert abs(vols[0] - disc) < 1e-9, vols
assert abs(vols[1] - shape) < 1e-3 * shape and abs(vols[2] - rounded) < 1e-3 * rounded, (vols, shape, rounded)
print("insert svg: OK")
