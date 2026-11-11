# Timeline through the scripting API: create, edit, suppress, delete, undo.
import adsk.core
import adsk.fusion
import tsr

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.run_command("tsr.primitive.cylinder", diameter=1.0, height=4.0, x=1.0, y=1.0, z=-1.0, operation="Cut")
f = tsr.features()
assert [x["name"] for x in f] == ["Box1", "Cylinder1"], f
assert root.bRepBodies.count == 1
v0 = root.bRepBodies.item(0).volume

tsr.edit_feature(f[0]["id"], height=3.0)
assert root.bRepBodies.item(0).volume > v0
tsr.suppress_feature(f[1]["id"])
assert abs(root.bRepBodies.item(0).volume - 12.0) < 1e-6
assert tsr.features()[1]["suppressed"]
tsr.undo()
tsr.undo()
assert abs(root.bRepBodies.item(0).volume - v0) < 1e-9

opts = [i for c in tsr.commands() if c["id"] == "tsr.primitive.box" for i in c["inputs"] if i["id"] == "operation"]
assert opts[0]["choices"] == ["New Body", "Join", "Cut", "Intersect"], opts
try:
    tsr.run_command("tsr.primitive.sphere", operation="Weld")
except RuntimeError:
    pass
else:
    raise AssertionError("bad operation accepted")
print("api features: OK")
