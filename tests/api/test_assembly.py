# Components and joints: a block jointed onto a plate; revolute and slider
# motion, rigid with offset, flip; wrong picks explained.
import math
import tsr

cmd = tsr.run_command


def box(name):
    lo, hi = tsr.bounding_box(name)
    return [round(v, 6) for v in lo + hi]


def near(a, b):
    assert all(abs(x - y) < 1e-6 for x, y in zip(a, b)), (a, b)


cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)                      # Body1: plate, top face at z = 1
cmd("tsr.primitive.box", length=1.0, width=2.0, height=3.0, x=10.0, y=10.0)     # Body2: block, elsewhere
cmd("tsr.assemble.newComponent", name="Plate", bodies="Body1")
cmd("tsr.assemble.newComponent", name="Block", bodies="Body2")
assert [c["name"] for c in tsr.components()] == ["Plate", "Block"]

# Block's bottom face onto the plate's top face: it stands centred on the plate.
cmd("tsr.assemble.joint", origin1="Body2|face|10.5,11,0", origin2="Body1|face|2,2,1", type="Revolute")
j = tsr.features()[-1]
assert j["name"] == "Joint1" and j["error"] == "", j
near(box("Body2"), [1.5, 1, 1, 2.5, 3, 4])
near(box("Body1"), [0, 0, 0, 4, 4, 1])                 # the plate does not move

# Drive the revolute joint 90 degrees: the footprint turns.
tsr.edit_feature(j["id"], rotation=math.pi / 2)
near(box("Body2"), [1, 1.5, 1, 3, 2.5, 4])

# As a slider, 5 mm up the joint axis (away from the plate).
tsr.edit_feature(j["id"], type="Slider", slide=0.5)
near(box("Body2"), [1.5, 1, 1.5, 2.5, 3, 4.5])

# Rigid with a 2 mm gap, then flipped (it faces the other way: into the plate).
tsr.edit_feature(j["id"], type="Rigid", offset=0.2)
near(box("Body2"), [1.5, 1, 1.2, 2.5, 3, 4.2])
tsr.edit_feature(j["id"], offset=0.0, flip="Yes")
near(box("Body2"), [1.5, 1, -2, 2.5, 3, 1])
tsr.edit_feature(j["id"], flip="No")

# The joint follows an edit of the plate: thicker plate, block still on top.
tsr.edit_feature(tsr.features()[0]["id"], height=2.0)
near(box("Body2")[2:3], [2])

# Wrong picks are explained.
for bad in [dict(origin1="Body1|face|2,2,1", origin2="Body1|face|2,2,0"),     # same component
            dict(origin1="Body9|face|0,0,0", origin2="Body1|face|2,2,1"),     # no such body
            dict(origin1="", origin2="Body1|face|2,2,1")]:                   # nothing picked
    try:
        cmd("tsr.assemble.joint", **bad)
    except RuntimeError:
        pass
    else:
        raise AssertionError("accepted %r" % bad)
cmd("tsr.primitive.cylinder", diameter=1.0, height=1.0, x=-10.0)                 # Body3: not in a component
try:
    cmd("tsr.assemble.joint", origin1="Body3|face|-10,0,1", origin2="Body1|face|2,2,2")
except RuntimeError as e:
    assert "New Component" in str(e), e
else:
    raise AssertionError("moved a body that is not in a component")
print("api assembly: OK")

# --- Pin-Slot, Planar and Ball joints, and motion limits (a fresh design).
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)
cmd("tsr.primitive.box", length=1.0, width=2.0, height=3.0, x=10.0, y=10.0)
cmd("tsr.assemble.newComponent", name="Plate", bodies="Body1")
cmd("tsr.assemble.newComponent", name="Block", bodies="Body2")
cmd("tsr.assemble.joint", origin1="Body2|face|10.5,11,0", origin2="Body1|face|2,2,1", type="Pin-Slot", slide=0.5)
j = tsr.features()[-1]
assert j["error"] == "", j
lo, hi = tsr.bounding_box("Body2")
moved = [round(v, 6) for v in lo + hi]
# Slid 5 mm across the plate (along the joint's X), still standing on it.
assert abs(moved[2] - 1) < 1e-6 and abs(moved[5] - 4) < 1e-6, moved
assert abs((moved[0] + moved[3]) / 2 - 2) > 0.4 or abs((moved[1] + moved[4]) / 2 - 2) > 0.4, moved
# Planar: two slides and a turn, still on the plate.
tsr.edit_feature(j["id"], type="Planar", slide=0.3, slide2=0.4, rotation=math.pi / 2)
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[2] - 1) < 1e-6 and abs(hi[2] - 4) < 1e-6, (lo, hi)
cx, cy = (lo[0] + hi[0]) / 2, (lo[1] + hi[1]) / 2
assert abs(math.hypot(cx - 2, cy - 2) - 0.5) < 1e-6, (cx, cy)          # 3-4-5: half a centimetre from the centre
assert abs((hi[0] - lo[0]) - 2) < 1e-6 and abs((hi[1] - lo[1]) - 1) < 1e-6, (lo, hi)   # turned 90 degrees
# Ball: pitched 90 degrees about the joint's X: the 30 mm tall block lies down.
tsr.edit_feature(j["id"], type="Ball", rotation=0.0, pitch=math.pi / 2)
lo, hi = tsr.bounding_box("Body2")
assert abs((hi[2] - lo[2]) - min(1.0, 2.0)) < 1e-6 or abs((hi[2] - lo[2]) - 2.0) < 1e-6, (lo, hi)
# Limits: a revolute turn of 120 degrees held to at most 90.
tsr.edit_feature(j["id"], type="Revolute", pitch=0.0, rotation=math.radians(120), rotationLimits=True,
                 rotationMin=0.0, rotationMax=math.pi / 2)
lo, hi = tsr.bounding_box("Body2")
assert abs((hi[0] - lo[0]) - 2) < 1e-6 and abs((hi[1] - lo[1]) - 1) < 1e-6, (lo, hi)   # stopped at 90
try:
    tsr.edit_feature(j["id"], rotationMin=1.0, rotationMax=0.5)
    raise AssertionError("min above max accepted")
except RuntimeError as e:
    assert "minimum" in str(e), e
# A slider limited to 3 mm.
tsr.edit_feature(j["id"], type="Slider", rotationLimits=False, slide=1.0, slideLimits=True, slideMin=0.0, slideMax=0.3)
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[2] - 1.3) < 1e-6, (lo, hi)
print("joint types and limits: OK")
