import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = [x for x in tsr.features() if x["command"] == "tsr.feature.shell"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert abs(f[0]["inputs"]["thickness"] - 0.3) < 1e-12, f[0]["inputs"]       # typed over the selected value
v = root.bRepBodies.item(0).volume
expected = 4 * 3 * 2 - (4 - 0.6) * (3 - 0.6) * (2 - 0.3)                    # open top, 3 mm walls and floor
assert abs(v - expected) < 1e-6, (v, expected)
print("live shell arrow: OK")
