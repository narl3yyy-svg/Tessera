# Silhouette Split, as in the familiar Modify menu: round faces split where
# their outline lies seen along a direction; or the body cut in two there.
import math
import tsr

cmd = tsr.run_command


def faces(body="Body1"):
    return tsr.mass_properties(body)["faces"]


# A cylinder lying along X (radius 1, axis at z = 1), seen from above (XY):
# its round side splits along its widest line, top half and bottom half.
cmd("tsr.primitive.cylinder", diameter=2.0, height=4.0, axis="X", z=1.0)
v0 = tsr.mass_properties("Body1")["volume"]
n0 = faces()
cmd("tsr.feature.silhouetteSplit", body="Body1", faces="2,0,2", direction="XY")
s = tsr.features()[-1]
assert s["error"] == "", s
assert faces() > n0 and abs(tsr.mass_properties("Body1")["volume"] - v0) < 1e-9, (faces(), n0)
# Split Solid Body: two half cylinders, one above z = 1 and one below.
tsr.edit_feature(s["id"], operation="Split Solid Body")
lo1, hi1 = tsr.bounding_box("Body1")
lo2, hi2 = tsr.bounding_box("Body2")
assert sorted([round(lo1[2], 6), round(lo2[2], 6)]) == [0, 1] and sorted([round(hi1[2], 6), round(hi2[2], 6)]) == [1, 2]
half = math.pi * 4 / 2
for b in ("Body1", "Body2"):
    assert abs(tsr.mass_properties(b)["volume"] - half) < 1e-9

# A sphere seen from the front (XZ): split along its outline in the XZ plane.
tsr.new_document()
cmd("tsr.primitive.sphere", diameter=4.0)
cmd("tsr.feature.silhouetteSplit", body="Body1", faces="0,0,2", direction="XZ", operation="Split Solid Body")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert abs(tsr.mass_properties("Body2")["volume"] - 4 / 3 * math.pi * 8 / 2) < 1e-6

# Seen straight along a cylinder's axis, or on a flat face: explained.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=2.0, height=2.0)
for faces_, why in [("1,0,1", "along the cylinder's axis"), ("0,0,2", "cylinders and spheres")]:
    try:
        cmd("tsr.feature.silhouetteSplit", body="Body1", faces=faces_, direction="XY")
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("split %s" % faces_)
print("silhouette split: OK")
