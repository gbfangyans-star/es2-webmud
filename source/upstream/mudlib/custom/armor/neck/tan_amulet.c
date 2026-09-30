/* 天鳴之符 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;31m天鳴之符\x1b[m", ({ "tan amulet", "amulet" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 15000);
        set("long",
            "相傳上古時代, 諸神大戰時遺留下來的護身符; 可以放在衣服裡.\n"
            "護身符表面汎出紫色的光芒, 好像隱藏著什麼力量似的.\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor_vs_lightning": 35,
            "awarness": 25,
            "intimidate": 15,
        ]));
    }
    setup();
}
