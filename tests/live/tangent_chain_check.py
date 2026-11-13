import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 2 and all(x["error"] == "" for x in f), tsr.features()
edges = [e for e in f[1]["inputs"]["edges"].split(";") if e]
assert len(edges) == 8, edges          # four lines and four arcs of the top loop
lo, hi = tsr.bounding_box("Body1")
assert abs(hi[2] - 2) < 1e-6, (lo, hi)
print("live tangent chain: OK")
