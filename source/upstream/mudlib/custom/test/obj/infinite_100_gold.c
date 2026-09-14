/* CUSTOM TEST OBJECT
 * Infinite 100-gold pickup for WebMUD development/testing.
 * The fixture remains in Snow Inn and grants canonical /obj/money/gold.
 */
inherit ITEM;

void create()
{
    set_name("測試用黃金（100兩）", ({ "test gold", "test_gold", "測試黃金", "gold100" }));
    set("unit", "份");
    set("long", "這是一份供測試使用的黃金。每次拿取都會得到一百兩真正的黃金，這份測試物本身不會消失。\n");
    set_weight(1);
    setup();
}

varargs int move(mixed dest, int silent)
{
    object gold;

    if (objectp(environment()) && base_name(environment()) == "/d/snow/inn_hall"
    && objectp(dest) && dest->is_character()) {
        gold = new("/obj/money/gold");
        gold->set_amount(100);
        if (!gold->move(dest)) {
            destruct(gold);
            return notify_fail("你現在拿不下這些測試黃金。\n");
        }
        tell_object(dest, "你取得了一百兩測試用黃金。\n");
        return 1;
    }

    return ::move(dest, silent);
}
