import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P = sk["points"]
el = [e for e in sk["entities"] if e["type"] == "ellipse"]
assert len(el) == 1, sk["entities"]
c, a = P[el[0]["c"]], P[el[0]["p"][0]]
assert abs(c[1] - 2) < 1e-9, c                      # free to slide along its axis when sized
assert abs(math.hypot(a[0] - c[0], a[1] - c[1]) - 4) < 1e-9 and abs(el[0]["r"] - 1.5) < 1e-9, (a, el)
types = sorted(k["type"] for k in sk["constraints"] if k["type"] in ("radius", "distance"))
assert types == ["distance", "radius"], sk["constraints"]
print("live ellipse: OK")
