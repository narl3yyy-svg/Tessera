# The timeline's history marker and feature order, as in the familiar tool:
# roll back, add a feature there, roll forward; reorders that break a
# feature are refused; the file keeps both.
import json
import math
import os
import tempfile
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command


def vol():
    return sum(root.bRepBodies.item(i).volume for i in range(root.bRepBodies.count))


def names():
    return [f["name"] for f in tsr.features()]


cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)                       # 16
stud = {"points": [[0, 0], [1, 1]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}
cmd("tsr.sketch.create", plane="XY", offset=1.0, data=json.dumps(stud))
cmd("tsr.feature.extrude", distance=1.0, operation="Join")                       # + pi/4
cmd("tsr.feature.fillet", body="Body1", edges="4,2,0.5", radius=0.2)
full = vol()
assert tsr.history_marker() == 4

tsr.roll_history(1)                                                              # just the box
assert tsr.history_marker() == 1 and abs(vol() - 16) < 1e-9, vol()
assert [f["rolled_back"] for f in tsr.features()] == [False, True, True, True]

cmd("tsr.primitive.cylinder", diameter=1.0, height=1.0, x=-3.0)                 # made at the marker
assert names() == ["Box1", "Cylinder1", "Sketch1", "Extrude1", "Fillet1"], names()
assert tsr.history_marker() == 2 and root.bRepBodies.count == 2

tsr.roll_history(5)                                                              # to the end
assert abs(vol() - (full + math.pi * 0.25)) < 1e-6 and all(f["error"] == "" for f in tsr.features()), tsr.features()

try:
    tsr.move_feature("Extrude1", 1)                                              # before its sketch
except RuntimeError as e:
    assert "breaks" in str(e), e
else:
    raise AssertionError("a reorder that breaks a feature was accepted")
tsr.move_feature("Cylinder1", 4)                                                 # independent: fine
assert names() == ["Box1", "Sketch1", "Extrude1", "Fillet1", "Cylinder1"], names()

tsr.roll_history(2)
path = os.path.join(tempfile.mkdtemp(), "timeline.tsr")
tsr.save(path)
tsr.open(path)
assert tsr.history_marker() == 2 and names()[4] == "Cylinder1" and abs(vol() - 16) < 1e-9, (tsr.history_marker(), vol())
print("api timeline: OK")
