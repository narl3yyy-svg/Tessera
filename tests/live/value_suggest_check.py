import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
ex = [x for x in tsr.features() if x["command"] == "tsr.feature.extrude"]
assert len(ex) == 1, tsr.features()                    # Space reopened Extrude, Esc/Cancel added nothing
i = ex[0]["inputs"]
assert i.get("=distance") == "width", i                # the suggested name was used
assert abs(i["distance"] - 2.0) < 1e-9, i
assert abs(root.bRepBodies.item(0).volume - 12 * 2.0) < 1e-6
print("live value suggestions + Space: OK")
