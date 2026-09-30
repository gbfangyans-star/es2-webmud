/* 白色長劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("白色長劍", ({ "white sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把雪白色的輕柔長劍, 它的劍刃看起來比白紙還薄, 你仔細一看, 劍柄上\n"
            "隱約刻著一個[齊]字...\n");
        set("apply_weapon/sword", ([
            "attack": 10,
            "force": 5,
            "armor_vs_fire": 15,
        ]));
    }
    setup();
}
