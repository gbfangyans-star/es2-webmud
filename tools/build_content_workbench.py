#!/usr/bin/env python3
"""Build a read-only development workbench index from canonical catalog outputs.

No gameplay data is invented here. This tool only reorganizes facts already
extracted from source/upstream/mudlib and the generated dependency/triage data.
"""
from __future__ import annotations
from collections import Counter, defaultdict
from pathlib import Path
import json, time

ROOT=Path(__file__).resolve().parents[1]
CAT=ROOT/'catalog'/'generated'
OUT=CAT/'content_workbench.json'

def load(name, default):
    try:return json.loads((CAT/name).read_text(encoding='utf-8'))
    except Exception:return default

def main():
    rows=load('all.json',[]) or []
    triage=load('triage.json',{}) or {}
    graph=load('reference_graph.json',{}) or {}
    source_status=load('source_status.json',{}) or {}
    type_counts=Counter(r.get('type','unknown') for r in rows)
    manual=defaultdict(list)
    review_rows=[]
    for r in rows:
        reasons=list(r.get('manual_review') or [])
        if reasons:
            item={
                'path':r.get('path'),'file':r.get('file'),'type':r.get('type'),
                'short':r.get('short'),'name':r.get('name'),'ids':r.get('ids') or [],
                'reasons':reasons,'sha256':r.get('sha256')
            }
            review_rows.append(item)
            for reason in reasons: manual[reason].append(r.get('path'))
    ranked=[]
    for x in triage.get('ranked',[])[:200]:
        ranked.append({'path':x.get('path'),'score':x.get('score',0),'reasons':x.get('reasons',[])})
    entities=graph.get('entities',{}) if isinstance(graph,dict) else {}
    dep_stats=[]
    for pth,rel in entities.items():
        incoming=len(rel.get('incoming',[]) or []); outgoing=len(rel.get('outgoing',[]) or [])
        if incoming or outgoing: dep_stats.append({'path':pth,'incoming':incoming,'outgoing':outgoing,'degree':incoming+outgoing})
    dep_stats.sort(key=lambda x:(-x['degree'],x['path']))
    out={
        'schema':1,
        'version':(ROOT/'VERSION').read_text(encoding='utf-8').strip(),
        'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),
        'sourceBoundary':'taedlar/es2_mudlib only',
        'readOnlyIndex':True,
        'summary':{
            'entities':len(rows),
            'types':dict(sorted(type_counts.items())),
            'manualReviewEntities':len(review_rows),
            'manualReviewReasons':{k:len(v) for k,v in sorted(manual.items())},
            'triageEntries':len(triage.get('ranked',[]) or []),
            'relationEntities':len(entities),
        },
        'manualReview':sorted(review_rows,key=lambda x:(x['type'] or '',x['path'] or '')),
        'manualReviewGroups':{k:sorted(v) for k,v in sorted(manual.items())},
        'triageTop':ranked,
        'dependencyHotspots':dep_stats[:100],
        'sourceStatus':source_status,
        'rules':[
            'Catalog and this workbench are indexes only; canonical gameplay source remains source/upstream/mudlib.',
            'manual_review is preserved and must not be guessed away.',
            'No entity, mechanic, room, NPC, item, skill, command, or relationship is created by this report.'
        ]
    }
    OUT.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps({'ok':True,'output':str(OUT.relative_to(ROOT)),'entities':len(rows),'manualReview':len(review_rows),'triage':len(ranked),'hotspots':len(dep_stats[:100])},ensure_ascii=False))
    return 0
if __name__=='__main__':raise SystemExit(main())
