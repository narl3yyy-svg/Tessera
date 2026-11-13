import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
edges = [e for e in f[0]["inputs"]["edges"].split(";") if e]
assert len(edges) == 1, edges            # Clear emptied the earlier picks
r = f[0]["inputs"]["radius"]
expected = 24 - (1 - math.pi / 4) * r * r * 3.0   # one 30 mm edge rounded
v = root.bRepBodies.item(0).volume
assert abs(v - expected) < 1e-6, (v, expected)
print("live fillet picks: OK")
