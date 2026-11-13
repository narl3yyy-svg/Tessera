# Sketch text in a box and along a path, as the familiar Text and Text on
# Path commands: aligned in the box (left / center / right, top / middle /
# bottom, several lines), or letters standing on a curve (left / center /
# right along it, flip to run it the other way).
import json
import tsr
import adsk.core
import adsk.fusion

root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent


def letters(texts, points, entities=()):
    """Extrudes the text; the box of all its solids (x0, y0, x1, y1)."""
    tsr.new_document()
    tsr.run_command("tsr.sketch.create", plane="XY",
                    data=json.dumps({"points": points, "entities": list(entities), "texts": texts}))
    tsr.run_command("tsr.feature.extrude", distance=0.2)
    boxes = [tsr.bounding_box(root.bRepBodies.item(i).name) for i in range(root.bRepBodies.count)]
    assert boxes, "no letters"
    return (min(b[0][0] for b in boxes), min(b[0][1] for b in boxes),
            max(b[1][0] for b in boxes), max(b[1][1] for b in boxes)), len(boxes)


box = [[0, 0], [0, 0], [10, 4]]   # corners (0,0) and (10,4) cm
(x0, y0, x1, y1), n = letters([{"p": 1, "corner": 2, "text": "HI", "h": 1.0}], box)
assert n == 2 and x0 < 0.3 and y0 > -0.05 and y0 < 0.3, (x0, y0, x1, y1)        # left, bottom
(x0, y0, x1, y1), _ = letters([{"p": 1, "corner": 2, "text": "HI", "h": 1.0, "halign": "right", "valign": "top"}], box)
assert 9.5 < x1 <= 10.05 and 3.0 < y1 <= 4.05 and x0 > 7, (x0, y0, x1, y1)        # right, top
(x0, y0, x1, y1), _ = letters([{"p": 1, "corner": 2, "text": "HI", "h": 1.0, "halign": "center", "valign": "middle"}], box)
assert abs((x0 + x1) / 2 - 5) < 0.3 and abs((y0 + y1) / 2 - 2) < 0.4, (x0, y0, x1, y1)
# Two lines: twice as tall, both inside the box.
(x0, y0, x1, y1), n = letters([{"p": 1, "corner": 2, "text": "HI\nHI", "h": 1.0, "valign": "top"}], box)
assert n == 4 and y1 - y0 > 1.6 and y1 <= 4.05, (x0, y0, x1, y1)

# On a path: a line from (0,0) to (10,0); the letters stand on it.
line = [[0, 0], [0, 0], [10, 0]]
(x0, y0, x1, y1), n = letters([{"p": 1, "path": 0, "text": "HI", "h": 1.0}], line,
                              [{"type": "line", "p": [1, 2]}])
assert n == 2 and x0 < 0.3 and abs(y0) < 0.05 and 0.6 < y1 < 1.1, (x0, y0, x1, y1)
(x0, y0, x1, y1), _ = letters([{"p": 1, "path": 0, "text": "HI", "h": 1.0, "halign": "right"}], line,
                              [{"type": "line", "p": [1, 2]}])
assert 9.5 < x1 <= 10.05, (x0, y0, x1, y1)
# Flipped: from the other end, letters below the line (upside down).
(x0, y0, x1, y1), _ = letters([{"p": 1, "path": 0, "text": "HI", "h": 1.0, "flip": True}], line,
                              [{"type": "line", "p": [1, 2]}])
assert y1 < 0.05 and y0 < -0.6 and x1 > 9.5, (x0, y0, x1, y1)
# Round a (construction) circle of radius 3, anticlockwise from its right: the letters
# stay close to the circle, on its inside (left of the way round).
circ = [[0, 0], [0, 0]]
(x0, y0, x1, y1), n = letters([{"p": 1, "path": 0, "text": "ABCDEFGH", "h": 1.0}], circ,
                              [{"type": "circle", "c": 1, "r": 3.0, "construction": True}])
assert n >= 8 and max(abs(x0), abs(x1), abs(y0), abs(y1)) < 3.3, (x0, y0, x1, y1)

# Saved form keeps it.
d = json.loads(tsr.features()[0]["inputs"]["data"])
assert d["texts"][0]["path"] == 0, d["texts"]
print("text box and path: OK")
