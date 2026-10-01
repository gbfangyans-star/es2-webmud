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

mapping query_action() {
    return beast_action[random(sizeof(beast_action))];
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
