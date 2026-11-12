import tsr
cmds = [f["command"] for f in tsr.features()]
assert cmds == ["tsr.sketch.create"], cmds
print("live timeline delete: OK")
