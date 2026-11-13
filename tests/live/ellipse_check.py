import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P = sk["points"]
el = [e for e in sk["entities"] if e["type"] == "ellipse"]
assert len(el) == 1, sk["entities"]
c, a = P[el[0]["c"]], P[el[0]["p"][0]]
assert abs(c[0] - 2) < 1e-9 and abs(c[1] - 2) < 1e-9, c
assert abs(math.hypot(a[0] - c[0], a[1] - c[1]) - 3) < 1e-9 and abs(el[0]["r"] - 2.0) < 1e-9, (a, el)
print("live ellipse: OK")
