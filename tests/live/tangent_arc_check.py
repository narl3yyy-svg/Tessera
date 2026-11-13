import json
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents, cons = sk["points"], sk["entities"], sk["constraints"]
arcs = [e for e in ents if e["type"] == "arc"]
assert len(arcs) == 2, ents
centres = sorted((round(P[a["c"]][0], 9), round(P[a["c"]][1], 9)) for a in arcs)
assert centres == [(2, 1), (2, 3)], centres                 # 10 mm radius each, one above the other
assert all(abs(a["r"] - 1) < 1e-9 for a in arcs), arcs
tangents = [c for c in cons if c["type"] == "tangent"]
assert len(tangents) == 2, cons                             # line-arc and arc-arc
line = [e for e in ents if e["type"] == "line"][0]
assert set(line["p"]) & set(arcs[0]["p"] + arcs[1]["p"]), (line, arcs)   # the first arc starts on the line's end
print("live tangent arc: OK")
