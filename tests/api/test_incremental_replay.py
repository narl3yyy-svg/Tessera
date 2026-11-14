# Editing a feature replays only from that feature on: what the features
# before it made is restored from memory. Every edit below is checked
# against a full replay (TSR_FULL_REPLAY=1) of the same design: the same
# bodies, volumes, sketches and errors.
import json
import os
import tsr
import adsk.core
import adsk.fusion

design = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct)
root = design.rootComponent
params = design.userParameters
cmd = tsr.run_command


def state():
    bodies = sorted((root.bRepBodies.item(i).name, round(root.bRepBodies.item(i).volume, 9))
                    for i in range(root.bRepBodies.count))
    feats = [(f["name"], f["error"]) for f in tsr.features()]
    sketches = [tsr.sketch_data(f["name"]) for f in tsr.features()
                if f["command"] == "tsr.sketch.create" and not f["rolled_back"] and not f["suppressed"]]
    return bodies, feats, sketches


def fid(name):
    return [f["id"] for f in tsr.features() if f["name"] == name][0]


def check(label, edit, reused):
    """Make the edit, then compare with a full replay of the result."""
    edit()
    got = state()
    r = tsr.last_replay()
    assert r[0] == reused, (label, r, reused)
    os.environ["TSR_FULL_REPLAY"] = "1"
    tsr.roll_history(tsr.history_marker())   # replays everything, same design
    os.environ.pop("TSR_FULL_REPLAY")
    assert tsr.last_replay()[0] == 0, tsr.last_replay()
    assert state() == got, (label, got, state())


params.add("w", adsk.core.ValueInput.createByString("40 mm"), "mm", "")
params.add("r", adsk.core.ValueInput.createByString("4 mm"), "mm", "")
cmd("tsr.primitive.box", length="w", width=3.0, height=1.0)                                   # 0 Box1
stud = {"points": [[0, 0], [1, 1]], "entities": [{"type": "circle", "c": 1, "r": 0.5}],
        "constraints": [{"type": "radius", "e": [0], "v": 0.4, "expr": "r"}]}
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(stud))                     # 1 Sketch1
cmd("tsr.feature.extrude", distance=1.0, operation="Join")                                   # 2 Extrude1
cmd("tsr.feature.fillet", body="Body1", edges="4,2,0.5", radius=0.1)                          # 3 Fillet1
cmd("tsr.primitive.cylinder", diameter=1.0, height=2.0, x=-3.0)                               # 4 Cylinder1
cmd("tsr.feature.rectangularPattern", patternType="Features", features="Extrude1", distanceType="Spacing",
    quantity1=2, distance1=1.5, direction1="X")                                                # 5 pattern
n = len(tsr.features())

# The last feature changed: everything before it is restored.
last = tsr.features()[-1]["name"]
check("last", lambda: tsr.edit_feature(fid(last), quantity1=3), n - 1)
# A middle feature: the ones before it restored, it and the rest replayed.
check("middle", lambda: tsr.edit_feature(fid("Cylinder1"), height=3.0), 4)
check("fillet", lambda: tsr.edit_feature(fid("Fillet1"), radius=0.15), 3)
# The first feature: nothing to restore.
check("first", lambda: tsr.edit_feature(fid("Box1"), height=1.5), 0)
# A parameter the sketch's dimension uses: replays from the sketch on.
check("sketch parameter", lambda: tsr.set_parameter("r", "3 mm", None), 1)
# A parameter the box uses: everything.
check("box parameter", lambda: tsr.set_parameter("w", "50 mm", None), 0)
# Suppress and unsuppress a middle feature.
check("suppress", lambda: tsr.suppress_feature(fid("Cylinder1"), True), 4)
check("unsuppress", lambda: tsr.suppress_feature(fid("Cylinder1"), False), 4)
# Roll the marker back and forward. A timeline change replays twice (once to
# check the new order breaks nothing, once to commit); the second restores
# every step the first made.
check("roll back", lambda: tsr.roll_history(3), n)
check("roll forward", lambda: tsr.roll_history(n), n)
# A body renamed (no replay by itself): names may be read anywhere, so the
# next edit replays everything.
check("rename", lambda: (tsr.rename("body", "Body1", "Plate"), tsr.edit_feature(fid(last), quantity1=2)), 0)
# Undo and redo keep matching too (the memory keys on the inputs).
tsr.undo()
tsr.edit_feature(fid("Cylinder1"), height=2.5)
r = tsr.last_replay()
assert r[0] == 4, r
print("incremental replay: OK")
