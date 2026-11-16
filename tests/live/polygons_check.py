import json
import math
import tsr
sk = json.loads(tsr.features()[0]["inputs"]["data"])
P, ents = sk["points"], sk["entities"]
polys = [c for c in sk["constraints"] if c["type"] == "polygon"]
assert len(polys) == 3, sk["constraints"]
sides = []
for c in polys:
    centre = P[c["p"][0]]
    corners = [P[ents[e]["p"][0]] for e in c["e"]]
    radii = [math.hypot(q[0] - centre[0], q[1] - centre[1]) for q in corners]
    lens = [math.hypot(corners[(i + 1) % 6][0] - corners[i][0], corners[(i + 1) % 6][1] - corners[i][1]) for i in range(6)]
    assert len(corners) == 6 and max(radii) - min(radii) < 1e-6 and max(lens) - min(lens) < 1e-6, (radii, lens)
    sides.append((round(centre[0], 6), round(centre[1], 6), lens[0]))
sides.sort()
circ, insc, edge = sides   # centres (0,0), (0,4), then the edge polygon's off to the right
assert (circ[0], circ[1]) == (0, 0) and abs(circ[2] - 2 * math.tan(math.pi / 6)) < 1e-6, circ   # across the flats 20 mm
assert (insc[0], insc[1]) == (0, 4) and abs(insc[2] - 1) < 1e-6, insc                          # corners 10 mm out
assert abs(edge[2] - 1) < 1e-6 and edge[1] > 0, edge                                           # side 10 mm, above it
# No construction circle for the edge polygon; one each for the others.
assert sum(1 for e in ents if e["type"] == "circle" and e.get("construction")) == 2, ents
print("live polygons: OK")
