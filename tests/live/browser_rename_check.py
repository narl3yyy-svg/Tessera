import adsk.core
import adsk.fusion
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
assert root.bRepBodies.item(0).name == "Lid", root.bRepBodies.item(0).name
print("live browser rename: OK")
