/* 纏布刀／玉戒尺 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

// 纏布刀：平常以纏布包著；裝備時抽出玉刀，名稱變成「玉戒尺」，解除裝備時收回。
#define WRAPPED_NAME    "纏布刀"
#define WRAPPED_IDS     ({ "wrapped blade", "blade" })
#define DRAWN_NAME      "玉戒尺"
#define DRAWN_IDS       ({ "green blade", "wrapped blade", "blade" })

varargs int wield(string as_skill)
{
    if( !::wield(as_skill) ) return 0;
    set_name(DRAWN_NAME, DRAWN_IDS);
    return 1;
}

int unequip()
{
    if( !::unequip() ) return 0;
    set_name(WRAPPED_NAME, WRAPPED_IDS);
    return 1;
}


void create()
{
    set_name(WRAPPED_NAME, WRAPPED_IDS);
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 55000);
        set("wield_msg", "$N從纏布抽出一把亮晃晃的玉刀，緊握在手上。\n");
        set("unwield_msg", "$N將手上的玉刀小心翼翼地收回纏布中。\n");
        set("long",
            "這是一把青綠色半透明的戒尺，但戒尺一邊開了鋒，所以可以當把刀刃使用﹐刀身上\n"
            "刻著【七傷七損】四個字，手握刀柄可感覺到戒尺上傳來微溫，稍稍摧動內力則可明\n"
            "顯感覺到體內真氣源源流入兵器中。\n");
        set("apply_weapon/blade", ([
            "huge force": 10,
            "force": 10,
            "parry": 10,
        ]));
    }
    setup();
}
