/* 妄焱兵絕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;31m妄焱兵絕\x1b[m", ({ "flame weapon", "blade" }));
    set_weight(8300);
    init_damage(4, 14, 110, 1, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "以煢榮宿鐵為體，經蜀水寒火淬鍊而成，寬約三指，赤中隱碧，柄上更\n"
            "雕有似火騰躍的奇異花紋。\n");
        set("apply_weapon/blade", ([
            "intimidate": 30,
            "str": 2,
        ]));
    }
    setup();
}
