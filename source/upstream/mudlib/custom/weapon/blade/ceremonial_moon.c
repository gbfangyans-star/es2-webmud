/* 井中月 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("井中月", ({ "ceremonial moon", "blade" }));
    set_weight(8300);
    init_damage(4, 14, 110, 1, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "造型典雅﹐做工精良的長刀﹐狹窄的刀身猶如倒映在井水中的彎月﹐似乎\n"
            "難以承受太大的力道。刀身散發著陣陣如霜似雪的寒光顯示出此刀的鋒芒。\n");
        set("apply_weapon/blade", ([
            "intimidate": 50,
        ]));
    }
    setup();
}
