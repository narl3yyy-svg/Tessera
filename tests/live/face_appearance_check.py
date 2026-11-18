import tsr
info = tsr.mass_properties("Body1")
assert info["color"] == "#2f6fc4", info["color"]                       # the body: blue
faces = sorted((tuple(round(v, 4) for v in c), colour) for c, colour in tsr.face_appearances("Body1"))
assert [colour for _, colour in faces] == ["#c8302c", "#c8302c"], faces  # two faces red
centres = [c for c, _ in faces]
assert (2.0, 1.5, 2.0) in centres and (2.0, 0.0, 1.0) in centres, centres
print("live face appearance: OK")
