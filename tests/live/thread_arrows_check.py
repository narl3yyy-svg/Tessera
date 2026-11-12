import tsr
th = [x for x in tsr.features() if x["command"] == "tsr.feature.thread"]
assert len(th) == 1 and th[0]["error"] == "", tsr.features()
i = th[0]["inputs"]
assert i["fullLength"] == "No", i
assert i["offset"] > 0.1 and abs(i["length"] - 1.0) > 1e-6, i   # both dragged from their defaults
print("live thread arrows: OK (offset %.2f mm, length %.2f mm)" % (i["offset"] * 10, i["length"] * 10))
