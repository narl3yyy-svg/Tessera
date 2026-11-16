# Emboss, as in the familiar Create menu: sketch profiles raised from a face
# (Emboss) or sunk into it (Deboss); rolled round a cylinder (Wrap to Face),
# or projected straight onto it.
import json
import math
import tsr

cmd = tsr.run_command


def vol(body="Body1"):
    return tsr.mass_properties(body)["volume"]


def rect(x0, y0, x1, y1):   # point 0 is the sketch origin
    return {"points": [[0, 0], [x0, y0], [x1, y0], [x1, y1], [x0, y1]],
            "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                         {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}


def refused(why, **inputs):
    try:
        cmd("tsr.feature.emboss", **inputs)
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("accepted %r" % inputs)


# A 6 x 4 x 2 cm block; a 1 cm square sketched above it, embossed 2 mm on its top.
cmd("tsr.primitive.box", length=6.0, width=4.0, height=2.0)
v0 = vol()
cmd("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(rect(1, 1, 2, 2)))
refused("Face", faces="")
cmd("tsr.feature.emboss", faces="3,2,2", depth=0.2)
e = tsr.features()[-1]
assert e["name"].startswith("Emboss") and e["error"] == "", e
assert abs(vol() - v0 - 0.2) < 1e-6, vol() - v0
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[2] - 2.2) < 1e-6, hi
# Deboss instead: the square sunk 2 mm into the top.
tsr.edit_feature(e["id"], effect="Deboss")
assert abs(v0 - vol() - 0.2) < 1e-6, v0 - vol()
assert abs(tsr.bounding_box("Body1")[1][2] - 2.0) < 1e-6
# Deeper: 5 mm.
tsr.edit_feature(e["id"], depth=0.5)
assert abs(v0 - vol() - 0.5) < 1e-6, v0 - vol()

# A square off the face is explained.
cmd("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(rect(10, 10, 11, 11)))
refused("do not lie over", faces="3,2,2", depth=0.2)

# Text: letters raised from the top face.
cmd("tsr.sketch.create", plane="XY", offset=5.0,
    data=json.dumps({"points": [[0, 0], [3.5, 1]], "entities": [], "texts": [{"p": 1, "text": "TO", "h": 1.5}]}))
v1 = vol()
cmd("tsr.feature.emboss", faces="1,3,2", depth=0.1)
assert vol() - v1 > 0.05, vol() - v1

# --- On a cylinder: radius 2 cm, 6 cm tall, on the origin.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=4.0, height=6.0)
v0 = vol()
# A 2 cm wide, 1 cm tall square on the front plane (parallel to the axis).
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(rect(-1, 2, 1, 3)))
cmd("tsr.feature.emboss", faces="2,0,3", depth=0.1)
# Wrapped: 2 cm of arc is 1 rad round; the ring sector between r 2 and 2.1, 1 cm tall.
wrapped = 0.5 * (2.1 ** 2 - 2 ** 2) * 1.0
assert abs(vol() - v0 - wrapped) < 1e-5, (vol() - v0, wrapped)
e = tsr.features()[-1]
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[2] - 6) < 1e-6 and lo[2] > -1e-6
# Not wrapped: projected straight on, 2 cm of chord spans a little more of
# the round than 2 cm of arc.
tsr.edit_feature(e["id"], wrap=False)
projected = vol() - v0
n = 2000
exact = sum(2 * r * math.asin(1 / r) * 0.1 / n for r in (2 + (k + 0.5) * 0.1 / n for k in range(n)))
assert abs(projected - exact) < 1e-4, (projected, exact, wrapped)
tsr.edit_feature(e["id"], wrap=True, effect="Deboss")
sunk = 0.5 * (2 ** 2 - 1.9 ** 2) * 1.0
assert abs(v0 - vol() - sunk) < 1e-5, (v0 - vol(), sunk)

# Wrapping needs a sketch parallel to the axis.
cmd("tsr.sketch.create", plane="XY", offset=7.0, data=json.dumps(rect(-0.5, -0.5, 0.5, 0.5)))
refused("parallel to its axis", faces="2,0,3", depth=0.1)
print("emboss: OK")
