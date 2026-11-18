# A 4 x 3 x 2 cm block and a line sketched above it, across its top.
import json
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
line = {"points": [[0, 0], [1, -1], [1, 4]], "entities": [{"type": "line", "p": [1, 2]}]}
tsr.run_command("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(line))
