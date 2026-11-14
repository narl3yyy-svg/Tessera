# Delete (faces): a hole's face removed, the block closes over it. Split Face:
# a face cut by a plane, the body's shape unchanged with one more face.
import tsr

cmd = tsr.run_command


def mp():
    return tsr.mass_properties("Body1")


cmd("tsr.primitive.box", length=4.0, width=4.0, height=2.0)
cmd("tsr.primitive.cylinder", diameter=1.0, height=4.0, x=2.0, y=2.0, z=-1.0, operation="Cut")
assert abs(mp()["volume"] - (32 - 3.141592653589793 * 0.25 * 2)) < 1e-6, mp()
holed = mp()["faces"]
cmd("tsr.feature.deleteFaces", body="Body1", faces="2.5,2,1")       # the hole's wall
assert abs(mp()["volume"] - 32) < 1e-6 and mp()["faces"] == 6, (mp(), holed)
try:
    cmd("tsr.feature.deleteFaces", body="Body1", faces="")
    raise AssertionError("no faces accepted")
except RuntimeError as e:
    assert "face" in str(e).lower(), e

# Split the top face along x = 20 mm.
cmd("tsr.construct.offsetPlane", plane="YZ", distance=2.0)
cmd("tsr.feature.splitFace", body="Body1", faces="1,1,2", plane="Plane1")
assert abs(mp()["volume"] - 32) < 1e-6 and mp()["faces"] == 7, mp()
try:
    cmd("tsr.construct.offsetPlane", plane="YZ", distance=10.0)
    cmd("tsr.feature.splitFace", body="Body1", faces="3,3,0", plane="Plane2")
    raise AssertionError("a plane missing the face was accepted")
except RuntimeError as e:
    assert "does not cross" in str(e), e
print("delete / split face: OK")
