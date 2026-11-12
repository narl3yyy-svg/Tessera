import json
import tsr
f = tsr.features()
sk_f = [x for x in f if x["command"] == "tsr.sketch.create"]
assert len(sk_f) == 1, f
inputs = sk_f[0]["inputs"]
plane = inputs["plane"]
assert plane.startswith("custom:"), plane                 # on the picked face ...
oz = float(plane[len("custom:"):].split(",")[2])
assert abs(oz + inputs.get("offset", 0) - 2.0) < 1e-6, plane   # ... the top face, z = 20 mm
sk = json.loads(inputs["data"])
lines = [e for e in sk["entities"] if e["type"] == "line" and not e.get("projected")]
assert len(lines) == 3, sk["entities"]                    # one of four deleted
assert sum(1 for e in lines if e.get("construction")) == 1, lines
cons = [c["type"] for c in sk["constraints"]]
assert "parallel" in cons, cons
assert "horizontal" not in cons and "vertical" not in cons, cons
print("live sketch habits: OK", cons)
