/* 六靈玄衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("六靈玄衣", ({ "omega dress", "dress" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 75000);
        set("long",
            "「六靈玄衣」據說是人靈「區冥」在凡間遊玩時，有感與人類不斷進步的\n"
            "文化，便搜集了千年老龍的鱗片、魔獸窮奇的毛髮還有凍塵谷冰蠶的蠶絲\n"
            "縫製而成的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "intimidate": 20,
            "mysticism": 15,
            "armor": 10,
        ]));
    }
    setup();
}
