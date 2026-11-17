# Two 2 cm cubes side by side, and a slot sketched across both their tops.
import json
import tsr
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0, x=3.0)
r = {"points": [[0, 0], [0.5, 0.5], [4.5, 0.5], [4.5, 1.5], [0.5, 1.5]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                  {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
tsr.run_command("tsr.sketch.create", plane="XY", offset=2.0, data=json.dumps(r))
