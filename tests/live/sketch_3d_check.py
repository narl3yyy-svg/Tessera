import json
import tsr
sk = [f for f in tsr.features() if f["command"] == "tsr.sketch.create"][-1]
d = json.loads(sk["inputs"]["data"])
P = d["points"]


def z(i):
    p = P[i]
    return p[2] if len(p) > 2 else 0.0


lines = [e for e in d["entities"] if e["type"] == "line"]
up = [e for e in lines if any(abs(z(k) - 1.0) < 1e-9 for k in e["p"])]
assert len(up) == 1, (lines, P)                                     # one line climbs to the corner
top = [k for k in up[0]["p"] if abs(z(k) - 1.0) < 1e-9][0]
assert abs(P[top][0] - 4) < 1e-9 and abs(P[top][1] - 2) < 1e-9, P[top]   # at (40, 20, 10) mm
other = [k for k in up[0]["p"] if k != top][0]
assert abs(P[other][0]) < 1e-9 and abs(P[other][1]) < 1e-9 and abs(z(other)) < 1e-9, P[other]
assert any(c["type"] == "fix" and top in c.get("p", []) for c in d["constraints"]), d["constraints"]
raised = [i for i in range(1, len(P)) if abs(z(i) - 1.5) < 1e-9]
assert raised and abs(P[raised[0]][0] - 1) < 1e-9, (raised, P)     # the point lifted 15 mm
print("live 3D sketch: OK")
