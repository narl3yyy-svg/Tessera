# Two separate rectangles in one sketch on XY: 40 x 30 mm at the origin and
# 20 x 20 mm at x = 60 mm. Two profiles, so Extrude picks neither by itself.
import json
import tsr
r = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3], [6, 0], [8, 0], [8, 2], [6, 2]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                  {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]},
                  {"type": "line", "p": [5, 6]}, {"type": "line", "p": [6, 7]},
                  {"type": "line", "p": [7, 8]}, {"type": "line", "p": [8, 5]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(r))
