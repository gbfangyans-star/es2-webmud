inherit ITEM;
void create()
{
    set_name("青銅丹爐", ({ "bronze furnace", "furnace" }));
    set_weight(5000); set_max_encumbrance(16000);
    set("unit", "座"); set("value", 10000);
    set("long", "一座沉重的青銅丹爐。舊資料確認原版可架設、放入丹鼎與燃料並依熱量煉丹；目前先恢復為可收納器具，完整 setup、ignite、熱量演算尚未冒充為完成。\n");
    setup();
}
int accept_object(object me, object ob) { return 1; }
