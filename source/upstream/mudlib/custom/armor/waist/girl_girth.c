/* 束腰帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("束腰帶", ({ "girl girth", "girth" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 500);
        set("long",
            "這是一條素白色的女用束腰帶，通常很多女子為了讓自己的身材看起\n"
            "來更為纖細，都會束上這樣的東西。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "dodge": 10,
            "dex": -1,
        ]));
    }
    setup();
}
