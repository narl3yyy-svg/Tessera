import tsr
f = tsr.features()[-1]
assert f["command"] == "tsr.feature.emboss" and f["error"] == "", tsr.features()
assert f["inputs"]["effect"] == "Emboss", f
v = tsr.mass_properties("Body1")["volume"]
assert abs(v - (48 + 0.1)) < 1e-6, v               # the 1 cm square, 1 mm proud
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[2] - 2.1) < 1e-6, hi
print("live emboss: OK")
