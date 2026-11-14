# Rib and Web: thin supports grown from a sketch's open curves to the body.
import json
import tsr

cmd = tsr.run_command


def vol():
    return tsr.mass_properties("Body1")["volume"]


# --- Web: an open 40 x 40 x 20 mm tray with 2 mm walls; a line across the
# floor (drawn short of the walls) becomes a 2 mm wall 10 mm high, reaching
# both walls: 36 x 2 x 10 mm added.
cmd("tsr.primitive.box", length=4.0, width=4.0, height=2.0)
cmd("tsr.feature.shell", faces="2,2,2", thickness=0.2)
v0 = vol()
line = {"points": [[0, 0], [1, 2], [3, 2]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XY", offset=0.2, data=json.dumps(line))
cmd("tsr.feature.web", body="Body1", thickness=0.2, extent="Distance", depth=1.0)
assert abs(vol() - (v0 + 3.6 * 0.2 * 1.0)) < 1e-6, (vol(), v0)
# To Next, growing down from a sketch 15 mm up: it stops on the floor (13 mm).
v1 = vol()
cross = {"points": [[0, 0], [2, 1], [2, 3]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XY", offset=1.5, data=json.dumps(cross))
cmd("tsr.feature.web", body="Body1", thickness=0.2, flip="Yes")
# Across y from wall to wall (36 mm), less where it crosses the first web.
added = vol() - v1
expect = 3.6 * 0.2 * 1.3 - 0.2 * 0.2 * 1.0
assert abs(added - expect) < 1e-6, (added, expect)

# --- Rib: an L bracket (base 40 x 20 x 5, upright 5 x 20 x 40 mm) braced
# by a diagonal from the upright to the base in the middle plane (y = 10 mm):
# a 25 x 25 mm triangle, 2 mm thick.
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=2.0, height=0.5)
cmd("tsr.primitive.box", length=0.5, width=2.0, height=4.0, operation="Join")
v0 = vol()
diag = {"points": [[0, 0], [0.5, 3.0], [3.0, 0.5]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XZ", offset=-1.0, data=json.dumps(diag))
cmd("tsr.feature.rib", body="Body1", thickness=0.2, flip="Yes")
assert abs(vol() - (v0 + 2.5 * 2.5 / 2 * 0.2)) < 1e-6, (vol(), v0)
lo, hi = tsr.bounding_box("Body1")
assert abs(lo[1]) < 1e-9 and abs(hi[1] - 2.0) < 1e-9, (lo, hi)   # nothing sticks out
# The wrong way: nothing to meet.
try:
    cmd("tsr.feature.rib", body="Body1", thickness=0.2, extent="Distance", depth=0.5)
    vol()
except RuntimeError:
    pass
print("rib / web: OK")
