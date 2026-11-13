# A 20 x 20 mm square on XY, 10 to 30 mm out from the sketch's Y axis.
import json
import tsr
r = {"points": [[0, 0], [1, 0], [3, 0], [3, 2], [1, 2]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                  {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(r))
