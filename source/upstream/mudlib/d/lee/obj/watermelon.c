inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
    set_name("西瓜", ({ "watermelon", "melon" }));
    if( !clonep() ) {
        set("unit", "堆");
        set("base_unit", "顆");
        set("base_value", 50);
        set("base_weight", 1200);
        set("food_stuff", 120);
        set("long", "一顆沉甸甸的西瓜，外皮翠綠。此處食用數值為復原版暫定值，後續若找到原物件資料再覆蓋。\n");
    }
    set_amount(1);
    setup();
}
