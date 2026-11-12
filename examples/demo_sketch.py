# Sketch + extrude demo for screenshots: a flanged plate with a slot-like
# pair of holes, drawn and constrained as sketches, then extruded.
import json
import tsr

plate = {
    "points": [[0, 0], [6, 0], [6, 4], [0, 4], [1.5, 2], [4.5, 2], [3, 2]],
    "entities": [
        {"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
        {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]},
        {"type": "circle", "c": 4, "r": 0.5}, {"type": "circle", "c": 5, "r": 0.5},
        {"type": "circle", "c": 6, "r": 1.0, "construction": True},
    ],
    "constraints": [
        {"type": "horizontal", "e": [0]}, {"type": "horizontal", "e": [2]},
        {"type": "vertical", "e": [1]}, {"type": "vertical", "e": [3]},
        {"type": "distance", "e": [0], "v": 6.0}, {"type": "distance", "e": [1], "v": 4.0},
        {"type": "diameter", "e": [4], "v": 1.0}, {"type": "equal", "e": [4, 5]},
        {"type": "horizontal", "p": [4, 5]},
        {"type": "horizontalDistance", "p": [0, 4], "v": 1.5},
        {"type": "horizontalDistance", "p": [5, 1], "v": 1.5},
        {"type": "verticalDistance", "p": [0, 4], "v": 2.0},
    ],
}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(plate))
tsr.run_command("tsr.feature.extrude", distance=0.8, profiles="0.2,0.2")

boss = {
    "points": [[0, 0], [3, 2]],
    "entities": [{"type": "circle", "c": 1, "r": 1.0}],
    "constraints": [{"type": "diameter", "e": [0], "v": 2.0}],
}
tsr.run_command("tsr.sketch.create", plane="XY", offset=0.8, data=json.dumps(boss))
tsr.run_command("tsr.feature.extrude", distance=1.5, operation="Join")
print("features:", ", ".join(f["name"] for f in tsr.features()))
