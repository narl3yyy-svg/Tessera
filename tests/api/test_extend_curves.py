# Extend of elliptical arcs and splines, as the familiar Extend: the clicked
# end runs on to the first curve it meets (round the ellipse; a spline along
# its own bend, or straight where it is flat) and ends on it.
import json
import math
import tsr

# Elliptical arc: a quarter of the ellipse x^2/4 + y^2 = 1, from (2,0) to
# (0,1); the line x = -1 crosses the ellipse at y = +-sqrt(3)/2.
ell = {"points": [[0, 0], [0, 0], [2, 0], [2, 0], [0, 1], [-1, -3], [-1, 3]],
       "entities": [{"type": "ellipse", "c": 1, "p": [2, -1], "r": 1.0, "ends": [3, 4]},
                    {"type": "line", "p": [5, 6]}],
       "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0}, {"type": "fix", "p": [2], "v": 2.0, "v2": 0.0},
                       {"type": "fix", "p": [5], "v": -1.0, "v2": -3.0}, {"type": "fix", "p": [6], "v": -1.0, "v2": 3.0}]}
ext = json.loads(tsr.sketch_extend(json.dumps(ell), 0, 0.05, 1.0))   # near the (0,1) end
e = ext["entities"][0]
end = ext["points"][e["ends"][1]]
assert abs(end[0] + 1) < 1e-6 and abs(end[1] - math.sqrt(3) / 2) < 1e-6, end   # on round to x = -1, upper side
start = ext["points"][e["ends"][0]]
assert abs(start[0] - 2) < 1e-9 and abs(start[1]) < 1e-9, start                # the other end stays
assert any(c["type"] == "pointOnEntity" for c in ext["constraints"])

# A flat spline end (three points on a line) runs straight on to x = 5.
flat = {"points": [[0, 0], [0, 0], [1, 0], [2, 0], [5, -2], [5, 2]],
        "entities": [{"type": "spline", "fit": [1, 2, 3]}, {"type": "line", "p": [4, 5]}],
        "constraints": [{"type": "fix", "p": [4], "v": 5.0, "v2": -2.0}, {"type": "fix", "p": [5], "v": 5.0, "v2": 2.0}]}
ext = json.loads(tsr.sketch_extend(json.dumps(flat), 0, 1.95, 0.0))
fit = ext["entities"][0]["fit"]
assert len(fit) == 4, fit                                   # the old end stays as a fit point
end = ext["points"][fit[-1]]
assert abs(end[0] - 5) < 1e-6 and abs(end[1]) < 1e-6, end

# A bending spline (three points round a quarter circle) keeps bending on to
# the line y = -0.5. Its end heads level (to -x), so a straight extension
# would never meet that line: reaching it means it bent.
c = math.sqrt(0.5)
bend = {"points": [[0, 0], [1, 0], [c, c], [0, 1], [-3, -0.5], [3, -0.5]],
        "entities": [{"type": "spline", "fit": [1, 2, 3]}, {"type": "line", "p": [4, 5]}],
        "constraints": [{"type": "fix", "p": [4], "v": -3.0, "v2": -0.5}, {"type": "fix", "p": [5], "v": 3.0, "v2": -0.5}]}
ext = json.loads(tsr.sketch_extend(json.dumps(bend), 0, 0.0, 0.95))     # the (0,1) end
end = ext["points"][ext["entities"][0]["fit"][-1]]
assert abs(end[1] + 0.5) < 1e-6 and -3.0 < end[0] < 0, end
# The front end too: from (1,0), heading down, it bends on to the line.
ext = json.loads(tsr.sketch_extend(json.dumps(bend), 0, 1.0, 0.05))
start = ext["points"][ext["entities"][0]["fit"][0]]
assert abs(start[1] + 0.5) < 1e-6 and 0 < start[0] < 1.0, start   # bending left of straight down

# A conic and a connected end are refused.
for data, ent, x, y in ((dict(bend, entities=[{"type": "spline", "fit": [1, 2, 3], "kind": "conic", "rho": 0.5},
                                              bend["entities"][1]]), 0, 0.0, 0.95),):
    try:
        tsr.sketch_extend(json.dumps(data), ent, x, y)
        raise AssertionError("conic extended")
    except RuntimeError as e:
        assert "conic" in str(e), e
print("extend of elliptical arcs and splines: OK")
