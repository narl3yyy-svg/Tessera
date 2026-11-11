# Revolve, fillet and chamfer through the API, with parametric replay.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent

# Revolve: a 10 x 10 mm square 10 mm from the Z axis, drawn on the front (XZ)
# plane, turned 360 deg about the sketch Y axis (= world Z): a square ring.
ring = {
    "points": [[0, 0], [1, 0], [2, 0], [2, 1], [1, 1]],
    "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                 {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}],
}
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(ring))
tsr.run_command("tsr.feature.revolve")
assert root.bRepBodies.count == 1
v = root.bRepBodies.item(0).volume
assert abs(v - math.pi * (4 - 1) * 1) < 1e-6, v

# Half turn, symmetric: half the volume.
f = tsr.features()
tsr.edit_feature(f[1]["id"], angle=math.pi, direction="Symmetric")
assert abs(root.bRepBodies.item(0).volume - v / 2) < 1e-6

# Revolving across the axis is refused with a clear message.
cross = {"points": [[0, 0], [-1, 0], [1, 0], [1, 1], [-1, 1]],
         "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                      {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(cross))
try:
    tsr.run_command("tsr.feature.revolve")
except RuntimeError as e:
    assert "axis" in str(e), e
else:
    raise AssertionError("profile across the axis accepted")

# Fillet and chamfer on a box; edges picked by points on them.
tsr.new_document()
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.run_command("tsr.feature.fillet", edges="1,0,2", radius=0.5)
tsr.run_command("tsr.feature.chamfer", edges="0,1,0;2,1,0", distance=0.25)
fs = tsr.features()
assert [x["name"] for x in fs] == ["Box1", "Fillet1", "Chamfer1"], fs
assert fs[1]["inputs"]["body"] == "Body1"
vol = root.bRepBodies.item(0).volume
expected = 8 - (0.25 - math.pi * 0.25 / 4) * 2 - 2 * (0.5 * 0.0625 * 2)
assert abs(vol - expected) < 1e-6, (vol, expected)

# Make the box taller: the fillet and chamfers are replayed on the new edges.
tsr.edit_feature(fs[0]["id"], height=3.0)
assert all(x["error"] == "" for x in tsr.features()), tsr.features()
assert abs(root.bRepBodies.item(0).volume - (expected + 4)) < 1e-6

# A fillet that cannot fit reports an error instead of breaking the body.
try:
    tsr.run_command("tsr.feature.fillet", edges="1,2,3", radius=5.0)   # back top edge
except RuntimeError as e:
    assert "too large" in str(e), e
else:
    raise AssertionError("oversized fillet accepted")
print("api fillet/chamfer/revolve: OK")
