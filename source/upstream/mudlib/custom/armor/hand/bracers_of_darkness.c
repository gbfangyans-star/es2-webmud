/* 暗金護腕 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;30m暗金護腕\x1b[m", ({ "bracers of darkness", "bracers" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 20000);
        set("long",
            "一雙由黑色細絲做成的護腕，雖然防禦力較差﹐但是卻可以使手腕變得十分靈活。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "dagger": 5,
            "stealing": 10,
            "secondhand dagger": 5,
        ]));
    }
    setup();
}
