#!/usr/bin/env python3
"""Fail closed when previously accepted LIVE multiplayer evidence becomes stale.

This checks only gates explicitly listed in coveredGateFingerprints. Pending or
withheld gates are never promoted. If implementing code for a covered gate has
changed, the tool exits non-zero so the next release cannot silently claim that
old Windows/Neolith evidence still applies.
"""
from __future__ import annotations
import importlib.util,json,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def load_current():
    spec=importlib.util.spec_from_file_location('mfp',ROOT/'tools/multiplayer_evidence_fingerprint.py')
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m.build()

def main():
    ledger=json.loads((ROOT/'MULTIPLAYER_ACCEPTANCE_LEDGER.json').read_text(encoding='utf-8'))
    cur=load_current();stored=ledger.get('evidenceFingerprints',{});covered=ledger.get('coveredGateFingerprints',[])
    rows=[]
    for gate in covered:
        now=cur.get('gates',{}).get(gate,{});old=stored.get(gate)
        fresh=bool(old and now.get('ok') and old==now.get('fingerprint'))
        rows.append({'gate':gate,'fresh':fresh,'recorded':old,'current':now.get('fingerprint'),'sourceComplete':bool(now.get('ok'))})
    stale=[x['gate'] for x in rows if not x['fresh']]
    out={'schema':1,'version':(ROOT/'VERSION').read_text().strip(),'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'ok':not stale,'coveredLiveEvidence':rows,'staleGates':stale,'rule':'Only previously recorded live gates are checked. Pending gates are never promoted to PASS.'}
    p=ROOT/'reports/multiplayer_evidence_carryforward.json';p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(out,ensure_ascii=False,indent=2));return 0 if out['ok'] else 4
if __name__=='__main__':raise SystemExit(main())
