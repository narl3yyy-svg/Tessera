# Boundary Fill, as in the familiar Create menu: the space that tool bodies
# (and a plane) enclose is divided into cells; ticked cells become a body, or
# are joined to / cut from the first tool. Cells are recorded as points
# inside them.
import math
import tsr

cmd = tsr.run_command


def vol(body):
    return tsr.mass_properties(body)["volume"]


def near(a, b, tol=1e-6):
    assert abs(a - b) < tol, (a, b)


def exists(body):
    try:
        tsr.bounding_box(body)
        return True
    except Exception:
        return False


def tube():
    # Body1: a tube (outer radius 2, inner 1, 2 cm tall) on Body2, a plate.
    cmd("tsr.primitive.cylinder", diameter=4.0, height=2.0)
    cmd("tsr.primitive.cylinder", diameter=2.0, height=2.0)
    cmd("tsr.feature.combine", target="Body1", tools="Body2", operation="Cut")
    cmd("tsr.primitive.box", length=6.0, width=6.0, height=0.5, x=-3.0, y=-3.0, z=-0.5)


def refused(why, **inputs):
    try:
        cmd("tsr.feature.boundaryFill", **inputs)
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("accepted %r" % inputs)


tube()
names = [n for n in ("Body1", "Body2", "Body3") if exists(n)]
assert len(names) == 2, names
plate = names[1]
cmd("tsr.primitive.box", length=6.0, width=6.0, height=0.5, x=-3.0, y=-3.0, z=2.0)   # a lid
lid = [n for n in ("Body2", "Body3", "Body4") if exists(n) and n != plate][0]
tools = ";".join(["Body1", plate, lid])

cells = tsr.boundary_fill_cells(tools)
assert len(cells) == 4, cells                          # the tube, the plate, the lid and the space inside
inner = [c for c in cells if abs(c["volume"] - 2 * math.pi) < 1e-6]
assert len(inner) == 1, cells

refused("Cells", tools=tools)
refused("Tools", cells=inner[0]["ref"])
refused("no longer exists", tools=tools, cells="40,40,40")

# The space inside the tube becomes a new body; the tools stay (Remove Tools off).
cmd("tsr.feature.boundaryFill", tools=tools, cells=inner[0]["ref"], removeTools=False)
f = tsr.features()[-1]
assert f["name"].startswith("BoundaryFill") and f["error"] == "", f
filled = [n for n in ("Body2", "Body3", "Body4", "Body5") if exists(n) and n not in (plate, lid)]
assert len(filled) == 1, filled
near(vol(filled[0]), 2 * math.pi)
assert exists("Body1") and exists(plate) and exists(lid)

# Remove Tools: only the filled body is left.
tsr.edit_feature(f["id"], removeTools=True)
left = [n for n in ("Body%d" % i for i in range(1, 7)) if exists(n)]
assert len(left) == 1, left
near(vol(left[0]), 2 * math.pi)

# Join: the space joined to the first tool, the tube: a solid cylinder.
tsr.edit_feature(f["id"], removeTools=False, operation="Join")
near(vol("Body1"), 8 * math.pi)

# Two cells at once: the space and the lid, joined into one new body.
lid_cell = [c for c in cells if c["volume"] > 17][-1]   # the plates are 18 cm3; the lid is the higher one
tsr.edit_feature(f["id"], operation="New Body", cells=inner[0]["ref"] + ";" + lid_cell["ref"])
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
near(sum(vol(n) for n in ("Body2", "Body3", "Body4", "Body5") if exists(n) and n not in (plate, lid)), 2 * math.pi + 18)

# --- A plane closes the top instead of the lid.
tsr.new_document()
tube()
cmd("tsr.construct.offsetPlane", plane="XY", distance=2.0)
plane = tsr.features()[-1]["name"]
plate = [n for n in ("Body2", "Body3") if exists(n)][0]
cells = tsr.boundary_fill_cells("Body1;" + plate, plane)
inner = [c for c in cells if abs(c["volume"] - 2 * math.pi) < 1e-6]
assert len(inner) == 1, cells
refused("Plane", tools="Body1;" + plate, withPlane=True, cells=inner[0]["ref"])
cmd("tsr.feature.boundaryFill", tools="Body1;" + plate, withPlane=True, plane=plane, cells=inner[0]["ref"], operation="Join")
near(vol("Body1"), 8 * math.pi)
print("boundary fill: OK")
