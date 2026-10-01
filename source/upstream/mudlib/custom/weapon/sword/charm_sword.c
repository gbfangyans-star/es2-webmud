/* 追月流星劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("追月流星劍", ({ "charm sword", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");
    init_damage(3, 18, 100, 6, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 40000);
        set("long",
            "「追月流星劍」，劍長兩尺半薄若蟬翼。據說是劍甲門門主選擇繼承人\n"
            "時才會要求他的弟子門打造此劍，取最為精良者立為新任門主。極品的\n"
            "追月流星劍講求的是鋒芒不露劍氣內藏，重百斤卻形若無物，以指彈其\n"
            "背，聲響不絕。\n");
        set("apply_weapon/sword", ([
            "damage": 10,
            "attack": 30,
        ]));
        set("apply_weapon/secondhand sword", ([
            "damage": 10,
            "attack": 30,
        ]));
    }
    setup();
}
