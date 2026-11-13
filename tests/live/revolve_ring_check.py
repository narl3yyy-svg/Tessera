import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = [x for x in tsr.features() if x["command"] == "tsr.feature.revolve"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert abs(f[0]["inputs"]["angle"] - math.pi / 2) < 1e-12, f[0]["inputs"]
# Pappus: angle / 2 * (r2^2 - r1^2) * height = pi/4 * 8 * 2.
v = root.bRepBodies.item(0).volume
assert abs(v - math.pi / 2 / 2 * (9 - 1) * 2) < 1e-6, v
print("live revolve ring: OK")
