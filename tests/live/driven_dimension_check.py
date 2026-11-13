import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, cons = sk["points"], sk["constraints"]
line = [e for e in sk["entities"] if e["type"] == "line"][0]
a, b = line["p"]
end = pts[b] if pts[a] == [0, 0] else pts[a]
assert abs(end[0] - 4) < 1e-6 and abs(end[1] - 2) < 1e-6, end    # driven by the two spans
driven = [c for c in cons if c.get("driven")]
assert len(driven) == 1 and driven[0]["type"] == "distance" and "lx" in driven[0], cons
print("live driven dimension: OK")
