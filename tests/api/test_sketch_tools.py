# Sketch Spline, Fillet and Offset through the scripting API, extruded.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent

def rect(w, h):
    return {
        "points": [[0, 0], [w, 0], [w, h], [0, h]],
        "entities": [{"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
                     {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]}],
        "constraints": [{"type": "horizontal", "e": [0]}, {"type": "vertical", "e": [1]},
                        {"type": "horizontal", "e": [2]}, {"type": "vertical", "e": [3]}],
    }

# Fillet one corner of a 40 x 30 mm rectangle with R5.
data = tsr.sketch_fillet(json.dumps(rect(4, 3)), 0, 1, 0.5)
assert any(e["type"] == "arc" for e in json.loads(data)["entities"])
tsr.run_command("tsr.sketch.create", plane="XY", data=data)
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(root.bRepBodies.item(0).volume - (12 - (1 - math.pi / 4) * 0.25)) < 1e-5, root.bRepBodies.item(0).volume

# Offset a rectangle outward by 10 mm: extruding both regions gives 60 x 50.
data = tsr.sketch_offset(json.dumps(rect(4, 3)), 2, 1.0)
assert len(json.loads(data)["entities"]) == 8
tsr.run_command("tsr.sketch.create", plane="XY", offset=2.0, data=data)
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(root.bRepBodies.item(1).volume - 30) < 1e-6, root.bRepBodies.item(1).volume

# A closed spline through four points, extruded; moving a point reshapes it.
spline = {"points": [[0, 0], [10, 0], [12, 3], [11, 6], [9, 3]],
          "entities": [{"type": "spline", "fit": [1, 2, 3, 4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(spline))
tsr.run_command("tsr.feature.extrude", distance=1.0)
f = tsr.features()
assert f[-1]["error"] == "", f[-1]
v = root.bRepBodies.item(2).volume
assert v > 1.0, v
spline["points"][3] = [11, 9]
tsr.edit_feature(f[-2]["id"], data=json.dumps(spline))
assert root.bRepBodies.item(2).volume > v
try:
    tsr.sketch_fillet(json.dumps(rect(4, 3)), 0, 1, 10)
except RuntimeError as e:
    assert "too large" in str(e), e
else:
    raise AssertionError("oversized fillet accepted")
print("api sketch tools: OK")
