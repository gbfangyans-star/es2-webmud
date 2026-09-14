# Runtime Smoke Testing

v1.4 adds a read-only TCP probe and login transcript validator.

The probe only connects and reads the initial MUD stream. It does not submit credentials or create characters. A successful probe proves that the configured TCP endpoint accepted a connection; it does not prove gameplay correctness.

`validate_login_transcript.py` accepts a captured text transcript and checks only confirmed canonical prompts from `logind.c`. Existing-login and new-character flows are recognized separately.

A release must not claim runtime completion until the canonical repo and Neolith have actually passed real login, character creation, movement/look, score/skills/inventory, combat, condition/death, and reconnect checks.
