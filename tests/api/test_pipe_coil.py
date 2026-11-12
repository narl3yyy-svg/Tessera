# Pipe along a sketch path and Coil (helix) through the scripting API.
import json
import math
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
cmd = tsr.run_command

def vol(i):
    return root.bRepBodies.item(i).volume

# A straight 100 mm path: round, hollow and square pipes.
path = {"points": [[0, 0], [0, 0], [10, 0]], "entities": [{"type": "line", "p": [1, 2]}]}
cmd("tsr.sketch.create", plane="XY", data=json.dumps(path))
cmd("tsr.feature.pipe", size=1.0)
assert abs(vol(0) - math.pi * 0.25 * 10) < 1e-4, vol(0)
cmd("tsr.feature.pipe", size=1.0, hollow="Yes", thickness=0.1)
assert abs(vol(1) - math.pi * (0.25 - 0.16) * 10) < 1e-4, vol(1)
cmd("tsr.feature.pipe", size=1.0, section="Square")
assert abs(vol(2) - 10) < 1e-4, vol(2)

# A bent path (line + tangent arc + line) still makes one valid pipe.
bent = {"points": [[0, 0], [0, 5], [5, 5], [5, 7], [7, 7], [7, 12]],
        "entities": [{"type": "line", "p": [1, 2]}, {"type": "arc", "c": 3, "p": [2, 4], "r": 2},
                     {"type": "line", "p": [4, 5]}]}
cmd("tsr.sketch.create", plane="XZ", data=json.dumps(bent))
cmd("tsr.feature.pipe", size=0.8)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert vol(3) > 0.5

# Coil: 40 mm diameter, 5 turns over 50 mm, 5 mm round wire.
cmd("tsr.feature.coil", diameter=4.0, revolutions=5.0, height=5.0, size=0.5)
wire_len = 5 * math.hypot(math.pi * 4.0, 1.0)
expected = math.pi * 0.25 ** 2 * wire_len
assert abs(vol(4) - expected) / expected < 0.02, (vol(4), expected)
# Defined by pitch, tapered, square section: still valid.
cmd("tsr.feature.coil", plane="XZ", x=20.0, diameter=3.0, type="Revolution and Pitch", revolutions=3.0,
    pitch=1.0, angle=math.radians(10), section="Square", size=0.4)
assert tsr.features()[-1]["error"] == "" and vol(5) > 0.1
# Overlapping turns are refused.
try:
    cmd("tsr.feature.coil", diameter=4.0, type="Height and Pitch", height=3.0, pitch=0.3, size=0.5)
except RuntimeError as e:
    assert "overlap" in str(e), e
else:
    raise AssertionError("overlapping coil accepted")
print("api pipe and coil: OK")
