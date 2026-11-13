# Hole tap types, as in the familiar tool: Clearance (ISO 273 sizes) and
# Tapped (drilled at the ISO 68-1 minor diameter; cosmetic or modeled thread).
import math
import adsk.core
import adsk.fusion
import tsr

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent


def vol(i):
    return root.bRepBodies.item(i).volume


def hole(body, x, **kw):
    tsr.run_command("tsr.feature.hole", placement="On Face", points="%g,1.5,2" % x, target=body, extent="All", **kw)
    f = tsr.features()[-1]
    assert f["error"] == "", f


# A 3 x 3 x 2 cm block per case; holes straight down through it.
for i in range(4):
    tsr.run_command("tsr.primitive.box", length=3.0, width=3.0, height=2.0, x=5.0 * i)
names = [root.bRepBodies.item(i).name for i in range(4)]
v0 = vol(0)

# Clearance M6, normal fit: 6.6 mm through 20 mm.
hole(names[0], 1.5, tapType="Clearance", size="M6", fit="Normal")
assert abs((v0 - vol(0)) - math.pi * 0.33 ** 2 * 2) < 1e-6, v0 - vol(0)
# Loose fit: 7.0 mm.
hole(names[1], 6.5, tapType="Clearance", size="M6", fit="Loose")
assert abs((v0 - vol(1)) - math.pi * 0.35 ** 2 * 2) < 1e-6, v0 - vol(1)
# Tapped M6 (pitch 1), cosmetic: drilled at D1 = 6 - 1.08253 = 4.91747 mm.
hole(names[2], 11.5, tapType="Tapped", size="M6")
r1 = (6 - 1.08253) / 20
assert abs((v0 - vol(2)) - math.pi * r1 ** 2 * 2) < 1e-6, v0 - vol(2)
# Tapped and modeled: the thread takes more, but never past the major diameter.
hole(names[3], 16.5, tapType="Tapped", size="M6", threadModeled=True)
removed = v0 - vol(3)
assert math.pi * r1 ** 2 * 2 + 0.02 < removed < math.pi * 0.3 ** 2 * 2 + 0.02, removed
print("tapped holes: OK", round(removed, 5))
