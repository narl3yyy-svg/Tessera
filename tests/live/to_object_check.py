import tsr
import adsk.core
import adsk.fusion
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
assert ex[0]["inputs"]["extent"] == "To Object" and ex[0]["inputs"]["toObject"].startswith("custom:"), ex[0]["inputs"]
assert abs(root.bRepBodies.item(1).volume - 12 * 2.5) < 1e-6, root.bRepBodies.item(1).volume
print("live extrude to object: OK")
