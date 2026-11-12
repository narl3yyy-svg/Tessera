import json
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.sketch.create"]
assert len(f) == 1, tsr.features()
sk = json.loads(f[0]["inputs"]["data"])
lines = [e for e in sk["entities"] if e["type"] == "line"]
assert len(lines) == 4 and all(e.get("projected") for e in lines), sk["entities"]
pts = sk["points"]
xs = sorted({round(pts[i][0], 6) for e in lines for i in e["p"]})
ys = sorted({round(pts[i][1], 6) for e in lines for i in e["p"]})
assert xs == [0.0, 4.0] and ys == [0.0, 3.0], (xs, ys)   # the 40 x 30 mm outline
print("live project: OK")
