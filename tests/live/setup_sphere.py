# A 30 mm diameter sphere centred on the origin: the XY plane cuts it in a
# 15 mm radius circle.
import tsr
tsr.run_command("tsr.primitive.sphere", diameter=3.0)
# An empty sketch on XY, opened from the Browser (the sphere hides the plane).
tsr.run_command("tsr.sketch.create", plane="XY", data="{}")
