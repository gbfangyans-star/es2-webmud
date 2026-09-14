#!/usr/bin/env python3
from pathlib import Path
import argparse,json,posixpath,collections

ap=argparse.ArgumentParser(description='Build read-only browser views from canonical ES2 catalog.')
ap.add_argument('catalog_dir');a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/'all.json').read_text(encoding='utf-8'))
by={r['path']:r for r in rows}

def canonical(owner,target,relative=False):
    if not target:return ""
    if relative:
        parent=posixpath.dirname(owner)
        return posixpath.normpath(posixpath.join(parent,target))
    return target if target.startswith('/') else '/'+target

# World graph: no invented coordinates.
rooms=[r for r in rows if r.get('type')=='room']
nodes=[];edges=[]
for r in rooms:
    nodes.append({'id':r['path'],'label':r.get('short') or r.get('name') or Path(r['file']).stem,
                  'manual_review':r.get('manual_review',[]),'doors':r.get('doors',[])})
    for direction,e in (r.get('exits') or {}).items():
        target=canonical(r['path'],e.get('target',''),e.get('relative',False))
        edges.append({'from':r['path'],'to':target,'direction':direction,'resolved':target in by})

# Cross-reference graph.
refs=[]
def addref(owner,kind,target,extra=None):
    t=canonical(owner['path'],target.get('target','') if isinstance(target,dict) else target,
                target.get('relative',False) if isinstance(target,dict) else False)
    refs.append({'from':owner['path'],'kind':kind,'to':t,'resolved':t in by,**(extra or {})})

for r in rows:
    for direction,e in (r.get('exits') or {}).items(): addref(r,'exit',e,{'direction':direction})
    for x in r.get('objects',[]): addref(r,'object',x,{'count':x.get('count',1)})
    for x in r.get('merchandise',[]): addref(r,'merchandise',x,{'stock':x.get('stock')})
    for x in r.get('equipment',[]):
        if x.get('target'): addref(r,'equipment',x,{'action':x.get('action')})
    for m in r.get('skill_maps',[]):
        refs.append({'from':r['path'],'kind':'skill_map','to':m.get('mapped_to',''),'resolved':False,'base':m.get('base')})

incoming=collections.defaultdict(list); outgoing=collections.defaultdict(list)
for x in refs:
    outgoing[x['from']].append(x); incoming[x['to']].append(x)

entity_relations={}
for p in by:
    entity_relations[p]={'incoming':incoming.get(p,[]),'outgoing':outgoing.get(p,[])}

commands=[{'command':r.get('command',Path(r['file']).stem),'group':r.get('command_group'),
           'path':r['path'],'functions':r.get('functions',[]),'runtime_traits':r.get('runtime_traits',[])}
          for r in rows if r.get('type')=='command']

vendors=[]
for r in rows:
    if r.get('merchandise') or 'vendor' in r.get('runtime_traits',[]):
        vendors.append({'path':r['path'],'name':r.get('name') or r.get('short'),
                        'merchandise':r.get('merchandise',[]),
                        'runtime_traits':r.get('runtime_traits',[]),
                        'manual_review':r.get('manual_review',[])})

skills=[]
for r in rows:
    if r.get('type')=='skill' or r.get('skills') or r.get('skill_maps'):
        skills.append({'path':r['path'],'name':r.get('name') or r.get('short'),
                       'type':r.get('type'),'skills':r.get('skills',[]),
                       'skill_maps':r.get('skill_maps',[]),
                       'required_skills':r.get('required_skills',{}),
                       'registered_skill_daemon':r.get('registered_skill_daemon'),
                       'functions':r.get('functions',[]),
                       'manual_review':r.get('manual_review',[])})

items=[]
for r in rows:
    if r.get('type')=='item':
        items.append({'path':r['path'],'name':r.get('name') or r.get('short'),
                      'ids':r.get('ids',[]),'value':r.get('value'),'weight':r.get('weight'),
                      'material':r.get('material'),'weapon_type':r.get('weapon_type'),
                      'required_skills':r.get('required_skills',{}),
                      'study_content':r.get('study_content',{}),
                      'inherits':r.get('inherits',[]),'runtime_traits':r.get('runtime_traits',[]),
                      'manual_review':r.get('manual_review',[])})

npcs=[]
for r in rows:
    if r.get('type')=='npc':
        npcs.append({'path':r['path'],'name':r.get('name') or r.get('short'),
                     'ids':r.get('ids',[]),'race':r.get('race'),'class':r.get('class'),
                     'gender':r.get('gender'),'level':r.get('level'),
                     'attributes':r.get('attributes',{}),'stat_maximums':r.get('stat_maximums',{}),
                     'skills':r.get('skills',[]),'skill_maps':r.get('skill_maps',[]),
                     'equipment':r.get('equipment',[]),'merchandise':r.get('merchandise',[]),
                     'actions':r.get('actions',[]),'callouts':r.get('callouts',[]),
                     'runtime_traits':r.get('runtime_traits',[]),
                     'manual_review':r.get('manual_review',[])})

entities={k:[r for r in rows if r.get('type')==k] for k in
          ['npc','item','skill','daemon','runtime','feature','prototype','command','room']}
summary={'counts':{k:len(v) for k,v in entities.items()},
         'manual_review':sum(bool(r.get('manual_review')) for r in rows),
         'runtime_traits':dict(collections.Counter(t for r in rows for t in r.get('runtime_traits',[]))),
         'references':{'total':len(refs),'resolved':sum(bool(x.get('resolved')) for x in refs)},
         'total':len(rows)}


skill_contracts=[]
equipment_lifecycle=[]
damage_contracts=[]
interactive_objects=[]
for r in rows:
    if r.get('skill_contract'):
        skill_contracts.append({
            'path':r['path'],'type':r.get('type'),'name':r.get('name') or r.get('short'),
            'registered_skill_daemon':r.get('registered_skill_daemon'),
            'skill_contract':r.get('skill_contract'),
            'required_skills':r.get('required_skills',{}),
            'runtime_traits':r.get('runtime_traits',[]),
            'manual_review':r.get('manual_review',[])
        })
    if r.get('equipment_hooks') or r.get('wear_as') or r.get('armor_apply'):
        equipment_lifecycle.append({
            'path':r['path'],'type':r.get('type'),'name':r.get('name') or r.get('short'),
            'equipment_hooks':r.get('equipment_hooks',[]),'wear_as':r.get('wear_as'),
            'armor_apply':r.get('armor_apply',[]),'apply_mappings':r.get('apply_mappings',[]),
            'numeric_calls':r.get('numeric_calls',{}),'manual_review':r.get('manual_review',[])
        })
    if r.get('damage_contract'):
        damage_contracts.append({
            'path':r['path'],'type':r.get('type'),'damage_contract':r.get('damage_contract',[]),
            'combat_surface':r.get('combat_surface',[]),'manual_review':r.get('manual_review',[])
        })
    if r.get('actions') or r.get('accept_hooks') or r.get('callouts') or r.get('doors'):
        interactive_objects.append({
            'path':r['path'],'type':r.get('type'),'name':r.get('name') or r.get('short'),
            'actions':r.get('actions',[]),'accept_hooks':r.get('accept_hooks',[]),
            'callouts':r.get('callouts',[]),'doors':r.get('doors',[]),
            'manual_review':r.get('manual_review',[])
        })

outputs={
 'world_graph.json':{'nodes':nodes,'edges':edges},
 'reference_graph.json':{'references':refs,'entities':entity_relations},
 'command_index.json':commands,
 'vendor_index.json':vendors,
 'skill_index.json':skills,
 'item_index.json':items,
 'npc_index.json':npcs,
 'browser_summary.json':summary,
 'skill_contract_index.json':skill_contracts,
 'equipment_lifecycle_index.json':equipment_lifecycle,
 'damage_contract_index.json':damage_contracts,
 'interactive_object_index.json':interactive_objects
}
for fn,obj in outputs.items():
    (d/fn).write_text(json.dumps(obj,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(summary,ensure_ascii=False,indent=2))
