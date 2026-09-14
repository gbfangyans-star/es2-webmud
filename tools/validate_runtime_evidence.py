#!/usr/bin/env python3
from pathlib import Path
import argparse,json,hashlib,re

ap=argparse.ArgumentParser();ap.add_argument('bundle');a=ap.parse_args()
d=Path(a.bundle).resolve();manifest_path=d/'manifest.json';issues=[];semantic={}
if not manifest_path.exists():
    print(json.dumps({'ok':False,'issues':[{'kind':'manifest_missing'}]},ensure_ascii=False,indent=2));raise SystemExit(2)
try:m=json.loads(manifest_path.read_text(encoding='utf-8'))
except Exception as e:
    print(json.dumps({'ok':False,'issues':[{'kind':'manifest_invalid','error':str(e)}]},ensure_ascii=False,indent=2));raise SystemExit(2)

payloads={}
for key in m.get('required',[]):
    rec=m.get('present',{}).get(key)
    if not rec:issues.append({'kind':'missing','evidence':key});continue
    p=d/rec['file']
    if not p.exists():issues.append({'kind':'file_missing','evidence':key,'file':rec['file']});continue
    data=p.read_bytes()
    if not data:issues.append({'kind':'empty','evidence':key,'file':rec['file']});continue
    actual=hashlib.sha256(data).hexdigest()
    if rec.get('sha256')!=actual:issues.append({'kind':'sha256_mismatch','evidence':key,'file':rec['file'],'expected':rec.get('sha256'),'actual':actual})
    if rec.get('bytes') is not None and rec.get('bytes')!=len(data):issues.append({'kind':'size_mismatch','evidence':key,'file':rec['file'],'expected':rec.get('bytes'),'actual':len(data)})
    payloads[key]=(p,data)

def json_ok(key):
    if key not in payloads:return False
    try:return bool(json.loads(payloads[key][1].decode('utf-8')).get('ok'))
    except:return False

semantic['source_status_ok']=json_ok('source_status')
semantic['runtime_smoke_ok']=json_ok('runtime_smoke')
if not semantic['source_status_ok']:issues.append({'kind':'source_status_not_ok'})
if not semantic['runtime_smoke_ok']:issues.append({'kind':'runtime_smoke_not_ok'})

# Login transcript must contain at least one exact canonical login prompt.
login_text=payloads.get('login_transcript',(None,b''))[1].decode('utf-8',errors='replace')
login_needles=['請輸入密碼:','請設定您的密碼:','您的電子郵件地址 (或 none):','您的顯示名稱:']
semantic['canonical_login_prompt_observed']=any(x in login_text for x in login_needles)
if not semantic['canonical_login_prompt_observed']:issues.append({'kind':'canonical_login_prompt_missing'})

# Reconnect transcript must contain exact canonical reconnect marker.
reconnect_text=payloads.get('reconnect_transcript',(None,b''))[1].decode('utf-8',errors='replace')
semantic['canonical_reconnect_observed']='重新連線完畢。' in reconnect_text
if not semantic['canonical_reconnect_observed']:issues.append({'kind':'canonical_reconnect_missing'})

# Movement/combat artifacts must have substantive captured content; semantics are checked in session acceptance.
semantic['movement_transcript_substantive']=len(payloads.get('movement_transcript',(None,b''))[1].strip())>=20
semantic['combat_transcript_substantive']=len(payloads.get('combat_transcript',(None,b''))[1].strip())>=20
if not semantic['movement_transcript_substantive']:issues.append({'kind':'movement_transcript_too_small'})
if not semantic['combat_transcript_substantive']:issues.append({'kind':'combat_transcript_too_small'})

out={'ok':not issues and bool(m.get('complete')),'issues':issues,'semantic':semantic,'manifest_complete':bool(m.get('complete')),'format':m.get('format'),'verified_files':len(m.get('present',{}))}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out['ok'] else 2)
