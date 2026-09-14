inherit ITEM;
void create()
{
    set_name("青銅丹鼎", ({ "bronze reactor", "reactor" }));
    set_weight(1500); set_max_encumbrance(8000);
    set("unit", "座"); set("value", 250);
    set("long", "一座厚實的青銅丹鼎。舊資料確認它用於容納煉丹配方與材料；目前已恢復容器功能，原版火候、配方容量與法術封印流程仍待核心機制復原。\n");
    setup();
}
int accept_object(object me, object ob) { return 1; }
