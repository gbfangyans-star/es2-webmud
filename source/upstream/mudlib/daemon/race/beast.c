/*---
description: 野獸種族。只用來區分 NPC（綿羊、野豬等），玩家建立角色時不能選。
---*/
#define BASE_WEIGHT 30000

#include <ansi.h>
#include <race.h>

inherit HUMANOID;

mapping *beast_action = ({
    ([ "action": "$N張口往$n的$l咬去",       "damage_type": "咬傷" ]),
    ([ "action": "$N低頭朝$n的$l猛力撞去",   "damage_type": "瘀傷" ]),
    ([ "action": "$N用蹄子往$n的$l踢了過去", "damage_type": "瘀傷" ]),
});

private void create() {
    ::create();
    seteuid(getuid());
    set("unit", "隻");
    set("civilized", 0);
    set("humanoid", 0);
    set("limbs", ({ "頭部", "頸部", "背上", "腹部", "前腿", "後腿", "尾巴" }));
    set("default_actions", (: call_other, __FILE__, "query_action" :));
    DAEMON_D->register_race_daemon("beast");
}

// NPC 可以用 set("beast_actions", ({ ... })) 指定自己的攻擊動作（例如熊用掌拍、狼用撲咬），
// 沒有指定就用預設的咬、撞、踢。
varargs mapping query_action(object me) {
    mixed acts;

    if( objectp(me) && arrayp(acts = me->query("beast_actions")) && sizeof(acts) )
        return acts[random(sizeof(acts))];
    return beast_action[random(sizeof(beast_action))];
}

/* 野獸強度 1～10（野豬為 4）：精、氣、野獸技能、傷害加成。
 * 用法：在 NPC 的 create() 裡 setup() 之前呼叫 set_beast(強度);
 *       （/std/char/npc.c 會在 setup() 完成後套用這張表）
 */
private mapping *strength_table = ({
    0,
    ([ "gin":  20, "kee":  30, "skill":  0, "damage":  0 ]),
    ([ "gin":  35, "kee":  55, "skill":  0, "damage":  0 ]),
    ([ "gin":  50, "kee":  80, "skill":  5, "damage":  0 ]),
    ([ "gin":  65, "kee": 105, "skill": 10, "damage":  0 ]),
    ([ "gin":  80, "kee": 130, "skill": 15, "damage":  3 ]),
    ([ "gin":  95, "kee": 150, "skill": 20, "damage":  6 ]),
    ([ "gin": 105, "kee": 175, "skill": 30, "damage": 10 ]),
    ([ "gin": 120, "kee": 200, "skill": 40, "damage": 15 ]),
    ([ "gin": 135, "kee": 225, "skill": 50, "damage": 20 ]),
    ([ "gin": 150, "kee": 250, "skill": 60, "damage": 25 ]),
});

void set_strength(object ob, int level) {
    mapping t;
    string st;

    if( !objectp(ob) ) return;
    if( level < 1 ) level = 1;
    if( level > 10 ) level = 10;
    t = strength_table[level];
    foreach(st in ({ "gin", "kee" })) {
        ob->set_stat_maximum(st, t[st]);
        ob->set_stat_effective(st, t[st]);
        ob->set_stat_current(st, t[st]);
    }
    if( t["skill"] ) ob->set_skill("beast", t["skill"]);
    if( t["damage"] ) ob->set_temp("apply/damage", t["damage"]);
    ob->set("beast_strength", level);
}

void setup(object ob) {
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT);
    // 徒手攻擊改用野獸的咬、撞、踢（daemon/skill/beast.c）。
    ob->map_skill("unarmed", "beast");
}

void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":10 + random(6), "cor":10 + random(6), "int":3 + random(3), "spi":3 + random(3),
        "cps":5 + random(6), "dex":10 + random(6), "con":10 + random(6), "wis":3 + random(3)
    ]));
    ob->init_statistic(([ "gin":20, "kee":30, "sen":10 ]));
}

// 野獸不能裝備武器與護具。
int valid_wield(object me, object ob, string skill) { return 0; }
int valid_wear(object me, object ob, string part) { return 0; }

string query_appearance(object ob) { return ""; }
