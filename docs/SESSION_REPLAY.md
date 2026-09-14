# Session Replay

v1.7 adds an offline replay analyzer for real captured command/response pairs.

Input is JSONL. Each record contains exactly:
`{"command":"score","response":"...raw ES2 response..."}`

The replay analyzer never sends commands to ES2 and never simulates world state. It passes each captured response through the same browser observation parser, then reports coverage for score, hp, skills, inventory, look and movement.

Movement parsing is deliberately asymmetric. Exact failure messages visible in canonical `cmds/std/go.c` are classified. The absence of a failure message is not treated as proof that movement succeeded. Room success remains raw unless a source-confirmed room/look boundary is available in the capture.
