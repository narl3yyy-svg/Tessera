# Pipe along a bent path and a coil spring.
import json
import tsr

bent = {"points": [[0, 0], [0, 0], [0, 5], [3, 5], [3, 8], [6, 8], [6, 12]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "arc", "c": 3, "p": [4, 2], "r": 3},
                     {"type": "line", "p": [4, 5]}]}
tsr.run_command("tsr.sketch.create", plane="XZ", data=json.dumps(bent))
tsr.run_command("tsr.feature.pipe", size=1.0, hollow="Yes", thickness=0.15)
tsr.run_command("tsr.feature.coil", x=-8.0, diameter=4.0, revolutions=6.0, height=8.0, size=0.5)
