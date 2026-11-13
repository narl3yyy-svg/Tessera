# Feature values as model parameters, as in the familiar Parameters table:
# an extrude's distance, a fillet's radius ... get names (d1, d2 ...) that
# any expression can use; any parameter can be renamed (its users follow)
# and starred as a favourite. All of it is kept in the design.
import json
import os
import tempfile
import tsr
import adsk.core
import adsk.fusion

design = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct)

rect = {"points": [[0, 0], [0, 0], [4, 0], [4, 2], [0, 2]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                     {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}],
        "constraints": [{"type": "distance", "e": [0], "v": 4.0, "name": "d1"}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(rect))
tsr.run_command("tsr.feature.extrude", distance=1.0)


def params():
    return {p["name"]: p for p in tsr.model_parameters()}


def name_of(owner, input_id):
    return [m["name"] for m in tsr.model_parameters() if m["owner"] == owner and m["input"] == input_id][0]


p = params()
# The sketch's d1, then the extrude's values in order: distance d2, taper angle d3.
assert set(p) == {"d1", "d2", "d3"}, p
assert p["d3"]["input"] == "taper" and p["d3"]["unit"] == "deg" and p["d3"]["angle"], p
assert p["d2"]["owner"] == "Extrude1" and p["d2"]["input"] == "distance" and p["d2"]["label"] == "Distance", p
assert abs(p["d2"]["value"] - 1.0) < 1e-12 and p["d2"]["unit"] == "mm", p
assert p["d1"]["input"] == "" and p["d1"]["owner"] == "Sketch1", p

# A later feature uses the extrude's distance by name.
tsr.run_command("tsr.primitive.box", length=1.0, width=1.0, height="d2 * 3", operation="New Body")
lo, hi = tsr.bounding_box("Body2")
assert abs(hi[2] - lo[2] - 3.0) < 1e-9, (lo, hi)
height = name_of("Box1", "height")
assert height not in ("d1", "d2", "d3") and params()[height]["expression"] == "d2 * 3", (height, params())
assert abs(tsr.evaluate("d2 + d1", "mm") - 5.0) < 1e-9   # cm, internal

# A user parameter may not take a model parameter's name.
try:
    tsr.run_command("tsr.parameters.addUser", name="d2", unit="mm", expression="1")
    raise AssertionError("a user parameter took d2")
except RuntimeError as e:
    assert "model parameter" in str(e), e

# Rename the extrude's distance: the box's expression follows; so do the values.
tsr.rename_parameter("d2", "thickness")
p = params()
assert "d2" not in p and p["thickness"]["owner"] == "Extrude1", p
assert p[height]["expression"] == "thickness * 3", p
ext = [f for f in tsr.features() if f["name"] == "Extrude1"][0]
tsr.edit_feature(ext["id"], distance=2.0)
lo, hi = tsr.bounding_box("Body2")
assert abs(hi[2] - lo[2] - 6.0) < 1e-9, (lo, hi)

# Rename a sketch dimension: the sketch keeps its value; users follow.
tsr.run_command("tsr.parameters.addUser", name="half", unit="mm", expression="d1 / 2")
tsr.rename_parameter("d1", "length")
p = params()
assert "length" in p and p["length"]["input"] == "" and abs(p["length"]["value"] - 4) < 1e-12, p
assert design.userParameters.itemByName("half").expression == "length / 2"

# Bad names: taken, a unit, not an identifier.
for bad in ("length", "half", "mm", "2x", "a b", "sin"):
    try:
        tsr.rename_parameter("thickness", bad)
        raise AssertionError("accepted " + bad)
    except RuntimeError:
        pass

# Favourites: starred, follow a rename, undoable.
tsr.set_favorite("thickness")
tsr.set_favorite("half")
assert tsr.favorite_parameters() == ["thickness", "half"]
tsr.rename_parameter("thickness", "wall")
assert tsr.favorite_parameters() == ["half", "wall"], tsr.favorite_parameters()
tsr.set_favorite("half", False)
assert tsr.favorite_parameters() == ["wall"]
assert tsr.undo()
assert tsr.favorite_parameters() == ["half", "wall"]

# Saved with the design.
path = os.path.join(tempfile.mkdtemp(), "params.tsr")
tsr.save(path)
tsr.new_document()
tsr.open(path)
p = params()
assert p["wall"]["owner"] == "Extrude1" and abs(p["wall"]["value"] - 2.0) < 1e-12, p
assert p[height]["expression"] == "wall * 3", p
assert tsr.favorite_parameters() == ["half", "wall"]
print("feature parameters: OK")
