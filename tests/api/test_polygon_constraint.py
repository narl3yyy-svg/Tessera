# The Polygon constraint, as in the familiar sketch: one constraint keeps a
# polygon regular about its centre (equal sides, equal angles). Drawn
# lopsided, it solves regular; a side's length sizes all of it; it can run
# either way round.
import json
import math
import tsr


def hexagon(points, sign=1.0, side=None):
    n = len(points)
    data = {"points": [[0, 0], [1, 1]] + points,
            "entities": [{"type": "line", "p": [2 + i, 2 + (i + 1) % n]} for i in range(n)],
            "constraints": [{"type": "fix", "p": [1], "v": 1.0, "v2": 1.0},
                            {"type": "polygon", "p": [1], "e": list(range(n)), "v": sign},
                            {"type": "fix", "p": [2], "v": points[0][0], "v2": points[0][1]}]}
    if side is not None:
        data["constraints"][2] = {"type": "horizontal", "e": [0]}
        data["constraints"].append({"type": "distance", "e": [0], "v": side})
    return data


def solved(data):
    tsr.new_document()
    tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(data))
    return json.loads(tsr.sketch_data("Sketch1"))


def check_regular(sk, n, centre=(1, 1)):
    P = sk["points"]
    corners = [P[sk["entities"][i]["p"][0]] for i in range(n)]
    radii = [math.hypot(p[0] - centre[0], p[1] - centre[1]) for p in corners]
    sides = [math.hypot(corners[(i + 1) % n][0] - corners[i][0], corners[(i + 1) % n][1] - corners[i][1]) for i in range(n)]
    assert max(radii) - min(radii) < 1e-7, radii
    assert max(sides) - min(sides) < 1e-7, sides
    return radii[0], sides[0]


# A lopsided hexagon round (1,1), its first corner fixed at (3,1): regular,
# radius 2, sides 2.
lop = [[3, 1], [2.2, 2.9], [-0.1, 2.6], [-1.2, 1.1], [0.1, -0.8], [2.3, -0.6]]
sk = solved(hexagon(lop))
r, s = check_regular(sk, 6)
assert abs(r - 2) < 1e-7 and abs(s - 2) < 1e-7, (r, s)
# Anticlockwise: the second corner is up and left of the first.
c1 = sk["points"][sk["entities"][1]["p"][0]]
assert abs(c1[0] - 2) < 1e-7 and abs(c1[1] - (1 + math.sqrt(3))) < 1e-7, c1

# Sized by one side: a level first side 30 mm long; all sides follow.
sk = solved(hexagon(lop, side=3.0))
r, s = check_regular(sk, 6)
assert abs(s - 3) < 1e-7 and abs(r - 3) < 1e-7, (r, s)

# Clockwise (-1): drawn the other way round, a pentagon.
pent = [[1 + 2 * math.cos(-2 * math.pi * k / 5) + 0.1 * (k % 2), 1 + 2 * math.sin(-2 * math.pi * k / 5)] for k in range(5)]
pent[0] = [3, 1]
sk = solved(hexagon(pent, sign=-1.0))
r, s = check_regular(sk, 5)
c1 = sk["points"][sk["entities"][1]["p"][0]]
assert c1[1] < 1, c1                      # clockwise: below the centre's level

# Saved form.
d = json.loads(tsr.features()[0]["inputs"]["data"])
assert [k for k in d["constraints"] if k["type"] == "polygon"][0]["v"] == -1.0
print("polygon constraint: OK")
