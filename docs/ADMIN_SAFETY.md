# Admin Safety

v2.3 hardens the two destructive/operator-sensitive paths.

## Reindex single-flight
Only one `reindex` admin job may run at a time. A second request receives HTTP 409 and the active job metadata instead of starting another catalog build. `/api/admin/jobs` exposes active and recent jobs.

## Restore safety backup
Before restoring a backup over an existing canonical LPC file, `backup_ops.py restore` creates a timestamped `pre_restore` safety backup of the current file. The restore result includes before, restore-source and after SHA-256 hashes.

## Source edits
Local source PUT responses now include before/after SHA-256 values and the timestamped backup path when the file existed.

These mechanisms protect operator changes only. They do not change or reinterpret ES2 gameplay.
