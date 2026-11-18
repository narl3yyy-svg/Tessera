import math
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
i = f[0]["inputs"]
assert i["radiusType"] == "Chord Length" and abs(i["chord"] - 0.4) < 1e-9, i
r = 0.4 / math.sqrt(2)
want = 24 - (1 - math.pi / 4) * r * r * 4.0          # the 40 mm top front edge
v = tsr.mass_properties("Body1")["volume"]
assert abs(v - want) < 1e-6, (v, want)
print("live fillet chord: OK")
