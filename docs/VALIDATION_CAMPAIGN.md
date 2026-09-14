# Validation Campaign

v2.5 consolidates the real-machine evidence path into four independently verifiable gates.

1. **Release gate**: package, canonical source, catalog/core audit, bridge/preflight.
2. **Runtime evidence bundle**: source/runtime/login/movement/combat/reconnect files; validator now recomputes every recorded SHA-256 and byte count.
3. **Session package**: raw JSONL + replay + parsed evidence + SHA-256 chain + acceptance matrix. Every packaged artifact has a hash and the raw chain is revalidated.
4. **Multiplayer plan**: all nine required multiplayer stages must be `pass`, and every pass must point to a non-empty evidence file. Optional recorded SHA-256 values are checked.

`final_campaign_gate.py` passes only when all four gates pass and the single-player acceptance matrix is complete. A status word alone is not enough.

The campaign tooling does not generate gameplay results. It verifies evidence captured from the canonical runtime.

When multiplayer evidence is attached, it is copied into a plan-local `multiplayer-evidence/` directory. The plan records the copied file path, byte count, and SHA-256. Later changes to the original source file therefore cannot silently mutate the retained campaign evidence.
