# Replace Face, as in the familiar Modify menu: source faces give way to a
# target surface (a plane or a face of any body, extended past its edges):
# the body grows out to it, or is trimmed back.
import math
import tsr

cmd = tsr.run_command


def vol(body="Body1"):
    return tsr.mass_properties(body)["volume"]


cmd("tsr.primitive.box", length=4.0, width=3.0, height=2.0)           # top at z = 2
cmd("tsr.construct.offsetPlane", plane="XY", distance=3.0)
up = tsr.features()[-1]["name"]
cmd("tsr.construct.offsetPlane", plane="XY", distance=1.0)
down = tsr.features()[-1]["name"]
# Grown up to z = 3.
cmd("tsr.feature.replaceFace", body="Body1", faces="2,1.5,2", target=up)
r = tsr.features()[-1]
assert r["error"] == "", r
assert abs(vol() - 36) < 1e-9, vol()
assert tsr.mass_properties("Body1")["faces"] == 6
# Trimmed back to z = 1.
tsr.edit_feature(r["id"], target=down)
assert abs(vol() - 12) < 1e-9, vol()
tsr.delete_feature(r["id"])

# Up to a cylinder's underside: a cylinder 6 cm across lying along X above,
# its axis at y = 1.5, z = 6 (underside at z = 3 over the block's middle).
cmd("tsr.primitive.cylinder", diameter=6.0, height=4.0, axis="X", y=1.5, z=6.0)
cmd("tsr.feature.replaceFace", body="Body1", faces="2,1.5,2", target="face:Body2|2,1.5,3")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
n = 2000
want = 4.0 * sum((6 - math.sqrt(9 - (y - 1.5) ** 2)) * 3.0 / n for y in ((k + 0.5) * 3.0 / n for k in range(n)))
assert abs(vol() - want) < 1e-4, (vol(), want)
assert abs(vol("Body2") - math.pi * 9 * 4) < 1e-6          # the target body stays

# Missing picks are explained.
for bad in [dict(faces="2,1.5,2"), dict(target=up)]:
    try:
        cmd("tsr.feature.replaceFace", body="Body1", **bad)
    except RuntimeError as e:
        assert "Faces" in str(e), e
    else:
        raise AssertionError("accepted %r" % bad)
print("replace face: OK")
