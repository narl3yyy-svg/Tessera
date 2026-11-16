# The Curvature (G2) constraint, as in the familiar sketch: a fit point spline
# joined to a line, an arc or another spline runs on from it smoothly, in the
# same direction and bending the same amount where they meet.
import json
import math
import tsr


def solved(data):
    tsr.new_document()
    tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(data))
    return json.loads(tsr.sketch_data("Sketch1"))


def end(sk, e, at_end=False):
    return tsr.sketch_curve_end(json.dumps(sk), e, at_end)


# An arc (centre (0,0), radius 2, anticlockwise (2,0) -> (0,2)) and a spline
# from (0,2) on round through (-1.8,0.9) to (-2.6,-1). At (0,2) the arc runs
# to -x and bends left with curvature 1/2: the spline must leave that way, as bent.
arc_spline = {"points": [[0, 0], [0, 0], [2, 0], [0, 2], [-1.8, 0.9], [-2.6, -1.0]],
              "entities": [{"type": "arc", "c": 1, "p": [2, 3], "r": 2.0}, {"type": "spline", "fit": [3, 4, 5]}],
              "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 2.0, "v2": 0.0},
                              {"type": "fix", "p": [4], "v": -1.8, "v2": 0.9}, {"type": "fix", "p": [5], "v": -2.6, "v2": -1.0},
                              {"type": "curvature", "p": [3, 3], "e": [1, 0]}]}
before = end(json.loads(json.dumps(dict(arc_spline, constraints=arc_spline["constraints"][:-1]))), 1)
sk = solved(arc_spline)
x, y, dx, dy, k = end(sk, 1)
assert abs(x) < 1e-7 and abs(y - 2) < 1e-7, (x, y)
assert abs(dx + 1) < 1e-6 and abs(dy) < 1e-6, (dx, dy)          # on along the arc's direction
assert abs(k - 0.5) < 1e-4, k                                    # bending as much as the arc
assert abs(before[4] - 0.5) > 0.05 or abs(before[2] + 1) > 1e-3, before   # it was not so before

# A line into a spline: straight on, no bend at the joint (curvature 0).
line_spline = {"points": [[0, 0], [-3, 0], [0, 0], [2, 1], [4, 0]],
               "entities": [{"type": "line", "p": [1, 2]}, {"type": "spline", "fit": [2, 3, 4]}],
               "constraints": [{"type": "fix", "p": [1], "v": -3.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 0.0, "v2": 0.0},
                               {"type": "fix", "p": [3], "v": 2.0, "v2": 1.0}, {"type": "fix", "p": [4], "v": 4.0, "v2": 0.0},
                               {"type": "curvature", "p": [2, 2], "e": [1, 0]}]}
sk = solved(line_spline)
x, y, dx, dy, k = end(sk, 1)
assert abs(dx - 1) < 1e-6 and abs(dy) < 1e-6 and abs(k) < 1e-4, (dx, dy, k)

# At the spline's far end: an arc after it (spline (0,3)->(2,2.3)->(4,2),
# coming down and levelling out; arc centre (4,4) radius 2 from (4,2)
# anticlockwise to (6,4)). Arriving at (4,2) the spline must run as the arc
# leaves, +x, bending left by 1/2.
spline_arc = {"points": [[0, 0], [0, 3], [2, 2.3], [4, 2], [4, 4], [6, 4]],
              "entities": [{"type": "spline", "fit": [1, 2, 3]}, {"type": "arc", "c": 4, "p": [3, 5], "r": 2.0}],
              "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 3.0}, {"type": "fix", "p": [2], "v": 2.0, "v2": 2.3},
                              {"type": "fix", "p": [3], "v": 4.0, "v2": 2.0}, {"type": "fix", "p": [4], "v": 4.0, "v2": 4.0},
                              {"type": "fix", "p": [5], "v": 6.0, "v2": 4.0},
                              {"type": "curvature", "p": [3, 3], "e": [0, 1]}]}
sk = solved(spline_arc)
x, y, dx, dy, k = end(sk, 0, True)
assert abs(x - 4) < 1e-7 and abs(y - 2) < 1e-7, (x, y)
assert abs(dx - 1) < 1e-6 and abs(dy) < 1e-6 and abs(k - 0.5) < 1e-4, (dx, dy, k)

# Ends apart are pulled together; the saved form keeps it.
apart = {"points": [[0, 0], [-3, 0], [0, 0], [2, 1], [4, 0], [0.3, -0.2]],   # the spline starts off the line's end
         "entities": [{"type": "line", "p": [1, 2]}, {"type": "spline", "fit": [5, 3, 4]}],
         "constraints": [{"type": "fix", "p": [1], "v": -3.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 0.0, "v2": 0.0},
                         {"type": "fix", "p": [3], "v": 2.0, "v2": 1.0}, {"type": "fix", "p": [4], "v": 4.0, "v2": 0.0},
                         {"type": "curvature", "p": [5, 2], "e": [1, 0]}]}
sk = solved(apart)
assert math.hypot(sk["points"][5][0], sk["points"][5][1]) < 1e-7, sk["points"][5]
assert any(c["type"] == "curvature" for c in json.loads(tsr.features()[0]["inputs"]["data"])["constraints"])
print("curvature constraint: OK")
