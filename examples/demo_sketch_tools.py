# Sketch Fillet, Offset and Spline: a plate outline with a rounded corner, its
# 5 mm offset, and a closed spline. Open it with --edit-sketch Sketch1.
import json
import tsr

outline = {
    "points": [[0, 0], [6, 0], [6, 4], [0, 4]],
    "entities": [{"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
                 {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]}],
    "constraints": [{"type": "horizontal", "e": [0]}, {"type": "vertical", "e": [1]},
                    {"type": "horizontal", "e": [2]}, {"type": "vertical", "e": [3]}],
}
data = tsr.sketch_fillet(json.dumps(outline), 1, 2, 1.0)
data = tsr.sketch_offset(data, 0, 0.5)
sk = json.loads(data)
base = len(sk["points"])
sk["points"] += [[1.5, 1.2], [3.2, 0.9], [4.2, 2.2], [2.6, 3.0], [1.4, 2.4]]
sk["entities"].append({"type": "spline", "fit": [base, base + 1, base + 2, base + 3, base + 4, base]})
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(sk))
