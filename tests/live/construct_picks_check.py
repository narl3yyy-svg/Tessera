import tsr
pat = [f for f in tsr.features() if f["command"] == "tsr.feature.circularPattern"]
assert len(pat) == 1 and pat[0]["inputs"]["axis"] == "Axis1" and pat[0]["error"] == "", pat
ax = [f for f in tsr.features() if f["command"] == "tsr.construct.axisTwoPoints"]
assert len(ax) == 1 and ax[0]["error"] == "", tsr.features()
assert sorted(ax[0]["inputs"]["vertices"].split(";")) == ["point:Point1", "point:Point2"], ax[0]["inputs"]
name, o, d = tsr.construction()["axes"][-1]
assert name == "Axis2" and abs(abs(d[0]) - 1) < 1e-9, (name, d)
print("live construct picks: OK")
