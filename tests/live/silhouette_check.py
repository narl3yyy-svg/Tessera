import math
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.silhouetteSplit"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
for b in ("Body1", "Body2"):
    v = tsr.mass_properties(b)["volume"]
    assert abs(v - math.pi * 4 / 2) < 1e-9, (b, v)
print("live silhouette split: OK")
