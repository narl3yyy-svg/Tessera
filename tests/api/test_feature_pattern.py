# Rectangular / Circular Pattern of features (Pattern Type = Features): the
# geometry a feature added (a joined stud) or removed (a hole) is copied onto
# the body, and the pattern follows when the original feature is edited.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command


def vol(i=0):
    return root.bRepBodies.item(i).volume


def feature(name):
    return [f for f in tsr.features() if f["name"] == name][0]


stud = math.pi * 0.25 ** 2 * 0.5   # r 2.5 mm, 5 mm tall

# A 40 x 20 x 10 mm block with one stud on top, joined.
cmd("tsr.primitive.box", length=4.0, width=2.0, height=1.0)
bb = tsr.bounding_box("Body1")
x0, y0 = bb[0][0], bb[0][1]
sk = {"points": [[0, 0], [x0 + 0.5, y0 + 0.5]], "entities": [{"type": "circle", "c": 1, "r": 0.25}]}   # point 0: origin
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(sk))
cmd("tsr.feature.extrude", distance=0.5, operation="Join")
assert root.bRepBodies.count == 1 and abs(vol() - (8 + stud)) < 1e-6, vol()

# Pattern the Extrude feature: 3 along X over an extent of 20 mm (10 mm apart).
cmd("tsr.feature.rectangularPattern", patternType="Features", features="Extrude1",
    direction1="X", distanceType="Extent", quantity1=3, distance1=2.0)
assert root.bRepBodies.count == 1 and abs(vol() - (8 + 3 * stud)) < 1e-6, vol()

# Two directions: 3 x 2 studs, spacing 10 mm each way.
tsr.undo()
cmd("tsr.feature.rectangularPattern", patternType="Features", features="Extrude1", distanceType="Spacing",
    quantity1=3, distance1=1.0, quantity2=2, distance2=1.0)
assert abs(vol() - (8 + 6 * stud)) < 1e-6, vol()

# Editing the original stud's height: the pattern follows.
tsr.edit_feature(feature("Extrude1")["id"], distance=0.3)
assert abs(vol() - (8 + 6 * math.pi * 0.25 ** 2 * 0.3)) < 1e-6, vol()
assert all(f["error"] == "" for f in tsr.features()), tsr.features()
tsr.edit_feature(feature("Extrude1")["id"], distance=0.5)

# A feature that removes material (a hole), patterned the same way.
pts = {"points": [[0, 0], [x0 + 3.5, y0 + 0.5]]}   # point 0 is the sketch origin
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(pts))
cmd("tsr.feature.hole", diameter=0.5, depth=0.5, drillPoint="Flat")
hole = math.pi * 0.25 ** 2 * 0.5
before = vol()
cmd("tsr.feature.rectangularPattern", patternType="Features", features="Hole1", direction1="Y",
    distanceType="Spacing", quantity1=2, distance1=1.0)
assert abs(vol() - (before - hole)) < 1e-6, (vol(), before)

# Survives a save and reopen (the history is replayed to find what each feature did).
import os, tempfile
path = os.path.join(tempfile.mkdtemp(), "pattern.tsr")
tsr.save(path)
expected = vol()
tsr.open(path)
p = feature("RectangularPattern2")
tsr.edit_feature(p["id"], quantity1=1)
assert abs(vol() - (expected + hole)) < 1e-6, vol()

# Circular pattern of a feature: 4 studs around the world Z axis.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=4.0, height=1.0)
sk = {"points": [[0, 0], [1.5, 0]], "entities": [{"type": "circle", "c": 1, "r": 0.25}]}
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(sk))
cmd("tsr.feature.extrude", distance=0.5, operation="Join")
base = math.pi * 2.0 ** 2 * 1.0
cmd("tsr.feature.circularPattern", patternType="Features", features="Extrude1", axis="Z", quantity=4)
assert abs(vol() - (base + 4 * stud)) < 1e-4, vol()

# Errors are reported, not crashes.
for bad in ({"features": ""}, {"features": "Nope1"}):
    try:
        cmd("tsr.feature.rectangularPattern", patternType="Features", **bad)
    except RuntimeError as e:
        assert "Features" in str(e), e
    else:
        raise AssertionError("bad features accepted: %r" % bad)
print("api feature pattern: OK")

# Pattern on Path: holes along a straight path and along a half circle.
tsr.new_document()
cmd("tsr.primitive.box", length=10.0, width=4.0, height=1.0)          # 100 x 40 x 10 mm from the origin
hole = math.pi * 0.25 ** 2 * 1.0
pts = {"points": [[0, 0], [1, 2]]}                                     # one hole centre at (10, 20) mm
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(pts))
cmd("tsr.feature.hole", diameter=0.5, extent="All")
path = {"points": [[0, 0], [1, 2], [9, 2]], "entities": [{"type": "line", "p": [1, 2]}]}   # 80 mm line from the hole
cmd("tsr.sketch.create", plane="XY", data=json.dumps(path))
cmd("tsr.feature.pathPattern", patternType="Features", features="Hole1", path="Sketch2", quantity=5,
    distanceType="Extent", distance=8.0)                               # holes every 20 mm
assert abs(vol() - (40 - 5 * hole)) < 1e-6, vol()
tsr.undo()
# Along a half circle of radius 30 mm centred at (50, 0): from (20, 0) over the top to (80, 0).
tsr.new_document()
cmd("tsr.primitive.box", length=10.0, width=4.0, height=1.0, y=-1.0)   # y from -10 to 30 mm
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps({"points": [[0, 0], [2, 0]]}))
cmd("tsr.feature.hole", diameter=0.5, extent="All")
arc = {"points": [[0, 0], [5, 0], [8, 0], [2, 0]], "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 3.0}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(arc))
cmd("tsr.feature.pathPattern", patternType="Features", features="Hole1", path="Sketch2", quantity=3,
    distanceType="Extent", distance=math.pi * 3.0)                     # start, top (50, 30) and end (80, 0)
# The box reaches y = 30 mm, so the hole at the top of the arc is half inside it.
assert abs(vol() - (40 - 2 * hole - hole / 2)) < 1e-6, vol()
try:
    cmd("tsr.feature.pathPattern", patternType="Features", features="Hole1", path="Sketch2", quantity=3,
        distance=6.0)                                                  # 2 x 60 mm = 120 mm > the 94 mm path
except RuntimeError as e:
    assert "past the end" in str(e), e
else:
    raise AssertionError("pattern past the end of the path accepted")
print("api path pattern: OK")

# Mirror of a feature: a stud at x = 10 mm mirrored across YZ onto the same block.
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=2.0, height=1.0, x=-2.0)   # x from -20 to 20 mm
sk = {"points": [[0, 0], [1.0, 1.0]], "entities": [{"type": "circle", "c": 1, "r": 0.25}]}
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(sk))
cmd("tsr.feature.extrude", distance=0.5, operation="Join")
cmd("tsr.feature.mirror", patternType="Features", features="Extrude1", plane="YZ")
assert root.bRepBodies.count == 1 and abs(vol() - (8 + 2 * stud)) < 1e-6, vol()
bb = tsr.bounding_box("Body1")
assert abs(bb[1][2] - 1.5) < 1e-9, bb
print("api mirror features: OK")

