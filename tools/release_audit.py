#!/usr/bin/env python3
from pathlib import Path
import argparse,json
ap=argparse.ArgumentParser();ap.add_argument("root");a=ap.parse_args()
root=Path(a.root).resolve()
version=(root/"VERSION").read_text(encoding="utf-8").strip() if (root/"VERSION").exists() else None
pkg={}
try:pkg=json.loads((root/"server/package.json").read_text(encoding="utf-8"))
except:pass
required=[
 "README.md","VERSION","LICENSE_NOTICE.md","TEST_REPORT.json","INTEGRITY.json",
 "server/index.js","server/telnet.js","server/admin_jobs.js",
 "web/app.js","web/session_recorder.js",
 "tools/verify_source.py","tools/preflight.py","tools/runtime_plan.py",
 "tools/build_acceptance_matrix.mjs","tools/final_runtime_gate.mjs",
 "tools/multiplayer_probe.mjs","tools/hash_session_chain.mjs","tools/validate_session_chain.mjs",
 "tools/source_fingerprint.py","tools/create_validation_campaign.py","tools/validate_campaign_provenance.py",
 "tools/build_session_package.mjs","tools/validate_session_package.mjs",
 "tools/validate_multiplayer_plan.mjs","tools/final_campaign_gate.py"
]
missing=[x for x in required if not (root/x).exists()]
recorder=(root/"web/session_recorder.js").read_text(encoding="utf-8",errors="replace")
app=(root/"web/app.js").read_text(encoding="utf-8",errors="replace")
server=(root/"server/index.js").read_text(encoding="utf-8",errors="replace")
checks={
 "version_matches_package":version==pkg.get("version"),
 "required_files_present":not missing,
 "source_policy_documented":"taedlar/es2_mudlib" in (root/"README.md").read_text(encoding="utf-8",errors="replace"),
 "password_redaction_code":"sensitive_input_redacted" in recorder and "sensitiveInputsStored:false" in recorder,
 "session_persistence_implemented":"this.persist()" in recorder and "this.restore()" in recorder,
 "raw_response_capture_hook":"sessionRecorder.appendResponse(s)" in app,
 "reindex_single_flight":"AdminJobState" in server,
 "restore_safety_core":(root/"tools/backup_core.py").exists()
}
out={"ok":all(checks.values()),"version":version,"checks":checks,"missing":missing}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
