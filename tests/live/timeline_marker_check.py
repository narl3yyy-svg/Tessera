import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = tsr.features()
assert [x["name"] for x in f] == ["Sketch1", "Extrude1"], f
assert tsr.history_marker() == 1 and f[1]["rolled_back"] and root.bRepBodies.count == 0, (tsr.history_marker(), f)
print("live timeline marker: OK")
