# Hole (simple, counterbore, countersink, through all) and patterns.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command
def vol(i=0):
    return root.bRepBodies.item(i).volume

# 40 x 40 x 10 mm plate; a sketch on its top face with two hole points.
cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)
pts = {"points": [[0, 0], [1, 1], [3, 3]]}
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(pts))
cmd("tsr.feature.hole", placement="Sketch Points", diameter=0.5, extent="All")
assert abs(vol() - (16 - 2 * math.pi * 0.0625 * 1.0)) < 1e-6, vol()
tsr.undo()
cmd("tsr.feature.hole", placement="Sketch Points", diameter=0.5, depth=0.5, drillPoint="Flat")
assert abs(vol() - (16 - 2 * math.pi * 0.0625 * 0.5)) < 1e-6, vol()
tsr.undo()
# By default blind holes end in a 118 degree drill point below the 5 mm depth.
cmd("tsr.feature.hole", placement="Sketch Points", diameter=0.5, depth=0.5)
tip = math.pi * 0.0625 * (0.25 / math.tan(math.radians(59))) / 3
assert abs(vol() - (16 - 2 * (math.pi * 0.0625 * 0.5 + tip))) < 1e-6, vol()
tsr.undo()
cmd("tsr.feature.hole", placement="Sketch Points", holeType="Counterbore", diameter=0.5, extent="All", cboreDiameter=1.0, cboreDepth=0.2)
expected = 16 - 2 * (math.pi * 0.0625 * 0.8 + math.pi * 0.25 * 0.2)
assert abs(vol() - expected) < 1e-6, (vol(), expected)
tsr.undo()
cmd("tsr.feature.hole", placement="Sketch Points", holeType="Countersink", diameter=0.5, extent="All", csinkDiameter=1.0)
assert vol() < 16 - 2 * math.pi * 0.0625
try:
    cmd("tsr.feature.hole", placement="Sketch Points", holeType="Counterbore", diameter=0.5, cboreDiameter=0.3)
except RuntimeError as e:
    assert "larger" in str(e), e
else:
    raise AssertionError("small counterbore accepted")

# Rectangular pattern 3 x 2 of a 1 cm cube, as new bodies and joined.
tsr.new_document()
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0)
cmd("tsr.feature.rectangularPattern", patternType="Bodies", distanceType="Spacing", quantity1=3, distance1=2.0,
    quantity2=2, distance2=2.0, result="New Bodies")
assert root.bRepBodies.count == 6
tsr.undo()
cmd("tsr.feature.rectangularPattern", patternType="Bodies", quantity1=3, distance1=2.0)   # extent: touching cubes join
assert root.bRepBodies.count == 1 and abs(vol() - 3.0) < 1e-6

# Circular pattern of 6 around Z.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=0.5, height=1.0, x=3.0)
cmd("tsr.feature.circularPattern", patternType="Bodies", quantity=6, result="New Bodies")
assert root.bRepBodies.count == 6
total = sum(root.bRepBodies.item(i).volume for i in range(6))
assert abs(total - 6 * math.pi * 0.0625) < 1e-6
# On Face (the default, as in the familiar tool): click a spot on any face;
# the hole goes in along the face normal there. On a cylinder that is radial.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=5.0, height=4.0)          # r 25 mm, axis Z
full = vol()
cmd("tsr.feature.hole", points="2.5,0,2", diameter=0.6, depth=1.0)   # 6 mm, 10 mm deep, 118 deg point
a = vol()
tsr.undo()
cmd("tsr.feature.hole", points="0,2.6,2", diameter=0.6, depth=1.0)   # a point just off the surface snaps to it
b = vol()
# Same hole by symmetry (volumes integrate over curved intersections: to 1e-3 of the hole).
assert full - a > 0.2 and abs(a - b) < 1e-3 * (full - a), (full, a, b)
tsr.undo()
# On a flat face it is the same as a sketch point there.
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)
cmd("tsr.feature.hole", points="1,1,1", diameter=0.5, extent="All")
assert abs(vol() - (16 - math.pi * 0.0625)) < 1e-6, vol()
try:
    cmd("tsr.feature.hole", diameter=0.5)
except RuntimeError as e:
    assert "Positions" in str(e), e
else:
    raise AssertionError("a hole without a position accepted")
print("api hole/pattern: OK")
