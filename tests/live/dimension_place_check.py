import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, ents, cons = sk["points"], sk["entities"], sk["constraints"]
hd = [c for c in cons if c["type"] == "horizontalDistance"]
assert len(hd) == 1 and abs(hd[0]["v"] - 4.0) < 1e-9 and "lx" in hd[0] and "ly" in hd[0], cons
a, b = hd[0]["p"]
assert abs((pts[b][0] - pts[a][0]) - 4.0) < 1e-6, (pts[a], pts[b])   # left to right, 40 mm
# Placed above the line: the value sits above the line's higher end.
assert hd[0]["ly"] > 0, hd[0]
dia = [c for c in cons if c["type"] == "diameter"]
assert len(dia) == 1 and abs(dia[0]["v"] - 2.5) < 1e-9 and "lx" in dia[0], cons
circle = [e for e in ents if e["type"] == "circle"][0]
assert abs(circle["r"] - 1.25) < 1e-6, circle
print("live dimension placement: OK")
