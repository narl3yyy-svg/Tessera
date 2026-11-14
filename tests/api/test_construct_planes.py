# Plane Through Three Points (body vertices) and Tangent Plane (on a
# cylinder's side, turned round it from a reference plane's normal).
import json
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command


def vols():
    return sorted(round(root.bRepBodies.item(i).volume, 9) for i in range(root.bRepBodies.count))


# A 20 mm cube cut corner to corner by the plane through three of its vertices.
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
cmd("tsr.construct.planeThreePoints", body="Body1", vertices="0,0,0;2,0,0;0,2,2")
assert [f["name"] for f in tsr.features()][-1] == "Plane1"
cmd("tsr.feature.splitBody", body="Body1", plane="Plane1")
assert vols() == [4.0, 4.0], vols()
try:
    cmd("tsr.construct.planeThreePoints", body="Body1", vertices="0,0,0;2,0,0")
    raise AssertionError("two vertices accepted")
except RuntimeError as e:
    assert "three" in str(e), e

# A cylinder of radius 10 mm: tangent planes facing -Y (the XZ plane's
# normal) and, turned 90 degrees, +X. A disc sketched on each and extruded
# 1 mm outward sits just outside the cylinder there.
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=2.0, height=2.0)
disc = {"points": [[0, 0], [0, 0]], "entities": [{"type": "circle", "c": 1, "r": 0.2}]}
for name, angle in (("Plane1", 0.0), ("Plane2", 1.5707963267948966)):
    cmd("tsr.construct.tangentPlane", body="Body1", faces="1,0,1", plane="XZ", angle=angle)
    cmd("tsr.sketch.create", plane=name, data=json.dumps(disc))
    cmd("tsr.feature.extrude", distance=0.1, operation="New Body")
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[1] + 1.1) < 1e-9 and abs(hi[1] + 1.0) < 1e-9 and abs(lo[2] - 0.8) < 1e-9, (lo, hi)
lo, hi = tsr.bounding_box("Body3")
assert abs(hi[0] - 1.1) < 1e-9 and abs(lo[0] - 1.0) < 1e-9, (lo, hi)
try:
    cmd("tsr.construct.tangentPlane", body="Body1", faces="0,0,2", plane="XZ")
    raise AssertionError("a flat face accepted")
except RuntimeError as e:
    assert "cylindrical" in str(e), e
print("construct planes: OK")

# --- Plane Through Two Edges, Plane Tangent to Face at Point, Axis
# Perpendicular at Point, on a 20 mm cube.
tsr.new_document()
cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
# The top front edge and the bottom back edge: the diagonal plane again.
cmd("tsr.construct.planeTwoEdges", body="Body1", edges="1,0,2;1,2,0")
cmd("tsr.feature.splitBody", body="Body1", plane="Plane1")
assert vols() == [4.0, 4.0], vols()
try:
    cmd("tsr.construct.planeTwoEdges", body="Body2", edges="1,0,2;0,1,0")
except RuntimeError as e:
    assert "plane" in str(e) or "Edges" in str(e), e
tsr.new_document()
cmd("tsr.primitive.cylinder", diameter=2.0, height=2.0)
# A plane touching the side at a top-rim vertex: a disc on it sits outside.
cmd("tsr.construct.planeFacePoint", body="Body1", faces="1,0,1", vertices="1,0,2")
cmd("tsr.sketch.create", plane="Plane1", data=json.dumps(disc))
cmd("tsr.feature.extrude", distance=0.1, operation="New Body")
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[0] - 1.0) < 1e-6 and abs(hi[0] - 1.1) < 1e-6, (lo, hi)
# The axis square to the top face through the same vertex: straight up.
cmd("tsr.construct.axisNormalAtPoint", body="Body1", faces="0,0,2", vertices="1,0,2")
assert [f["name"] for f in tsr.features()][-1] == "Axis1"
print("construct planes 2: OK")
