import tsr
p = {m["name"]: m for m in tsr.model_parameters()}
assert "stud" in p and "d7" not in p, sorted(p)
assert p["stud"]["owner"] == "Extrude1" and p["stud"]["input"] == "distance", p["stud"]
assert tsr.favorite_parameters() == ["stud"], tsr.favorite_parameters()
print("live parameters table: OK")
