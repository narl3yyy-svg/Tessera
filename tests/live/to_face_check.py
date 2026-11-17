import math
import tsr
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
assert ex[0]["inputs"]["toObject"].startswith("face:Body1|"), ex[0]["inputs"]
n, r, total = 400, 0.5, 0.0
for i in range(n):
    y = -r + (i + 0.5) * 2 * r / n
    total += (5 - math.sqrt(4 - y * y)) * 2 * math.sqrt(r * r - y * y) * (2 * r / n)
v = tsr.mass_properties("Body2")["volume"]
assert abs(v - total) < 1e-3, (v, total)
print("live extrude to face: OK")
