# Preflight

v2.0 adds one real-machine prerequisite gate. It checks the canonical source verifier, Python, Node, npm, Neolith submodule path, `neolith.conf`, and whether the MUD TCP port is open.

`ok` means prerequisites are present. `runtime_online` only means a TCP connection could be opened. It is not gameplay acceptance.
