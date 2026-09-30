/* 猿仙絲冑 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("猿仙絲冑", ({ "monkey armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 80000);
        set("long",
            "相傳乃陷空島島主路經幻仙池遇一八尺雪猿, 與之酣鬥七天七\n"
            "夜終將雪猿斬殺, 見雪猿皮厚異常乃神物也, 於是割其皮, 食\n"
            "其肉, 突感功力大增。再將猿皮製成寶甲, 穿上後風寒不侵刀\n"
            "劍難傷! 終於獨步武林, 成為一代大俠。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor_vs_ice": 20,
            "armor_vs_wind": 20,
            "mao-shan magic": 10,
            "armor": 20,
        ]));
    }
    setup();
}
