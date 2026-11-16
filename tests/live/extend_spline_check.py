import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
sp = [e for e in sk["entities"] if e["type"] == "spline"][0]
end = sk["points"][sp["fit"][-1]]
assert abs(end[0] - 5) < 1e-6 and abs(end[1]) < 1e-6, end   # on the line at x = 50 mm
print("live extend spline: OK")
