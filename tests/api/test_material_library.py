# The material library, as the familiar Physical Material browser and Material
# Editor, offline: materials of your own kept on this machine (here a test
# file), and a copy carried by each design that uses one.
import json
import os
import tempfile
import tsr

lib = os.path.join(tempfile.mkdtemp(), "materials.json")
os.environ["TESSERA_MATERIALS"] = lib
cmd = tsr.run_command

built_in = len(tsr.materials())
assert built_in >= 17, tsr.materials()
tsr.add_material("Carbon Fibre", 1.6, "#202020")
names = [n for n, _ in tsr.materials()]
assert "Carbon Fibre" in names and len(names) == built_in + 1, names
assert json.load(open(lib))[0]["name"] == "Carbon Fibre"

cmd("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.set_material("Body1", "Carbon Fibre")
p = tsr.mass_properties("Body1")
assert abs(p["mass"] - 8 * 1.6) < 1e-9 and p["material"] == "Carbon Fibre", p

# Wrong materials are explained.
for args, why in [(("Steel", 2.0), "built-in"), (("Foam", 0.0), "density"), (("Foam", 0.1, "grey"), "#rrggbb"),
                  (("", 1.0), "name")]:
    try:
        tsr.add_material(*args)
    except RuntimeError as e:
        assert why in str(e), e
    else:
        raise AssertionError("took %r" % (args,))

# The design carries its copy: gone from the library, it still weighs the same,
# saved and opened again too.
path = os.path.join(tempfile.mkdtemp(), "cf.tsr")
tsr.save(path)
tsr.remove_material("Carbon Fibre")
assert json.load(open(lib)) == []
assert "Carbon Fibre" in [n for n, _ in tsr.materials()]
tsr.open(path)
assert abs(tsr.mass_properties("Body1")["mass"] - 12.8) < 1e-9

# Renamed in the library (the Material Editor's Save).
tsr.new_document()
tsr.add_material("Foam", 0.05, "#e8e2c8")
tsr.add_material("Packing Foam", 0.04, "#e8e2c8", rename="Foam")
assert [m["name"] for m in json.load(open(lib))] == ["Packing Foam"]
try:
    tsr.remove_material("Nothing")
except RuntimeError as e:
    assert "no material" in str(e), e
else:
    raise AssertionError("removed a material that is not there")
print("material library: OK")
