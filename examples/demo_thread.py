# An M10 bolt shank and an M10 threaded hole.
import tsr

tsr.run_command("tsr.primitive.cylinder", diameter=1.0, height=3.0)
tsr.run_command("tsr.primitive.cylinder", diameter=1.7, height=0.7, z=3.0, operation="Join")
tsr.run_command("tsr.feature.thread", body="Body1", faces="0.5,0,1", fullLength="No", length=2.0, offset=0.0)
tsr.run_command("tsr.primitive.box", length=3.0, width=3.0, height=1.5, x=2.5, y=-1.5)
tsr.run_command("tsr.primitive.cylinder", diameter=1.0, height=1.5, x=4.0, operation="Cut", target="Body2")
tsr.run_command("tsr.feature.thread", body="Body2", faces="4.5,0,0.75")
