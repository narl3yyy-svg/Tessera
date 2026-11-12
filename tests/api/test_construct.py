# Construction planes: offset, angle, midplane; sketch on them; split and
# mirror with them; editing the offset moves everything built on the plane.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command

cmd("tsr.construct.offsetPlane", plane="XY", distance=2.0)          # Plane1 at z = 20 mm
sq = {"points": [[0, 0], [0, 0], [1, 0], [1, 1], [0, 1]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                   {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="Plane1", data=json.dumps(sq))
cmd("tsr.feature.extrude", distance=1.0)
f = tsr.features()
assert [x["name"] for x in f] == ["Plane1", "Sketch1", "Extrude1"], f
b = root.bRepBodies.item(0)
assert abs(b.volume - 1.0) < 1e-9

# Move the plane: the sketch and the extrude follow (bounding check via a split).
tsr.edit_feature(f[0]["id"], distance=5.0)
cmd("tsr.construct.offsetPlane", plane="XY", distance=5.5)           # Plane2 through the box middle
cmd("tsr.feature.splitBody", plane="Plane2")
assert root.bRepBodies.count == 2
assert abs(root.bRepBodies.item(0).volume - 0.5) < 1e-9

# Plane at angle and midplane.
cmd("tsr.construct.planeAtAngle", plane="XZ", axis="Plane Y axis", angle=math.radians(90))
cmd("tsr.construct.midplane", plane="XY", plane2="Plane2")
names = [x["name"] for x in tsr.features()]
assert names[-2:] == ["Plane3", "Plane4"], names
try:
    cmd("tsr.construct.midplane", plane="XY", plane2="XZ")
except RuntimeError as e:
    assert "parallel" in str(e), e
else:
    raise AssertionError("non-parallel midplane accepted")

# Mirror across the midplane (z = 27.5 mm): the copy lands below it.
cmd("tsr.feature.mirror", body="Body1", plane="Plane4")
assert root.bRepBodies.count == 3
print("api construct: OK")
