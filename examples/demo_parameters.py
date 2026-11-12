# A parametric bracket driven by user parameters. Open Modify > Change
# Parameters (or double-click User Parameters in the browser) and change
# "width" or "thick": the plate, its hole pattern and the boss follow.
import json
import tsr
import adsk.core
import adsk.fusion

params = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).userParameters
params.add("width", adsk.core.ValueInput.createByString("80 mm"), "mm", "plate width")
params.add("depth", adsk.core.ValueInput.createByString("width * 5 / 8"), "mm", "plate depth")
params.add("thick", adsk.core.ValueInput.createByString("6 mm"), "mm", "plate thickness")
params.add("boss_d", adsk.core.ValueInput.createByString("depth / 2"), "mm", "boss diameter")
params.add("copies", adsk.core.ValueInput.createByString("3"), "", "plates in the row")

tsr.run_command("tsr.primitive.box", length="width", width="depth", height="thick")
boss = {
    "points": [[0, 0], [4.0, 2.5]],
    "entities": [{"type": "circle", "c": 1, "r": 1.0}],
    "constraints": [
        {"type": "horizontalDistance", "p": [0, 1], "v": 4.0, "expr": "width / 2"},
        {"type": "verticalDistance", "p": [0, 1], "v": 2.5, "expr": "depth / 2"},
        {"type": "diameter", "e": [0], "v": 2.0, "expr": "boss_d"},
    ],
}
tsr.run_command("tsr.sketch.create", plane="XY", offset="thick", data=json.dumps(boss))
tsr.run_command("tsr.feature.extrude", distance="thick * 3", operation="Join")
tsr.run_command("tsr.feature.fillet", edges="0,0,0.3", radius="thick / 2")
tsr.run_command("tsr.feature.rectangularPattern", quantity1="copies", distance1="width + 20 mm")
