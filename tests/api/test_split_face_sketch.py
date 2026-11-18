# Split Face with a sketch, as in the familiar tool (Splitting Tool: sketch
# curves, Along Vector): the sketch's curves, along its normal, cut the
# picked faces; the body keeps its shape.
import json
import tsr

cmd = tsr.run_command


def props():
    p = tsr.mass_properties("Body1")
    return round(p["volume"], 9), p["faces"]


cmd("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
v0, f0 = props()
assert f0 == 6
# A line across the top (sketched above it): the top becomes two faces.
line = {"points": [[0, 0], [1, -1], [1, 4]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(line))
cmd("tsr.feature.splitFace", body="Body1", faces="2,1.5,2", tool="Sketch")
s = tsr.features()[-1]
assert s["error"] == "", s
assert props() == (v0, 7), props()
# A circle on the top's other part: a disc face inside it.
circle = {"points": [[0, 0], [3, 1.5]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}
cmd("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(circle))
cmd("tsr.feature.splitFace", body="Body1", faces="2.5,0.3,2", tool="Sketch")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert props() == (v0, 8), props()
# A sketch on the front plane: its vertical line cuts the front face only.
upright = {"points": [[0, 0], [2, -1], [2, 3]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(upright))
cmd("tsr.feature.splitFace", body="Body1", faces="1,0,1", tool="Sketch")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert props() == (v0, 9), props()
# Curves that miss the face are explained.
far = {"points": [[0, 0], [10, 10]], "entities": [{"type": "circle", "c": 1, "r": 0.5}]}
cmd("tsr.sketch.create", plane="XY", offset=5.0, data=json.dumps(far))
try:
    cmd("tsr.feature.splitFace", body="Body1", faces="0.5,1.5,2", tool="Sketch")
except RuntimeError as e:
    assert "do not cross" in str(e), e
else:
    raise AssertionError("split with curves that miss the face")
print("split face by sketch: OK")
