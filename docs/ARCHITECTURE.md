# Architecture

## Runtime lane
Browser -> WebSocket `/mud` -> TCP -> Neolith -> ES2 mudlib.

This preserves the exact upstream command, combat, NPC, skill, room and object behavior.

## Content lane
Local checkout of `taedlar/es2_mudlib` -> `tools/index_es2.py` -> generated catalogs -> browser workbench.

The catalog is an index, not an alternate game database. Editing writes to the upstream LPC working tree, with a local backup before each save.

## Audit lane
`tools/audit_es2.py` checks the generated graph for dangling room exits, dangling object references, duplicate indexed paths and files that contain complex logic requiring human review.

## Extension policy
New content should be authored as LPC following the same upstream object model. JSON catalogs may be regenerated at any time and should never become canonical gameplay data.
