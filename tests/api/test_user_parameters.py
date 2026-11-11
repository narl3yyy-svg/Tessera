# Written the way a Fusion script is written: run(context), adsk.* only.
# Followed (in CTest) by --save, --open and check_reopened.py.
import adsk.core
import adsk.fusion


def run(context):
    app = adsk.core.Application.get()
    design = adsk.fusion.Design.cast(app.activeProduct)
    assert design is not None
    params = design.userParameters

    p = params.add("width", adsk.core.ValueInput.createByString("25 mm"), "mm", "plate width")
    assert p.name == "width"
    assert abs(p.value - 2.5) < 1e-12, p.value  # internal units: cm

    q = params.add("thickness", adsk.core.ValueInput.createByReal(0.3), "mm", "")
    assert q.expression == "3 mm", q.expression

    assert params.count == 2
    assert params.itemByName("width").comment == "plate width"
    assert params.itemByName("missing") is None
    assert [x.name for x in params] == ["width", "thickness"]

    try:
        params.add("width", adsk.core.ValueInput.createByReal(1), "mm", "")
    except RuntimeError as e:
        assert "already exists" in str(e)
    else:
        raise AssertionError("duplicate parameter accepted")
    print("api user parameters: OK")
