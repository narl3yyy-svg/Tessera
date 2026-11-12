# A 40 x 30 mm rectangle sketch, and a box beside it whose top is at 25 mm.
import json
import tsr
r = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                  {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.5, x=6.0)
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(r))
