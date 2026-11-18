import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.replaceFace"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert f[0]["inputs"]["target"] == "Plane1", f[0]["inputs"]
v = tsr.mass_properties("Body1")["volume"]
assert abs(v - 36) < 1e-9, v
print("live replace face: OK")
