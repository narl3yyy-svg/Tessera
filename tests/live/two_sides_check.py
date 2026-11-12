import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = tsr.features()
ex = [x for x in f if x["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", f
i = ex[0]["inputs"]
assert i["direction"] == "Two Sides", i
d1, d2 = i["distance"], i["distance2"]
assert d1 > 0.5 and d2 > 0.5, (d1, d2)   # both dragged well past the defaults
assert abs(root.bRepBodies.item(0).volume - 12 * (d1 + d2)) < 1e-6
print("live two sides: OK (%.2f mm up, %.2f mm down)" % (d1 * 10, d2 * 10))
