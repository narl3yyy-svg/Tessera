# Construct axes and points from body geometry and planes, and using a
# construction axis in Circular Pattern and Revolve.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command
cmd("tsr.primitive.box", length=2.0, width=2.0, height=1.0)                      # Body1
cmd("tsr.primitive.cylinder", diameter=1.0, height=2.0, x=5.0, y=1.0)            # Body2, axis x=5,y=1


def near(a, b, tol=1e-6):
    return all(abs(x - y) < tol for x, y in zip(a, b))


cmd("tsr.construct.axisCylinder", body="Body2", faces="5.5,1,1")
cmd("tsr.construct.axisEdge", body="Body1", edges="1,0,0")                      # bottom front edge, along X
cmd("tsr.construct.axisTwoPoints", body="Body1", vertices="0,0,0;2,2,1")
cmd("tsr.construct.axisTwoPlanes", plane="XZ", plane2="YZ")                     # the Z axis
cmd("tsr.construct.pointVertex", body="Body1", vertices="2,2,1")
cmd("tsr.construct.pointTwoEdges", body="Body1", edges="1,0,0;0,1,0")           # meet at the origin corner
cmd("tsr.construct.pointThreePlanes", plane="XY", plane2="XZ", plane3="YZ")
cmd("tsr.construct.pointCenter", body="Body2", edges="5.5,1,2")                  # top circle of the cylinder
cmd("tsr.construct.offsetPlane", plane="XY", distance=0.5)                        # Plane1
cmd("tsr.construct.pointEdgePlane", body="Body1", edges="0,0,0.5", plane="Plane1")
f = tsr.features()
assert all(x["error"] == "" for x in f), [x for x in f if x["error"]]
names = [x["name"] for x in f]
assert names[2:6] == ["Axis1", "Axis2", "Axis3", "Axis4"], names
assert names[6:10] == ["Point1", "Point2", "Point3", "Point4"], names
assert names[11] == "Point5", names

# Wrong picks are explained.
for bad in [dict(id="tsr.construct.axisCylinder", body="Body1", faces="1,1,1"),
            dict(id="tsr.construct.pointThreePlanes", plane="XY", plane2="XY", plane3="YZ"),
            dict(id="tsr.construct.axisTwoPlanes", plane="XY", plane2="Plane1")]:
    try:
        cmd(bad.pop("id"), **bad)
    except RuntimeError:
        pass
    else:
        raise AssertionError("accepted %r" % bad)

# Circular pattern of the box about the cylinder's axis: 4 copies in all.
cmd("tsr.feature.circularPattern", patternType="Bodies", body="Body1", axis="Axis1", quantity=4, result="New Bodies")
assert root.bRepBodies.count == 5, root.bRepBodies.count
assert tsr.features()[-1]["error"] == ""

# Revolve a 1 x 1 square (x 3..4) about Axis4 (the Z axis): a ring of mean radius 3.5.
sq = {"points": [[0, 0], [3, 0], [4, 0], [4, 1], [3, 1]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                   {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(sq))
cmd("tsr.feature.revolve", axis="Construction axis", constructionAxis="Axis4", angle=2 * math.pi)
v = root.bRepBodies.item(root.bRepBodies.count - 1).volume
assert abs(v - 2 * math.pi * 3.5 * 1.0) < 1e-6, v
print("api construct axes and points: OK")
