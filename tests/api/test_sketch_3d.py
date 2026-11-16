# 3D sketch curves, as in the familiar 3D Sketch: a line may leave the plane
# (its point stands at a height); it is kept with the sketch but bounds no
# profile, so the flat region it crosses stays whole.
import json
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
# A 40 x 20 mm rectangle, and a line from its corner (0,0) rising across it to
# (40, 20) mm, 10 mm above the plane.
data = {"points": [[0, 0], [4, 0], [4, 2], [0, 2], [4, 2, 1.0]],
        "entities": [{"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
                     {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]},
                     {"type": "line", "p": [0, 4]}],
        "constraints": [{"type": "fix", "p": [4], "v": 4.0, "v2": 2.0}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(data))
saved = json.loads(tsr.sketch_data("Sketch1"))
assert saved["points"][4] == [4, 2, 1.0], saved["points"]          # the height is kept
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert root.bRepBodies.count == 1, root.bRepBodies.count          # not split by the 3D line
assert abs(root.bRepBodies.item(0).volume - 8.0) < 1e-9, root.bRepBodies.item(0).volume
print("3D sketch curves: OK")
