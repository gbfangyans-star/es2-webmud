from pathlib import Path
import tempfile,json,hashlib,sys
ROOT=Path(__file__).parents[1]
sys.path.insert(0,str(ROOT/"tools"))
from campaign_binding import binding_from_campaign

with tempfile.TemporaryDirectory() as td:
    d=Path(td)
    c1={"format":"es2-validation-campaign-v1","campaignId":"c1","projectVersion":"2.7.0","source":{"commit":"a"*40,"mudlibTreeSha256":"1"*64}}
    c2={"format":"es2-validation-campaign-v1","campaignId":"c2","projectVersion":"2.7.0","source":{"commit":"a"*40,"mudlibTreeSha256":"2"*64}}
    p1=d/"c1.json";p2=d/"c2.json"
    p1.write_text(json.dumps(c1),encoding="utf-8");p2.write_text(json.dumps(c2),encoding="utf-8")
    b1=binding_from_campaign(p1);b2=binding_from_campaign(p2)
    assert b1["campaignId"]!=b2["campaignId"]
    assert b1["campaignSha256"]!=b2["campaignSha256"]
    assert b1["mudlibTreeSha256"]!=b2["mudlibTreeSha256"]
print("v2.7 provenance mismatch detection fixture passed")
