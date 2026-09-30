/* 封印冰環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

// 緊握戒指祝禱（clutch），得到雨神加持；效果見 daemon/condition/rain_blessing.c。
void init()
{
    add_action("do_clutch", "clutch");
}

int do_clutch(string arg)
{
    if( !arg || !id(arg) ) return 0;
    if( environment() != this_player() ) return 0;
    CONDITION_D("rain_blessing")->clutch(this_player());
    return 1;
}

void create()
{
    set_name("\x1b[1;34m封印冰環\x1b[m", ({ "freeze ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 140000);
        set("long",
            "這枚發出陣陣寒意的戒指，是雨神天龍賜給僕人們用的護身法寶之一。在暗\n"
            "金色的戒環之上，一個呈五爪狀的基座，將其中那顆看起來不起眼的深藍色\n"
            "石頭牢牢扣住。傳說中，雨神天龍的僕人們，在與敵人對戰前，都會事先緊\n"
            "握住(clutch)這枚戒指祝禱一番。透過這個方法得到雨神的神力加持。因此\n"
            "每每都能剋敵至勝。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": 10,
            "taoism-freeze": 15,
            "wis": 2,
        ]));
    }
    setup();
}
