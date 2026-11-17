# Extrude, as in the familiar panel: Participant Bodies (the bodies a Join,
# Cut or Intersect acts on), and To Object up to a curved face whose surface
# is extended past its edges.
import json
import math
import tsr

cmd = tsr.run_command


def vol(body):
    return tsr.mass_properties(body)["volume"]


def near(a, b, tol=1e-6):
    assert abs(a - b) < tol, (a, b)


def exists(body):
    try:
        tsr.bounding_box(body)
        return True
    except Exception:
        return False


def rect(x0, y0, x1, y1):   # point 0 is the sketch origin
    return {"points": [[0, 0], [x0, y0], [x1, y0], [x1, y1], [x0, y1]],
            "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                         {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}


def circle(x, y, r):
    return {"points": [[0, 0], [x, y]], "entities": [{"type": "circle", "c": 1, "r": r}]}


# Two 2 cm cubes side by side; a slot 1 cm deep cut across both.
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0, x=3.0)
cmd("tsr.sketch.create", plane="XY", offset=2.0, data=json.dumps(rect(0.5, 0.5, 4.5, 1.5)))
cmd("tsr.feature.extrude", distance=-1.0, operation="Cut", participants="Body1;Body2")
cut = tsr.features()[-1]
assert cut["error"] == "", cut
near(vol("Body1"), 6.5)
near(vol("Body2"), 6.5)
# Only the second cube takes part.
tsr.edit_feature(cut["id"], participants="Body2")
near(vol("Body1"), 8)
near(vol("Body2"), 6.5)
# None listed: the target body alone (the most recent), as before.
tsr.edit_feature(cut["id"], participants="")
near(vol("Body1"), 8)
near(vol("Body2"), 6.5)
tsr.delete_feature(cut["id"])

# Join: a bridge over the gap joins both cubes into one body.
cmd("tsr.sketch.create", plane="XY", offset=2.0, data=json.dumps(rect(1, 0, 4, 2)))
cmd("tsr.feature.extrude", distance=1.0, operation="Join", participants="Body1;Body2")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(vol("Body1"), 8 + 8 + 6)
assert not exists("Body2")

# Intersect: each cube keeps only what lies inside the tool.
tsr.new_document()
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0, x=3.0)
cmd("tsr.sketch.create", plane="XY", data=json.dumps(rect(1, 0, 4, 2)))
cmd("tsr.feature.extrude", distance=1.0, operation="Intersect", participants="Body1;Body2")
near(vol("Body1"), 2)
near(vol("Body2"), 2)

# --- Up to a curved face: a cylinder lying along X (radius 2 cm, axis 5 cm up,
# from x 0 to 10). A 1 cm disc on XY under it runs up to its underside.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=4.0, height=10.0, axis="X", z=5.0)
underside = "5,0,3"


def up_to_underside(r):
    # Volume under the surface z = 5 - sqrt(4 - y^2) over a disc of radius r.
    n = 400
    total = 0.0
    for i in range(n):
        y = -r + (i + 0.5) * 2 * r / n
        total += (5 - math.sqrt(4 - y * y)) * 2 * math.sqrt(r * r - y * y) * (2 * r / n)
    return total


cmd("tsr.sketch.create", plane="XY", data=json.dumps(circle(5, 0, 0.5)))
cmd("tsr.feature.extrude", extent="To Object", toObject="face:Body1|" + underside, operation="New Body")
e = tsr.features()[-1]
assert e["error"] == "" and e["inputs"]["toObject"].startswith("face:Body1|"), e
near(vol("Body2"), up_to_underside(0.5), 1e-3)

# Past the cylinder's end (x 12): the surface is extended, so it still stops there.
cmd("tsr.sketch.create", plane="XY", data=json.dumps(circle(12, 0, 0.5)))
cmd("tsr.feature.extrude", extent="To Object", toObject="face:Body1|" + underside, operation="New Body")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(vol("Body3"), up_to_underside(0.5), 1e-3)

# Beside it (y 5): the surface is never in the way.
cmd("tsr.sketch.create", plane="XY", data=json.dumps(circle(5, 5, 0.5)))
try:
    cmd("tsr.feature.extrude", extent="To Object", toObject="face:Body1|" + underside, operation="New Body")
except RuntimeError as err:
    assert "not in the way" in str(err), err
else:
    raise AssertionError("extruded to a surface that is not in the way")
print("extrude participants and to face: OK")
