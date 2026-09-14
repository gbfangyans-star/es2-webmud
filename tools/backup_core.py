from pathlib import Path
import datetime
import hashlib

def within(base, p):
    base=Path(base).resolve()
    p=Path(p).resolve()
    if p!=base and base not in p.parents:
        raise ValueError("path rejected")
    return p

def restore_with_safety(root, backup_rel, current_rel):
    root=Path(root).resolve()
    patches=(root/"patches").resolve()
    upstream=(root/"source/upstream").resolve()
    b=within(patches,root/backup_rel)
    c=within(upstream,root/current_rel)
    if not b.is_file():
        raise FileNotFoundError("backup not found")
    patches.mkdir(parents=True,exist_ok=True)
    c.parent.mkdir(parents=True,exist_ok=True)
    before=c.read_bytes() if c.exists() else b""
    incoming=b.read_bytes()
    before_sha=hashlib.sha256(before).hexdigest() if c.exists() else None
    restore_sha=hashlib.sha256(incoming).hexdigest()
    safety=None
    if c.exists():
        stamp=datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%S.%fZ")
        rel=str(c.relative_to(upstream)).replace("/", "__").replace("\\", "__")
        safety=patches/f"{stamp}__pre_restore__{rel}.bak"
        safety.write_bytes(before)
    c.write_bytes(incoming)
    after_sha=hashlib.sha256(c.read_bytes()).hexdigest()
    return {
        "restored":True,
        "backup":str(b.relative_to(root)),
        "current":str(c.relative_to(root)),
        "safety_backup":str(safety.relative_to(root)) if safety else None,
        "before_sha256":before_sha,
        "restore_sha256":restore_sha,
        "after_sha256":after_sha
    }
