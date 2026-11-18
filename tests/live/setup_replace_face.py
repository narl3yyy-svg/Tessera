# A 4 x 3 x 2 cm block and a construction plane 3 cm up.
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
tsr.run_command("tsr.construct.offsetPlane", plane="XY", distance=3.0)
