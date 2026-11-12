# Sketch Chamfer, Extend and Mirror through the scripting API.
import json
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent

def rect(w, h):
    return {"points": [[0, 0], [w, 0], [w, h], [0, h]],
            "entities": [{"type": "line", "p": [0, 1]}, {"type": "line", "p": [1, 2]},
                         {"type": "line", "p": [2, 3]}, {"type": "line", "p": [3, 0]}]}

# Chamfer one corner by 5 mm: 40 x 30 minus a 5 x 5 / 2 triangle.
data = tsr.sketch_chamfer(json.dumps(rect(4, 3)), 0, 1, 0.5)
tsr.run_command("tsr.sketch.create", plane="XY", data=data)
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(root.bRepBodies.item(0).volume - (12 - 0.125)) < 1e-6, root.bRepBodies.item(0).volume

# Extend: a line stopping short of a wall reaches it.
s = {"points": [[0, 0], [5, -1], [5, 5], [0, 1], [2, 1]],
     "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [3, 4]}]}
out = json.loads(tsr.sketch_extend(json.dumps(s), 1, 1.9, 1.0))
end = out["points"][out["entities"][1]["p"][1]]
assert abs(end[0] - 5.0) < 1e-7, end

# Mirror a triangle across a construction line: a closed diamond outline.
tri = {"points": [[0, 0], [0, -3], [0, 3], [2, 0]],
       "entities": [{"type": "line", "p": [1, 2], "construction": True},
                    {"type": "line", "p": [1, 3]}, {"type": "line", "p": [3, 2]}]}
d = json.loads(tsr.sketch_mirror(json.dumps(tri), [1, 2], 0))
assert len(d["entities"]) == 5 and any(c["type"] == "symmetry" for c in d["constraints"]), d
tsr.run_command("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(d))
tsr.run_command("tsr.feature.extrude", distance=1.0)
assert abs(root.bRepBodies.item(1).volume - 12.0) < 1e-6, root.bRepBodies.item(1).volume   # 4 x 6 diamond / 2
print("api sketch chamfer/extend/mirror: OK")
