/* 黃玉指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("黃玉指環", ({ "topaz symbol", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 60000);
        set("long",
            "象徵虎刀門人身份的信物指環，用一般的黃玉雕成。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "intimidate": 5,
        ]));
    }
    setup();
}
