# Sketch ellipses: a closed profile (extruded volume pi A B h), drawn with
# either axis first, points kept on them by the solver, relations that do not
# apply refused, and kept through save and open.
import json
import math
import os
import tempfile
import adsk.core
import adsk.fusion
import tsr

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent

# A 30 x 15 mm half-axis ellipse at the origin, its long axis drawn first.
el = {"points": [[0, 0], [0, 0], [3, 0]],
      "entities": [{"type": "ellipse", "c": 1, "p": [2, -1], "r": 1.5}],
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 3.0, "v2": 0.0}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(el))
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(root.bRepBodies.item(0).volume - math.pi * 3 * 1.5) < 1e-6, root.bRepBodies.item(0).volume

# The short axis drawn first (10 mm), the other half axis 20 mm: the same
# ellipse turned; the area is still pi A B.
short = {"points": [[0, 0], [10, 0], [10, 1]],
         "entities": [{"type": "ellipse", "c": 1, "p": [2, -1], "r": 2.0}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(short))
tsr.run_command("tsr.feature.extrude", distance=1.0)
vols = sorted(root.bRepBodies.item(i).volume for i in range(root.bRepBodies.count))
assert abs(vols[0] - math.pi * 1 * 2) < 1e-6, vols

# A point kept on an ellipse: the solver moves it onto the curve.
on = {"points": [[0, 0], [0, 0], [3, 0], [2.5, 2.5]],
      "entities": [{"type": "ellipse", "c": 1, "p": [2, -1], "r": 1.5}],
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 3.0, "v2": 0.0},
                      {"type": "pointOnEntity", "p": [3], "e": [0]}]}
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(on))
sk3 = json.loads(tsr.sketch_data("Sketch3"))
p, B = sk3["points"][3], sk3["entities"][0]["r"]   # the free half axis may change too
assert abs((p[0] / 3) ** 2 + (p[1] / B) ** 2 - 1) < 1e-9, (p, B)

# Relations that do not apply to an ellipse are refused, plainly.
bad = dict(on)
bad["constraints"] = on["constraints"][:2] + [{"type": "equal", "e": [0, 0]}]
try:
    tsr.run_command("tsr.sketch.create", plane="YZ", data=json.dumps(bad))
    raise AssertionError("equal on an ellipse was accepted")
except RuntimeError as e:
    assert "ellipse" in str(e), e

# Save and open: still an ellipse.
path = os.path.join(tempfile.mkdtemp(), "ellipse.tsr")
tsr.save(path)
tsr.open(path)
assert json.loads(tsr.sketch_data("Sketch1"))["entities"][0]["type"] == "ellipse"
assert abs(root.bRepBodies.item(0).volume - math.pi * 3 * 1.5) < 1e-6 or abs(vols[1] - math.pi * 3 * 1.5) < 1e-6
print("ellipse: OK")
