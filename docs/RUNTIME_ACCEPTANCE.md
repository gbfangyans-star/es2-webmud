# Runtime Acceptance

v1.9 defines the final runtime acceptance matrix.

Source-confirmed exact lifecycle markers:
- `你死了！！`
- `你已經魂飛魄散了！！！`
- `你的眼前一黑，接著什麼也不知道了....`
- `慢慢地你終於又有了知覺....`
- `重新連線完畢。`
- fight win/loss messages from `obj/user.c`

The matrix deliberately distinguishes command coverage from actual runtime success. A captured `go north` command is not proof that movement succeeded. Lifecycle and reconnect checks require canonical output to be present in the replay observations.

The acceptance builder does not execute ES2, modify state or synthesize missing evidence.
