import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents = sk["points"], sk["entities"]
lines = [e for e in ents if e["type"] == "line" and not e.get("construction")]
assert len(lines) == 4, ents
# The rectangle: four corners, square ones, first side from (0,20) to (30,30) mm.
def vec(e):
    a, b = P[e["p"][0]], P[e["p"][1]]
    return b[0] - a[0], b[1] - a[1]
for i in range(4):
    u, v = vec(lines[i]), vec(lines[(i + 1) % 4])
    assert abs(u[0] * v[0] + u[1] * v[1]) < 1e-9, (u, v)
assert abs(math.hypot(*vec(lines[0])) - math.hypot(3, 1)) < 1e-9, vec(lines[0])
# The width click (20, 60) mm snapped: the far corner is exactly there.
assert any(abs(p[0] - 2) < 1e-9 and abs(p[1] - 6) < 1e-9 for p in P), P
circles = sorted([e for e in ents if e["type"] == "circle"], key=lambda e: P[e["c"]][0])
assert len(circles) == 2, ents
c2, c3 = circles
assert abs(P[c2["c"]][0] - 7) < 1e-9 and abs(P[c2["c"]][1] - 2) < 1e-9 and abs(c2["r"] - 1) < 1e-9, (P[c2["c"]], c2)
assert abs(P[c3["c"]][0] - 11) < 1e-9 and abs(P[c3["c"]][1] - 2) < 1e-9 and abs(c3["r"] - 1) < 1e-9, (P[c3["c"]], c3)
arcs = [e for e in ents if e["type"] == "arc"]
assert len(arcs) == 1, ents
a = arcs[0]
c = P[a["c"]]
assert abs(c[0] - 1) < 1e-9 and abs(c[1] + 4) < 1e-9 and abs(a["r"] - 1) < 1e-9, (c, a, P[a["p"][0]], P[a["p"][1]], [k for k in sk["constraints"] if a["c"] in k.get("p", []) or a["p"][0] in k.get("p", []) or a["p"][1] in k.get("p", [])])
s, e = P[a["p"][0]], P[a["p"][1]]
# Counter-clockwise from (20,-40) to (0,-40): over the top, through (10,-30).
assert abs(s[0] - 2) < 1e-9 and abs(e[0]) < 1e-9, (s, e)
print("live 3-point tools: OK")
