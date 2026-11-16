# A 6 x 4 x 2 cm block, and a 1 cm square sketched on XY under it.
import json
import tsr
tsr.run_command("tsr.primitive.box", length=6.0, width=4.0, height=2.0)
square = {"points": [[0, 0], [1, 1], [2, 1], [2, 2], [1, 2]],
          "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                       {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(square))
