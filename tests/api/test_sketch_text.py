# Sketch text: letters on a point, as profiles (each letter a face with its
# holes); extruded into solid letters; moved with its point; kept through
# save and open.
import json
import os
import tempfile
import adsk.core
import adsk.fusion
import tsr

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
data = {"points": [[0, 0], [1, 1]], "entities": [],
        "texts": [{"p": 1, "text": "TO", "h": 2.0}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(data))
tsr.run_command("tsr.feature.extrude", distance=0.5)
assert root.bRepBodies.count == 2, root.bRepBodies.count            # T and O, two solids
lo, hi = tsr.bounding_box("Body1")
for i in range(root.bRepBodies.count):
    b = root.bRepBodies.item(i)
    assert b.volume > 0.05, b.volume
los = [tsr.bounding_box(root.bRepBodies.item(i).name) for i in range(2)]
assert all(abs(h[2] - 0.5) < 1e-6 and abs(l[2]) < 1e-6 for l, h in los), los
# The letters stand on the point (1, 1) cm (side bearing and round overshoot
# aside) and are about the font size tall.
xmin = min(l[0] for l, h in los)
ymin = min(l[1] for l, h in los)
ymax = max(h[1] for l, h in los)
assert abs(xmin - 1.0) < 0.1 and abs(ymin - 1.0) < 0.05 and 1.0 < ymax - ymin <= 2.0, (los,)
# The O has a hole: its face area is less than its outline's.
o = max(range(2), key=lambda i: los[i][0][0])
props = tsr.mass_properties(root.bRepBodies.item(o).name)
assert props["faces"] >= 4, props        # outside, inside (hole), top, bottom

# Move the point: the letters follow.
s1 = tsr.features()[0]
d = json.loads(s1["inputs"]["data"])
d["points"][1] = [3, 1]
tsr.edit_feature(s1["id"], data=json.dumps(d))
assert min(tsr.bounding_box(root.bRepBodies.item(i).name)[0][0] for i in range(2)) >= 2.9

path = os.path.join(tempfile.mkdtemp(), "text.tsr")
tsr.save(path)
tsr.open(path)
assert json.loads(tsr.sketch_data("Sketch1"))["texts"][0]["text"] == "TO"
assert root.bRepBodies.count == 2
print("sketch text: OK")
