from pathlib import Path
import json,re,hashlib
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
OUT=ROOT/'reports/snow_special_npc_audit.json'
SPECS={
'child.c': {'name':'阿寶','room':'d/snow/tree.c','tokens':['set_name("阿寶"','accept_object','give_comb','relay_say','try/fon','command("follow "+me->query("id"))']},
'gammer.c': {'name':'瞎眼老太婆','room':'d/snow/square.c','tokens':['set_name("瞎眼老太婆"','accept_object','ask_join','thief_qualified','set_class("thief")','relay_say','random_move']},
'teacher.c': {'name':'王懷芝','room':'d/snow/school.c','tokens':['set_name("王懷芝"','add_action("do_sit", "sit")','improve_skill("literate"','set_class("scholar")','acquire_skill']},
'alchemist.c': {'name':'陳維俠','room':'d/snow/school.c','tokens':['set_name("陳維俠"','accept_apprentice','set_class("alchemist")','龍圖丹派弟子','acquire_skill','alchemy-medication']},
'girl.c': {'name':'白衣女子','room':'d/snow/ruin2.c','tokens':['set_name("白衣女子"','attack_intruder','hairpin_quest','accept_object','bronze hairpin','pending_requester','英雄帖','invitation']},
}
rows=[]; failures=[]
for fn,spec in SPECS.items():
 p=MUD/'d/snow/npc'/fn; text=p.read_text(encoding='utf-8')
 room=(MUD/spec['room']); rt=room.read_text(encoding='utf-8')
 stem=fn[:-2]
 room_ref=('npc/'+stem) in rt
 missing=[t for t in spec['tokens'] if t not in text]
 # absolute LPC paths used by these NPCs must resolve when they are canonical object paths.
 refs=[]
 for ref in sorted(set(re.findall(r'"(/(?:obj|d)/[^"\\n]+)"',text))):
  rp=MUD/ref.lstrip('/')
  ok=rp.exists() or rp.with_suffix('.c').exists()
  refs.append({'path':ref,'exists':ok})
  if not ok: failures.append(f'{fn}: missing dependency {ref}')
 if not room_ref: failures.append(f'{fn}: room does not reference npc/{stem}')
 if missing: failures.append(f'{fn}: missing canonical behavior tokens: {missing}')
 rows.append({'file':fn,'name':spec['name'],'room':spec['room'],'roomReferenced':room_ref,'behaviorTokensPresent':len(spec['tokens'])-len(missing),'behaviorTokensExpected':len(spec['tokens']),'missingTokens':missing,'absoluteDependencies':refs,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
report={'scope':'snow special NPC canonical wiring audit','sourceBoundary':'local canonical source/upstream/mudlib; no legacy-ES2','canonicalFilesModified':False,'npcCount':len(rows),'passed':not failures,'failures':failures,'npcs':rows}
OUT.parent.mkdir(exist_ok=True); OUT.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,ensure_ascii=False,indent=2))
raise SystemExit(0 if report['passed'] else 1)
