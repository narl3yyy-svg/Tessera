# Construction planes demo: a base plate, a sketch on an offset plane above
# it extruded down to the plate, and an angled plane.
import json
import math
import tsr

cmd = tsr.run_command
cmd("tsr.primitive.box", length=6.0, width=4.0, height=0.6, x=-3.0, y=-2.0)
cmd("tsr.construct.offsetPlane", plane="XY", distance=3.0)
ring = {"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 1.2}, {"type": "circle", "c": 0, "r": 0.7}]}
cmd("tsr.sketch.create", plane="Plane1", data=json.dumps(ring))
cmd("tsr.feature.extrude", distance=-2.4, profiles="0.95,0", operation="Join")
cmd("tsr.construct.planeAtAngle", plane="XZ", axis="Plane X axis", angle=math.radians(30))
print("features:", ", ".join(f["name"] for f in tsr.features()))
for f in tsr.features():
    assert f["error"] == "", f
