# Sketch patterns, Move/Copy and Scale: exact placements, constraints carried
# over when they still hold, the result solvable.
import json
import math
import tsr

# A 10 x 5 mm rectangle (H/V, a width dimension) and a 2 mm circle.
rect = {"points": [[0, 0], [1, 1], [2, 1], [2, 1.5], [1, 1.5], [3, 1]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                     {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]},
                     {"type": "circle", "c": 5, "r": 0.2}],
        "constraints": [{"type": "horizontal", "e": [0]}, {"type": "vertical", "e": [1]},
                        {"type": "horizontal", "e": [2]}, {"type": "vertical", "e": [3]},
                        {"type": "distance", "e": [0], "v": 1.0, "name": "d1"}]}
data = json.dumps(rect)


def corners(sk, line):
    a, b = sk["entities"][line]["p"]
    return sk["points"][a], sk["points"][b]


# Rectangular: 3 along X (15 mm apart) x 2 along Y (8 mm): 6 rectangles.
sk = json.loads(tsr.sketch_pattern_rect(data, [0, 1, 2, 3], 0.0, 3, 1.5, 2, 0.8))
lines = [e for e in sk["entities"] if e["type"] == "line"]
assert len(lines) == 24, len(lines)
starts = sorted((round(sk["points"][e["p"][0]][0], 9), round(sk["points"][e["p"][0]][1], 9))
                for e in sk["entities"][4:] if e["type"] == "line" and abs(sk["points"][e["p"][0]][1] - sk["points"][e["p"][1]][1]) < 1e-12
                and sk["points"][e["p"][0]][0] < sk["points"][e["p"][1]][0])
assert (2.5, 1.0) in starts and (4.0, 1.8) in starts, starts          # copies' bottom-left corners
types = [c["type"] for c in sk["constraints"]]
assert types.count("horizontal") == 12 and types.count("distance") == 6, types   # carried to each copy
assert sum(1 for c in sk["constraints"] if c.get("name")) == 1             # the copies' dimensions are unnamed

# Circular: 6 circles round the origin, a full turn: 60 degrees apart.
sk = json.loads(tsr.sketch_pattern_circular(data, [4], 0, 6, 2 * math.pi))
circles = [e for e in sk["entities"] if e["type"] == "circle"]
assert len(circles) == 6, circles
angles = sorted(round(math.degrees(math.atan2(sk["points"][c["c"]][1], sk["points"][c["c"]][0])) % 360, 6) for c in circles)
base = math.degrees(math.atan2(1, 3))
assert all(abs(((a - base) % 60)) < 1e-6 or abs(((a - base) % 60) - 60) < 1e-6 for a in angles), angles
assert all(abs(math.hypot(*sk["points"][c["c"]]) - math.hypot(3, 1)) < 1e-9 for c in circles)
# Over 90 degrees with 3: 0, 45, 90 (the ends included).
sk = json.loads(tsr.sketch_pattern_circular(data, [4], 0, 3, math.pi / 2))
angles = sorted(math.degrees(math.atan2(sk["points"][c["c"]][1], sk["points"][c["c"]][0])) for c in sk["entities"] if c["type"] == "circle")
assert abs(angles[1] - angles[0] - 45) < 1e-9 and abs(angles[2] - angles[0] - 90) < 1e-9, angles

# Move: 5 mm right, the rectangle keeps its shape and constraints.
sk = json.loads(tsr.sketch_place(data, [0, 1, 2, 3], dx=0.5))
a, b = corners(sk, 0)
assert abs(a[0] - 1.5) < 1e-9 and abs(b[0] - 2.5) < 1e-9 and abs(a[1] - 1) < 1e-9, (a, b)
# Turned 90 degrees about (1, 1): H/V go, the shape (and width 10) stays.
sk = json.loads(tsr.sketch_place(data, [0, 1, 2, 3], angle=math.pi / 2, cx=1, cy=1))
a, b = corners(sk, 0)
assert abs(a[0] - 1) < 1e-9 and abs(a[1] - 1) < 1e-9 and abs(b[0] - 1) < 1e-9 and abs(b[1] - 2) < 1e-9, (a, b)
assert not any(c["type"] in ("horizontal", "vertical") for c in sk["constraints"]), sk["constraints"]
# Copy instead of move: the original stays, a copy appears.
sk = json.loads(tsr.sketch_place(data, [4], dx=1.0, copy=True))
cs = sorted(sk["points"][e["c"]][0] for e in sk["entities"] if e["type"] == "circle")
assert cs == [3.0, 4.0], cs
# Scale x2 about (1, 1): the rectangle doubles, its width dimension too.
sk = json.loads(tsr.sketch_place(data, [0, 1, 2, 3], scale=2.0, cx=1, cy=1))
a, b = corners(sk, 0)
assert abs(b[0] - 3) < 1e-9 and [c for c in sk["constraints"] if c["type"] == "distance"][0]["v"] == 2.0, (a, b)
print("sketch patterns / move / scale: OK")
