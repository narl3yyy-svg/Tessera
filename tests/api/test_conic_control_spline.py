# Conic Curve and Control Point Spline, as in the familiar CREATE menu: each
# closes a profile with a line, and the solid has the exact (or integrated)
# area of the curve's region.
import json
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent


def extrude_area(entities, points):
    tsr.new_document()
    tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps({"points": points, "entities": entities}))
    tsr.run_command("tsr.feature.extrude", distance=1.0)
    return root.bRepBodies.item(0).volume


# Conic, rho 0.5 (a parabola): from (4,0) to (0,0), its tangents meeting at
# (2,2); the parabola peaks halfway to the vertex, at 1. Area 2/3 * 4 * 1.
pts = [[0, 0], [0, 0], [4, 0], [2, 2]]
conic = [{"type": "line", "p": [1, 2]}, {"type": "spline", "fit": [2, 3, 1], "kind": "conic", "rho": 0.5}]
v = extrude_area(conic, pts)
assert abs(v - 8 / 3) < 1e-6, v

# Rho changes the shape: below 0.5 flatter (an ellipse's arc), above fuller.
low = extrude_area([conic[0], dict(conic[1], rho=0.3)], pts)
high = extrude_area([conic[0], dict(conic[1], rho=0.8)], pts)
assert low < 8 / 3 < high < 4, (low, high)            # never past the triangle (area 4)

# Saved form: kind and rho kept.
data = json.loads(tsr.features()[0]["inputs"]["data"])
sp = [e for e in data["entities"] if e["type"] == "spline"][0]
assert sp["kind"] == "conic" and abs(sp["rho"] - 0.8) < 1e-12, sp

# Control Point Spline: a cubic on the frame (0,0) (1,2) (3,2) (4,0), closed
# by the line back; it starts and ends on the frame's ends.
cpts = [[0, 0], [0, 0], [1, 2], [3, 2], [4, 0]]
ctrl = [{"type": "spline", "fit": [1, 2, 3, 4], "kind": "control"}, {"type": "line", "p": [4, 1]}]
v = extrude_area(ctrl, cpts)


def bez(t, c):
    u = 1 - t
    return u ** 3 * c[0] + 3 * u * u * t * c[1] + 3 * u * t * t * c[2] + t ** 3 * c[3]


def dbez(t, c):
    u = 1 - t
    return 3 * (u * u * (c[1] - c[0]) + 2 * u * t * (c[2] - c[1]) + t * t * (c[3] - c[2]))


X, Y = [p[0] for p in cpts[1:]], [p[1] for p in cpts[1:]]
n = 2000
area = sum(bez((i + 0.5) / n, Y) * dbez((i + 0.5) / n, X) / n for i in range(n))   # integral of y dx
assert abs(v - area) < 1e-5, (v, area)                 # 2.4 for this frame
data = json.loads(tsr.features()[0]["inputs"]["data"])
assert [e for e in data["entities"] if e["type"] == "spline"][0]["kind"] == "control"

# A bad rho is refused.
try:
    tsr.new_document()
    tsr.run_command("tsr.sketch.create", plane="XY",
                    data=json.dumps({"points": pts, "entities": [dict(conic[1], rho=1.0)]}))
    raise AssertionError("rho 1 accepted")
except RuntimeError:
    pass
print("conic and control point spline: OK")
