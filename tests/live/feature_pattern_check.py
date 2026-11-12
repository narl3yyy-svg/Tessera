import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = tsr.features()
pat = [x for x in f if x["command"] == "tsr.feature.rectangularPattern"]
assert len(pat) == 1 and pat[0]["error"] == "", f
i = pat[0]["inputs"]
assert i["patternType"] == "Features" and i["features"] == "Extrude1", i
assert abs(i["distance1"] - 0.2) > 1e-6, i          # dragged away from the 2 mm default
stud = math.pi * 0.25 ** 2 * 0.5
v = root.bRepBodies.item(0).volume
assert root.bRepBodies.count == 1 and v > 8 + stud + 1e-6, v   # copies of the stud were added
print("live feature pattern: OK (distance %.2f mm, volume %.3f)" % (i["distance1"] * 10, v))
