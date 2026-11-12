# A 40 x 20 x 10 mm block with one joined stud (an Extrude) on top.
import json
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=2.0, height=1.0)
bb = tsr.bounding_box("Body1")
sk = {"points": [[0, 0], [bb[0][0] + 0.5, bb[0][1] + 0.5]], "entities": [{"type": "circle", "c": 1, "r": 0.25}]}
tsr.run_command("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(sk))
tsr.run_command("tsr.feature.extrude", distance=0.5, operation="Join")
