# Sketch + extrude through the scripting API, including parametric edits:
# change a sketch dimension and the extrude follows.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent

# 40 x 30 mm plate outline with a 10 mm hole, origin at a corner.
pts = [[0, 0], [4.1, 0.1], [4.0, 3.1], [-0.1, 3.0], [2.0, 1.4]]
sketch = {
    "points": pts,
    "entities": [
        {"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
        {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]},
        {"type": "circle", "c": 4, "r": 0.4},
    ],
    "constraints": [
        {"type": "horizontal", "e": [0]}, {"type": "horizontal", "e": [2]},
        {"type": "vertical", "e": [1]}, {"type": "vertical", "e": [3]},
        {"type": "distance", "e": [0], "v": 4.0},
        {"type": "distance", "e": [1], "v": 3.0},
        {"type": "diameter", "e": [4], "v": 1.0},
        {"type": "horizontalDistance", "p": [0, 4], "v": 2.0},
        {"type": "verticalDistance", "p": [0, 4], "v": 1.5},
    ],
}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(sketch))
tsr.run_command("tsr.feature.extrude", distance=0.5, profiles="0.3,0.3")   # the plate region only
f = tsr.features()
assert [x["name"] for x in f] == ["Sketch1", "Extrude1"], f
assert f[1]["inputs"]["sketch"] == "Sketch1", f[1]["inputs"]
assert root.bRepBodies.count == 1
v = root.bRepBodies.item(0).volume
assert abs(v - (12 - math.pi * 0.25) * 0.5) < 1e-6, v

# Make the hole 20 mm by editing the sketch's dimension: the extrude replays.
sketch["constraints"][6]["v"] = 2.0
tsr.edit_feature(f[0]["id"], data=json.dumps(sketch))
v2 = root.bRepBodies.item(0).volume
assert abs(v2 - (12 - math.pi) * 0.5) < 1e-6, v2

# A second sketch on the front plane, extruded symmetric and cut through.
cut = {"points": [[0, 0], [2, 0.25]], "entities": [{"type": "circle", "c": 1, "r": 0.1}]}  # 2 mm drill through the 5 mm plate
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(cut))
tsr.run_command("tsr.feature.extrude", distance=5.0, direction="Symmetric", operation="Cut")
assert tsr.features()[3]["error"] == "", tsr.features()[3]
assert root.bRepBodies.item(0).volume < v2

# Over-constrained data is rejected.
bad = dict(sketch)
bad["constraints"] = sketch["constraints"] + [{"type": "distance", "e": [0], "v": 5.0}]
try:
    tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(bad))
except RuntimeError as e:
    assert "conflict" in str(e), e
else:
    raise AssertionError("conflicting sketch accepted")
print("api sketch/extrude: OK")
