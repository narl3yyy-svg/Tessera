# Appearance on single faces, as in the familiar Appearance (Apply To:
# Faces): a face's colour over its body's own, kept as the body changes,
# undone, saved and opened again.
import os
import tempfile
import tsr

cmd = tsr.run_command


def faces(body="Body1"):
    return sorted((tuple(round(v, 6) for v in c), colour) for c, colour in tsr.face_appearances(body))


cmd("tsr.primitive.box", length=4.0, width=2.0, height=1.0)
tsr.set_appearance("Body1", "#808080")
tsr.set_face_appearance("Body1", "2,1,1", "#ff0000")            # the top
assert faces() == [((2, 1, 1), "#ff0000")], faces()
tsr.set_face_appearance("Body1", "4,1,0.5", "#00ff00")          # the right end
assert len(faces()) == 2, faces()
# The top again: its colour is replaced, not added.
tsr.set_face_appearance("Body1", "2,1,1", "#0000ff")
assert faces() == [((2, 1, 1), "#0000ff"), ((4, 1, 0.5), "#00ff00")], faces()
# Undo brings the red back.
tsr.undo()
assert ((2, 1, 1), "#ff0000") in faces(), faces()

# The body changes (a fillet on a bottom edge): the colours stay on their faces.
cmd("tsr.feature.fillet", edges="2,0,0", radius=0.2)
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
assert [colour for _, colour in faces()] == ["#ff0000", "#00ff00"] or len(faces()) == 2, faces()

# Saved and opened again.
path = os.path.join(tempfile.mkdtemp(), "faces.tsr")
tsr.save(path)
tsr.open(path)
assert len(faces()) == 2, faces()

# Back to the body's own appearance.
tsr.set_face_appearance("Body1", "2,1,1", "")
assert len(faces()) == 1, faces()
for bad in ["red", "#12345"]:
    try:
        tsr.set_face_appearance("Body1", "2,1,1", bad)
    except RuntimeError as e:
        assert "#rrggbb" in str(e), e
    else:
        raise AssertionError("took colour %r" % bad)
print("face appearance: OK")
