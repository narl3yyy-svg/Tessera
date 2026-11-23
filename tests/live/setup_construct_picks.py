# A block, an axis standing at x = 6 cm (where the XZ plane meets Plane1)
# and two construction points 3 cm up: (0, 0, 3) and (6, 0, 3).
import tsr
cmd = tsr.run_command
cmd("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
cmd("tsr.construct.offsetPlane", plane="YZ", distance=6.0)
cmd("tsr.construct.offsetPlane", plane="XY", distance=3.0)
cmd("tsr.construct.axisTwoPlanes", plane="XZ", plane2="Plane1")
cmd("tsr.construct.pointThreePlanes", plane="XZ", plane2="YZ", plane3="Plane2")
cmd("tsr.construct.pointThreePlanes", plane="XZ", plane2="Plane1", plane3="Plane2")
