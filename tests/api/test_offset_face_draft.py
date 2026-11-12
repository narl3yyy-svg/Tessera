# Offset Face, Draft, and Press Pull on curved faces.
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command

def vol(i):
    return root.bRepBodies.item(i).volume

# Offset the top face of a 2 x 2 x 2 box up by 0.5.
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.feature.offsetFace", body="Body1", faces="1,1,2", distance=0.5)
assert abs(vol(0) - 10.0) < 1e-6, vol(0)

# Offset a cylinder's round face out by 0.25 (diameter 2 -> 2.5).
cmd("tsr.primitive.cylinder", diameter=2.0, height=1.0, x=10.0)
cmd("tsr.feature.offsetFace", body="Body2", faces="11,0,0.5", distance=0.25)
assert abs(vol(1) - math.pi * 1.25 ** 2) < 1e-4, vol(1)

# Press Pull on a curved face offsets it too.
cmd("tsr.feature.pressPull", body="Body2", faces="11.25,0,0.5", distance=-0.25)
assert abs(vol(1) - math.pi) < 1e-4, vol(1)

# Draft the +X side of a fresh box by 5 deg about the XY plane (pull +Z).
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0, y=10.0)
v0 = vol(2)
cmd("tsr.feature.draft", body="Body3", faces="2,11,1", plane="XY", angle=math.radians(5))
f = tsr.features()[-1]
assert f["error"] == "", f
change = abs(vol(2) - v0)
expected = 0.5 * 2.0 ** 2 * math.tan(math.radians(5)) * 2.0
assert abs(change - expected) < 1e-3, (change, expected)

try:
    cmd("tsr.feature.draft", body="Body3", faces="1,11,2", plane="XY", angle=math.radians(5))   # top face: parallel to the plane
except RuntimeError:
    pass
else:
    raise AssertionError("drafted a face parallel to the neutral plane")
print("api offset face and draft: OK")
