# Runtime Evidence

v1.5 defines a reproducible evidence bundle for the final real-server validation phase.

Required artifacts:
- source status
- runtime smoke result
- login transcript
- movement/look transcript
- combat/condition/death transcript
- reconnect transcript

`evidence_bundle.py` copies these local artifacts into one directory and records SHA-256 hashes. `validate_runtime_evidence.py` checks that the required evidence exists and is non-empty.

This bundle records observations only. It cannot make a failed or untested runtime path pass.

## v1.6 player observation
After capturing real `hp`, `skills`, and `inventory` output, `tools/build_player_observation.mjs` can produce a structured observation JSON. The source transcript SHA-256 is stored alongside the parsed state so reviewers can always return to the raw authoritative output.
