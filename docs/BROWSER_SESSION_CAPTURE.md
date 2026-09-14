# Browser Session Capture

v1.8 adds an in-memory browser session recorder.

The recorder pairs each outgoing command with the raw text received before the next command is sent. Closing/reconnecting finalizes the pending response and increments a reconnect counter.

The recorder does not parse or alter gameplay. It only captures evidence.

Exports:
- `es2-session.jsonl`
- `es2-session-manifest.json`

`build_session_evidence.mjs` can turn the JSONL into replay-derived coverage evidence using the same source-confirmed observer parsers.

Important: command/response boundaries are operational capture boundaries, not LPC transaction boundaries. Multi-command unsolicited server output can still appear inside a response. Raw text remains authoritative.
