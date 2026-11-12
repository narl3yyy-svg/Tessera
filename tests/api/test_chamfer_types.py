# Chamfer types: Equal Distance, Two Distances, Distance and Angle (and Flip).
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command


def vol():
    return root.bRepBodies.item(0).volume


cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)   # 20 mm cube from the origin
edge = "0,1,0"                                                 # a bottom edge, 20 mm long

cmd("tsr.feature.chamfer", edges=edge, distance=0.2)
assert abs(vol() - (8 - 0.5 * 0.2 * 0.2 * 2)) < 1e-6, vol()
assert tsr.features()[-1]["inputs"]["chamferType"] == "Equal Distance"
tsr.undo()

cmd("tsr.feature.chamfer", edges=edge, chamferType="Two Distances", distance=0.2, distance2=0.4)
assert abs(vol() - (8 - 0.5 * 0.2 * 0.4 * 2)) < 1e-6, vol()
bb1 = tsr.bounding_box("Body1")
tsr.undo()
cmd("tsr.feature.chamfer", edges=edge, chamferType="Two Distances", distance=0.2, distance2=0.4, flip=True)
assert abs(vol() - (8 - 0.5 * 0.2 * 0.4 * 2)) < 1e-6, vol()
tsr.undo()

# 2 mm along the first face and 60 degrees to it: the other leg is 2 * tan(60) mm.
cmd("tsr.feature.chamfer", edges=edge, chamferType="Distance and Angle", distance=0.2, angle=math.radians(60))
leg = 0.2 * math.tan(math.radians(60))
assert abs(vol() - (8 - 0.5 * 0.2 * leg * 2)) < 1e-6, (vol(), 8 - 0.5 * 0.2 * leg * 2)
tsr.undo()

for bad in ({"chamferType": "Distance and Angle", "angle": math.radians(95)},
            {"chamferType": "Two Distances", "distance2": 5.0}):
    try:
        cmd("tsr.feature.chamfer", edges=edge, distance=0.2, **bad)
    except RuntimeError as e:
        assert "Chamfer" in str(e) or "Angle" in str(e) or "Distance" in str(e), e
    else:
        raise AssertionError("bad chamfer accepted: %r" % bad)
print("api chamfer types: OK")
