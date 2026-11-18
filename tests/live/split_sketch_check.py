import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.splitFace"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert f[0]["inputs"]["tool"] == "Sketch", f[0]["inputs"]
p = tsr.mass_properties("Body1")
assert p["faces"] == 7 and abs(p["volume"] - 24) < 1e-9, p
print("live split face by sketch: OK")
