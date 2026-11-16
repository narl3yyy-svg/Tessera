import math
import tsr
f = tsr.features()[-1]
assert f["command"] == "tsr.feature.boundaryFill" and f["error"] == "", tsr.features()
assert len(f["inputs"]["tools"].split(";")) == 3, f["inputs"]
assert len(f["inputs"]["cells"].split(";")) == 1, f["inputs"]
# Remove Tools (on by default): only the filled space is left, a 1 cm x 2 cm cylinder.
v = tsr.mass_properties("Body1")["volume"]
assert abs(v - 2 * math.pi) < 1e-6, v
print("live boundary fill: OK")
