# Named sketch dimensions (d1, d2 ...) as model parameters, as in the
# familiar tool: a later sketch and a feature use them by name, and follow
# when the dimension changes. They survive save and open.
import json
import os
import tempfile
import tsr

rect = {"points": [[0, 0], [0, 0], [4, 0], [4, 3], [0, 3]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [2, 3]},
                     {"type": "line", "p": [3, 4]}, {"type": "line", "p": [4, 1]}],
        "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 0.0},
                        {"type": "horizontal", "e": [0]}, {"type": "vertical", "e": [1]},
                        {"type": "horizontal", "e": [2]}, {"type": "vertical", "e": [3]},
                        {"type": "distance", "e": [0], "v": 4.0, "name": "d1"},
                        {"type": "distance", "e": [1], "v": 3.0, "name": "d2"}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(rect))
# Two level lines from fixed starts: d4 (first) uses d3 (second).
line = {"points": [[0, 0], [0, 5], [1, 5], [0, 8], [1, 8]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [3, 4]}],
        "constraints": [{"type": "fix", "p": [1], "v": 0.0, "v2": 5.0}, {"type": "horizontal", "e": [0]},
                        {"type": "fix", "p": [3], "v": 0.0, "v2": 8.0}, {"type": "horizontal", "e": [1]},
                        {"type": "distance", "e": [0], "v": 1.0, "expr": "d1 / 2 + d3", "name": "d4"},
                        {"type": "distance", "e": [1], "v": 1.0, "expr": "d2 + 2 mm", "name": "d3"}]}
tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(line))
# After both sketches (its own values take the next names, d5 and d6).
tsr.run_command("tsr.feature.extrude", sketch="Sketch1", distance="d1 / 4")


def params():
    return {p["name"]: p for p in tsr.model_parameters() if p["input"] == ""}   # the sketch dimensions


def check(d1):
    p = params()
    assert set(p) == {"d1", "d2", "d3", "d4"}, p
    assert p["d1"]["owner"] == "Sketch1" and p["d4"]["owner"] == "Sketch2", p
    assert abs(p["d1"]["value"] - d1) < 1e-12 and abs(p["d2"]["value"] - 3) < 1e-12, p
    assert abs(p["d3"]["value"] - 3.2) < 1e-12, p                    # d2 + 2 mm
    assert abs(p["d4"]["value"] - (d1 / 2 + 3.2)) < 1e-12, p         # uses d3, defined after it
    assert p["d4"]["expression"] == "d1 / 2 + d3", p
    lo, hi = tsr.bounding_box("Body1")
    assert abs(hi[2] - d1 / 4) < 1e-9 and abs(hi[0] - d1) < 1e-9, (lo, hi)   # extruded d1 / 4
    sk = json.loads(tsr.sketch_data("Sketch2"))
    pts = sk["points"]
    assert abs(abs(pts[2][0] - pts[1][0]) - (d1 / 2 + 3.2)) < 1e-9, pts  # the line follows d4


check(4.0)
assert abs(tsr.evaluate("d1 * 2", "mm") - 8.0) < 1e-12

# Change d1: everything that uses it follows.
s1 = tsr.features()[0]
data = json.loads(s1["inputs"]["data"])
for c in data["constraints"]:
    if c.get("name") == "d1":
        c["v"] = 6.0
tsr.edit_feature(s1["id"], data=json.dumps(data))
check(6.0)

# Save and open: the names are kept.
path = os.path.join(tempfile.mkdtemp(), "dims.tsr")
tsr.save(path)
tsr.new_document()
assert tsr.model_parameters() == []
tsr.open(path)
check(6.0)
print("model parameters: OK")
