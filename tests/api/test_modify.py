# Shell, Combine, Split Body, Move/Copy, Mirror, Scale and Remove.
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
def vol(i=0):
    return root.bRepBodies.item(i).volume
cmd = tsr.run_command

# Shell a 20 mm cube, open at the top, 2 mm walls inside.
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.feature.shell", faces="1,1,2", thickness=0.2)
assert abs(vol() - (8 - 1.6 * 1.6 * 1.8)) < 1e-6, vol()
f = tsr.features()
assert "@" in f[-1]["inputs"]["faces"], f[-1]          # signature recorded
# Taller box: the shell is replayed on the new top face.
tsr.edit_feature(f[0]["id"], height=3.0)
assert tsr.features()[-1]["error"] == "", tsr.features()
assert abs(vol() - (12 - 1.6 * 1.6 * 2.8)) < 1e-6, vol()

# Closed hollow (no open faces).
tsr.new_document()
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.feature.shell", thickness=0.2)
assert abs(vol() - (8 - 1.6 ** 3)) < 1e-6, vol()

# Combine: cut a cylinder out of a box, keeping nothing of the tool.
tsr.new_document()
cmd("tsr.primitive.box", length=2.0, width=2.0, height=1.0)
cmd("tsr.primitive.cylinder", diameter=1.0, height=1.0, x=1.0, y=1.0)
assert root.bRepBodies.count == 2
cmd("tsr.feature.combine", target="Body1", tools="Body2", operation="Cut")
assert root.bRepBodies.count == 1
assert abs(vol() - (4 - math.pi * 0.25)) < 1e-6

# Split the result in half with the YZ plane moved to x = 10 mm.
cmd("tsr.feature.splitBody", plane="YZ", offset=1.0)
assert root.bRepBodies.count == 2
assert abs(vol(0) + vol(1) - (4 - math.pi * 0.25)) < 1e-6
try:
    cmd("tsr.feature.splitBody", body="Body1", plane="XY", offset=5.0)
except RuntimeError as e:
    assert "does not cross" in str(e), e
else:
    raise AssertionError("split by a plane that misses accepted")

# Move/Copy, Mirror, Scale, Remove.
tsr.new_document()
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0)
cmd("tsr.feature.move", x=3.0, copy=True)
assert root.bRepBodies.count == 2
cmd("tsr.feature.mirror", body="Body2", plane="YZ")           # mirror x=3..4 to x=-4..-3
assert root.bRepBodies.count == 3
cmd("tsr.feature.scale", body="Body3", factor=2.0)
assert abs(vol(2) - 8.0) < 1e-6
cmd("tsr.feature.remove", body="Body1")
assert root.bRepBodies.count == 2
assert tsr.undo() and root.bRepBodies.count == 3
names = [x["name"] for x in tsr.features()]
assert names == ["Box1", "Move1", "Mirror1", "Scale1"], names   # Remove1 was undone
print("api modify: OK")
