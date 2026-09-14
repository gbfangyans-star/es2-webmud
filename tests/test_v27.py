from pathlib import Path
import tempfile,json,hashlib,sys
ROOT=Path(__file__).parents[1]
sys.path.insert(0,str(ROOT/"tools"))
from campaign_binding import binding_from_campaign

with tempfile.TemporaryDirectory() as td:
    d=Path(td)
    c={
      "format":"es2-validation-campaign-v1",
      "campaignId":"campaign-test-1",
      "projectVersion":"2.7.0",
      "source":{"commit":"a"*40,"mudlibTreeSha256":"b"*64}
    }
    cp=d/"campaign.json";cp.write_text(json.dumps(c),encoding="utf-8")
    b=binding_from_campaign(cp)
    assert b["campaignId"]=="campaign-test-1"
    assert b["sourceCommit"]=="a"*40
    assert b["mudlibTreeSha256"]=="b"*64
    assert b["campaignSha256"]==hashlib.sha256(cp.read_bytes()).hexdigest()
print("v2.7 campaign binding tests passed")
