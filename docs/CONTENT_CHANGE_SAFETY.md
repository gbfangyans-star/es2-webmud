# Canonical Content Change Safety

This layer exists so future content work can be large without becoming opaque.

## Before editing canonical LPC
1. Run `CHECK_CONTENT_CHANGE_SAFETY.bat`. It must show no unaccounted canonical changes.
2. For every canonical file intentionally targeted, create a pre-change snapshot with `tools/content_transaction_snapshot.py <relative LPC paths> --name <batch>`.
3. Keep unresolved source questions as `manual_review`; never infer missing gameplay.

## During/after a content batch
- `content_change_guard.py` reports exact added/removed/changed canonical paths against the sealed baseline.
- `content_change_impact.py` produces a read-only impact report and maps directly affected catalog entities where possible.
- Rebuild catalog/workbench, run regression and release gates, then package.
- The snapshot contains original bytes for forensic rollback, but **no tool auto-restores gameplay**. Restoration remains an explicit reviewed action.

## Boundary
These tools do not authorize new sources. The project source boundary remains `taedlar/es2_mudlib` unless the user explicitly changes that policy later.
