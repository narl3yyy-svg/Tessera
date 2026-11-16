import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents = sk["points"], sk["entities"]
lines = [e for e in ents if e["type"] == "line"]
arcs = [e for e in ents if e["type"] == "arc"]
assert len(lines) == 2 and len(arcs) == 1, ents          # the line, the chamfer and the arc
first = [e for e in lines if any(abs(P[k][1]) < 1e-9 and abs(P[k][0]) < 1e-9 for k in e["p"])][0]
ends = sorted(P[k][0] for k in first["p"])
assert abs(ends[1] - 1.5) < 1e-6, ends                    # cut back 5 mm from (20, 0)
chamfer = [e for e in lines if e is not first][0]
for k in chamfer["p"]:
    assert abs(math.hypot(P[k][0] - 2, P[k][1]) - 0.5) < 1e-6, P[k]   # both cuts 5 mm from the corner
print("live chamfer with an arc: OK")
