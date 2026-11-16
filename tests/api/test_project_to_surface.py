# Project to Surface, as in the familiar sketch: sketch curves dropped along
# the sketch normal onto a body's face become fixed 3D curves lying on it.
import json
import math
import tsr

tsr.run_command("tsr.primitive.sphere", diameter=4.0)        # radius 2 cm, centred on the origin
# A sketch on a plane 3 cm up: a line across, and a circle, both over the sphere.
data = {"points": [[0, 0], [-1.5, 0], [1.5, 0], [0, 0.5]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "circle", "c": 3, "r": 1.0}]}
out = json.loads(tsr.sketch_project_to_surface(json.dumps(data), "XY", "Body1", (0, 0, 2), [0, 1], offset=3.0))
made = [e for e in out["entities"] if e.get("included")]
assert len(made) >= 2, out["entities"]
P = out["points"]


def world(i):
    p = P[i]
    return p[0], p[1], 3.0 + (p[2] if len(p) > 2 else 0.0)   # the sketch plane is 3 cm up


checked = 0
for e in made:
    pts = e.get("fit") or [k for k in (e.get("p") or []) if k >= 0]
    for k in pts:
        x, y, z = world(k)
        assert abs(math.sqrt(x * x + y * y + z * z) - 2) < 1e-4, (x, y, z)   # on the sphere
        checked += 1
assert checked >= 20, checked
# Draped on the top half (the face nearest (0,0,2)): the line's middle at the pole.
tops = [world(k) for e in made for k in (e.get("fit") or []) if abs(world(k)[0]) < 0.05 and abs(world(k)[1]) < 0.05]
assert any(z > 1.99 for _, _, z in tops), tops
# Fixed where they landed.
fixed = {c["p"][0] for c in out["constraints"] if c["type"] == "fix"}
assert all(k in fixed for e in made for k in (e.get("fit") or [])), "projected points are fixed"

# Nothing over the face: refused.
far = {"points": [[0, 0], [5, 5], [6, 5]], "entities": [{"type": "line", "p": [1, 2]}]}
try:
    tsr.sketch_project_to_surface(json.dumps(far), "XY", "Body1", (0, 0, 2), [0], offset=3.0)
    raise AssertionError("projected nothing yet accepted")
except RuntimeError as e:
    assert "nothing" in str(e), e
print("project to surface: OK")
