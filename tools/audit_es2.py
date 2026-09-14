#!/usr/bin/env python3
from pathlib import Path, PurePosixPath
import argparse,json,posixpath

def ensure_c(s):
    return s if s.endswith(('.c','.h')) else s+'.c'

def resolve(owner,target,relative):
    if relative:
        return posixpath.normpath(posixpath.join(posixpath.dirname(owner), ensure_c(target)))
    return ensure_c(target.lstrip('/'))

def main():
    ap=argparse.ArgumentParser();ap.add_argument('catalog');a=ap.parse_args()
    root=Path(a.catalog); rows=json.loads((root/'all.json').read_text(encoding='utf-8')); files={r['file'] for r in rows}
    issues=[]; stats={'dangling_exits':0,'dangling_objects':0,'dangling_merchandise':0,'dangling_equipment':0,'door_without_exit':0,'manual_review_files':0,'duplicate_paths':0}
    seen=set()
    for r in rows:
        if r['path'] in seen:
            issues.append({'kind':'duplicate_path','file':r['file'],'path':r['path']});stats['duplicate_paths']+=1
        seen.add(r['path'])
        if r.get('manual_review'):stats['manual_review_files']+=1
        for d,x in r.get('exits',{}).items():
            f=resolve(r['file'],x['target'],x['relative'])
            if f not in files: issues.append({'kind':'dangling_exit','file':r['file'],'direction':d,'target':f});stats['dangling_exits']+=1
        for x in r.get('objects',[]):
            f=resolve(r['file'],x['target'],x['relative'])
            if f not in files: issues.append({'kind':'dangling_object','file':r['file'],'target':f});stats['dangling_objects']+=1
        for x in r.get('merchandise',[]):
            f=resolve(r['file'],x['target'],x['relative'])
            if f not in files: issues.append({'kind':'dangling_merchandise','file':r['file'],'target':f});stats['dangling_merchandise']+=1
        exits=set((r.get('exits') or {}).keys())
        for door in r.get('doors',[]):
            if door.get('direction') not in exits:
                issues.append({'kind':'door_without_exit','file':r['file'],'direction':door.get('direction'),'name':door.get('name')})
                stats['door_without_exit']+=1
        for x in r.get('equipment',[]):
            if 'target' not in x: continue
            f=resolve(r['file'],x['target'],x.get('relative',False))
            if f not in files: issues.append({'kind':'dangling_equipment','file':r['file'],'target':f});stats['dangling_equipment']+=1
    report={'stats':stats,'issues':issues}
    (root/'audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(stats,ensure_ascii=False,indent=2))
if __name__=='__main__':main()
