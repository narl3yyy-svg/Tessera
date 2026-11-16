import math
import tsr
f = tsr.features()[-1]
assert f["command"] == "tsr.feature.circularPattern" and f["error"] == "", tsr.features()
assert f["inputs"]["patternType"] == "Faces" and len(f["inputs"]["faces"].split(";")) == 2, f["inputs"]
v = tsr.mass_properties("Body1")["volume"]
want = 25 * math.pi - 6 * math.pi * 0.25 * 0.2
assert abs(v - want) < 1e-5, (v, want)
print("live face pattern: OK")
