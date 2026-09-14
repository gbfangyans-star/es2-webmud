#!/usr/bin/env python3
from pathlib import Path
import argparse, subprocess, sys

def run(cmd):
    print('+',' '.join(map(str,cmd)))
    subprocess.run(cmd,check=True)

def main():
    ap=argparse.ArgumentParser(description='Build and audit a source-only ES2 catalog.')
    ap.add_argument('repo')
    ap.add_argument('-o','--out',default='catalog/generated')
    ap.add_argument('--allow-fixture',action='store_true')
    a=ap.parse_args()
    here=Path(__file__).resolve().parent

    # Real builds are gated by the canonical source verifier.
    if not a.allow_fixture:
        run([sys.executable,str(here/'verify_source.py'),a.repo])

    cmd=[sys.executable,str(here/'index_es2.py'),a.repo,'-o',a.out]
    if a.allow_fixture:
        cmd.append('--allow-fixture')
    run(cmd)
    run([sys.executable,str(here/'audit_es2.py'),a.out])
    run([sys.executable,str(here/'build_views.py'),a.out])

    for tool in [
        'build_combat_views.py',
        'build_dependency_graph.py',
        'build_combat_profiles.py',
        'audit_interactions.py',
        'audit_contracts.py',
        'equipment_audit.py',
        'build_world_audit.py',
        'build_triage.py',
    ]:
        tp=here/tool
        if tp.exists():
            run([sys.executable,str(tp),a.out])

    if not a.allow_fixture:
        run([sys.executable,str(here/'core_audit.py'),a.out])
        status=here/'build_source_status.py'
        if status.exists():
            run([sys.executable,str(status),a.repo,a.out])

if __name__=='__main__':
    main()
