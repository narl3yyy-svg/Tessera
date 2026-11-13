import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
t = sk["texts"]
assert len(t) == 1 and t[0]["text"] == "AB" and t[0]["path"] == 0 and t[0]["halign"] == "center", t
print("live text on path: OK")
