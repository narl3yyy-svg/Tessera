import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = tsr.features()
ex = [x for x in f if x["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", f
d = ex[0]["inputs"]["distance"]
assert d > 0.5, d                        # dragged well past the 10 mm default
assert abs(root.bRepBodies.item(0).volume - 12 * d) < 1e-6
print("live extrude arrow: OK (distance %.2f mm)" % (d * 10))
