import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, cons = sk["points"], sk["constraints"]
lines = [e for e in sk["entities"] if e["type"] == "line"]
assert len(lines) == 1, sk["entities"]
a, b = lines[0]["p"]
# The start is on the X axis (x may follow the grid) and tied to it.
assert abs(pts[a][1]) < 1e-12 and abs(pts[a][0] - 1.2) < 0.25, pts[a]
assert any(c["type"] == "horizontal" and sorted(c.get("p", [])) == sorted([0, a]) for c in cons), cons
# The end lines up with the far point (x = 50 mm) but is not tied to it.
far = [i for i, p in enumerate(pts) if abs(p[0] - 5) < 1e-9 and abs(p[1] - 4) < 1e-9]
assert far and abs(pts[b][0] - 5) < 1e-12, (pts[b], far)
assert not any(far[0] in c.get("p", []) for c in cons), cons
print("live axis snap / alignment: OK")
