#!/usr/bin/env python3
"""Build a risk-ordered multiplayer certification plan from the live ledger.

This is intentionally a planner, not a test result generator. It never upgrades
ASSISTED/STATIC work to live PASS. It also computes evidence freshness by
comparing gate fingerprints captured in the acceptance ledger against current
source.
"""
from __future__ import annotations
import json,time
from pathlib import Path
import importlib.util
ROOT=Path(__file__).resolve().parents[1]

def load_fingerprints():
    spec=importlib.util.spec_from_file_location('mfp',ROOT/'tools/multiplayer_evidence_fingerprint.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m.build()

def main():
    ledger=json.loads((ROOT/'MULTIPLAYER_ACCEPTANCE_LEDGER.json').read_text(encoding='utf-8'))
    fp=load_fingerprints();stored=ledger.get('evidenceFingerprints',{})
    covered=set(ledger.get('coveredGateFingerprints',[]))
    freshness={}
    for gate,row in fp['gates'].items():
        old=stored.get(gate)
        freshness[gate]={'fresh':bool(gate in covered and old and old==row['fingerprint']),'liveEvidenceRecorded':gate in covered,'implementationUnchanged':bool(old and old==row['fingerprint']),'recorded':old,'current':row['fingerprint'],'sourceComplete':row['ok']}
    # Low risk first. Destructive gates are never put into automatic execution.
    steps=[
      {'priority':1,'gate':'mutual player fight in a canonical combat-allowed room','mode':'ASSISTED LIVE','launcher':'CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat','risk':'LOW','reason':'Uses canonical mutual-consent fight only; never kill.'},
      {'priority':2,'gate':'single-owner ground-item contention using a real visible item','mode':'ASSISTED LIVE','launcher':'CHECK_MULTIPLAYER_SHARED_WORLD.bat','risk':'LOW','reason':'Uses one already-present canonical ground item; no spawning.'},
      {'priority':3,'gate':'server restart persistence with both test characters offline before snapshot','mode':'ASSISTED LIVE','launcher':'CHECK_RESTART_BEFORE.bat -> restart -> CHECK_RESTART_AFTER.bat','risk':'LOW','reason':'Read-only hash comparison after explicit save/logout.'},
      {'priority':4,'gate':'guard relation when canonical level requirement is met','mode':'ASSISTED LIVE','launcher':'CHECK_MULTIPLAYER_ROOM.bat','risk':'LOW','reason':'Conditional only; never levels a character for testing.'},
      {'priority':90,'gate':'live death/corpse/revival','mode':'WITHHELD','launcher':None,'risk':'DESTRUCTIVE','reason':'Requires explicitly approved disposable scenario.'},
      {'priority':100,'gate':'live kill/PK','mode':'WITHHELD','launcher':None,'risk':'DESTRUCTIVE','reason':'Not required for low-risk multiplayer certification.'},
    ]
    out={'schema':1,'version':(ROOT/'VERSION').read_text().strip(),'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'livePassed':ledger.get('livePassed',[]),'freshness':freshness,'nextSteps':steps,'rule':'A static audit or fresh fingerprint never creates a live PASS; only prior real Windows/Neolith evidence can do that.'}
    p=ROOT/'reports/multiplayer_certification_plan.json';p.parent.mkdir(exist_ok=True);p.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(out,ensure_ascii=False,indent=2));return 0
if __name__=='__main__':raise SystemExit(main())
