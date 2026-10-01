/* 玉蛛佩 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("玉蛛佩", ({ "jade spider girdle", "girdle" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 65000);
        set("long",
            "玉蛛佩為十三精靈之一的林鬼「青蛛」所有。約兩百多年前，釘\n"
            "靈族的叛軍崛起，但卻總是無法戰勝釘靈王。最後叛軍不惜一切\n"
            "代價，求助於林鬼，林鬼「青蛛」將他從侮天鬼處得來的「玉蛛\n"
            "佩」借給了叛軍首領。此後叛軍數次擊潰釘靈王的軍隊，幸好天\n"
            "朝軍隊及時援助，將叛軍全數斬殺，而「玉蛛佩」則在戰亂後期\n"
            "遺失。林鬼得知「玉蛛佩」存於釘靈古墓，數度想奪回，卻因為\n"
            "已被侮天鬼蠱惑，無法進入由金烏與銀蟾神使所保護的釘靈王族\n"
            "古墓，只好以法力控制著裡面的死屍守護「玉蛛佩」。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor_vs_lightning": 50,
            "force": 10,
        ]));
    }
    setup();
}
