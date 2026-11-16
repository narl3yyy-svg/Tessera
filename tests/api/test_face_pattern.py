# Pattern Type: Faces, as in the familiar patterns and Mirror: the boss,
# pocket or hole that picked faces make is copied, joined where it stood out
# of the body and cut where it was cut into it.
import json
import math
import tsr

cmd = tsr.run_command


def vol(body="Body1"):
    return tsr.mass_properties(body)["volume"]


def near(a, b, tol=1e-6):
    assert abs(a - b) < tol, (a, b)


def square(x0, y0, x1, y1):   # point 0 is the sketch origin
    return {"points": [[0, 0], [x0, y0], [x1, y0], [x1, y1], [x0, y1]],
            "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                         {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}


def circle(x, y, r):
    return {"points": [[0, 0], [x, y]], "entities": [{"type": "circle", "c": 1, "r": r}]}


# A 10 x 4 x 1 cm plate with a 1 cm cube boss on its top at (1..2, 1..2).
cmd("tsr.primitive.box", length=10.0, width=4.0, height=1.0)
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(square(1, 1, 2, 2)))
cmd("tsr.feature.extrude", distance=1.0, operation="Join", target="Body1")
near(vol(), 41)
boss = "1.5,1.5,2;1,1.5,1.5;2,1.5,1.5;1.5,1,1.5;1.5,2,1.5"     # top and four sides

# Only the top face: it closes up on nothing.
try:
    cmd("tsr.feature.rectangularPattern", patternType="Faces", body="Body1", faces="1.5,1.5,2")
except RuntimeError as e:
    assert "Faces" in str(e), e
else:
    raise AssertionError("patterned a lone face")

# Three bosses along X, 3 cm apart.
cmd("tsr.feature.rectangularPattern", patternType="Faces", body="Body1", faces=boss, distanceType="Spacing",
    direction1="X", quantity1=3, distance1=3.0, quantity2=1)
p = tsr.features()[-1]
assert p["error"] == "", p
near(vol(), 43)
try:
    tsr.bounding_box("Body2")
except Exception:
    pass
else:
    raise AssertionError("the copies made a new body")
lo, hi = tsr.bounding_box("Body1")
near(hi[2], 2)

# The boss made taller: the copies follow.
ext = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"][0]
tsr.edit_feature(ext["id"], distance=2.0)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(vol(), 46)

# A round pocket (1 cm across, 5 mm deep) mirrored across the plate's middle.
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(circle(1.5, 3, 0.5)))
cmd("tsr.feature.extrude", distance=-0.5, operation="Cut", target="Body1")
pocket = math.pi * 0.25 * 0.5
near(vol(), 46 - pocket, 1e-5)
cmd("tsr.feature.mirror", patternType="Faces", body="Body1", faces="2,3,0.75;1.5,3,0.5", plane="YZ", offset=5.0)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(vol(), 46 - 2 * pocket, 1e-5)

# --- A through hole round a disc: Circular Pattern of its one face.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=10.0, height=1.0)
cmd("tsr.sketch.create", plane="XY", data=json.dumps(circle(3, 0, 0.5)))
cmd("tsr.feature.extrude", extent="All", direction="Symmetric", operation="Cut", target="Body1")
hole = math.pi * 0.25 * 1.0
near(vol(), 25 * math.pi - hole, 1e-5)
cmd("tsr.feature.circularPattern", patternType="Faces", body="Body1", faces="3.5,0,0.5", axis="Z", quantity=4)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(vol(), 25 * math.pi - 4 * hole, 1e-5)
lo, hi = tsr.bounding_box("Body1")
near(hi[2], 1)

# The disc's top face with the hole's wall makes no feature: explained.
try:
    cmd("tsr.feature.circularPattern", patternType="Faces", body="Body1", faces="0,0,1;3.5,0,0.5", axis="Z", quantity=3)
except RuntimeError as e:
    assert "Faces" in str(e), e
else:
    raise AssertionError("patterned a disc's top face with a hole wall")
print("face pattern: OK")
