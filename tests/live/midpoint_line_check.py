import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts, ents = sk["points"], sk["entities"]
lines = [e for e in ents if e["type"] == "line"]
assert len(lines) == 1, ents
a, b = (pts[i] for i in lines[0]["p"])
ends = sorted([(round(a[0], 6), round(a[1], 6)), (round(b[0], 6), round(b[1], 6))])
assert ends == [(0.0, 1.0), (4.0, 3.0)], ends
assert any(c["type"] == "midpoint" for c in sk["constraints"]), sk["constraints"]
assert sum(1 for e in ents if e["type"] == "arc") == 1, ents      # the A key reached the sketch
print("live midpoint line: OK")
