# Thicken: faces given a thickness as a new body (one side, inward,
# symmetric), and joined to the body they came from.
import math
import tsr

cmd = tsr.run_command


def vol(name):
    return tsr.mass_properties(name)["volume"]


cmd("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
# The top face (40 x 30 mm) 5 mm thick, outward: a 4 x 3 x 0.5 slab on top.
cmd("tsr.feature.thicken", body="Body1", faces="2,1.5,2", thickness=0.5, operation="New Body")
assert abs(vol("Body2") - 6.0) < 1e-6, vol("Body2")
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[2] - 2.0) < 1e-6 and abs(hi[2] - 2.5) < 1e-6, (lo, hi)
# Symmetric: half above, half below.
cmd("tsr.feature.thicken", body="Body1", faces="2,1.5,2", thickness=0.5, direction="Symmetric", operation="New Body")
lo, hi = tsr.bounding_box("Body3")
assert abs(lo[2] - 1.75) < 1e-6 and abs(hi[2] - 2.25) < 1e-6, (lo, hi)
# A cylinder's side 2 mm thick, joined to it: a tube's worth of material added.
cmd("tsr.primitive.cylinder", diameter=2.0, height=1.0, x=10.0)
before = vol("Body4")
cmd("tsr.feature.thicken", body="Body4", faces="11,0,0.5", thickness=0.2, operation="Join", target="Body4")
assert abs(vol("Body4") - (before + math.pi * (1.2 ** 2 - 1) * 1.0)) < 1e-6, vol("Body4")
try:
    cmd("tsr.feature.thicken", body="Body1", faces="2,1.5,2", thickness=0.0)
    raise AssertionError("zero thickness accepted")
except RuntimeError as e:
    assert "zero" in str(e), e
print("thicken: OK")
