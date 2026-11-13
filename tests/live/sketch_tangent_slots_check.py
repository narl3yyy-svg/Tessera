import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents = sk["points"], sk["entities"]
lines = [e for e in ents if e["type"] == "line" and not e.get("construction")]
circles = [e for e in ents if e["type"] == "circle"]
arcs = [e for e in ents if e["type"] == "arc" and not e.get("construction")]


def dist_to_line(c, e):
    a, b = P[e["p"][0]], P[e["p"][1]]
    dx, dy = b[0] - a[0], b[1] - a[1]
    return abs(dx * (c[1] - a[1]) - dy * (c[0] - a[0])) / math.hypot(dx, dy)


assert len(circles) == 2, circles
inc = max(circles, key=lambda e: P[e["c"]][0])
r = (6 + 6 - 6 * math.sqrt(2)) / 2                      # incircle of the 60 mm right triangle
ci = P[inc["c"]]
assert abs(inc["r"] - r) < 1e-9 and abs(ci[0] - r) < 1e-9 and abs(ci[1] - r) < 1e-9, (ci, inc)
corner = min(circles, key=lambda e: P[e["c"]][0])
cc = P[corner["c"]]
legs = [e for e in lines if max(P[e["p"][0]][0], P[e["p"][1]][0]) < -3]
assert len(legs) == 2, legs
for e in legs:
    assert abs(dist_to_line(cc, e) - corner["r"]) < 1e-9, (cc, corner, e)   # tangent to both
assert abs(cc[0] + 8 - corner["r"]) < 1e-9 and abs(corner["r"] - 1.75) < 0.1, (cc, corner)
# Overall slot: 60 long, 20 wide: end arcs of radius 10 centred 10 in.
slot = sorted([a for a in arcs if abs(P[a["c"]][1] + 4) < 1e-9], key=lambda a: P[a["c"]][0])
assert len(slot) == 2 and all(abs(a["r"] - 1) < 1e-9 for a in slot), slot
assert abs(P[slot[0]["c"]][0] - 1) < 1e-9 and abs(P[slot[1]["c"]][0] - 5) < 1e-9, [P[a["c"]] for a in slot]
# Arc slot round (100, -60): outer 40, inner 20, caps 10 at the path's ends.
round_ = [a for a in arcs if abs(P[a["c"]][0] - 10) < 1e-9 and abs(P[a["c"]][1] + 6) < 1e-9]
assert sorted(round(a["r"], 9) for a in round_) == [2.0, 4.0], round_
caps = [a for a in arcs if abs(a["r"] - 1) < 1e-9 and a not in slot]
assert len(caps) == 2, caps
ends = sorted(tuple(round(v, 9) for v in P[a["c"]]) for a in caps)
assert ends == [(10.0, -3.0), (13.0, -6.0)], ends
print("live tangent circles and slots: OK")
