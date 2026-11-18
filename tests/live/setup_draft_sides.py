# A 2 cm cube and a construction plane through its middle (z = 1 cm).
import tsr
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.run_command("tsr.construct.offsetPlane", plane="XY", distance=1.0)
