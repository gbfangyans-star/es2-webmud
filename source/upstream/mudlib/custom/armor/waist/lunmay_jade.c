/* 寒梅玉珮 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;37m寒梅玉珮\x1b[m", ({ "lunmay jade", "jade" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 65000);
        set("long",
            "這是一條用整塊白玉彫刻而成的梅花形玉珮，是梅影風年少時送給梅\n"
            "夫人的。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "damage": 5,
            "lunmay": 10,
            "advance_lunmay": 10,
        ]));
    }
    setup();
}
