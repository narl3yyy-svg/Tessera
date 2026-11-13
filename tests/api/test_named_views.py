# Named views, as in the familiar Browser: saved cameras kept in the design,
# renamed and deleted one undo step at a time, never replaying the history.
import os
import tempfile
import tsr

assert tsr.named_views() == []
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.add_named_view("Corner", eye=(10, -10, 10), target=(1, 1, 1), up=(0, 0, 1), size=6.5)
v = tsr.named_views()
assert [x["name"] for x in v] == ["Corner"], v
assert v[0]["eye"] == (10, -10, 10) and v[0]["target"] == (1, 1, 1) and v[0]["up"] == (0, 0, 1), v
assert v[0]["size"] == 6.5

# Names: unique, never a standard view's.
for bad in ("Corner", "TOP", "HOME", ""):
    try:
        tsr.add_named_view(bad, eye=(0, 0, 5), target=(0, 0, 0))
        raise AssertionError("accepted " + repr(bad))
    except RuntimeError:
        pass
tsr.add_named_view("Underside", eye=(0, 0, -8), target=(0, 0, 0), up=(0, 1, 0))
tsr.rename_named_view("Underside", "Bottom up")
assert [x["name"] for x in tsr.named_views()] == ["Corner", "Bottom up"]

# Undo steps: the rename, then the add; the timeline is untouched.
features = len(tsr.features())
assert tsr.undo()
assert [x["name"] for x in tsr.named_views()] == ["Corner", "Underside"]
assert tsr.undo()
assert [x["name"] for x in tsr.named_views()] == ["Corner"]
assert len(tsr.features()) == features
tsr.delete_named_view("Corner")
assert tsr.named_views() == []
assert tsr.undo()

# Saved with the design.
path = os.path.join(tempfile.mkdtemp(), "views.tsr")
tsr.save(path)
tsr.new_document()
assert tsr.named_views() == []
tsr.open(path)
v = tsr.named_views()
assert [x["name"] for x in v] == ["Corner"] and v[0]["size"] == 6.5, v
print("named views: OK")
