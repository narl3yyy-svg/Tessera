import json
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.sketch.create"]
assert len(f) == 1, tsr.features()
sk = json.loads(f[0]["inputs"]["data"])
lines = [e for e in sk["entities"] if e["type"] == "line"]
assert len(lines) == 5 and all(e.get("included") and e.get("projected") for e in lines), sk["entities"]
pts = sk["points"]
heights = {round(pts[i][2], 6) if len(pts[i]) > 2 else 0.0 for e in lines for i in e["p"]}
assert heights == {2.0}, heights               # the top face, 20 mm above the sketch
print("live include 3d: OK")
