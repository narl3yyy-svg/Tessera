# Sweep, Loft and Press Pull.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command
def vol(i=0):
    return root.bRepBodies.item(i).volume

# Sweep a 10 mm circle (on the XY plane at the origin) along a straight
# 50 mm path up Z, then along an L-shaped path.
cmd("tsr.sketch.create", plane="XY", data=json.dumps({"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 0.5}]}))
cmd("tsr.sketch.create", plane="XZ", data=json.dumps({"points": [[0, 0], [0, 5]], "entities": [{"type": "line", "p": [0, 1]}]}))
cmd("tsr.feature.sweep")
f = tsr.features()
assert f[-1]["inputs"]["sketch"] == "Sketch1" and f[-1]["inputs"]["path"] == "Sketch2", f[-1]
assert abs(vol() - math.pi * 0.25 * 5) < 1e-4, vol()
tsr.undo()
lpath = {"points": [[0, 0], [0, 4], [3, 4]], "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [0, 1]}]}
tsr.edit_feature(f[1]["id"], data=json.dumps(lpath))
cmd("tsr.feature.sweep")
assert vol() > math.pi * 0.25 * 6, vol()

# Loft from a 20 mm square at z=0 to a 10 mm circle at z=30 mm.
tsr.new_document()
sq = {"points": [[0, 0], [-1, -1], [1, -1], [1, 1], [-1, 1]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                   {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(sq))
cmd("tsr.sketch.create", plane="XY", offset=3.0, data=json.dumps({"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 0.5}]}))
cmd("tsr.feature.loft")
v = vol()
assert math.pi * 0.25 * 3 < v < 4 * 3, v
assert tsr.features()[-1]["inputs"]["sections"] == "Sketch1;Sketch2"
tsr.undo()
cmd("tsr.feature.loft", sections="Sketch1;Sketch2", transition="Ruled")
assert vol() > 0
try:
    cmd("tsr.feature.loft", sections="Sketch1")
except RuntimeError as e:
    assert "two" in str(e), e
else:
    raise AssertionError("one-section loft accepted")

# Press Pull the top face of a 20 mm cube up 5 mm, then push a side in 2 mm.
tsr.new_document()
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.feature.pressPull", faces="1,1,2", distance=0.5)
assert abs(vol() - 10.0) < 1e-6, vol()
cmd("tsr.feature.pressPull", faces="2,1,1", distance=-0.2)
assert abs(vol() - (10.0 - 0.2 * 2 * 2.5)) < 1e-6, vol()
# Replays after the box is resized.
tsr.edit_feature(tsr.features()[0]["id"], length=3.0)
assert all(x["error"] == "" for x in tsr.features()), tsr.features()
print("api sweep/loft/press pull: OK")
