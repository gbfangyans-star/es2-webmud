/* 斑斕虎氅 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("斑斕虎氅", ({ "tiger coat", "coat" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "用數件虎皮組合而成的大氅，最內層是虎毛，中間是烏金絲，最\n"
            "外層則是虎皮。在虎刀門內是只有教席才能穿著的服色。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_wind": 50,
            "armor": 5,
            "intimidate": 25,
        ]));
    }
    setup();
}
