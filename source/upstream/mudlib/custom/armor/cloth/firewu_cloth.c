/* 焚羽護衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m焚羽護衣\x1b[m", ({ "firewu cloth", "cloth" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 500);
        set("long",
            "一件看起來遍體漆黑, 不知道用什麼質料製成的緊身衣,\n"
            "上面有著許多厚重的鱗片, 不知道有什麼功用.\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_fire": 50,
            "taoism-fire": 10,
            "armor": 5,
            "su cloudy": 10,
        ]));
    }
    setup();
}
