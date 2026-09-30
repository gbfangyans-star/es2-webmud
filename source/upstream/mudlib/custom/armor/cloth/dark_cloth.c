/* 闇之絲衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

// 原資料「職業限制：盜賊」：只有盜賊能穿。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "thief" )
        return notify_fail("只有盜賊才能穿這件衣服。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;30m闇之絲衣\x1b[m", ({ "dark cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "一件全黑的衣服，其材質為黑色細絲所縫製而成的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "dex": 1,
            "sneak": 20,
        ]));
    }
    setup();
}
