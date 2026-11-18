import math
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.move"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
i = f[0]["inputs"]
assert i["x"] > 0.1 and abs(i["y"]) > 0.05 and abs(i["z"]) < 1e-9, i       # arrow, then square: in the XY plane
assert abs(i["xAngle"]) < 1e-9 and abs(i["yAngle"]) < 1e-9, i
assert abs(i["zAngle"] - math.pi / 4) < 1e-9, i                           # the ring's box: 45 deg
print("live move triad: OK")
