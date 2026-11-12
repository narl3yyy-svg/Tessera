import tsr
ex = [f for f in tsr.features() if f["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", tsr.features()
i = ex[0]["inputs"]
assert i["faces"] and i["operation"] == "Join" and i["distance"] > 0.2, i
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[0] - (4 + i["distance"])) < 1e-6 and abs(hi[2] - 2) < 1e-6, (lo, hi)   # grew in +X only
print("live face extrude: OK (%.2f mm out of the side face)" % (i["distance"] * 10))
