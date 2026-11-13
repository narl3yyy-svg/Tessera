import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
splines = [e for e in sk["entities"] if e["type"] == "spline"]
kinds = sorted(e.get("kind", "fit") for e in splines)
assert kinds == ["conic", "control"], splines             # the fit spline was thrown away
conic = [e for e in splines if e.get("kind") == "conic"][0]
assert abs(conic["rho"] - 0.3) < 1e-12, conic              # set by double-clicking it
P = sk["points"]
s, v, e = (P[i] for i in conic["fit"])
assert abs(v[0] - 2) < 1e-9 and abs(v[1] - 2) < 1e-9, v   # the vertex where clicked (20, 20 mm)
ctrl = [e for e in splines if e.get("kind") == "control"][0]
assert len(ctrl["fit"]) == 4, ctrl
print("live conic and control point spline: OK")
