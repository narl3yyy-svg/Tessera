# Sketch Chamfer where arcs meet, as the familiar Chamfer: each curve is cut
# the chamfer distance from the corner (straight across: on an arc, the point
# that far from the corner) and a line joins the cuts.
import json
import math
import tsr


def dist(p, q):
    return math.hypot(p[0] - q[0], p[1] - q[1])


# A quarter arc (centre (0,0), radius 2, from (2,0) to (0,2)) meeting a line
# from (2,0) to (5,0) at (2,0); a 10 mm chamfer.
al = {"points": [[0, 0], [0, 0], [2, 0], [0, 2], [5, 0]],
      "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 2.0}, {"type": "line", "p": [2, 4]}],
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [4], "v": 5.0, "v2": 0.0}]}
out = json.loads(tsr.sketch_chamfer(json.dumps(al), 0, 1, 1.0))
P, ents = out["points"], out["entities"]
assert len(ents) == 3 and ents[2]["type"] == "line", ents
a, b = P[ents[2]["p"][0]], P[ents[2]["p"][1]]
corner = [2, 0]
assert abs(dist(a, corner) - 1) < 1e-6 and abs(dist(b, corner) - 1) < 1e-6, (a, b)   # 10 mm from the corner each way
arc = ents[0]
s, c = P[arc["p"][0]], P[arc["c"]]
assert abs(dist(s, c) - 2) < 1e-6 and s[1] > 0, s                # the arc now starts up its circle
d = 2 * math.asin(0.25)
assert abs(s[0] - 2 * math.cos(d)) < 1e-6 and abs(s[1] - 2 * math.sin(d)) < 1e-6, s
line = ents[1]
ends = sorted([P[line["p"][0]], P[line["p"][1]]])
assert abs(ends[0][0] - 3) < 1e-6 and abs(ends[1][0] - 5) < 1e-6, ends   # the line starts at 30 mm

# Two arcs meeting at a point (an S): both cut, the corner gone.
ss = {"points": [[0, 0], [0, 0], [-1, 0], [0, 1], [0, 2], [1, 2]],
      "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 1.0},   # anticlockwise (-1,0) -> under -> (0,1)
                   {"type": "arc", "c": 4, "p": [3, 5], "r": 1.0}],  # anticlockwise (0,1) -> (1,2)
      "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [4], "v": 0.0, "v2": 2.0}]}
out = json.loads(tsr.sketch_chamfer(json.dumps(ss), 0, 1, 0.5))
P, ents = out["points"], out["entities"]
ch = ents[-1]
assert ch["type"] == "line", ents
a, b = P[ch["p"][0]], P[ch["p"][1]]
assert abs(dist(a, [0, 1]) - 0.5) < 1e-6 and abs(dist(b, [0, 1]) - 0.5) < 1e-6, (a, b)
for e, centre in ((ents[0], [0, 0]), (ents[1], [0, 2])):
    for k in e["p"]:
        assert abs(dist(P[k], centre) - 1) < 1e-6, (e, P[k])      # cut points stay on each circle

# Too large: refused.
try:
    tsr.sketch_chamfer(json.dumps(al), 0, 1, 5.0)
    raise AssertionError("a 50 mm chamfer was accepted")
except RuntimeError as e:
    assert "too large" in str(e), e
print("sketch chamfer with arcs: OK")
