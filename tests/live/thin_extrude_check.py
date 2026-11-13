import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
ex = [x for x in tsr.features() if x["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
i = ex[0]["inputs"]
assert i["thin"] is True and i["wallLocation"] == "Center" and abs(i["wallThickness"] - 0.4) < 1e-9, i
v = root.bRepBodies.item(0).volume
assert abs(v - (4.4 * 3.4 - 3.6 * 2.6) * 1.0) < 1e-6, v   # 40 x 30 outline, 2 mm each side, 10 mm tall
print("live thin extrude: OK")
