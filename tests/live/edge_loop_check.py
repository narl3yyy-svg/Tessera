import math
import adsk.core
import adsk.fusion
import tsr
root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
edges = [e for e in f[0]["inputs"]["edges"].split(";") if e]
assert len(edges) == 4, edges            # the top face's loop
# The 40 x 30 top loop rounded with radius r: the swept corner region (area
# (1 - pi/4) r^2, centroid xc = (10 - 3 pi) / (3 (4 - pi)) r from each side)
# along the loop, mitred at the four corners (Pappus).
r = f[0]["inputs"]["radius"]
xc = (10 - 3 * math.pi) / (3 * (4 - math.pi)) * r
expected = 24 - (1 - math.pi / 4) * r * r * (2 * (4 + 3) - 8 * xc)
v = root.bRepBodies.item(0).volume
assert abs(v - expected) < 1e-6, (v, expected)
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[2] - 2) < 1e-6, (lo, hi)
print("live edge loop: OK")
