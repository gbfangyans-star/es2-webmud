from pathlib import Path
import json,hashlib

def load_campaign(path):
    p=Path(path).resolve()
    data=p.read_bytes()
    x=json.loads(data.decode("utf-8"))
    if x.get("format")!="es2-validation-campaign-v1":
        raise ValueError("invalid campaign format")
    source=x.get("source") or {}
    required=[x.get("campaignId"),x.get("projectVersion"),source.get("mudlibTreeSha256")]
    if not all(required):
        raise ValueError("campaign missing required provenance fields")
    return x,hashlib.sha256(data).hexdigest()

def binding_from_campaign(path):
    x,sha=load_campaign(path)
    return {
        "campaignId":x["campaignId"],
        "campaignSha256":sha,
        "projectVersion":x["projectVersion"],
        "sourceCommit":x["source"].get("commit"),
        "mudlibTreeSha256":x["source"]["mudlibTreeSha256"]
    }
