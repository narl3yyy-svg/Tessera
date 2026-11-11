# Fillet, chamfer and revolve demo for screenshots: a rounded mounting
# block with chamfered top edges and a revolved knob on top.
import json
import tsr

block = {"points": [[0, 0], [5, 0], [5, 3], [0, 3]],
         "entities": [{"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
                      {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(block))
tsr.run_command("tsr.feature.extrude", distance=1.2)
# Round the four vertical edges, bevel the top outline.
tsr.run_command("tsr.feature.fillet", edges="0,0,0.6;5,0,0.6;5,3,0.6;0,3,0.6", radius=0.6)
tsr.run_command("tsr.feature.chamfer", edges="2.5,0,1.2", distance=0.15)

# Knob profile on a vertical plane through the block centre, turned about
# its own construction centre line.
knob = {"points": [[0, 0], [2.5, 1.2], [3.3, 1.2], [3.3, 1.6], [3.0, 2.4], [3.0, 2.9], [2.5, 2.9], [2.5, 0.0], [2.5, 3.5]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                     {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 5]},
                     {"type": "line", "p": [5, 6]}, {"type": "line", "p": [6, 1]},
                     {"type": "line", "p": [7, 8], "construction": True}]}
tsr.run_command("tsr.sketch.create", plane="XZ", offset=-1.5, data=json.dumps(knob))
tsr.run_command("tsr.feature.revolve", axis="Construction line", operation="Join")
print("features:", ", ".join(f["name"] for f in tsr.features()))
for f in tsr.features():
    assert f["error"] == "", f
