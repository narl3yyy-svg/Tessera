import adsk.core
import adsk.fusion

design = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct)
params = design.userParameters
assert params.count == 2, params.count
assert params.itemByName("thickness").expression == "3 mm"
assert abs(params.itemByName("width").value - 2.5) < 1e-12
print("reopened .tsr: OK")
