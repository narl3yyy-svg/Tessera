import tsr
v = tsr.named_views()
assert [x["name"] for x in v] == ["Side"], v
eye, target, up = v[0]["eye"], v[0]["target"], v[0]["up"]
d = [e - t for e, t in zip(eye, target)]
n = sum(c * c for c in d) ** 0.5
assert abs(d[0] / n) < 1e-6 and d[1] / n < -0.999999 and abs(d[2] / n) < 1e-6, d   # from the front (-Y)
assert up[2] > 0.999999, up
assert v[0]["size"] > 0
print("live named views: OK")
