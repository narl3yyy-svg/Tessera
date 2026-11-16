import json
import math
import tsr
sk = [f for f in tsr.features() if f["command"] == "tsr.sketch.create"][-1]
d = json.loads(sk["inputs"]["data"])
made = [e for e in d["entities"] if e.get("included")]
assert made, d["entities"]
P = d["points"]
on = 0
for e in made:
    for k in e.get("fit") or e.get("p") or []:
        p = P[k]
        z = p[2] if len(p) > 2 else 0.0
        assert abs(math.sqrt(p[0] ** 2 + p[1] ** 2 + z ** 2) - 1.5) < 1e-4, p   # on the 15 mm sphere
        on += 1
assert on >= 10, on
print("live project to surface: OK")
