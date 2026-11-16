# A tube (outer radius 2 cm, inner 1 cm, 2 cm tall) between a plate under it
# and a lid over it: the space inside is closed in.
import tsr
tsr.run_command("tsr.primitive.cylinder", diameter=4.0, height=2.0)
tsr.run_command("tsr.primitive.cylinder", diameter=2.0, height=2.0)
tsr.run_command("tsr.feature.combine", target="Body1", tools="Body2", operation="Cut")
tsr.run_command("tsr.primitive.box", length=6.0, width=6.0, height=0.5, x=-3.0, y=-3.0, z=-0.5)   # plate
tsr.run_command("tsr.primitive.box", length=6.0, width=6.0, height=0.5, x=-3.0, y=-3.0, z=2.0)    # lid
