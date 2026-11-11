# Every registered command must be scriptable through the generic path.
import adsk.core
import adsk.fusion
import tsr

ids = [c["id"] for c in tsr.commands()]
assert "tsr.primitive.box" in ids and "tsr.parameters.addUser" in ids, ids

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
tsr.run_command("tsr.primitive.box", length=1.0, width=2.0, height=3.0)
assert root.bRepBodies.count == 1
body = root.bRepBodies.item(0)
assert body.name == "Body1"
assert abs(body.volume - 6.0) < 1e-9
assert abs(body.area - 22.0) < 1e-9

try:
    tsr.run_command("tsr.primitive.box", length=-1.0)
except RuntimeError:
    pass
else:
    raise AssertionError("negative length accepted")

assert tsr.undo() and root.bRepBodies.count == 0
assert tsr.redo() and root.bRepBodies.count == 1
print("api commands: OK")
