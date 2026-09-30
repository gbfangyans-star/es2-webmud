/* 斷魂槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("斷魂槍", ({ "spear of slaying", "pike" }));
    set_weight(7300);
    init_damage(3, 15, 90, 5, "pike");
    init_damage(3, 15, 45, 5, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把約五尺長的短槍﹐槍頭乃是用上好的黃銅打造而成。\n"
            "槍柄處刻有一個淺淺的花紋﹐顯得古樸大方。\n");
        set("apply_weapon/pike", ([
            "attack": 15,
            "cor": 1,
        ]));
        set("apply_weapon/secondhand pike", ([
            "attack": 15,
            "cor": 1,
        ]));
    }
    setup();
}
