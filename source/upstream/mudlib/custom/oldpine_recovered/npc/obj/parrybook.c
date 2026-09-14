/* Historical Old Pine reward. Legacy study metadata preserved verbatim; modern study adapter remains pending. */
inherit ITEM;
void create(){ set_name("过招要旨",({"parrybook","pbook"})); set_weight(800); if(clonep()) set_default_object(__FILE__); else { set("unit","把"); set("long","这是一本介绍过招时如何拆招卸力的书籍。\n对练武人来说是本不可多得的珍宝。\n"); set("value",100); set("material","paper"); set("skill",(["name":"parry","exp_required":15000,"sen_cost":30,"difficulty":25,"max_skill":50])); } }
