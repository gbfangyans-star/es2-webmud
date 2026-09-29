/* 古銅刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("古銅刀", ({ "copper blade", "blade" }));
    set_weight(14500);
    init_damage(3, 16, 105, 0, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一把用黃銅製造的大刀﹐雖然不很鋒利﹐但是也有相當的殺傷力。刀口處散發\n"
            "出一種銅綠般的粉末﹐不知道有沒有毒。\n");
    }
    setup();
}
