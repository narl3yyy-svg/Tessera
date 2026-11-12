# Extrude a flat face of a body (Fusion: click a face, pull the arrow):
# pulling out joins, pushing in with Cut removes, and the feature replays.
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command
cmd("tsr.primitive.box", length=2.0, width=2.0, height=1.0)

# Top face (z = 1) pulled up 0.5 and joined: 2 x 2 x 1.5.
cmd("tsr.feature.extrude", faces="1,1,1", distance=0.5, operation="Join")
f = tsr.features()[-1]
assert f["error"] == "" and f["inputs"]["target"] == "Body1", f
assert root.bRepBodies.count == 1
assert abs(root.bRepBodies.item(0).volume - 6.0) < 1e-6, root.bRepBodies.item(0).volume

# Bottom face (z = 0, facing down) pushed in 0.5 with Cut: 6 - 2.
cmd("tsr.feature.extrude", faces="1,1,0", distance=-0.5, operation="Cut")
assert abs(root.bRepBodies.item(0).volume - 4.0) < 1e-6, root.bRepBodies.item(0).volume

# The face extrudes follow a change to the box: 2 x 2 x 2.5 - 2.
tsr.edit_feature(tsr.features()[0]["id"], height=2.0)
assert all(x["error"] == "" for x in tsr.features()), tsr.features()
assert abs(root.bRepBodies.item(0).volume - 8.0) < 1e-6, root.bRepBodies.item(0).volume

# Curved faces are refused.
cmd("tsr.primitive.cylinder", diameter=1.0, height=1.0, x=5.0)
try:
    cmd("tsr.feature.extrude", faces="5.5,0,0.5", target="Body2", distance=0.2, operation="Join")
except RuntimeError as e:
    assert "flat" in str(e), e
else:
    raise AssertionError("curved face extruded")
print("api extrude faces: OK")
