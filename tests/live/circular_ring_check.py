import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = [x for x in tsr.features() if x["command"] == "tsr.feature.circularPattern"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert abs(f[0]["inputs"]["angle"] - math.pi) < 1e-12, f[0]["inputs"]
# Six cubes from 0 to 180 deg (ends included): the last one sits on -X.
lo, hi = tsr.bounding_box(root.bRepBodies.item(0).name)
assert abs(lo[0] + 4) < 1e-6 and abs(hi[0] - 4) < 1e-6, (lo, hi)
print("live circular pattern ring: OK")
