import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, ents, cons = sk["points"], sk["entities"], [c["type"] for c in sk["constraints"]]
lines = [e for e in ents if e["type"] == "line" and not e.get("construction")]
assert len(lines) == 4 + 1 + 1 + 2, len(lines)              # rectangle, chamfer line, extended line, 2 mirrored
# Chamfer: a 5 mm bevel at (40, 30)
assert any(abs(pts[e["p"][0]][0] - 4.0) < 1e-6 and abs(pts[e["p"][0]][1] - 2.5) < 1e-6 or
           abs(pts[e["p"][1]][0] - 4.0) < 1e-6 and abs(pts[e["p"][1]][1] - 2.5) < 1e-6 for e in lines), pts
# Extend: the line at y = 50 now ends on the construction line (x = 70)
ext = [e for e in lines if abs(pts[e["p"][0]][1] - 5.0) < 1e-6 and abs(pts[e["p"][1]][1] - 5.0) < 1e-6]
assert ext and max(pts[ext[0]["p"][0]][0], pts[ext[0]["p"][1]][0]) > 6.99, ext
# Mirror: two symmetry-tied copies on the far side (x > 70)
assert cons.count("symmetry") >= 2, cons
assert sum(1 for e in lines if min(pts[e["p"][0]][0], pts[e["p"][1]][0]) > 7.0 - 1e-6) == 2
print("live sketch chamfer/extend/mirror: OK")
