# Modeled ISO metric threads: on a shaft, in a hole, part length, left hand.
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command

def vol(i):
    return root.bRepBodies.item(i).volume

# M10 shaft, 20 mm long: the coarse pitch (1.5 mm) is chosen from the diameter.
cmd("tsr.primitive.cylinder", diameter=1.0, height=2.0)
v0 = vol(0)
cmd("tsr.feature.thread", body="Body1", faces="0.5,0,1", modeled=True)
f = tsr.features()[-1]
assert f["error"] == "", f
removed = v0 - vol(0)
assert 0.1 < removed < 0.3, removed

# A threaded hole (internal): material is removed outward from the hole.
cmd("tsr.primitive.box", length=3.0, width=3.0, height=2.0, x=5.0)
cmd("tsr.primitive.cylinder", diameter=1.0, height=2.0, x=6.5, y=1.5, operation="Cut", target="Body2")
v1 = vol(1)
cmd("tsr.feature.thread", body="Body2", faces="7,1.5,1", modeled=True)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert 0.1 < v1 - vol(1) < 0.3, v1 - vol(1)

# Part length, left hand, explicit fine pitch.
cmd("tsr.primitive.cylinder", diameter=1.0, height=2.0, x=12.0)
v2 = vol(2)
cmd("tsr.feature.thread", body="Body3", faces="12.5,0,1", modeled=True, pitch=0.1, fullLength="No", length=1.0, offset=0.5,
    hand="Left hand")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert 0.02 < v2 - vol(2) < removed, v2 - vol(2)

try:
    cmd("tsr.feature.thread", body="Body2", faces="5,1,1")   # a flat side of the box
except RuntimeError as e:
    assert "cylindrical" in str(e), e
else:
    raise AssertionError("threaded a flat face")
# Cosmetic (the default, as in the familiar tool): recorded, no geometry.
before = vol(2)
cmd("tsr.feature.thread", body="Body3", faces="12.5,0,1")
assert tsr.features()[-1]["error"] == "" and abs(vol(2) - before) < 1e-12, vol(2)
tsr.undo()
print("api thread: OK")
