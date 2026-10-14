/*---
description: NPC 基本技能 —— 依職業、等級、門派自動算出 NPC 的技能等級。
custom: NEW. WebMUD NPC 技能設計（使用者設計，2026-10-14）：技能只看等級，不受強度 C/B/A/S 影響。
---*/

// 用法：有 set_power() 的 NPC 在 setup() 時自動套用，不必另外寫。
//
// 規則（docs/CUSTOM_NPC_SKILL.md）：
//   技能等級 = 等級 × 係數，最高 200。
//     主修 ×3、通用 ×2、輔助 ×1.5。
//   平民：不設技能。
//   其他職業通用：dodge、parry、unarmed（×2）。
//   手上武器的技能一律算主修（裝備後才知道，見 apply_weapon_skills()）。
//   各職業主修／輔助見下方 class_skill。
//   門派（custom_faction）：達到內功門檻等級時學會該門派內功（主修），
//     並把 force 對應到該內功；門派武功清單之後補上（sect 表的 "arts"）。
//   create() 裡手動 set_skill()/map_skill() 的項目保留不覆蓋。

#define SKILL_CAP       200

// 係數（百分比）
#define MAIN_PCT        300
#define COMMON_PCT      200
#define AUX_PCT         150

private string *common_skill = ({ "dodge", "parry", "unarmed" });

// 各職業的主修與輔助技能。平民不在表上（不設技能）。
// "common" 為 0 表示該職業不套用通用技能。
private mapping class_skill = ([
    "fighter":   ([ "main": ({ }),                                      "aux": ({ }) ]),
    "soldier":   ([ "main": ({ "berserk" }),                            "aux": ({ }) ]),
    "thief":     ([ "main": ({ "backstab", "killerhood" }),             "aux": ({ "sneak", "dagger" }) ]),
    "taoist":    ([ "main": ({ "spells" }),                             "aux": ({ }) ]),
    "scholar":   ([ "main": ({ "dodge", "literate", "archaic attainment" }), "aux": ({ }) ]),
    "monk":      ([ "main": ({ "magic" }),                              "aux": ({ }) ]),
    "alchemist": ([ "main": ({ "magic" }),                              "aux": ({ }) ]),
]);

// 門派表，以 custom_faction 為索引（與玩家拜師後的記號相同）。
//   name        門派名稱
//   force       門派內功；force_level 為學會內功所需的人物等級
//   arts        門派武功：({ ([ "skill": 武功, "map": 對應的基本技能或 0, "level": 人物等級門檻 ]) })
//               （使用者之後提供對照表再補）
private mapping sect = ([
    "fighter.tiger": ([
        "name":        "虎刀門",
        "force":       "tiger-force",
        "force_level": 15,
        "arts":        ({ }),
    ]),
    "fighter.lunmay": ([
        "name":        "冷梅莊",
        "force":       "hainmay force",
        "force_level": 15,
        "arts":        ({ }),
    ]),
]);

void create() { seteuid(getuid()); }

int calc_level(int lv, int pct)
{
    int val;

    if( lv < 1 ) lv = 1;
    val = lv * pct / 100;
    if( val < 1 ) val = 1;
    return val > SKILL_CAP ? SKILL_CAP : val;
}

mapping query_sect(string faction) { return mapp(sect[faction]) ? copy(sect[faction]) : 0; }

private void put(mapping m, string skill, int val)
{
    if( val > m[skill] ) m[skill] = val;
}

// 依職業、等級、門派算出應有的技能（不含武器技能）。
// 傳回 ([ "skills": ([ 技能: 等級 ]), "map": ([ 基本技能: 對應武功 ]) ])
mapping calc_skills(string cls, int lv, string faction)
{
    mapping skills, maps, cs, s;
    string sk;

    skills = ([]);
    maps = ([]);
    if( !mapp(cs = class_skill[cls]) )      // 平民或未知職業：不設技能
        return ([ "skills": skills, "map": maps ]);

    foreach( sk in common_skill ) put(skills, sk, calc_level(lv, COMMON_PCT));
    foreach( sk in cs["aux"] )    put(skills, sk, calc_level(lv, AUX_PCT));
    foreach( sk in cs["main"] )   put(skills, sk, calc_level(lv, MAIN_PCT));

    if( mapp(s = sect[faction]) ) {
        if( s["force"] && lv >= s["force_level"] ) {
            put(skills, "force", calc_level(lv, MAIN_PCT));
            put(skills, s["force"], calc_level(lv, MAIN_PCT));
            maps["force"] = s["force"];
        }
        foreach( mapping art in s["arts"] ) {
            if( lv < art["level"] ) continue;
            put(skills, art["skill"], calc_level(lv, MAIN_PCT));
            if( art["map"] ) {
                put(skills, art["map"], calc_level(lv, MAIN_PCT));
                maps[art["map"]] = art["skill"];
            }
        }
    }
    return ([ "skills": skills, "map": maps ]);
}

// 套用到 NPC 身上。由 /std/char/npc.c 的 setup() 呼叫。
void apply_skills(object ob, mapping manual_skill, mapping manual_map)
{
    mapping r;
    string sk;
    int lv;

    if( !objectp(ob) ) return;
    if( !mapp(manual_skill) ) manual_skill = ([]);
    if( !mapp(manual_map) ) manual_map = ([]);

    r = calc_skills(ob->query_class(), ob->query_level(), ob->query("custom_faction"));
    foreach( sk, lv in r["skills"] )
        if( !manual_skill[sk] ) ob->set_skill(sk, lv);
    foreach( sk in keys(r["map"]) )
        if( !manual_map[sk] && !manual_skill[sk] ) ob->map_skill(sk, r["map"][sk]);
}

// 手上武器的技能（主修）。NPC 在 setup() 之後才拿武器，所以晚一步套用。
void apply_weapon_skills(object ob, mapping manual_skill)
{
    mapping weapon;
    string sk;

    if( !objectp(ob) || !mapp(class_skill[ob->query_class()]) ) return;
    if( !mapp(manual_skill) ) manual_skill = ([]);
    if( !mapp(weapon = ob->query_temp("weapon")) ) return;

    foreach( sk in keys(weapon) ) {
        if( manual_skill[sk] ) continue;
        if( ob->query_skill(sk, 1) < calc_level(ob->query_level(), MAIN_PCT) )
            ob->set_skill(sk, calc_level(ob->query_level(), MAIN_PCT));
    }
}
