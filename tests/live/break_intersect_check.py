import json
import math
import tsr
sk = json.loads([f for f in tsr.features() if f["command"] == "tsr.sketch.create"][-1]["inputs"]["data"])
P, ents, cons = sk["points"], sk["entities"], sk["constraints"]
# Intersect: the sphere's section, a projected circle of 15 mm round the origin.
proj = [e for e in ents if e.get("projected")]
assert len(proj) == 1 and proj[0]["type"] in ("circle", "arc"), proj
assert abs(proj[0]["r"] - 1.5) < 1e-9 and math.hypot(*P[proj[0]["c"]]) < 1e-9, (proj, P[proj[0]["c"]])
# Break: the level line in two pieces meeting at (-35, 20), kept collinear.
level = [e for e in ents if e["type"] == "line" and abs(P[e["p"][0]][1] - 2) < 1e-9 and abs(P[e["p"][1]][1] - 2) < 1e-9]
assert len(level) == 2, level
ends = sorted(round(P[p][0], 9) for e in level for p in e["p"])
assert ends == [-4.5, -3.5, -3.5, -2.5], ends
assert any(c["type"] == "collinear" for c in cons), cons
# The circle in two arcs of one circle (centre (-35, -12), one radius).
arcs = [e for e in ents if e["type"] == "arc" and not e.get("projected")]
assert len(arcs) == 2 and all(abs(a["r"] - arcs[0]["r"]) < 1e-12 and a["c"] == arcs[0]["c"] for a in arcs), arcs
c = P[arcs[0]["c"]]
assert abs(c[0] + 3.5) < 1e-9 and abs(c[1] + 1.2) < 0.05, c   # on the vertical line (snapped onto it)
assert any(c["type"] == "equal" for c in cons), cons
print("live break / intersect: OK")
