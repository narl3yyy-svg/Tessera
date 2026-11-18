# A 2 cm cube, and a 1 cm cube beside it.
import tsr
tsr.run_command("tsr.primitive.box", length=2.0, width=2.0, height=2.0)
tsr.run_command("tsr.primitive.box", length=1.0, width=1.0, height=1.0, x=4.0)
