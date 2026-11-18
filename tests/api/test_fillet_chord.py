# Fillet Radius Type Chord Length, as in the familiar panel: the width
# across the fillet (face to face) is given; on a right-angled edge the
# radius is chord / sqrt(2), on an edge whose faces meet at 135 deg it is
# chord / (2 sin(22.5 deg)).
import json
import math
import tsr

cmd = tsr.run_command


def vol():
    return tsr.mass_properties("Body1")["volume"]


# A 4 x 3 x 2 cm block: one 4 cm edge with a 4 mm chord.
cmd("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
v0 = vol()
cmd("tsr.feature.fillet", edges="2,0,2", radiusType="Chord Length", chord=0.4)
f = tsr.features()[-1]
assert f["error"] == "", f
r = 0.4 / math.sqrt(2)
near = v0 - (1 - math.pi / 4) * r * r * 4.0
assert abs(vol() - near) < 1e-6, (vol(), near)
# Constant with that radius gives the same body.
tsr.edit_feature(f["id"], radiusType="Constant", radius=r)
assert abs(vol() - near) < 1e-6
try:
    tsr.edit_feature(f["id"], radiusType="Chord Length", chord=10.0)    # far too wide: explained
except RuntimeError as e:
    assert "chord length is too large" in str(e), e
else:
    raise AssertionError("took a 10 cm chord")

# A prism whose top edges meet the sides at 135 deg: a trapezoid extruded.
tsr.new_document()
pts = [[0, 0], [0, 0], [4, 0], [3, 1], [1, 1]]   # point 0 is the origin; sides at 45 deg
data = {"points": pts, "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                                    {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(data))
cmd("tsr.feature.extrude", distance=-2.0)
lo, hi = tsr.bounding_box("Body1")
v0 = vol()
# The top right edge (top face z = 1, slanted side): faces meet at 135 deg, normals 45 deg apart.
cmd("tsr.feature.fillet", edges="3,%g,1" % ((lo[1] + hi[1]) / 2), radiusType="Chord Length", chord=0.2)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
a = math.pi / 4
r = 0.2 / (2 * math.sin(a / 2))
# Removed: the area between the corner and the arc, (tan(a/2) - a/2) r^2, along 2 cm.
removed = (math.tan(a / 2) - a / 2) * r * r * 2.0
assert abs(v0 - vol() - removed) < 1e-6, (v0 - vol(), removed)
print("fillet chord length: OK")
