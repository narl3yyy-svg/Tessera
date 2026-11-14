# Inputs that used to be able to hang the app: huge typed angles, far too
# many pattern copies or coil turns. Each must answer quickly, with a plain
# error where the request cannot be met.
import json
import time
import tsr


def quick(label, fn, expect_error=None, either=False):
    # either: solving or refusing are both fine, as long as it answers.
    t0 = time.monotonic()
    try:
        fn()
        assert expect_error is None, label + ": accepted"
    except RuntimeError as e:
        assert either or (expect_error is not None and expect_error in str(e)), (label, str(e))
    took = time.monotonic() - t0
    assert took < 10, (label, took)


# An angle dimension of 1e18 radians: the solver wraps it in one step.
lines = {"points": [[0, 0], [0, 0], [3, 0], [0, 0.1], [2, 2]],
         "entities": [{"type": "line", "p": [1, 2]}, {"type": "line", "p": [3, 4]}],
         "constraints": [{"type": "angle", "e": [0, 1], "v": 1e18}]}
quick("huge angle", lambda: tsr.run_command("tsr.sketch.create", plane="XY", data=json.dumps(lines)), either=True)

# Coils: at most 1000 turns, however they are asked for.
quick("fine pitch", lambda: tsr.run_command("tsr.feature.coil", diameter=4.0, type="Height and Pitch", height=100.0,
                                            pitch=0.0001, size=0.00005), "1000 turns")
quick("many turns", lambda: tsr.run_command("tsr.feature.coil", diameter=4.0, revolutions=1e6, height=5.0, size=0.5),
      "1000 turns")

# Patterns: at most 1000 copies in all.
tsr.run_command("tsr.primitive.box", length=1.0, width=1.0, height=1.0)
quick("pattern", lambda: tsr.run_command("tsr.feature.rectangularPattern", patternType="Bodies", quantity1=1000,
                                         quantity2=1000), "1000 copies")
sq = {"points": [[0, 0], [0, 0], [1, 0]], "entities": [{"type": "line", "p": [1, 2]}]}
quick("sketch pattern", lambda: tsr.sketch_pattern_rect(json.dumps(sq), [0], 0.0, 1000, 1.0, 1000, 1.0), "1000 copies")
quick("sketch circular", lambda: tsr.sketch_pattern_circular(json.dumps(sq), [0], 0, 100000, 6.283185307179586),
      "1000 copies")
print("robustness: OK")
