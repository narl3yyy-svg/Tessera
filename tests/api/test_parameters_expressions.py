# Parameters and expressions: user parameters that refer to each other,
# feature inputs and sketch dimensions given as expressions, and the model
# following a parameter change. Followed (in CTest) by --save, --open and
# check_parameters_reopened.py.
import json
import math
import tsr
import adsk.core
import adsk.fusion

design = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct)
params = design.userParameters
root = design.rootComponent

w = params.add("width", adsk.core.ValueInput.createByString("40 mm"), "mm", "plate width")
params.add("depth", adsk.core.ValueInput.createByString("width * 3 / 4"), "mm", "")
params.add("thick", adsk.core.ValueInput.createByString("5"), "mm", "")   # bare number: the parameter's unit
params.add("holes", adsk.core.ValueInput.createByString("2"), "", "")
assert abs(params.itemByName("depth").value - 3.0) < 1e-12
assert abs(params.itemByName("thick").value - 0.5) < 1e-12
assert abs(tsr.evaluate("width / 2 + 3", "mm") - 2.3) < 1e-12
assert abs(tsr.evaluate("atan(depth / width)", "deg") - math.atan(0.75)) < 1e-12

# Feature inputs as expressions (strings); the text is kept next to the value.
tsr.run_command("tsr.primitive.box", length="width", width="depth", height="thick")
box = tsr.features()[0]
assert box["inputs"]["=length"] == "width", box["inputs"]
assert "=height" in box["inputs"] and abs(box["inputs"]["height"] - 0.5) < 1e-12
assert abs(root.bRepBodies.item(0).volume - 4 * 3 * 0.5) < 1e-9

# Integer inputs take expressions too.
tsr.run_command("tsr.feature.rectangularPattern", patternType="Bodies", distanceType="Spacing", quantity1="holes + 1", distance1="width + 10 mm", result="New Bodies")
pat = tsr.features()[1]
assert pat["inputs"]["quantity1"] == 3 and pat["error"] == "", pat
assert root.bRepBodies.count == 3

# A sketch dimension driven by a parameter.
sk = {
    "points": [[0, 0], [1.0, 1.0]],
    "entities": [{"type": "circle", "c": 1, "r": 0.2}],
    "constraints": [{"type": "fix", "p": [1], "v": 1.0, "v2": 1.0},
                    {"type": "diameter", "e": [0], "v": 0.4, "expr": "thick * 2"}],
}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(sk))
tsr.run_command("tsr.feature.extrude", distance="thick", operation="New Body")
v_disc = math.pi * 0.5 ** 2 * 0.5
assert abs(root.bRepBodies.item(3).volume - v_disc) < 1e-6, root.bRepBodies.item(3).volume

# Change the parameters: everything that refers to them follows, one undo step each.
w.expression = "60 mm"
assert abs(params.itemByName("depth").value - 4.5) < 1e-12        # dependent parameter
assert abs(root.bRepBodies.item(0).volume - 6 * 4.5 * 0.5) < 1e-9
params.itemByName("thick").value = 1.0                              # 10 mm
assert params.itemByName("thick").expression == "10 mm"
assert abs(root.bRepBodies.item(3).volume - math.pi * 1.0 ** 2 * 1.0) < 1e-6
tsr.undo()
assert abs(params.itemByName("thick").value - 0.5) < 1e-12
assert abs(root.bRepBodies.item(3).volume - v_disc) < 1e-6

# Errors: cycles, unknown names, wrong dimensions, deleting a used parameter.
for bad in ["depth + 1", "nope * 2", "10 deg"]:
    try:
        w.expression = bad
    except RuntimeError:
        pass
    else:
        raise AssertionError("accepted " + bad)
assert w.expression == "60 mm"
try:
    tsr.run_command("tsr.primitive.box", length="width - 100 mm")
except RuntimeError as e:
    assert "Length" in str(e), e
else:
    raise AssertionError("negative length accepted")
assert not w.isDeletable and not w.deleteMe()
try:
    tsr.delete_parameter("thick")
except RuntimeError as e:
    assert "Box1" in str(e) and "Sketch1" in str(e), e
else:
    raise AssertionError("deleted a used parameter")

# A parameter change that breaks a feature is reported on that feature.
tsr.set_parameter("holes", "-1")
assert "Quantity" in tsr.features()[1]["error"], tsr.features()[1]
tsr.set_parameter("holes", "2", "copies besides the original")
assert tsr.features()[1]["error"] == ""
assert params.itemByName("holes").comment == "copies besides the original"

params.add("spare", adsk.core.ValueInput.createByReal(1), "mm", "")
assert params.itemByName("spare").deleteMe() and params.itemByName("spare") is None
print("api parameters and expressions: OK")
