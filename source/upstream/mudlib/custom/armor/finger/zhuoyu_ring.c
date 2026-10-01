/* 濁魚珠 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("濁魚珠", ({ "zhuoyu ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 93000);
        set("long",
            "濁魚珠為十三精靈之一的川鬼「濁魚」所有。三百年前於蘭淳焉\n"
            "破聖木取穿靈釋放了侮天鬼，川鬼「濁魚」為救被侮天鬼劫持的\n"
            "璃虹不敵被擒。因恐人間因此洪水氾濫，川鬼「濁魚」盡其餘力\n"
            "將濁魚珠投入羿水河中以定天下百川。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor_vs_fire": 50,
            "wittiness": 50,
        ]));
    }
    setup();
}
