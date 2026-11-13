import tsr
f = tsr.features()
ex = [x for x in f if x["command"] == "tsr.feature.extrude"]
assert len(ex) == 1 and ex[0]["error"] == "", f
profiles = [p for p in ex[0]["inputs"]["profiles"].split(";") if p]
assert len(profiles) == 1 and float(profiles[0].split(",")[0]) > 5.9, profiles   # the square at x = 60..80 mm
lo, hi = tsr.bounding_box("Body1")
assert abs(lo[0] - 6) < 1e-6 and abs(hi[0] - 8) < 1e-6, (lo, hi)
fl = [x for x in f if x["command"] == "tsr.feature.fillet"]
assert len(fl) == 1 and fl[0]["error"] == "", f
assert len([e for e in fl[0]["inputs"]["edges"].split(";") if e]) == 1, fl[0]["inputs"]
print("live pre-selection: OK")
