import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
h = [x for x in tsr.features() if x["command"] == "tsr.feature.hole"]
assert len(h) == 1 and h[0]["error"] == "", tsr.features()
i = h[0]["inputs"]
assert i["placement"] == "On Face", i
x, y, z = (float(v) for v in i["points"].split(";")[0].split(","))
assert abs(math.hypot(x, y) - 1.0) < 1e-3 and abs(z - 2.0) < 0.1, i["points"]   # on the side, half way up
v = root.bRepBodies.item(0).volume
assert v < math.pi * 1.0 * 4.0 - 0.1, v                                     # material removed
print("live hole on face: OK")
