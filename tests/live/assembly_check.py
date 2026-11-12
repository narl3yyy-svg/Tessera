import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.assemble.joint"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
j = f[0]["inputs"]
assert j["type"] == "Revolute", j
assert j["origin1"].startswith("Body2|face|") and j["origin2"].startswith("Body1|face|"), j
assert 0.05 < abs(j["rotation"]) < 6.2, j          # Drive Joints turned it part way
lo, hi = tsr.bounding_box("Body2")
assert abs(lo[2] - 1.0) < 1e-6 and abs(hi[2] - 4.0) < 1e-6, (lo, hi)   # standing on the plate (upside down)
cx, cy = (lo[0] + hi[0]) / 2, (lo[1] + hi[1]) / 2
assert abs(cx - 2) < 1e-6 and abs(cy - 2) < 1e-6, (cx, cy)              # centred on the plate's top face
print("live assembly: OK")
