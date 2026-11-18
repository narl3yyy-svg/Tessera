import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.align"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
lo, hi = tsr.bounding_box("Body2")
got = [round(v, 6) for v in lo + hi]
assert got == [0.5, 0.5, 2, 1.5, 1.5, 3], got
print("live align: OK")
