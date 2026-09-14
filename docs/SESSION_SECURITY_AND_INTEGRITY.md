# Session Security and Integrity

v2.4 fixes three evidence-path defects:

1. Password-mode input is sent to ES2 but never stored as a command. The recorder writes only a `sensitive_input_redacted` operational event.
2. Raw non-system WebSocket output is appended to the pending command response.
3. Recorder state persists in `sessionStorage`, so the session page can recover evidence captured during the same browser session.

The main game page can export JSONL and a manifest directly.

`hash_session_chain.mjs` creates an ordered SHA-256 chain. `validate_session_chain.mjs` detects edits, reordering, and ordinary truncation against the retained chain manifest.

Hash integrity proves the evidence file was unchanged. It does not prove gameplay semantics.
