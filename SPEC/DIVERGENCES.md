# Known divergences

Every gap between Tessera and the plan or the reference behaviour goes here (plan §9).
One line per item: id, what differs, why, and the phase that closes it.

| Id | Divergence | Reason | Closes in |
|---|---|---|---|
| P0-1 | Expressions accept only `number [unit]`: no arithmetic, functions or parameter references | P0 scope | P1 (expression engine) |
| P0-2 | The ribbon is a `QTabWidget` in a fixed toolbar, text-only buttons; no KDDockWidgets, no icons | P0 scope; icons must be rebuilt from spec, not copied | P0 follow-up / R2 |
| P0-3 | `.tsr` members are all STORED (no deflate) | No compression dependency in core yet | before 1.0 |
| P0-4 | Undo depth is capped at 1,000,000 steps, not unbounded | OCAF needs a numeric limit | accepted |
| P0-5 | No 3D viewport; the bodies list in the browser is the only view of geometry | tsr-view not started | P2 |
| P0-6 | adsk shim covers only `Application.get/activeProduct/version`, `ValueInput.createByReal/createByString`, `Design.cast/userParameters/rootComponent`, `UserParameters.add/count/item/itemByName`, `UserParameter` read-only properties, `Component.bRepBodies`, `BRepBody.name/volume/area` | P0 scope | R6 / P10 |
| P0-7 | adsk error behaviour (exception type and text) is assumed to be `RuntimeError` with a message; not yet checked against the reference | Not yet probed in the reference (R6) | R6 |
| P0-8 | Builds against OCCT 7.9.2 (the Kubuntu 26.04 package), not 8.0 | 8.0 not packaged | when packaged, or a source build |
| P0-9 | Lab 10.0.60.100 is 4 cores / 15 GB / iGPU, not the plan's 32 cores / 128 GB; it cannot host the Windows reference VM | Hardware | Hardware decision pending |
