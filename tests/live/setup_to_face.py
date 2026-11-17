# A cylinder lying along X (4 cm across, axis 5 cm up, x 0 to 10 cm) and a
# 1 cm disc sketched on XY under it.
import json
import tsr
tsr.run_command("tsr.primitive.cylinder", diameter=4.0, height=10.0, axis="X", z=5.0)
tsr.run_command("tsr.sketch.create", plane="XY",
                data=json.dumps({"points": [[0, 0], [5, 0]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}))
