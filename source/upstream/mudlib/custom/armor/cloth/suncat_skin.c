/* 烏金皮 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("烏金皮", ({ "suncat skin", "skin" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "張");
        set("value", 18000);
        set("long",
            "這是日神所養的神獸烏金貓的皮毛，實乃無價之寶。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_fire": 50,
            "cor": 1,
            "damage": 20,
        ]));
    }
    setup();
}
