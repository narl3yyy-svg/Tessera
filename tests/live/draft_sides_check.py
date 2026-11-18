import math
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.draft"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
i = f[0]["inputs"]
assert i["sides"] == "Symmetric" and i["plane"] == "Plane1", i
v = tsr.mass_properties("Body1")["volume"]
want = 8 - 2 * 0.5 * 1.0 * math.tan(i["angle"]) * 2.0
assert abs(v - want) < 1e-9, (v, want)
print("live draft two sides: OK")
