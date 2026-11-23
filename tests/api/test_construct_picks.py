# Construction points as picks, as in the familiar tool: Axis Through Two
# Points and Plane Through Three Points take construction points as well as
# body vertices (no body needed).
import tsr

cmd = tsr.run_command

cmd("tsr.construct.offsetPlane", plane="YZ", distance=6.0)             # Plane1: x = 6
cmd("tsr.construct.offsetPlane", plane="XY", distance=3.0)             # Plane2: z = 3
cmd("tsr.construct.pointThreePlanes", plane="XZ", plane2="YZ", plane3="Plane2")        # Point1 (0, 0, 3)
cmd("tsr.construct.pointThreePlanes", plane="XZ", plane2="Plane1", plane3="Plane2")    # Point2 (6, 0, 3)
cmd("tsr.construct.pointThreePlanes", plane="XY", plane2="YZ", plane3="XZ")            # Point3 (0, 0, 0)
pts = {n: tuple(round(v, 9) for v in p) for n, p in tsr.construction()["points"]}
assert pts == {"Point1": (0, 0, 3), "Point2": (6, 0, 3), "Point3": (0, 0, 0)}, pts

cmd("tsr.construct.axisTwoPoints", vertices="point:Point1;point:Point2")
a = tsr.features()[-1]
assert a["error"] == "", a
name, o, d = tsr.construction()["axes"][-1]
assert name == "Axis1" and abs(abs(d[0]) - 1) < 1e-9 and abs(o[2] - 3) < 1e-9, (o, d)

cmd("tsr.construct.planeThreePoints", vertices="point:Point1;point:Point2;point:Point3")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
name, o, d = tsr.construction()["planes"][-1]
assert abs(abs(d[1]) - 1) < 1e-9, d                                    # the XZ plane, through all three

# A body vertex and a construction point together.
cmd("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=10.0)
cmd("tsr.construct.axisTwoPoints", body="Body1", vertices="10,0,0;point:Point3")
assert tsr.features()[-1]["error"] == "", tsr.features()[-1]
try:
    cmd("tsr.construct.axisTwoPoints", vertices="point:Point1;point:Nothing")
except RuntimeError as e:
    assert "Nothing" in str(e), e
else:
    raise AssertionError("took a point that is not there")
print("construct picks: OK")
