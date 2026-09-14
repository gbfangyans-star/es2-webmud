# Catalog model

Catalog JSON is an index, not a second gameplay database.

`tools/index_es2.py` scans the canonical checkout and records source path, SHA-256, inheritance, functions and conservative semantic fields. `tools/audit_es2.py` checks known object references. `tools/build_views.py` generates UI-oriented read-only views:

- `world_graph.json`: rooms and parsed exit edges. No invented coordinates.
- `command_index.json`: command objects from `/cmds/*` with command group and source path.
- `browser_summary.json`: entity counts and manual-review coverage.

The browser explorer searches the generated catalog. Editing still opens the canonical LPC source file, so catalog output never becomes authoritative gameplay state.
