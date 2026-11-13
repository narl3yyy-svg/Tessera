import json
import adsk.core
import adsk.fusion
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
t = sk["texts"]
assert len(t) == 1 and t[0]["text"] == "TO" and abs(t[0]["h"] - 1.0) < 1e-12, t
p = sk["points"][t[0]["p"]]
assert abs(p[0] - 1) < 1e-9 and abs(p[1] - 1) < 1e-9, p
# Its letters are profiles: Extrude makes the two solid letters.
tsr.run_command("tsr.feature.extrude", distance=0.3)
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
assert root.bRepBodies.count == 2, root.bRepBodies.count
print("live sketch text: OK")
