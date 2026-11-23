# A 4 cm line sketched along X on XY.
import json
import tsr
line = {"points": [[0, 0], [0, 0], [4, 0]], "entities": [{"type": "line", "p": [1, 2]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(line))
