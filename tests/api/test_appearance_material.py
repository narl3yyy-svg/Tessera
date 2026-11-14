# Appearance and Physical Material: per body, kept through save and open,
# their own undo steps, and the material's density gives the mass.
import os
import tempfile
import tsr

tsr.run_command("tsr.primitive.box", length=2.0, width=3.0, height=4.0)      # 24 cm^3
names = [m[0] for m in tsr.materials()]
assert "Steel" in names and "Aluminum" in names and "PLA" in names, names
tsr.set_material("Body1", "Aluminum")
mp = tsr.mass_properties("Body1")
assert mp["material"] == "Aluminum" and abs(mp["mass"] - 24 * 2.70) < 1e-9, mp
tsr.set_appearance("Body1", "#ff8800")
assert tsr.mass_properties("Body1")["color"] == "#ff8800"
for bad in [lambda: tsr.set_material("Body1", "Unobtainium"), lambda: tsr.set_appearance("Body1", "orange"),
            lambda: tsr.set_material("Nope", "Steel")]:
    try:
        bad()
        raise AssertionError("accepted")
    except RuntimeError:
        pass
# Undo takes the colour back, then the material.
tsr.undo()
assert tsr.mass_properties("Body1")["color"] == ""
tsr.redo()
# Kept by body name through a timeline edit and through save / open.
tsr.edit_feature(tsr.features()[0]["id"], height=5.0)
mp = tsr.mass_properties("Body1")
assert mp["color"] == "#ff8800" and abs(mp["mass"] - 30 * 2.70) < 1e-9, mp
path = os.path.join(tempfile.mkdtemp(), "looks.tsr")
tsr.save(path)
tsr.new_document()
tsr.open(path)
mp = tsr.mass_properties("Body1")
assert mp["material"] == "Aluminum" and mp["color"] == "#ff8800", mp
tsr.set_material("Body1", "")
assert "mass" not in tsr.mass_properties("Body1")
print("appearance / material: OK")
