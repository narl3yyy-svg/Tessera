# A plate and a block, each in its own component.
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=4.0, height=1.0)                     # plate, top at 10 mm
tsr.run_command("tsr.primitive.box", length=1.0, width=2.0, height=3.0, x=6.0, y=1.0)      # block beside it
tsr.run_command("tsr.assemble.newComponent", name="Plate", bodies="Body1")
tsr.run_command("tsr.assemble.newComponent", name="Block", bodies="Body2")
