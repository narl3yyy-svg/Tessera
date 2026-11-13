import tsr
f = [x for x in tsr.features() if x["command"] == "tsr.feature.fillet"]
assert len(f) == 1 and f[0]["error"] == "", tsr.features()
edges = [e for e in f[0]["inputs"]["edges"].split(";") if e]
assert len(edges) == 12, edges
print("live window selection of edges: OK")
