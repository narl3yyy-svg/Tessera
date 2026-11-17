import tsr
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
assert ex[0]["inputs"]["participants"] == "Body2", ex[0]["inputs"]
v1, v2 = tsr.mass_properties("Body1")["volume"], tsr.mass_properties("Body2")["volume"]
assert abs(v1 - 8) < 1e-6 and abs(v2 - 6.5) < 1e-6, (v1, v2)
print("live participant bodies: OK")
