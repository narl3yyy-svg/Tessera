# Parity harness

Not started. Plan §7: the same operation is run in the reference (through its Python API) and in
Tessera (through `tessera-cli` and the adsk shim). Both emit a metric vector as JSON, and a comparator
diffs them against the §7.3 tolerances. `report.json` is published per commit.

The Tessera side can already run reference-style scripts:
`tessera-cli --open input.tsr --script op.py`.
