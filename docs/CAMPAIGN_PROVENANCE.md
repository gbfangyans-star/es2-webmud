# Campaign Provenance

v2.7 prevents a subtle false-green failure mode: combining valid evidence from different source versions or different test runs.

A validation campaign now binds all artifacts to:
- campaign ID
- SHA-256 of the campaign manifest
- project version
- canonical Git commit
- exact `mudlib/**` tree SHA-256

The mudlib tree fingerprint includes local edits. This matters because a clean Git commit hash alone is not enough when the admin editor has modified canonical LPC files locally.

The final campaign gate refuses to combine release, runtime, session, and multiplayer artifacts when any provenance field differs.

`start_validation_campaign_windows.ps1` creates the source status, exact source fingerprint, campaign manifest, and multiplayer plan together.
