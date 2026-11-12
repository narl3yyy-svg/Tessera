# Runs after test_parameters_expressions.py, --save and --open: expressions
# survive the .tsr round trip and still drive the model.
import adsk.core
import adsk.fusion
import tsr

design = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct)
params = design.userParameters
root = design.rootComponent
assert params.itemByName("depth").expression == "width * 3 / 4"
assert abs(params.itemByName("depth").value - 4.5) < 1e-12
assert tsr.features()[0]["inputs"]["=length"] == "width"
params.itemByName("width").expression = "20 mm"
assert abs(root.bRepBodies.item(0).volume - 2 * 1.5 * 0.5) < 1e-9
print("reopened parameters: OK")
