/* 櫻吹雪 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m櫻吹雪\x1b[m", ({ "cherry blossoms sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 7, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 40000);
        set("long",
            "一把隱隱透出白光的雪白寶劍, 劍身上以紅寶石鑲了數朵花的形狀, 急速揮舞下\n"
            "白色劍網中閃著紅色光芒, 就像極了雪中飄落的花雨。\n");
        set("apply_weapon/sword", ([
            "lunmay": 10,
            "attack": 20,
        ]));
        set("apply_weapon/secondhand sword", ([
            "attack": 20,
            "advance_lunmay": 20,
        ]));
    }
    setup();
}
