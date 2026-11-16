import tsr
g = [c for c in tsr.components() if c["rigid"]]
assert len(g) == 1, tsr.components()
assert g[0]["name"] == "RigidGroup1" and sorted(g[0]["bodies"]) == ["Block", "Pin"], g
f = tsr.features()[-1]
assert f["command"] == "tsr.assemble.rigidGroup" and f["error"] == "", f
print("live rigid group: OK")
