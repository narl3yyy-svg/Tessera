import tsr
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
i = ex[0]["inputs"]
assert i["faces"] and i["operation"] == "Join", i
lo, hi = tsr.bounding_box("Body1")
# Seen from the front-right-top, the ray through the front face's centre
# (20, 0, 10) mm leaves the box through the bottom face (at (10, 10, 0)):
# that face moved down by the distance; the top stayed.
assert abs(lo[2] + i["distance"]) < 1e-6 and abs(hi[2] - 2) < 1e-6 and abs(hi[1] - 3) < 1e-6, (lo, hi)
print("live select other: OK")
