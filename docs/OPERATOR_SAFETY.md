# Operator Safety

v1.3 adds a localhost-only operator surface.

- Real catalog rebuilds first run `verify_source.py`.
- The verifier requires the exact `taedlar/es2_mudlib` Git origin plus canonical marker files.
- A failed source verification blocks reindex and restore operations.
- Source edits remain limited to `mudlib/*`.
- Every source edit keeps a timestamped backup under `patches/`.
- Backup list/diff/restore are constrained to `patches/` and `source/upstream/`; arbitrary filesystem access is rejected.
- Fixture builds bypass the source gate only with the explicit `--allow-fixture` test flag.

Restore changes LPC source but does not silently rebuild the catalog. Reindex should be run after reviewing the restored source.
