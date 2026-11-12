# Lab notes

Facts about the build/test machine, one row each: date, phase, fact, how it was checked, confidence.

| Timestamp | Phase | Claim | Source | Confidence |
|---|---|---|---|---|
| 2026-11-11 | P0 | Lab 10.0.60.100 runs Ubuntu 26.04.1 with 4 cores, 15 GB RAM, an Alder Lake-N iGPU and no VMs; sudo needs a password | `nproc`, `free`, `lspci`, `virsh list` over SSH | high |
| 2026-11-11 | P0 | Lab has no direct internet access (DNS works, TCP 80/443 out time out); packages were installed through an SSH reverse SOCKS tunnel | curl / `/dev/tcp` probes over SSH | high |
| 2026-11-11 | P0 | Kubuntu 26.04 ships OCCT 7.9.2, Qt 6.10.2, pybind11 3.0.1, Python 3.14 | `apt-cache policy` on the lab | high |
