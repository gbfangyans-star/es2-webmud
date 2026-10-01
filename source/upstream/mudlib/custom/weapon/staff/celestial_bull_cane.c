/* 饕餮法杖 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

// 饕餮法杖：帶在身上（不必裝備），knock <裝備或武器> 把它餵給饕餮，
// 每 25 文價值換一張空白符紙（custom/item/scroll/blank.c）。
#define BLANK_SCROLL    "/custom/item/scroll/blank"
#define VALUE_PER_SHEET 25

void init()
{
    if( this_player() == environment() )
        add_action("do_knock", "knock");
}

int do_knock(string arg)
{
    object me = this_player(), ob, paper;
    int value, sheets;

    if( !arg || environment() != me ) return 0;
    if( !objectp(ob = present(arg, me)) || ob == this_object() ) return 0;

    if( !ob->query("wield_as") && !ob->query("wear_as") )
        return notify_fail("饕餮只吃裝備和武器。\n");
    if( ob->query("equipped") )
        return notify_fail("你得先把" + ob->name() + "卸下來。\n");
    value = ob->query("value");
    if( (sheets = value / VALUE_PER_SHEET) < 1 )
        return notify_fail("饕餮嗅了嗅" + ob->name() + "，一點興趣也沒有。\n");

    paper = new(BLANK_SCROLL);
    paper->set_amount(sheets);
    message_vision("$N拿起$n在杖首的牛嘴上敲了敲，饕餮一口把" + ob->name()
        + "吞了下去，吐出" + chinese_number(sheets) + "張空白符紙。\n", me, this_object());
    destruct(ob);
    if( !paper->move(me) ) paper->move(environment(me));
    return 1;
}


void create()
{
    set_name("饕餮法杖", ({ "celestial bull cane", "staff" }));
    set_weight(17700);
    init_damage(3, 18, 150, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "根");
        set("value", 65000);
        set("long",
            "一根銅製長杖，杖首貌似一張牛嘴，整個看起來好像是一隻仰口朝天、貪得無厭\n"
            "的饕餮等著你在給他東西吃 (knock)。\n");
        set("apply_weapon/twohanded staff", ([
            "str": 3,
            "spi": 3,
            "armor": 50,
        ]));
    }
    setup();
}
