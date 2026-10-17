/*---
description: 封山劍法（NEW 新版武功寫法）。封山派劍法，可 enable 在劍術與雙手劍，不能 enable 在招架上。
             攻守兼備、變化多端，爆發不足；招式敘述取自「梅影風 vs 柳東蘆」對戰紀錄。
             設計見 docs/martial_arts/封山派_封山劍法與倒亂七星步法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

private void create()
{
    seteuid(getuid());

    art_id    = "fonxansword";
    art_name  = "封山劍法";
    art_usage = "sword";
    art_desc  = "封山派最受推崇的劍法，變化多端、攻守兼備，"
                + "不以一擊之威見長，而以綿長的後勁取勝。";
    art_bonus = 0;

    moves = ({
        ([ "name": "峰迴路轉", "attack": 7, "defense": 5, "force": 1, "bonus": 0, "damage_type": "刺傷",
           "action": "$N使一招「峰迴路轉」﹐手中$w如一條銀蛇般刺向$n的$l" ]),
        ([ "name": "空山鳥語", "attack": 7, "defense": 4, "force": 2, "bonus": 0, "damage_type": "割傷",
           "action": "$N使出封山劍法中的「空山鳥語」﹐劍光霍霍斬向$n的$l" ]),
        ([ "name": "御風而行", "attack": 6, "defense": 7, "force": 1, "bonus": 0, "damage_type": "割傷",
           "action": "$N一招「御風而行」﹐身形隨劍滑出數尺﹐手中$w斬向$n的$l" ]),
        ([ "name": "旭日東昇", "attack": 9, "defense": 3, "force": 2, "bonus": 5, "damage_type": "刺傷",
           "action": "$N手中$w中宮直進﹐一式「旭日東昇」對準$n的$l刺出一劍" ]),
        ([ "name": "金光瀉地", "attack": 9, "defense": 2, "force": 2, "bonus": 5, "damage_type": "刺傷",
           "action": "$N縱身一躍﹐手中$w一招「金光瀉地」對準$n的$l斜斜刺出一劍" ]),
        ([ "name": "童子引路", "attack": 5, "defense": 4, "force": 3, "bonus": 10, "damage_type": "刺傷",
           "action": "$N的$w憑空一指﹐一招「童子引路」刺向$n的$l" ]),
        ([ "name": "柳暗花明", "attack": 7, "defense": 5, "force": 1, "bonus": 0, "damage_type": "刺傷",
           "action": "$N手中$w向外一分﹐使一招「柳暗花明」反手對準$n$l一劍刺去" ]),
        ([ "name": "空谷秋虹", "attack": 6, "defense": 6, "force": 1, "bonus": 0, "damage_type": "割傷",
           "action": "$N橫劍上前﹐身形一轉手中$w使一招「空谷秋虹」畫出一道光弧斬向$n的$l" ]),
    });

    art_entry     = 20;
    art_entry_msg = "你終於練成了封山劍法。\n";

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 29;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon("fonxansword");
    setup();
}

/* 可當劍術、雙手劍使用，不能當招架（使用者定案，2026-10-17）。 */
int valid_enable(string usage) { return usage == "sword" || usage == "twohanded sword"; }

/* 學習條件：封山派弟子。 */
int valid_learn(object me)
{
    if( !is_faction(me, "fighter.fonxan") )
        return notify_fail("你不是封山派弟子﹐無法修練封山劍法。\n");
    return 1;
}
