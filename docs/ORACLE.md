# Reference parts

90 parts with known answers, from SolidCraft's kernel-neutral oracle
(`tests/oracle/cases`, MIT; see `tests/oracle/NOTICE`). Each case is a recipe
(sketches and features) and what the finished part must measure: body count,
volume, area, centre of mass, bounding box and, where the geometry fixes it,
the face count. The values are worked out by hand or come from an open-source
CAD build; none come from a commercial product.

`tests/oracle/run_oracle.py` replays each recipe through Tessera's own commands
and compares. The CTest `oracle` runs all of them and fails if any case listed
in `tests/oracle/required.txt` stops passing. Run it alone with:

```bash
ctest --test-dir build -R oracle --output-on-failure
```

Results: *unsupported* means the recipe uses something Tessera does not have
yet (sheet metal, variable-radius fillets, thin extrudes, holes on curved
faces); *fail* and
*error* are differences to investigate.

70 pass, 1 fail, 0 error, 19 unsupported of 90.

| Case | Result | Notes |
|---|---|---|
| 01-box | pass |  |
| 02-cylinder | pass |  |
| 03-box-through-hole | pass |  |
| 04-revolve-vase | pass |  |
| 05-taper-extrude | pass |  |
| 06-symmetric-extrude | pass |  |
| 07-fillet-all-edges | pass |  |
| 08-chamfer | pass |  |
| 09-shell | pass |  |
| 10-rect-pattern-holes | pass |  |
| 11-circular-pattern-flange | pass |  |
| 12-mirror-feature | pass |  |
| 13-combine-join | pass |  |
| 14-combine-cut | pass |  |
| 15-combine-intersect | pass |  |
| 16-sweep | pass |  |
| 17-loft | pass |  |
| 18-hole-features | pass |  |
| 19-l-bracket-constrained | pass |  |
| 20-slot-constrained | pass |  |
| 21-draft | pass |  |
| 22-split-body | pass |  |
| 23-bracket-multifeature | pass |  |
| 24-user-parameters | pass |  |
| 25-sketch-triangle | pass |  |
| 26-sketch-belt | unsupported | no point found inside a profile |
| 27-sketch-trapezoid | pass |  |
| 28-blind-pocket-fillets | pass |  |
| 29-two-sided-and-partial-revolve | pass |  |
| 30-fillet-after-shell | pass |  |
| 31-fillet-l-all-edges | pass |  |
| 32-boss-plate-fillets | pass |  |
| 33-fillet-tangent-chain | pass |  |
| 34-chamfer-then-fillet | pass |  |
| 35-fillet-curved-curved | pass |  |
| 36-corner-blend-two-radii | pass |  |
| 37-pyramid-apex-blend | pass |  |
| 38-coincident-cylinders | pass |  |
| 39-tee-pipe | pass |  |
| 40-box-sphere-torus | pass |  |
| 41-tube-radial-holes | pass |  |
| 42-overlapping-patterns | pass |  |
| 43-cut-splits-body | pass |  |
| 44-shell-l-bracket | pass |  |
| 45-shell-boss-plate | pass |  |
| 46-shell-two-open-faces | pass |  |
| 47-draft-curved-pocket | pass |  |
| 48-pulley | pass |  |
| 49-helical-sweep | unsupported | sketch entity 'fitted_spline' |
| 50-sweep-tight-bend | pass |  |
| 51-loft-rect-circle-offset | pass |  |
| 52-circular-pattern-fillet | pass |  |
| 53-path-pattern | pass |  |
| 54-mirror-body-fillets | pass |  |
| 55-tapped-hole-cosmetic | pass |  |
| 56-holes-on-curved-face | unsupported | hole on a cylinder face |
| 57-hole-pattern-sketch-points | pass |  |
| 58-phone-stand | pass |  |
| 59-enclosure-base | pass |  |
| 60-pipe-flange | pass |  |
| 61-shaft-keyway | pass |  |
| 62-heat-sink | pass |  |
| 63-hinge-knuckle | pass |  |
| 64-sketch-tangent-arc-chain | pass |  |
| 65-sketch-gear-tooth | pass |  |
| 66-sketch-linkage | pass |  |
| 67-sm-base-flange | unsupported | operation 'sm_flange' |
| 68-sm-edge-flange | unsupported | operation 'sm_flange' |
| 69-sm-tray | unsupported | operation 'sm_flange' |
| 70-sm-flange-45 | unsupported | operation 'sm_flange' |
| 71-sm-custom-rule | unsupported | operation 'sm_flange' |
| 72-sm-contour-flange | unsupported | operation 'sm_flange' |
| 73-sm-hem | unsupported | operation 'sm_flange' |
| 74-sm-unfold-refold | unsupported | operation 'sm_flange' |
| 75-sm-bracket-holes | unsupported | operation 'sm_flange' |
| 76-sm-thickness-variant | unsupported | operation 'sm_flange' |
| 77-fillet-variable-linear | unsupported | fillet type 'variable_radius' |
| 78-fillet-variable-to-zero | unsupported | fillet type 'variable_radius' |
| 79-fillet-chord-length | unsupported | fillet type 'chord_length' |
| 80-fillet-taper-to-fit | fail | area_mm2: got 2412, expected 2415 |
| 81-fillet-spline-radius | unsupported | fillet type 'spline_radius' |
| 82-thin-extrude-frame | unsupported | thin extrude |
| 83-boundary-loop-thicken | unsupported | operation 'boundary_surface' |
| 84-plate-two-bores | pass |  |
| 85-plate-width-100 | pass |  |
| 86-plate-first-bore-12 | pass |  |
| 87-plate-bore1-deleted | pass |  |
| 88-plate-four-bores | pass |  |
| 94-plate-four-rounded-corners | pass |  |
| 95-plate-rounded-top-chamfer | pass |  |
