# A disc 10 cm across, 1 cm thick, with a round pocket (1 cm across, 2 mm
# deep) 3 cm from its centre.
import json
import tsr
tsr.run_command("tsr.primitive.cylinder", diameter=10.0, height=1.0)
tsr.run_command("tsr.sketch.create", plane="XY", offset=1.0,
                data=json.dumps({"points": [[0, 0], [3, 0]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}))
tsr.run_command("tsr.feature.extrude", distance=-0.2, operation="Cut", target="Body1")
