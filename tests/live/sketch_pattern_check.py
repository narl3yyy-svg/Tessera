import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents = sk["points"], sk["entities"]
circles = [e for e in ents if e["type"] == "circle"]
assert len(circles) == 6, circles
angles = sorted(round(math.degrees(math.atan2(P[c["c"]][1], P[c["c"]][0])) % 360, 6) for c in circles)
assert angles == [0.0, 60.0, 120.0, 180.0, 240.0, 300.0], angles
assert all(abs(math.hypot(*P[c["c"]]) - 3) < 1e-9 and abs(c["r"] - 1.0) < 1e-9 for c in circles), [(P[c["c"]], c["r"]) for c in circles]
lines = [e for e in ents if e["type"] == "line"]
assert len(lines) == 12, len(lines)
xs = sorted({round(min(P[e["p"][0]][0], P[e["p"][1]][0]), 9) for e in lines})
assert xs == [-6.0, -5.0, -4.0, -3.0], xs     # rectangles at -60, -50, -40 mm (their right sides too)
print("live sketch patterns: OK")
