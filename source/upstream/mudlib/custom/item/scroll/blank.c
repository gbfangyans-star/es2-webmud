/* 空白符紙 — 符紙，可以疊在一起。重量每張 1，價值每張 10 文。 */

inherit COMBINED_ITEM;

void create()
{
    set_name("空白符紙", ({ "blank scroll", "scroll" }));
    if( !clonep() ) {
        set("long", "一張空白的符紙。\n");
        set("unit", "疊");
        set("base_unit", "張");
        set("base_value", 10);
        set("base_weight", 1);
    }
    set_amount(1);
    setup();
}
