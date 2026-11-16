import json
import tsr
data = tsr.features()[0]["inputs"]["data"]
sk = json.loads(data)
cs = [c for c in sk["constraints"] if c["type"] == "curvature"]
assert len(cs) == 1, sk["constraints"]
sp = cs[0]["e"][0]
assert sk["entities"][sp]["type"] == "spline", sk["entities"][sp]
x, y, dx, dy, k = tsr.sketch_curve_end(data, sp)
assert abs(x) < 1e-6 and abs(y) < 1e-6, (x, y)                   # starts at the line's end
assert abs(dx - 1) < 1e-6 and abs(dy) < 1e-6 and abs(k) < 1e-6, (dx, dy, k)   # straight on, unbent
print("live curvature constraint: OK")
