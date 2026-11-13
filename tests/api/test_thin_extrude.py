# Thin Extrude: a wall along the profile's outline (Side 1 inside, Side 2
# outside, Center half each way), mitred corners. Volumes worked out by hand.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command


def vol():
    return sum(root.bRepBodies.item(i).volume for i in range(root.bRepBodies.count))


square = {"points": [[0, 0], [-2, -2], [2, -2], [2, 2], [-2, 2]],
          "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                       {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(square))         # 40 x 40 mm, centred
for loc, t, area in (("Side 1", 0.3, 4.0 ** 2 - 3.4 ** 2), ("Side 2", 0.2, 4.4 ** 2 - 4.0 ** 2),
                     ("Center", 0.2, 4.2 ** 2 - 3.8 ** 2)):   # 1 mm each side of every edge
    cmd("tsr.feature.extrude", distance=1.0, thin=True, wallLocation=loc, wallThickness=t)
    assert root.bRepBodies.count == 1 and abs(vol() - area * 1.0) < 1e-6, (loc, vol(), area)
    tsr.undo()
# A wall thicker than half the profile fills it.
cmd("tsr.feature.extrude", distance=1.0, thin=True, wallLocation="Side 1", wallThickness=3.0)
assert abs(vol() - 16.0) < 1e-6, vol()
tsr.undo()

# A square with a round hole: the hole's wall grows into the material too.
tsr.new_document()
holed = {"points": square["points"] + [[0, 0]],
         "entities": square["entities"] + [{"type": "circle", "c": 5, "r": 0.5}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(holed))
cmd("tsr.feature.extrude", profiles="1.5,1.5", distance=1.0, thin=True, wallLocation="Side 1", wallThickness=0.2)
expected = (16 - math.pi * 0.25) - (3.6 ** 2 - math.pi * 0.49)
assert abs(vol() - expected) < 1e-6, (vol(), expected)

# A circle: a tube.
tsr.new_document()
cmd("tsr.sketch.create", plane="XY", data=json.dumps({"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 1.0}]}))
cmd("tsr.feature.extrude", distance=1.0, thin=True, wallLocation="Side 1", wallThickness=0.2)
assert abs(vol() - math.pi * (1.0 - 0.64)) < 1e-6, vol()
# A tapered circle (the same offset code): a cone frustum, no crash.
tsr.new_document()
cmd("tsr.sketch.create", plane="XY", data=json.dumps({"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 1.0}]}))
cmd("tsr.feature.extrude", distance=1.0, taper=math.radians(10))
r2 = 1.0 + math.tan(math.radians(10))
assert abs(vol() - math.pi * 1.0 / 3 * (1 + r2 + r2 * r2)) < 1e-6, vol()
print("api thin extrude: OK")
