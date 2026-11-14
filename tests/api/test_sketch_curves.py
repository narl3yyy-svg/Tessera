# Sketch curves: Trim / Break / Offset of ellipses and splines, spline
# tangent handles, and Include 3D Geometry.
import json
import math
import os
import tempfile
import adsk.core
import adsk.fusion
import tsr

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent


def volumes():
    return sorted(root.bRepBodies.item(i).volume for i in range(root.bRepBodies.count))


# --- Trim an ellipse: a 30 x 15 mm half-axis ellipse cut by a vertical line
# through its centre; clicking the right half leaves the left elliptical arc,
# which with the line bounds half the ellipse.
ell = {"points": [[0, 0], [0, 0], [3, 0], [0, -3], [0, 3]],
       "entities": [{"type": "ellipse", "c": 1, "p": [2, -1], "r": 1.5}, {"type": "line", "p": [3, 4]}],
       "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 3.0, "v2": 0.0}]}
cross = tsr.sketch_crossings(json.dumps(ell), 0)
assert sorted(round(y, 6) for _, y in cross) == [-1.5, 1.5] and all(abs(x) < 1e-6 for x, _ in cross), cross
trimmed = json.loads(tsr.sketch_trim(json.dumps(ell), 0, 3.0, 0.0))
arcs = [e for e in trimmed["entities"] if e["type"] == "ellipse"]
assert len(arcs) == 1 and "ends" in arcs[0], trimmed["entities"]
s, e = (trimmed["points"][i] for i in arcs[0]["ends"])
assert abs(s[0]) < 1e-6 and abs(s[1] - 1.5) < 1e-6 and abs(e[0]) < 1e-6 and abs(e[1] + 1.5) < 1e-6, (s, e)
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(trimmed))
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(volumes()[0] - math.pi * 3 * 1.5 / 2) < 1e-6, volumes()

# Break needs a crossing inside the curve: the arc's ends do not count.
try:
    tsr.sketch_trim(json.dumps(trimmed), [i for i, x in enumerate(trimmed["entities"]) if x["type"] == "ellipse"][0],
                    -3.0, 0.0, True)
    raise AssertionError("break with nothing crossing was accepted")
except RuntimeError as err:
    assert "Break" in str(err), err

# Break the full ellipse: two elliptical arcs that together are the ellipse.
broken = json.loads(tsr.sketch_trim(json.dumps(ell), 0, 3.0, 0.0, True))
assert sum(1 for x in broken["entities"] if x["type"] == "ellipse" and "ends" in x) == 2, broken["entities"]

# --- Trim a fit point spline crossed by a line at x = 10 mm: clicking the
# right part keeps the left one, which still runs through its own points and
# now ends on the line.
spl = {"points": [[0, 0], [-4, 0], [-2, 1], [0, 0], [2, -1], [4, 0], [1, -3], [1, 3]],
       "entities": [{"type": "spline", "fit": [1, 2, 3, 4, 5]}, {"type": "line", "p": [6, 7]}],
       "constraints": [{"type": "fix", "p": [p], "v": x, "v2": y}
                       for p, (x, y) in enumerate([[0, 0], [-4, 0], [-2, 1], [0, 0], [2, -1], [4, 0]]) if p > 0]}
crossings = tsr.sketch_crossings(json.dumps(spl), 0)
assert len(crossings) == 1 and abs(crossings[0][0] - 1) < 1e-6, crossings
left = json.loads(tsr.sketch_trim(json.dumps(spl), 0, 3.0, -0.7))
sp = [x for x in left["entities"] if x["type"] == "spline"]
assert len(sp) == 1, left["entities"]
fit = [left["points"][i] for i in sp[0]["fit"]]
assert fit[0] == [-4, 0] and [-2, 1] in fit and [0, 0] in fit and [4, 0] not in fit, fit
assert abs(fit[-1][0] - 1) < 1e-6 and abs(fit[-1][1] - crossings[0][1]) < 1e-6, fit
assert "handles" in sp[0], sp[0]   # the cut end keeps the original's direction

# Break it there instead: two splines sharing the cut point.
two = json.loads(tsr.sketch_trim(json.dumps(spl), 0, -1.0, 0.3, True))
pieces = [x for x in two["entities"] if x["type"] == "spline"]
assert len(pieces) == 2 and set(pieces[0]["fit"]) & set(pieces[1]["fit"]), pieces

# --- Offset: the ellipse 5 mm outward becomes a closed spline enclosing the
# ellipse's area plus perimeter x d plus pi d^2 (a convex curve's offset).
A, B, d = 3.0, 1.5, 0.5
out = json.loads(tsr.sketch_offset(json.dumps({"points": ell["points"][:3], "entities": ell["entities"][:1],
                                               "constraints": ell["constraints"]}), 0, d))
assert out["entities"][1]["type"] == "spline" and out["entities"][1]["fit"][0] == out["entities"][1]["fit"][-1]
perimeter = math.pi * (3 * (A + B) - math.sqrt((3 * A + B) * (A + 3 * B)))
only = dict(out)
only["entities"] = out["entities"][1:]
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(only))
tsr.run_command("tsr.feature.extrude", distance=1.0)
expect = math.pi * A * B + perimeter * d + math.pi * d * d
assert any(abs(v - expect) < 0.01 * expect for v in volumes()), (volumes(), expect)
try:
    tsr.sketch_offset(json.dumps({"points": ell["points"][:3], "entities": ell["entities"][:1]}), 0, -1.0)
    raise AssertionError("an inward offset past the tightest curve was accepted")
except RuntimeError as err:
    assert "tightest" in str(err), err

# An open spline offsets to its right: the copy starts 5 mm from its start.
side = json.loads(tsr.sketch_offset(json.dumps(spl), 0, 0.5))
new = side["entities"][-1]
p0 = side["points"][new["fit"][0]]
assert new["type"] == "spline" and abs(math.hypot(p0[0] + 4, p0[1]) - 0.5) < 1e-6, (new, p0)

# --- Tangent handles: a two-point spline is straight; handles leaving at
# 45 degrees up and arriving at 45 degrees down make a cubic bump whose area
# over its 40 mm chord is 8/3 cm^2 (Hermite: y = 4 u (1 - u) for x = 4 u).
bump = {"points": [[0, 0], [0, 0], [4, 0]],
        "entities": [{"type": "spline", "fit": [1, 2]}, {"type": "line", "p": [1, 2]}]}
data = tsr.sketch_spline_handle(json.dumps(bump), 0, 0, 1.0, 1.0)
data = tsr.sketch_spline_handle(data, 0, 1, 1.0, -1.0)
hs = tsr.sketch_spline_handles(data, 0)
assert [h[5] for h in hs] == [True, True] and hs[0][3:5] == (1.0, 1.0), hs
assert json.loads(data)["entities"][0]["handles"] == [[1.0, 1.0], [1.0, -1.0]]
tsr.run_command("tsr.sketch.create", plane="YZ", data=data)
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert any(abs(v - 8 / 3) < 1e-6 for v in volumes()), volumes()
# Freeing both handles makes it straight again.
free = tsr.sketch_spline_handle(tsr.sketch_spline_handle(data, 0, 0, 0, 0), 0, 1, 0, 0)
assert "handles" not in json.loads(free)["entities"][0]
assert all(abs(h[4]) < 1e-9 and not h[5] for h in tsr.sketch_spline_handles(free, 0))
try:
    tsr.sketch_spline_handle(json.dumps(ell), 0, 0, 1, 0)
    raise AssertionError("a handle on an ellipse was accepted")
except RuntimeError as err:
    assert "fit point" in str(err), err

# --- Include 3D Geometry: a 20 mm box's twelve edges in a sketch on XY, as
# they are in space (the top ones 20 mm up), fixed and not profiles.
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
box = [b.name for b in (root.bRepBodies.item(i) for i in range(root.bRepBodies.count))][-1]
inc = json.loads(tsr.sketch_include("{}", "XY", box))
lines = [x for x in inc["entities"] if x["type"] == "line"]
assert len(lines) == 12 and all(x.get("included") and x.get("projected") for x in lines), inc["entities"]
zs = sorted({round(inc["points"][i][2] if len(inc["points"][i]) > 2 else 0.0, 6) for x in lines for i in x["p"]})
assert zs[0] == 0.0 and zs[-1] == 2.0, zs
# A circle drawn with it still makes the one profile; the 3D edges make none.
inc["points"].append([10, 10])
inc["entities"].append({"type": "circle", "c": len(inc["points"]) - 1, "r": 1.0})
n = root.bRepBodies.count
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(inc))
name = [f["name"] for f in tsr.features() if f["command"] == "tsr.sketch.create"][-1]
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert root.bRepBodies.count == n + 1 and any(abs(v - math.pi) < 1e-6 for v in volumes()), volumes()
kept = json.loads(tsr.sketch_data(name))
assert sum(1 for x in kept["entities"] if x.get("included")) == 12

# Save and open: elliptical arcs, handles and included heights come back.
path = os.path.join(tempfile.mkdtemp(), "curves.tsr")
tsr.save(path)
tsr.open(path)
again = json.loads(tsr.sketch_data(name))
assert max(len(p) for p in again["points"]) == 3 and sum(1 for x in again["entities"] if x.get("included")) == 12
assert any("ends" in x for x in json.loads(tsr.sketch_data("Sketch1"))["entities"])
print("sketch curves: OK")

# --- Extend: an arc's end runs on round its circle to the first curve; a line
# reaches an ellipse.
arc = {"points": [[0, 0], [0, 0], [1, 0], [0, 1], [-0.5, -2], [-0.5, 2]],
       "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 1.0}, {"type": "line", "p": [4, 5]}],
       "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}]}
ext = json.loads(tsr.sketch_extend(json.dumps(arc), 0, 0.0, 1.05))
end = ext["points"][ext["entities"][0]["p"][1]]
assert abs(end[0] + 0.5) < 1e-6 and abs(end[1] - math.sqrt(0.75)) < 1e-6, end
assert any(c["type"] == "pointOnEntity" for c in ext["constraints"]), ext["constraints"]
toell = {"points": [[0, 0], [0, 0], [1, 0], [5, 0], [7, 0]],
         "entities": [{"type": "line", "p": [1, 2]}, {"type": "ellipse", "c": 3, "p": [4, -1], "r": 1.0}],
         "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [3], "v": 5.0, "v2": 0.0},
                         {"type": "fix", "p": [4], "v": 7.0, "v2": 0.0}]}
ext = json.loads(tsr.sketch_extend(json.dumps(toell), 0, 0.9, 0.0))
assert abs(ext["points"][2][0] - 3.0) < 1e-6, ext["points"]
print("sketch extend: OK")

# --- Fillet where an arc meets a line: a 5 mm round, tangent to both.
al = {"points": [[0, 0], [0, 0], [2, 0], [0, 2], [0, 5]],
      "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 2.0}, {"type": "line", "p": [3, 4]}],
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 2.0, "v2": 0.0},
                      {"type": "fix", "p": [4], "v": 0.0, "v2": 5.0}, {"type": "vertical", "e": [1]}]}
fil = json.loads(tsr.sketch_fillet(json.dumps(al), 0, 1, 0.5))
arcs = [e for e in fil["entities"] if e["type"] == "arc" and abs(e["r"] - 0.5) < 1e-9]
assert len(arcs) == 1, fil["entities"]
c = fil["points"][arcs[0]["c"]]
assert abs(c[0] - 0.5) < 1e-6 and abs(c[1] - math.sqrt(6.0)) < 1e-6, c
assert sum(1 for k in fil["constraints"] if k["type"] == "tangent") == 2
# Two arcs meeting at a point: a round between them.
aa = {"points": [[0, 0], [0, 0], [2, 0], [0, 2], [0, 4], [-2, 4]],
      "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 2.0}, {"type": "arc", "c": 4, "p": [3, 5], "r": 2.0}],
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [4], "v": 0.0, "v2": 4.0}]}
fil = json.loads(tsr.sketch_fillet(json.dumps(aa), 0, 1, 0.3))
assert any(e["type"] == "arc" and abs(e["r"] - 0.3) < 1e-9 for e in fil["entities"]), fil["entities"]
print("sketch fillet arcs: OK")
