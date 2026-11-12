# Shapes for surface analysis: a filleted block, a sphere and a drafted box.
import math
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
tsr.run_command("tsr.feature.fillet", body="Body1", edges="4,1.5,2;0,1.5,2;2,0,2;2,3,2", radius=0.8)
tsr.run_command("tsr.primitive.sphere", diameter=3.0, x=7.0, y=1.5, z=1.5)
tsr.run_command("tsr.primitive.box", length=3.0, width=3.0, height=2.0, x=-5.0)
tsr.run_command("tsr.feature.draft", body="Body3", faces="-2,1.5,1;-5,1.5,1", plane="XY", angle=math.radians(4))
