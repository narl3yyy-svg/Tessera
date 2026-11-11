# A small bracket built only from primitives and booleans: base plate, a boss,
# a through hole and two mounting holes. Used by the gui_render test.
import tsr

cmd = tsr.run_command
cmd("tsr.primitive.box", length=8.0, width=5.0, height=1.0)
cmd("tsr.primitive.cylinder", diameter=3.0, height=2.5, x=4.0, y=2.5, z=1.0, operation="Join")
cmd("tsr.primitive.cylinder", diameter=1.6, height=5.0, x=4.0, y=2.5, z=-1.0, operation="Cut")
for x in (1.0, 7.0):
    cmd("tsr.primitive.cylinder", diameter=0.6, height=3.0, x=x, y=2.5, z=-1.0, operation="Cut")
cmd("tsr.primitive.torus", diameter=3.4, section=0.5, x=4.0, y=2.5, z=1.0, operation="Join")
cmd("tsr.primitive.sphere", diameter=1.5, x=11.0, y=2.5, z=0.75)
print("features:", ", ".join(f["name"] for f in tsr.features()))
