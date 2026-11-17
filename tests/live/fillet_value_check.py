import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
assert len([e for e in f[0]["inputs"]["edges"].split(";") if e]) == 3, f[0]["inputs"]
assert abs(f[0]["inputs"]["radius"] - 0.4) < 1e-9, f[0]["inputs"]["radius"]   # 4 mm
print("live fillet value: OK")
