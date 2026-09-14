inherit COMBINED_ITEM;
void create()
{
    set_name("松柴", ({ "firewood", "pine firewood" }));
    if( !clonep() ) {
        set("unit", "捆"); set("base_unit", "根");
        set("base_value", 5); set("base_weight", 120);
        set("long", "曬乾的松木柴，原 ES2 資料顯示它是煉丹燃料。現版先恢復為可攜帶、可堆疊物品；真正燃燒與熱量演算待煉丹器具核心復原後接回。\n");
    }
    set_amount(1); setup();
}
