#!/usr/bin/env python3
from pathlib import Path
import argparse,json,html,datetime
ap=argparse.ArgumentParser()
ap.add_argument('--campaign',required=True);ap.add_argument('--out',required=True)
a=ap.parse_args()
c=json.loads(Path(a.campaign).read_text(encoding='utf-8'))
steps=c.get('steps',{})
rows=[]
for k,v in steps.items():
    status='PASS' if v.get('ok') else 'FAIL'
    detail=v.get('result',{})
    rows.append((k,status,json.dumps(detail,ensure_ascii=False,indent=2)[:8000]))
overall='PASS' if c.get('ok') else 'FAIL'
doc=['<!doctype html><html lang="zh-Hant"><head><meta charset="utf-8"><title>ES2 Final Campaign</title><style>body{font-family:system-ui;margin:32px;max-width:1100px}table{border-collapse:collapse;width:100%}td,th{border:1px solid #aaa;padding:8px;vertical-align:top}pre{white-space:pre-wrap;word-break:break-word}.PASS{font-weight:700}.FAIL{font-weight:700}</style></head><body>']
doc.append(f'<h1>ES2 Final Campaign: <span class="{overall}">{overall}</span></h1>')
doc.append('<p>Generated from validated campaign artifacts. This page does not execute gameplay.</p><table><tr><th>Gate</th><th>Status</th><th>Details</th></tr>')
for k,status,detail in rows:
    doc.append(f'<tr><td>{html.escape(k)}</td><td class="{status}">{status}</td><td><pre>{html.escape(detail)}</pre></td></tr>')
doc.append('</table></body></html>')
Path(a.out).write_text(''.join(doc),encoding='utf-8')
print(json.dumps({'ok':True,'campaignOk':bool(c.get('ok')),'out':a.out},ensure_ascii=False))
