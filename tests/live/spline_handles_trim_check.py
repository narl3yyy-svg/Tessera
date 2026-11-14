import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, ents = sk["points"], sk["entities"]
spline = [e for e in ents if e["type"] == "spline"]
assert len(spline) == 1 and "handles" in spline[0], spline
hx, hy = spline[0]["handles"][1]
assert abs(hx) < 0.05 and 1.2 < hy < 1.5, (hx, hy)      # straight up, about 10 / 7.45
assert spline[0]["handles"][0] == [0, 0] and spline[0]["handles"][2] == [0, 0]
arcs = [e for e in ents if e["type"] == "ellipse"]
assert len(arcs) == 1 and "ends" in arcs[0], arcs
ends = [pts[i] for i in arcs[0]["ends"]]
assert all(abs(p[0] - 7.0) < 1e-6 for p in ends) and sorted(round(p[1], 6) for p in ends) == [-2.0, 2.0], ends
print("live spline handles / ellipse trim: OK")
