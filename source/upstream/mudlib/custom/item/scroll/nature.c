/* 先天符 — 符紙，可以疊在一起。重量每張 1，價值每張 50 文。 */

inherit COMBINED_ITEM;

void create()
{
    set_name("先天符", ({ "scroll of nature", "scroll" }));
    if( !clonep() ) {
        set("long", "一張散發著自然的氣息的符紙。\n");
        set("unit", "疊");
        set("base_unit", "張");
        set("base_value", 50);
        set("base_weight", 1);
    }
    set_amount(1);
    setup();
}
