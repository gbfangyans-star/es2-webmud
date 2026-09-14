inherit NPC;
inherit F_VENDOR;
void create(){
  set_name("測試者", ({"tester"}));
  set_race("human"); set_class("commoner"); set_level(20);
  set_attr("str",20); set_stat_maximum("kee",80);
  set_skill("unarmed",12); map_skill("unarmed","test-art");
  set("merchandise",([ __DIR__ "../obj/thing":3 ]));
  carry_object(STOCK_WEAPON("longsword"))->wield();
}
void init(){ add_action("do_go","go"); }
