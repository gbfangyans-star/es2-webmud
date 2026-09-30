/* 六靈妖姬鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("六靈妖姬鞭", ({ "whip of evil beauties", "whip" }));
    set_weight(4800);
    init_damage(3, 9, 65, 5, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一條散發著淡淡胭脂香氣的軟鞭﹐整條鞭子上精細的刻畫著六位半裸的\n"
            "妖媚女子﹐握在手中有些心神不寧。\n");
        set("apply_weapon/whip", ([
            "magic_ability": 30,
            "wis": 1,
        ]));
    }
    setup();
}
