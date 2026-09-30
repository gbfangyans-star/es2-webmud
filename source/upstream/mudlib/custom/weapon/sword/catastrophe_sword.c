/* 邪劍燹日 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;30m邪劍燹日\x1b[m", ({ "catastrophe sword", "sword" }));
    set_weight(16900);
    init_damage(3, 18, 80, 6, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 90000);
        set("long",
            "此劍名為燹日﹐劍開雙刃﹐劍長九尺﹐劍身漆黑如夜﹐隱約之中透露出陣陣邪異氣氛\n"
            "劍名燹日乃源於連綿戰火遮雲蔽日之意﹐傳說擁有此劍者將步入無盡殺戮之修羅道。\n");
        set("apply_weapon/twohanded sword", ([
            "cor": 2,
            "damage": 10,
        ]));
    }
    setup();
}
