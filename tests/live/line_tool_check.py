import json
import tsr
f = tsr.features()
assert len(f) == 1 and f[0]["command"] == "tsr.sketch.create", f
sk = json.loads(f[0]["inputs"]["data"])
types = [e["type"] for e in sk["entities"]]
assert types.count("arc") == 1, types
assert types.count("line") >= 6, types   # 2 chain lines + 4 rectangle sides
cons = [c["type"] for c in sk["constraints"]]
assert "tangent" in cons and "horizontal" in cons, cons
dims = [c.get("v") for c in sk["constraints"] if c["type"] == "distance"]
assert any(abs(d - 3.0) < 1e-6 for d in dims) and any(abs(d - 2.0) < 1e-6 for d in dims), dims
print("live line tool: OK")
