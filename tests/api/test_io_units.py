# Units, export to every format, and insert back.
import os
import tempfile
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
assert tsr.units() == "mm"
tsr.set_units("in")
assert tsr.units() == "in"
assert tsr.undo() and tsr.units() == "mm"
try:
    tsr.set_units("furlong")
except RuntimeError:
    pass
else:
    raise AssertionError("bad unit accepted")

tsr.run_command("tsr.primitive.box", length=2.0, width=3.0, height=4.0)   # 20 x 30 x 40 mm
d = tempfile.mkdtemp()
for ext in ("step", "iges", "stl", "obj", "3mf", "brep"):
    p = os.path.join(d, "part." + ext)
    tsr.export(p)
    assert os.path.getsize(p) > 100, (ext, os.path.getsize(p))

# Round trips: exact formats keep the volume, STL closely.
for ext, tol in (("step", 1e-6), ("iges", 1e-3), ("brep", 1e-9), ("stl", 1e-3)):
    tsr.new_document()
    tsr.insert(os.path.join(d, "part." + ext))
    assert root.bRepBodies.count == 1, ext
    v = root.bRepBodies.item(0).volume
    assert abs(v - 24.0) < tol * 24 + 1e-9, (ext, v)

# Inserted bodies take part in modelling and survive save/reopen.
tsr.run_command("tsr.primitive.cylinder", diameter=1.0, height=10.0, x=1.0, y=1.5, z=-1.0, operation="Cut")
v = root.bRepBodies.item(0).volume
p = os.path.join(d, "doc.tsr")
tsr.save(p)
tsr.open(p)
assert abs(root.bRepBodies.item(0).volume - v) < 1e-9
with open(os.path.join(d, "part.3mf"), "rb") as f:
    assert f.read(2) == b"PK"
print("api io/units: OK")
