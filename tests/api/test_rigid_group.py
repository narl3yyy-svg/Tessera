# Rigid Group, as in the familiar Assemble panel: components locked together
# move as one when a joint moves any of them, and cannot be jointed to each
# other. Picks are bodies (each stands for its component) or component names.
import tsr

cmd = tsr.run_command


def box(name):
    lo, hi = tsr.bounding_box(name)
    return [round(v, 6) for v in lo + hi]


def near(a, b):
    assert all(abs(x - y) < 1e-6 for x, y in zip(a, b)), (a, b)


def refused(why, **inputs):
    try:
        cmd("tsr.assemble.rigidGroup", **inputs)
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("accepted %r" % inputs)


cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)                      # Body1: plate
cmd("tsr.primitive.box", length=1.0, width=2.0, height=3.0, x=10.0, y=10.0)     # Body2: block
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=12.0, y=10.0)     # Body3: pin beside the block
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=-10.0)            # Body4: in no component
cmd("tsr.assemble.newComponent", name="Plate", bodies="Body1")
cmd("tsr.assemble.newComponent", name="Block", bodies="Body2")
cmd("tsr.assemble.newComponent", name="Pin", bodies="Body3")

# Wrong picks are explained.
refused("at least two", components="Body2")
refused("at least two", components="Body2;Block")          # one component, picked twice
refused("not in a component", components="Body2;Body4")
refused("not a component or body", components="Body2;Nothing")
refused("letters, digits", name="a b", components="Body2;Body3")

# Block and Pin locked: picked by a body and by name.
cmd("tsr.assemble.rigidGroup", components="Body2;Pin")
g = tsr.features()[-1]
assert g["name"] == "RigidGroup1" and g["error"] == "", g
comps = {c["name"]: c for c in tsr.components()}
assert comps["RigidGroup1"]["rigid"] and comps["RigidGroup1"]["bodies"] == ["Block", "Pin"], comps
assert not comps["Block"]["rigid"]

# A joint moving the block moves the pin with it, kept where it was relative
# to the block (the joint also turns the block half a turn about Z).
pin0 = box("Body3")
cmd("tsr.assemble.joint", origin1="Body2|face|10.5,11,0", origin2="Body1|face|2,2,1", type="Rigid")
j = tsr.features()[-1]
assert j["error"] == "", j
near(box("Body2"), [1.5, 1, 1, 2.5, 3, 4])                  # block on the plate
near(box("Body3"), [-0.5, 2, 1, 0.5, 3, 2])


def centre(b):
    return [(b[i] + b[i + 3]) / 2 for i in range(3)]


def gap(a, b):
    return sum((x - y) ** 2 for x, y in zip(centre(a), centre(b))) ** 0.5


assert abs(gap(box("Body2"), box("Body3")) - gap([10, 10, 0, 11, 12, 3], pin0)) < 1e-6
near(box("Body1"), [0, 0, 0, 4, 4, 1])                       # the plate stays

# Locked components cannot be jointed to each other.
try:
    cmd("tsr.assemble.joint", origin1="Body3|face|0,2.5,2", origin2="Body2|face|2,2,4")
except RuntimeError as e:
    assert "Rigid Group" in str(e), e
else:
    raise AssertionError("jointed two locked components")

# Deleting the group: the joint moves the block alone; the pin stays put.
tsr.delete_feature(g["id"])
assert all(not c["rigid"] for c in tsr.components()), tsr.components()
near(box("Body2"), [1.5, 1, 1, 2.5, 3, 4])
near(box("Body3"), pin0)

# Groups chain: Block+Pin and Pin+Plate lock all three, so the block can no
# longer be jointed onto the plate.
tsr.new_document()
cmd("tsr.primitive.box", length=4.0, width=4.0, height=1.0)
cmd("tsr.primitive.box", length=1.0, width=2.0, height=3.0, x=10.0, y=10.0)
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=12.0, y=10.0)
cmd("tsr.assemble.newComponent", name="Plate", bodies="Body1")
cmd("tsr.assemble.newComponent", name="Block", bodies="Body2")
cmd("tsr.assemble.newComponent", name="Pin", bodies="Body3")
cmd("tsr.assemble.rigidGroup", components="Block;Pin")
cmd("tsr.assemble.rigidGroup", name="Base", components="Body3;Body1")
assert [c["name"] for c in tsr.components() if c["rigid"]] == ["RigidGroup1", "Base"]
try:
    cmd("tsr.assemble.joint", origin1="Body2|face|10.5,11,0", origin2="Body1|face|2,2,1")
except RuntimeError as e:
    assert "Rigid Group" in str(e), e
else:
    raise AssertionError("jointed components locked through two groups")
print("rigid group: OK")
