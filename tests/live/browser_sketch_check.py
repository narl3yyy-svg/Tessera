import json
import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.sketch.create"]
assert len(f) == 1, tsr.features()
assert f[0]["inputs"]["plane"] == "XY", f[0]["inputs"]
sk = json.loads(f[0]["inputs"]["data"])
assert [e["type"] for e in sk["entities"]] == ["circle"], sk["entities"]
print("live browser create sketch: OK")
