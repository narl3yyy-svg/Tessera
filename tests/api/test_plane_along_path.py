# Plane Along Path, as in the familiar Construct menu: a plane square to a
# path (a sketch's open curve, or body edges) at a proportion of its length or
# a distance along it.
import json
import math
import tsr

cmd = tsr.run_command


def plane(name):
    for n, o, d in tsr.construction()["planes"]:
        if n == name:
            return o, d
    raise AssertionError(name)


def near(a, b, tol=1e-6):
    assert all(abs(x - y) < tol for x, y in zip(a, b)), (a, b)


# A straight 4 cm line along X: halfway, the plane stands at x = 2, facing X
# (its origin's x tells where it is).
line = {"points": [[0, 0], [0, 0], [4, 0]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(line))
cmd("tsr.construct.planeAlongPath")
p = tsr.features()[-1]
assert p["error"] == "" and p["name"] == "Plane1", p
o, d = plane("Plane1")
near([o[0]], [2])
near([abs(v) for v in d], (1, 0, 0))
tsr.edit_feature(p["id"], proportion=0.25)
near([plane("Plane1")[0][0]], [1])
tsr.edit_feature(p["id"], distanceType="Physical", length=3.0)
near([plane("Plane1")[0][0]], [3])

# A quarter circle (radius 2 about the origin): halfway round, the plane is at
# 45 degrees, square to the arc there.
tsr.new_document()
arc = {"points": [[0, 0], [0, 0], [2, 0], [0, 2]], "entities": [{"type": "arc", "c": 1, "p": [2, 3]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(arc))
cmd("tsr.construct.planeAlongPath", proportion=0.5)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
o, d = plane("Plane1")
h = math.sqrt(2)
# (h, h, 0) on the arc lies on the plane (the plane keeps any point as its origin).
assert abs(sum((a - b) * c for a, b, c in zip(o, (h, h, 0), d))) < 1e-6, (o, d)
assert abs(abs(d[0]) - h / 2) < 1e-6 and abs(abs(d[1]) - h / 2) < 1e-6 and abs(d[2]) < 1e-9, d
assert d[0] * d[1] < 0                                    # along the arc, not out from its centre

# Body edges as the path: the top front edge of a box, 1 cm in.
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=2.0, height=1.0)
cmd("tsr.construct.planeAlongPath", body="Body1", edges="2,0,1", distanceType="Physical", length=1.0)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
o, d = plane("Plane1")
assert min(abs(o[0] - 1), abs(o[0] - 3)) < 1e-9, o
near([abs(v) for v in d], (1, 0, 0))
# Past the end: explained.
try:
    cmd("tsr.construct.planeAlongPath", body="Body1", edges="2,0,1", distanceType="Physical", length=9.0)
except RuntimeError as e:
    assert "past the end" in str(e), e
else:
    raise AssertionError("placed a plane past the path's end")
print("plane along path: OK")
