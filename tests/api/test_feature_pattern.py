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
cmd("tsr.feature.hole", diameter=0.5, depth=0.5)
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
