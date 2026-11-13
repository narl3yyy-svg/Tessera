# Renaming bodies, sketches and timeline features, as in the familiar Browser
# and timeline. References follow; a replay and a reopened file keep the names.
import json
import os
import tempfile
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command

sq = {"points": [[0, 0], [0, 0], [4, 0], [4, 2], [0, 2]],
      "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                   {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(sq))
cmd("tsr.feature.extrude", distance=1.0)

# Body: the new name shows and works; replays keep it; undo restores it.
tsr.rename("body", "Body1", "Base")
assert root.bRepBodies.item(0).name == "Base"
assert tsr.bounding_box("Base") == tsr.bounding_box("Body1")
cmd("tsr.feature.fillet", body="Base", edges="2,0,1", radius=0.1)
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"][0]
tsr.edit_feature(ex["id"], distance=1.5)                 # replay
assert root.bRepBodies.item(0).name == "Base" and all(f["error"] == "" for f in tsr.features()), tsr.features()
try:
    tsr.rename("body", "Base", "")
except RuntimeError:
    pass
else:
    raise AssertionError("empty name accepted")

# Sketch: features that use it follow.
tsr.rename("sketch", "Sketch1", "Outline")
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"][0]
assert ex["inputs"]["sketch"] == "Outline" and ex["error"] == "", ex
assert [f["name"] for f in tsr.features()][0] == "Outline"

# Feature: a pattern of it follows.
stud = {"points": [[0, 0], [0.5, 0.5]], "entities": [{"type": "circle", "c": 1, "r": 0.2}]}
cmd("tsr.sketch.create", plane="XY", offset=1.5, data=json.dumps(stud))
cmd("tsr.feature.extrude", distance=0.5, operation="Join")
cmd("tsr.feature.rectangularPattern", patternType="Features", features="Extrude2", distanceType="Spacing",
    quantity1=3, distance1=1.0)
v = root.bRepBodies.item(0).volume
tsr.rename("feature", "Extrude2", "Stud")
pat = [f for f in tsr.features() if f["command"] == "tsr.feature.rectangularPattern"][0]
assert pat["inputs"]["features"] == "Stud" and pat["error"] == "", pat
assert abs(root.bRepBodies.item(0).volume - v) < 1e-9

# Undo puts a name back; a saved file keeps the names.
tsr.undo()
assert any(f["name"] == "Extrude2" for f in tsr.features())
tsr.redo()
path = os.path.join(tempfile.mkdtemp(), "renamed.tsr")
tsr.save(path)
tsr.open(path)
assert root.bRepBodies.item(0).name == "Base" and any(f["name"] == "Stud" for f in tsr.features())
print("api rename: OK")
