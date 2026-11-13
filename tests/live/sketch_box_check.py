import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
pts = sk["points"]
lines = [e for e in sk["entities"] if e["type"] == "line" and not e.get("construction")]
# Left and right sides went; the top and bottom (horizontal) stay.
assert len(lines) == 2, lines
for e in lines:
    a, b = pts[e["p"][0]], pts[e["p"][1]]
    assert abs(a[1] - b[1]) < 1e-9 and abs(abs(a[0] - b[0]) - 4.0) < 1e-6, (a, b)
print("live sketch window/crossing selection: OK")
