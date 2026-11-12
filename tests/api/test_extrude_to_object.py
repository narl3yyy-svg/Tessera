# Extrude To Object: up to a parallel plane, a tilted plane, and a body face.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command
rect = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                     {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}

cmd("tsr.sketch.create", plane="XY", data=json.dumps(rect))
cmd("tsr.construct.offsetPlane", plane="XY", distance=2.5)                       # Plane1, z = 25 mm
cmd("tsr.feature.extrude", sketch="Sketch1", extent="To Object", toObject="Plane1")
assert abs(root.bRepBodies.item(0).volume - 12 * 2.5) < 1e-6, root.bRepBodies.item(0).volume

# A plane tilted 5 degrees: the top is slanted, volume = area x mean height.
cmd("tsr.construct.offsetPlane", plane="XY", distance=0.5)                       # Plane2, z = 5 mm
cmd("tsr.construct.planeAtAngle", plane="Plane2", axis="Plane X axis", angle=math.radians(5))   # Plane3
cmd("tsr.feature.extrude", sketch="Sketch1", extent="To Object", toObject="Plane3", operation="New Body")
v = root.bRepBodies.item(1).volume
slope = 1.5 * math.tan(math.radians(5))
assert min(abs(v - 12 * (0.5 + slope)), abs(v - 12 * (0.5 - slope))) < 1e-4, v

# Up to the top face of a box (a picked flat face gives a custom plane).
cmd("tsr.primitive.box", length=2.0, width=2.0, height=4.0, x=10.0)
sk2 = {"points": [[0, 0], [12, 0], [12, 1]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(sk2))
face_plane = "custom:0,0,4,0,0,1,1,0,0"
cmd("tsr.feature.extrude", extent="To Object", toObject=face_plane, operation="New Body")
assert abs(root.bRepBodies.item(3).volume - math.pi * 0.25 * 4) < 1e-4, root.bRepBodies.item(3).volume

try:
    cmd("tsr.feature.extrude", sketch="Sketch1", extent="To Object", toObject="XY")   # the profile's own plane
except RuntimeError as e:
    assert "already lies" in str(e), e
else:
    raise AssertionError("extruded to its own plane")
print("api extrude to object: OK")
