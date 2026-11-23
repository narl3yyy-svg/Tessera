import tsr
planes = tsr.construction()["planes"]
assert len(planes) == 1, planes
name, o, d = planes[0]
assert name == "Plane1" and abs(o[0] - 2) < 1e-9 and abs(abs(d[0]) - 1) < 1e-9, planes
print("live plane along path: OK")
