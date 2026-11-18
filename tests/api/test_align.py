# Align, as in the familiar Modify menu: a body moved so a face, edge or
# point lines up with one on another body.
import math
import tsr

cmd = tsr.run_command


def box(name="Body2"):
    lo, hi = tsr.bounding_box(name)
    return [round(v, 6) for v in lo + hi]


def near(a, b):
    assert all(abs(x - y) < 1e-6 for x, y in zip(a, b)), (a, b)


cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)                # Body1
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=10.0)        # Body2, beside it
# Its bottom face onto Body1's top: it sits on top, centred.
cmd("tsr.feature.align", **{"from": "Body2|face|10.5,0.5,0", "to": "Body1|face|1,1,2"})
a = tsr.features()[-1]
assert a["error"] == "", a
near(box(), [0.5, 0.5, 2, 1.5, 1.5, 3])
near(box("Body1"), [0, 0, 0, 2, 2, 2])                                     # the target stays
# Flip: facing the same way, it sinks into Body1 instead.
tsr.edit_feature(a["id"], flip=True)
near(box(), [0.5, 0.5, 1, 1.5, 1.5, 2])
# Turned 45 degrees about the shared normal.
tsr.edit_feature(a["id"], flip=False, angle=math.pi / 4)
h = math.sqrt(2) / 2
near(box(), [1 - h, 1 - h, 2, 1 + h, 1 + h, 3])
# A copy keeps the original.
tsr.edit_feature(a["id"], angle=0.0, copy=True)
near(box("Body2"), [10, 0, 0, 11, 1, 1])
near(box("Body3"), [0.5, 0.5, 2, 1.5, 1.5, 3])
tsr.delete_feature(a["id"])

# A corner onto a corner: moved, not turned.
cmd("tsr.feature.align", **{"from": "Body2|vertex|10,0,0", "to": "Body1|vertex|2,2,2"})
near(box(), [2, 2, 2, 3, 3, 3])
tsr.undo()

# An edge onto an edge: they become one line.
cmd("tsr.feature.align", **{"from": "Body2|edge|10.5,0,0", "to": "Body1|edge|1,0,2"})
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[1]) < 1e-6 or abs(hi[1]) < 1e-6, (lo, hi)                   # on the line y = 0 ...
assert abs(lo[2] - 2) < 1e-6 or abs(hi[2] - 2) < 1e-6, (lo, hi)            # ... z = 2

# Wrong picks are explained.
for bad, why in [({"from": "Body2|face|10.5,0.5,0", "to": "Body2|face|10.5,0.5,1"}, "another body"),
                 ({"from": "", "to": "Body1|face|1,1,2"}, "From")]:
    try:
        cmd("tsr.feature.align", **bad)
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("accepted %r" % bad)
print("align: OK")
