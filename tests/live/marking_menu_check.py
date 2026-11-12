import tsr
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
lo, hi = tsr.bounding_box("Body1")
assert hi[2] > 2.2, (lo, hi)   # grew upwards from the top face
print("live marking menu: OK")
