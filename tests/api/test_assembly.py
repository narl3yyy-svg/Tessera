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
