import subprocess,sys,tempfile,json
from pathlib import Path
ROOT=Path(__file__).parents[1]

files=[
 ROOT/'tools/evidence_bundle.py',
 ROOT/'tools/validate_runtime_evidence.py',
 ROOT/'tools/runtime_probe.py',
 ROOT/'tools/runtime_smoke.py',
 ROOT/'tools/validate_login_transcript.py',
 ROOT/'tools/build_catalog.py',
 ROOT/'tools/verify_source.py',
]
for f in files:
    subprocess.run([sys.executable,'-m','py_compile',str(f)],check=True)

with tempfile.TemporaryDirectory() as td:
    td=Path(td)
    sample_text={
      'source_status':json.dumps({'ok':True}),
      'runtime_smoke':json.dumps({'ok':True}),
      'login_transcript':'您的使用者代號: tester\n請輸入密碼: [redacted]\n',
      'movement_transcript':'canonical movement transcript evidence with substantive captured content',
      'combat_transcript':'canonical combat transcript evidence with substantive captured content',
      'reconnect_transcript':'重新連線完畢。\ncanonical reconnect evidence'
    }
    samples={}
    for name,text in sample_text.items():
        p=td/(name+'.txt');p.write_text(text,encoding='utf-8');samples[name]=p
    campaign=td/'campaign.json'
    campaign.write_text(json.dumps({
      'format':'es2-validation-campaign-v1','campaignId':'test-v15-fast','projectVersion':(ROOT/'VERSION').read_text().strip(),
      'source':{'commit':'test','mudlibTreeSha256':'0'*64}
    }),encoding='utf-8')
    out=td/'bundle'
    cmd=[sys.executable,str(ROOT/'tools/evidence_bundle.py'),str(out),'--campaign',str(campaign)]
    for k,p in samples.items():
        cmd += ['--'+k.replace('_','-'),str(p)]
    r=subprocess.run(cmd,capture_output=True,text=True,check=True)
    m=json.loads(r.stdout)
    assert m['complete'] is True
    r2=subprocess.run([sys.executable,str(ROOT/'tools/validate_runtime_evidence.py'),str(out)],capture_output=True,text=True,check=True)
    assert json.loads(r2.stdout)['ok'] is True

print('v1.5 fast tests passed')
