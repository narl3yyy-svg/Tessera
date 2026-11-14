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
