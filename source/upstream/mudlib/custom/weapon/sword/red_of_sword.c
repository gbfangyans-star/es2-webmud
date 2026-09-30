/* 朱綸祭劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("朱綸祭劍", ({ "red of sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 7, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一把以玉鐵所打造而成的劍器，劍身上以天河硃砂書寫著道家密咒，密宗\n"
            "心經等古老文字。\n");
        set("apply_weapon/sword", ([
            "taoism of nature": 10,
            "taoism of darkness": 10,
        ]));
        set("apply_weapon/secondhand sword", ([
            "taoism of nature": 10,
            "taoism of darkness": 10,
        ]));
    }
    setup();
}
