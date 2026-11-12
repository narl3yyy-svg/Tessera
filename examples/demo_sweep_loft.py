# Sweep, Loft and Press Pull demo: a lofted vase, a swept handle, and a
# base plate whose top face was pulled up.
import json
import tsr

cmd = tsr.run_command
cmd("tsr.primitive.box", length=8.0, width=5.0, height=0.5, x=-4.0, y=-2.5)
cmd("tsr.feature.pressPull", faces="0,0,0.5", distance=0.3)

# Vase: square base to round top.
sq = {"points": [[0, 0], [-1.2, -1.2], [1.2, -1.2], [1.2, 1.2], [-1.2, 1.2]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                   {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XY", offset=0.8, data=json.dumps(sq))
cmd("tsr.sketch.create", plane="XY", offset=4.0, data=json.dumps({"points": [[0, 0]], "entities": [{"type": "circle", "c": 0, "r": 0.8}]}))
cmd("tsr.feature.loft", operation="Join")

# Handle: a 3.6 mm circle on a side plane (YZ moved to x = 10 mm), swept
# along a half-circle path that leaves the vase and comes back.
cmd("tsr.sketch.create", plane="YZ", offset=1.0,
    data=json.dumps({"points": [[0, 0], [0, 1.4]], "entities": [{"type": "circle", "c": 1, "r": 0.18}]}))
path = {"points": [[0, 0], [1.0, 2.4], [1.0, 1.4], [1.0, 3.4]],
        "entities": [{"type": "arc", "c": 1, "p": [2, 3]}]}
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(path))
cmd("tsr.feature.sweep", operation="Join")
print("features:", ", ".join(f["name"] for f in tsr.features()))
for f in tsr.features():
    assert f["error"] == "", f
