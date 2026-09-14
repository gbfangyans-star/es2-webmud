from pathlib import Path
R=Path(__file__).resolve().parents[1]/'source/upstream/mudlib/custom/oldpine_recovered'
checks={
'bandit source profile': ('npc/bandit.c','set("combat_exp",600)'),
'tall bandit source profile': ('npc/tall_bandit.c','set("combat_exp",900)'),
'fat bandit help chain': ('npc/fat_bandit.c','ob=new(__DIR__"bandit_chief")'),
'chief source profile': ('npc/bandit_chief.c','set_skill("blade",60)'),
'butterfly source profile': ('npc/butterfly.c','set_temp("apply/dodge",50)'),
'wolf dog source profile': ('npc/wolf_dog.c','set_temp("apply/attack",45)'),
'short sword': ('npc/obj/short_sword.c','init_sword(15, SECONDARY)'),
'long sword': ('npc/obj/long_sword.c','init_sword(25)'),
'blade': ('npc/obj/blade.c','init_blade(25)'),
'leather': ('npc/obj/leather.c','set("armor_prop/armor",5)'),
'tree2 butterflies': ('room/tree2.c','../npc/butterfly" : 6'),
'pine1 paired bandits': ('room/pine1.c','../npc/tall_bandit" : 1'),
'pine7 wolf dog': ('room/pine7.c','../npc/wolf_dog" : 1'),
}
ok=0
for name,(rel,needle) in checks.items():
    text=(R/rel).read_text()
    passed=needle in text
    ok+=passed
    print(('PASS' if passed else 'FAIL'),name)
print(f'{ok}/{len(checks)} PASS')
raise SystemExit(0 if ok==len(checks) else 1)
