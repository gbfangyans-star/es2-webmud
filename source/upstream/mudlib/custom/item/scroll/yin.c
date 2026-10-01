/* 少陰符 — 符紙，可以疊在一起。重量每張 1，價值每張 50 文。 */

inherit COMBINED_ITEM;

void create()
{
    set_name("少陰符", ({ "scroll of yin", "scroll" }));
    if( !clonep() ) {
        set("long", "一張冷冽透著陰氣的符紙。\n");
        set("unit", "疊");
        set("base_unit", "張");
        set("base_value", 50);
        set("base_weight", 1);
    }
    set_amount(1);
    setup();
}
