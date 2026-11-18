# Move/Copy as the familiar Free Move: X / Y / Z distances and X / Y / Z
# angles (turned about the body's centre, X then Y then Z, then moved);
# designs made with the old Rotate about / Angle keep working.
import math
import tsr

cmd = tsr.run_command


def box(name="Body1"):
    lo, hi = tsr.bounding_box(name)
    return [round(v, 6) for v in lo + hi]


def near(a, b):
    assert all(abs(x - y) < 1e-6 for x, y in zip(a, b)), (a, b)


cmd("tsr.primitive.box", length=2.0, width=1.0, height=1.0)            # centre (1, 0.5, 0.5)
cmd("tsr.feature.move", zAngle=math.pi / 2)
m = tsr.features()[-1]
assert m["error"] == "", m
near(box(), [0.5, -0.5, 0, 1.5, 1.5, 1])                               # 2 long along Y now, about the centre
tsr.edit_feature(m["id"], x=3.0, z=-1.0)
near(box(), [3.5, -0.5, -1, 4.5, 1.5, 0])
# X then Z: the long side ends up along Y still; a turn about Y first lays it along Z.
tsr.edit_feature(m["id"], x=0.0, z=0.0, zAngle=0.0, yAngle=math.pi / 2)
near(box(), [0.5, 0, -0.5, 1.5, 1, 1.5])
tsr.edit_feature(m["id"], xAngle=math.pi / 2, yAngle=0.0)
near(box(), [0, 0, 0, 2, 1, 1])                                        # 1 x 1 section: unchanged box
# A copy keeps the original.
tsr.edit_feature(m["id"], xAngle=0.0, y=2.0, copy=True)
near(box("Body1"), [0, 0, 0, 2, 1, 1])
near(box("Body2"), [0, 2, 0, 2, 3, 1])

# Made before: Rotate about X by 90 degrees.
tsr.new_document()
cmd("tsr.primitive.box", length=1.0, width=2.0, height=1.0)            # centre (0.5, 1, 0.5)
cmd("tsr.feature.move", axis="X", angle=math.pi / 2)
near(box(), [0, 0.5, -0.5, 1, 1.5, 1.5])
print("move triad: OK")
