#!/usr/bin/env python3
from pathlib import Path
import argparse, json, re, hashlib, subprocess

REPO_URL = "https://github.com/taedlar/es2_mudlib"
MARKERS = ["mudlib/std/char.c", "mudlib/feature/char/combat.c", "mudlib/d/snow"]


def sha256(path):
    h=hashlib.sha256()
    with open(path,"rb") as f:
        for b in iter(lambda:f.read(1024*1024), b""):
            h.update(b)
    return h.hexdigest()


def git_meta(repo):
    out={"repository":REPO_URL}
    try:
        remote=subprocess.check_output(["git","-C",str(repo),"remote","get-url","origin"],text=True,stderr=subprocess.DEVNULL).strip()
        head=subprocess.check_output(["git","-C",str(repo),"rev-parse","HEAD"],text=True,stderr=subprocess.DEVNULL).strip()
        branch=subprocess.check_output(["git","-C",str(repo),"branch","--show-current"],text=True,stderr=subprocess.DEVNULL).strip()
        out.update({"origin":remote,"commit":head,"branch":branch})
    except Exception:
        out.update({"origin":None,"commit":None,"branch":None})
    return out


def verify_repo(repo, strict_remote=True):
    repo=Path(repo).resolve()
    missing=[m for m in MARKERS if not (repo/m).exists()]
    if missing:
        raise SystemExit("拒絕索引：不是預期 ES2 工作樹，缺少："+", ".join(missing))
    meta=git_meta(repo)
    if strict_remote and meta.get("origin") and "taedlar/es2_mudlib" not in meta["origin"]:
        raise SystemExit("拒絕索引：Git origin 不是 taedlar/es2_mudlib")
    return repo/"mudlib", meta


def sdecode(s):
    return bytes(s,"utf-8").decode("unicode_escape") if "\\" in s and s.isascii() else s.replace(r'\"','"').replace(r'\n','\n')


def string_set(text,key):
    m=re.search(r'set\s*\(\s*["\']'+re.escape(key)+r'["\']\s*,\s*"((?:\\.|[^"])*)"\s*\)',text,re.S)
    return sdecode(m.group(1)) if m else None


def number_set(text,key):
    m=re.search(r'set\s*\(\s*["\']'+re.escape(key)+r'["\']\s*,\s*(-?\d+)\s*\)',text)
    return int(m.group(1)) if m else None


def heredoc_set(text,key):
    pat=r'set\s*\(\s*["\']'+re.escape(key)+r'["\']\s*,\s*@([A-Z_][A-Z0-9_]*)\s*\n(.*?)\n\1\s*\)'
    m=re.search(pat,text,re.S)
    return m.group(2).strip() if m else None


def parse_inherits(text):
    return [x.strip() for x in re.findall(r'^\s*inherit\s+([^;]+);',text,re.M)]


def parse_exits(text):
    out={}
    m=re.search(r'set\s*\(\s*"exits"\s*,\s*\(\[(.*?)\]\)\s*\)',text,re.S)
    if not m: return out
    for d,prefix,target in re.findall(r'"([^"]+)"\s*:\s*(?:(__DIR__)\s*)?"([^"]+)"',m.group(1)):
        out[d]={"target":target,"relative":bool(prefix)}
    return out


def parse_objects(text):
    out=[]
    m=re.search(r'set\s*\(\s*"objects"\s*,\s*\(\[(.*?)\]\)\s*\)',text,re.S)
    if not m: return out
    for prefix,target,count in re.findall(r'(?:(__DIR__)\s*)?"([^"]+)"\s*:\s*(\d+)',m.group(1)):
        out.append({"target":target,"relative":bool(prefix),"count":int(count)})
    return out


def parse_set_name(text):
    # Common forms in ES2:
    # set_name("foo", ({"foo", "bar"}));
    # set_name("book", "book id", "book");
    m=re.search(r'set_name\s*\(\s*"([^"]+)"\s*,\s*\(\{(.*?)\}\)\s*\)',text,re.S)
    if m:
        return {"name":m.group(1),"ids":re.findall(r'"([^"]+)"',m.group(2))}
    m=re.search(r'set_name\s*\(\s*"([^"]+)"\s*,(.*?)\)\s*;',text,re.S)
    if m:
        ids=re.findall(r'"([^"]+)"',m.group(2))
        return {"name":m.group(1),"ids":ids}
    return {}


def parse_direct_setters(text):
    out={}
    for fn,key in [("set_race","race"),("set_class","class"),("set_gender","gender")]:
        m=re.search(fn+r'\s*\(\s*"([^"]+)"\s*\)',text)
        if m: out[key]=m.group(1)
    for fn,key in [("set_level","level"),("set_weight","weight")]:
        m=re.search(fn+r'\s*\(\s*(-?\d+)\s*\)',text)
        if m: out[key]=int(m.group(1))
    attrs={k:int(v) for k,v in re.findall(r'set_attr\s*\(\s*"([^"]+)"\s*,\s*(-?\d+)\s*\)',text)}
    stats={k:int(v) for k,v in re.findall(r'set_stat_maximum\s*\(\s*"([^"]+)"\s*,\s*(-?\d+)\s*\)',text)}
    if attrs: out["attributes"]=attrs
    if stats: out["stat_maximums"]=stats
    return out


def parse_string_int_mapping(text,key):
    m=re.search(r'set\s*\(\s*"'+re.escape(key)+r'"\s*,\s*\(\[(.*?)\]\)\s*\)',text,re.S)
    if not m:return {}
    return {k:int(v) for k,v in re.findall(r'"([^"]+)"\s*:\s*(-?\d+)',m.group(1))}


def parse_merchandise(text):
    m=re.search(r'set\s*\(\s*"merchandise"\s*,\s*\(\[(.*?)\]\)\s*\)',text,re.S)
    if not m:return []
    rows=[]
    # quoted LPC paths, optionally prefixed with __DIR__
    for prefix,target,count in re.findall(r'(?:(__DIR__)\s*)?"([^"]+)"\s*:\s*(\d+)',m.group(1)):
        rows.append({"target":target,"relative":bool(prefix),"stock":int(count)})
    return rows


def parse_actions(text):
    return [{"handler":fn,"verb":verb} for fn,verb in re.findall(r'add_action\s*\(\s*"([^"]+)"\s*,\s*"([^"]+)"\s*\)',text)]


def parse_equipment(text):
    rows=[]
    for kind,name,action in re.findall(r'carry_object\s*\(\s*STOCK_(WEAPON|ARMOR)\s*\(\s*"([^"]+)"\s*\)\s*\)\s*->\s*(wield|wear)\s*\(',text):
        rows.append({"stock_type":kind.lower(),"name":name,"action":action})
    for prefix,target,action in re.findall(r'carry_object\s*\(\s*(?:(__DIR__)\s*)?"([^"]+)"\s*\)\s*->\s*(wield|wear)\s*\(',text):
        rows.append({"target":target,"relative":bool(prefix),"action":action})
    return rows

def parse_skill_calls(text):
    return [{"skill":s,"level":int(n)} for s,n in re.findall(r'set_skill\s*\(\s*"([^"]+)"\s*,\s*(\d+)\s*\)',text)]


def parse_skill_maps(text):
    rows=[]
    for a,b in re.findall(r'map_skill\s*\(\s*"([^"]+)"\s*,\s*"([^"]+)"\s*\)',text): rows.append({"base":a,"mapped_to":b})
    return rows



def parse_doors(text):
    rows=[]
    # create_door("west", "客棧大門", "east", DOOR_CLOSED);
    for direction,name,other,state in re.findall(
        r'create_door\s*\(\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)',
        text):
        rows.append({"direction":direction,"name":name,"other_side":other,"state":state})
    return rows


def parse_set_temp(text):
    out={}
    # Conservative scalar extraction only.
    for key,val in re.findall(r'set_temp\s*\(\s*"([^"]+)"\s*,\s*"([^"]*)"\s*\)',text):
        out[key]=val
    for key,val in re.findall(r'set_temp\s*\(\s*"([^"]+)"\s*,\s*(-?\d+)\s*\)',text):
        out[key]=int(val)
    return out


def parse_callouts(text):
    rows=[]
    for fn,delay in re.findall(r'call_out\s*\(\s*"([^"]+)"\s*,\s*(\d+)',text):
        rows.append({"function":fn,"delay":int(delay)})
    return rows


def parse_command_hooks(text):
    rows=[]
    # add_action handler/verb pairs are authoritative hooks, not rewritten logic.
    for fn,verb in re.findall(r'add_action\s*\(\s*"([^"]+)"\s*,\s*"([^"]+)"\s*\)',text):
        rows.append({"kind":"add_action","handler":fn,"verb":verb})
    # init() presence tells us the object participates in command registration.
    if re.search(r'(?m)^\s*void\s+init\s*\(',text):
        rows.append({"kind":"init"})
    return rows


def parse_inherit_paths(text):
    rows=[]
    for raw in parse_inherits(text):
        raw=raw.strip()
        quoted=re.fullmatch(r'"([^"]+)"',raw)
        if quoted:
            rows.append({"raw":raw,"target":quoted.group(1),"kind":"literal"})
        else:
            rows.append({"raw":raw,"target":raw,"kind":"symbolic"})
    return rows



def parse_condition_hooks(text):
    rows=[]
    if "update_condition(" in text: rows.append({"hook":"update_condition"})
    if "apply_condition(" in text: rows.append({"hook":"apply_condition"})
    if "clear_condition(" in text or "delete_condition(" in text: rows.append({"hook":"clear_condition"})
    return rows

def parse_death_hooks(text):
    out=[]
    for token,label in [("die(","die"),("death(","death"),("revive(","revive"),
                        ("unconscious(","unconscious"),("corpse","corpse"),
                        ("receive_damage(","receive_damage"),("receive_wound(","receive_wound"),
                        ("kill_ob","kill_ob")]:
        if token in text: out.append(label)
    return sorted(set(out))

def parse_combat_message_traits(text):
    out=[]
    for token,label in [("COMBAT_D","combat_daemon"),("message_vision(","message_vision"),
                        ("tell_object(","tell_object"),("tell_room(","tell_room"),
                        ("damage","damage_text"),("wound","wound_text"),
                        ("attack","attack_text"),("miss","miss_text"),("dodge","dodge_text"),
                        ("parry","parry_text")]:
        if token in text: out.append(label)
    return sorted(set(out))

def parse_runtime_traits(text):
    traits=[]
    checks=[
        ("heart_beat","heart_beat("),
        ("reset","reset("),
        ("init","init("),
        ("combat","attack("),
        ("damage","receive_damage("),
        ("damage","inflict_damage("),
        ("vendor","affirm_merchandise("),
        ("vendor","deliver_merchandise("),
        ("vendor","query_trading_price("),
        ("inventory","carry_object("),
        ("movement","move("),
        ("teaching","improve_skill("),
        ("teaching","set_skill("),
        ("skill_mapping","map_skill("),
        ("timed","call_out("),
        ("interactive","input_to("),
    ]
    for name,token in checks:
        if token in text: traits.append(name)
    return sorted(set(traits))


def parse_wear_profile(text):
    out={}
    wear=string_set(text,"wear_as")
    if wear is not None: out["wear_as"]=wear
    setups=sorted(set(re.findall(r'\bsetup_([A-Za-z0-9_]+)\s*\(\s*\)',text)))
    if setups: out["setup_kinds"]=setups

    # Source pattern used by repository armor objects:
    # set("apply_armor/head_eq", ([ "armor": 1, ... ]));
    applies=[]
    pat=r'set\s*\(\s*"apply_armor/([^"]+)"\s*,\s*\(\[(.*?)\]\)\s*\)'
    for slot,body in re.findall(pat,text,re.S):
        vals={}
        for key,val in re.findall(r'"([^"]+)"\s*:\s*(-?\d+)',body):
            vals[key]=int(val)
        applies.append({"slot":slot,"values":vals})
    if applies: out["armor_apply"]=applies
    return out


def parse_apply_mappings(text):
    """Conservative generic apply_* mapping index. Values are source literals only."""
    rows=[]
    pat=r'set\s*\(\s*"((?:apply|modifier)_[^"]+)"\s*,\s*\(\[(.*?)\]\)\s*\)'
    for key,body in re.findall(pat,text,re.S):
        vals={}
        for k,v in re.findall(r'"([^"]+)"\s*:\s*(-?\d+)',body):
            vals[k]=int(v)
        if vals: rows.append({"key":key,"values":vals})
    return rows


def parse_combat_surface(text):
    """Index combat-facing function names/calls without evaluating LPC."""
    tokens={
      "attack":["attack(", "fight_ob(", "kill_ob("],
      "defense":["defend(", "query_defense("],
      "damage":["receive_damage(", "inflict_damage(", "receive_wound("],
      "weapon":["query_weapon(", "wield(", "unwield("],
      "armor":["query_armor(", "wear(", "remove("],
      "skill":["query_skill(", "map_skill(", "improve_skill("],
      "condition":["update_condition(", "apply_condition("],
      "death":["die(", "killed_by(", "revive("],
      "busy":["is_busy(", "start_busy(", "continue_action("]
    }
    return sorted(k for k,vals in tokens.items() if any(v in text for v in vals))


def parse_numeric_calls(text):
    """Common direct numeric setters, kept separately from generic set()."""
    out={}
    funcs=[
      "set_damage","set_armor","set_value","set_weight","set_level",
      "set_capacity","set_max_encumbrance"
    ]
    for fn in funcs:
        m=re.search(r'\b'+re.escape(fn)+r'\s*\(\s*(-?\d+)\s*\)',text)
        if m: out[fn]=int(m.group(1))
    return out


def parse_skill_contract(text):
    """Source-visible skill daemon interface only; no semantic inference."""
    names=[
        "valid_enable","valid_learn","valid_effect","valid_exercise",
        "skill_improved","skill_advanced","attack_using","dodge_using",
        "parry_using","exert_function","perform_action","practice_skill",
        "query_skill_name","query_action","query_damage_type"
    ]
    present=[n for n in names if re.search(r'\b'+re.escape(n)+r'\s*\(',text)]
    enables=[]
    for fn in ["valid_enable","valid_learn"]:
        # Collect only literal string arguments occurring in these function bodies/signatures.
        if re.search(r'\b'+fn+r'\s*\(',text):
            enables.append(fn)
    return {"functions":present,"contracts":enables} if present or enables else {}

def parse_equipment_hooks(text):
    names=["wear","remove","wield","unwield","query_wielded","query_worn",
           "query_weapon","query_armor","setup_weapon","setup_armor"]
    return sorted(n for n in names if re.search(r'\b'+re.escape(n)+r'\s*\(',text))

def parse_damage_contract(text):
    names=["query_strength","query_ability","defend","absorb","inflict_damage",
           "receive_damage","receive_wound","attack","fight_ob","select_opponent"]
    return sorted(n for n in names if re.search(r'\b'+re.escape(n)+r'\s*\(',text))

def parse_object_accept_hooks(text):
    out=[]
    for n in ["accept_object","accept_fight","accept_kill","accept_give","accept_message"]:
        if re.search(r'\b'+re.escape(n)+r'\s*\(',text): out.append(n)
    return out



def extract_function_body(text, name):
    """Return a conservative brace-balanced function body, or empty string."""
    m=re.search(r'\b'+re.escape(name)+r'\s*\([^)]*\)\s*\{',text,re.S)
    if not m:return ""
    start=m.end();depth=1;i=start
    in_str=False;esc=False
    while i<len(text):
        c=text[i]
        if in_str:
            if esc:esc=False
            elif c=="\\":esc=True
            elif c=='"':in_str=False
        else:
            if c=='"':in_str=True
            elif c=='{':depth+=1
            elif c=='}':
                depth-=1
                if depth==0:return text[start:i]
        i+=1
    return ""

def parse_valid_enable_literals(text):
    body=extract_function_body(text,"valid_enable")
    if not body:return []
    # Only string literals visibly compared/returned inside valid_enable.
    return sorted(set(re.findall(r'"([^"]+)"',body)))

def parse_wield_as(text):
    one=string_set(text,"wield_as")
    if one is not None:return [one]
    m=re.search(r'set\s*\(\s*"wield_as"\s*,\s*\(\{(.*?)\}\)\s*\)',text,re.S)
    return re.findall(r'"([^"]+)"',m.group(1)) if m else []

def parse_skill_daemon_calls(text):
    rows=[]
    # Exact literal daemon references only.
    for name,method in re.findall(r'SKILL_D\s*\(\s*"([^"]+)"\s*\)\s*->\s*([A-Za-z_][A-Za-z0-9_]*)\s*\(',text):
        rows.append({"skill":name,"method":method,"dynamic":False})
    # Dynamic dispatch is recorded separately and never resolved by guessing.
    for expr,method in re.findall(r'SKILL_D\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*->\s*([A-Za-z_][A-Za-z0-9_]*)\s*\(',text):
        rows.append({"expression":expr,"method":method,"dynamic":True})
    return rows

def parse_weapon_dispatch(text):
    out={}
    if re.search(r'\battack_with\s*\(',text):out["attack_with"]=True
    if re.search(r'\binflict_damage\s*\(',text):out["inflict_damage"]=True
    wa=parse_wield_as(text)
    if wa:out["wield_as"]=wa
    # init_damage literals expose supported weapon skill names when literal.
    dmg=[]
    for args in re.findall(r'\binit_damage\s*\((.*?)\)\s*;',text,re.S):
        names=re.findall(r'"([^"]+)"',args)
        if names:dmg.extend(names)
    if dmg:out["damage_skills"]=sorted(set(dmg))
    return out

def parse_function_calls(text):
    """Small source-link surface for audited gameplay dispatch."""
    names=["attack_using","dodge_using","parry_using","exert_function","perform_action",
           "improve_skill","query_skill","map_skill","wield","wear","unequip",
           "receive_damage","inflict_damage","apply_condition","update_condition"]
    return sorted(n for n in names if re.search(r'(?:->|\b)'+re.escape(n)+r'\s*\(',text))


def parse_functions(text):
    # LPC function signatures, intentionally conservative
    pat=r'(?m)^\s*(?:(?:private|protected|public|static|nomask|varargs)\s+)*(?:int|string|void|object|mapping|mixed|float|status|mixed\*|string\*|object\*)\s+([A-Za-z_][A-Za-z0-9_]*)\s*\('
    return sorted(set(re.findall(pat,text)))


def classify(rel,text):
    p="/"+rel.replace("\\","/")
    inh=" ".join(parse_inherits(text))
    if p.startswith("/cmds/"): return "command"
    if "/skill/" in p or p=="/std/skill.c" or "SKILL" in inh: return "skill"
    if p in {"/obj/login.c","/obj/user.c"}: return "runtime"
    if "/npc/" in p or "NPC" in inh: return "npc"
    if "/obj/" in p or any(x in inh for x in ["ITEM","WEAPON","ARMOR","MONEY"]): return "item"
    if p.startswith("/d/") and ('"exits"' in text or "inherit ROOM" in text): return "room"
    if p.startswith("/daemon/") or p.startswith("/adm/daemon/") or p.startswith("/adm/daemons/"): return "daemon"
    if p.startswith("/feature/"): return "feature"
    if p.startswith("/std/"): return "prototype"
    if p.startswith("/include/"): return "include"
    return "other"


def extract(path,mudlib):
    rel=path.relative_to(mudlib).as_posix(); text=path.read_text(encoding="utf-8",errors="replace")
    typ=classify(rel,text); sn=parse_set_name(text)
    rec={"file":rel,"path":"/"+(rel[:-2] if rel.endswith(".c") else rel),"type":typ,"sha256":sha256(path),"inherits":parse_inherits(text),"inherit_refs":parse_inherit_paths(text),"functions":parse_functions(text),"runtime_traits":parse_runtime_traits(text),"combat_surface":parse_combat_surface(text),"source_policy":"taedlar/es2_mudlib only"}
    if typ == "command":
        rec["command"] = Path(rel).stem
        rec["command_group"] = Path(rel).parts[1] if len(Path(rel).parts) > 1 else ""
    if "input_to" in text:
        rec["uses_input_to"] = True
    if re.search(r'input_to\s*\([^\n]*,\s*1\s*[,)]', text):
        rec["uses_hidden_input"] = True
    prompts = re.findall(r'write\s*\(\s*"([^"\n]{2,120})"\s*\)', text)
    if prompts:
        rec["literal_prompts"] = prompts[:40]
    if sn: rec.update(sn)
    rec.update(parse_direct_setters(text))
    wear_profile=parse_wear_profile(text)
    if wear_profile: rec.update(wear_profile)
    apply_maps=parse_apply_mappings(text)
    if apply_maps: rec["apply_mappings"]=apply_maps
    numeric_calls=parse_numeric_calls(text)
    skill_contract=parse_skill_contract(text)
    equipment_hooks=parse_equipment_hooks(text)
    damage_contract=parse_damage_contract(text)
    accept_hooks=parse_object_accept_hooks(text)
    valid_enable_literals=parse_valid_enable_literals(text)
    skill_daemon_calls=parse_skill_daemon_calls(text)
    weapon_dispatch=parse_weapon_dispatch(text)
    function_calls=parse_function_calls(text)
    if numeric_calls: rec["numeric_calls"]=numeric_calls
    if skill_contract: rec["skill_contract"]=skill_contract
    if equipment_hooks: rec["equipment_hooks"]=equipment_hooks
    if damage_contract: rec["damage_contract"]=damage_contract
    if accept_hooks: rec["accept_hooks"]=accept_hooks
    if valid_enable_literals: rec["valid_enable_literals"]=valid_enable_literals
    if skill_daemon_calls: rec["skill_daemon_calls"]=skill_daemon_calls
    if weapon_dispatch: rec["weapon_dispatch"]=weapon_dispatch
    if function_calls: rec["function_calls"]=function_calls
    for k in ["short","name","race","gender","unit","material","attitude","life_form","weapon_type","wear_as"]:
        v=string_set(text,k)
        if v is not None: rec[k]=v
    longv=heredoc_set(text,"long") or string_set(text,"long")
    if longv is not None: rec["long"]=longv
    for k in ["weight","value","damage","armor","age"]:
        v=number_set(text,k)
        if v is not None: rec[k]=v
    ex=parse_exits(text); objs=parse_objects(text); skills=parse_skill_calls(text); maps=parse_skill_maps(text)
    if ex: rec["exits"]=ex
    if objs: rec["objects"]=objs
    if skills: rec["skills"]=skills
    if maps: rec["skill_maps"]=maps
    merchandise=parse_merchandise(text)
    actions=parse_actions(text)
    equipment=parse_equipment(text)
    doors=parse_doors(text)
    temp_values=parse_set_temp(text)
    callouts=parse_callouts(text)
    command_hooks=parse_command_hooks(text)
    condition_hooks=parse_condition_hooks(text)
    death_hooks=parse_death_hooks(text)
    combat_message_traits=parse_combat_message_traits(text)
    required=parse_string_int_mapping(text,"required/skill")
    content=parse_string_int_mapping(text,"content")
    if merchandise: rec["merchandise"]=merchandise
    if actions: rec["actions"]=actions
    if equipment: rec["equipment"]=equipment
    if doors: rec["doors"]=doors
    if temp_values: rec["temp_values"]=temp_values
    if callouts: rec["callouts"]=callouts
    if command_hooks: rec["command_hooks"]=command_hooks
    if condition_hooks: rec["condition_hooks"]=condition_hooks
    if death_hooks: rec["death_hooks"]=death_hooks
    if combat_message_traits: rec["combat_message_traits"]=combat_message_traits
    if required: rec["required_skills"]=required
    if content: rec["study_content"]=content
    m=re.search(r'DAEMON_D->register_skill_daemon\s*\(\s*"([^"]+)"\s*\)',text)
    if m: rec["registered_skill_daemon"]=m.group(1)
    flags=[]
    for token,label in [("add_action(","custom_action"),("create_door(","door"),("call_out(","timed_logic"),("set_leader(","leader_ai"),("set_vendor(","vendor_logic"),("merchandise","vendor_logic"),("set_temp(\"weapon", "weapon_runtime"),("receive_damage(","damage_logic"),("inflict_damage(","damage_logic")]:
        if token in text: flags.append(label)
    rec["manual_review"]=sorted(set(flags))
    return rec


def write_indexes(records,out,meta):
    out.mkdir(parents=True,exist_ok=True)
    bytype={}
    for r in records: bytype.setdefault(r["type"],[]).append(r)
    manifest={"source":REPO_URL,"source_policy":"SOURCE-ONLY / no external augmentation","git":meta,"total_files":len(records),"counts":{k:len(v) for k,v in sorted(bytype.items())}}
    (out/"manifest.json").write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding="utf-8")
    (out/"all.json").write_text(json.dumps(records,ensure_ascii=False,indent=2),encoding="utf-8")
    for typ,rows in bytype.items(): (out/(typ+"s.json")).write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding="utf-8")
    return manifest


def main():
    ap=argparse.ArgumentParser(); ap.add_argument("repo"); ap.add_argument("-o","--out",default="catalog/generated"); ap.add_argument("--allow-fixture",action="store_true")
    a=ap.parse_args(); mudlib,meta=verify_repo(a.repo,strict_remote=not a.allow_fixture)
    records=[extract(p,mudlib) for p in mudlib.rglob("*") if p.is_file() and p.suffix in {".c",".h"}]
    records.sort(key=lambda x:x["file"])
    print(json.dumps(write_indexes(records,Path(a.out),meta),ensure_ascii=False,indent=2))

if __name__=="__main__": main()
