# A 40 x 30 mm rectangle sketch on XY and a user parameter "width" = 20 mm.
import json
import tsr
r = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                  {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(r))
tsr.run_command("tsr.parameters.addUser", name="width", expression="20 mm")
