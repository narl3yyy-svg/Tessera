# A 40 x 30 x 20 mm box with its four vertical edges rounded (5 mm): the top
# loop is four lines and four arcs meeting without corners.
import tsr
tsr.run_command("tsr.primitive.box", length=4.0, width=3.0, height=2.0)
tsr.run_command("tsr.feature.fillet", edges="0,0,1;4,0,1;4,3,1;0,3,1", radius=0.5)
