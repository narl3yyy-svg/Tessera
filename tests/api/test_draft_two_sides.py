# Draft Direction Two Sides / Symmetric, as in the familiar tool: each side
# of the neutral plane tapers in towards its own pull direction (a mould part
# is widest at its parting line).
import math
import tsr

cmd = tsr.run_command


def vol():
    return tsr.mass_properties("Body1")["volume"]


# A 2 cm cube; the neutral plane through its middle (z = 1).
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
v0 = vol()
cmd("tsr.construct.offsetPlane", plane="XY", distance=1.0)
plane = tsr.features()[-1]["name"]
a = math.radians(5)
# Symmetric on the +X side: each 1 cm half loses 0.5 * 1^2 * tan(a) * 2 cm.
cmd("tsr.feature.draft", body="Body1", faces="2,1,1.5", plane=plane, sides="Symmetric", angle=a)
d = tsr.features()[-1]
assert d["error"] == "", d
half = 0.5 * 1.0 ** 2 * math.tan(a) * 2.0
assert abs(v0 - vol() - 2 * half) < 1e-9, (v0 - vol(), 2 * half)
p = tsr.mass_properties("Body1")
assert p["faces"] == 7, p                              # the side is two faces now
# Two Sides: 5 deg above, 10 deg below.
b = math.radians(10)
tsr.edit_feature(d["id"], sides="Two Sides", angle2=b)
want = half + 0.5 * 1.0 ** 2 * math.tan(b) * 2.0
assert abs(v0 - vol() - want) < 1e-9, (v0 - vol(), want)
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[0] - 2) < 1e-9, hi                       # widest at the plane
# One Side, as before: the whole face tilts about the plane (in above it,
# out below it: no volume change about the middle).
tsr.edit_feature(d["id"], sides="One Side")
assert tsr.mass_properties("Body1")["faces"] == 6
assert abs(vol() - v0) < 1e-9
print("draft two sides: OK")
