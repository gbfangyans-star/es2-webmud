from pathlib import Path
import tempfile,hashlib,sys
ROOT=Path(__file__).parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from backup_core import restore_with_safety

with tempfile.TemporaryDirectory() as td:
    r=Path(td);(r/'patches').mkdir();(r/'source/upstream/mudlib').mkdir(parents=True)
    cur=r/'source/upstream/mudlib/test.c';cur.write_text('current\n',encoding='utf-8')
    bak=r/'patches/old.bak';bak.write_text('old\n',encoding='utf-8')
    x=restore_with_safety(r,'patches/old.bak','source/upstream/mudlib/test.c')
    assert cur.read_text(encoding='utf-8')=='old\n'
    safety=r/x['safety_backup']
    assert safety.read_text(encoding='utf-8')=='current\n'
    assert x['before_sha256']==hashlib.sha256(b'current\n').hexdigest()
    assert x['restore_sha256']==hashlib.sha256(b'old\n').hexdigest()
    assert x['after_sha256']==hashlib.sha256(b'old\n').hexdigest()
print('v2.3 restore safety-backup tests passed')
