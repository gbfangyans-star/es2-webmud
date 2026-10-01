/* 旱魃簪 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("旱魃簪", ({ "hanba hairpin", "hairpin" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "支");
        set("value", 31000);
        set("long",
            "旱魃簪為十三精靈之一的原鬼「旱魃」所有。百年前，原鬼「旱\n"
            "魃」為躲避侮天鬼而化為人形隱於人間時遇到一個嬌美的女子，\n"
            "就當兩人盡享人間浮華之時，原鬼「旱魃」漸漸感到自己的心已\n"
            "被侮天鬼的惡咒侵蝕。為了保護心愛的女人及其后人，他留下此\n"
            "物便自封於古木『丱天樹』。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor_vs_wind": 50,
            "damage": 10,
        ]));
    }
    setup();
}
