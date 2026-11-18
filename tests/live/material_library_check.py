import tsr
p = tsr.mass_properties("Body1")
assert p["material"] == "Carbon Fibre", p
assert abs(p["mass"] - 24 * 1.6) < 1e-9, p
print("live material library: OK")
