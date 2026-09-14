inherit NPC;
inherit F_VENDOR;
void create(){
 set_name("商人", ({"vendor","merchant"}));
 set_race("human"); set_gender("male"); set_level(7);
 set_skill("unarmed", 20); map_skill("unarmed","test-art");
 set("merchandise", ([ __DIR__ "../obj/thing": 3 ]));
 call_out("hello", 2);
}
void init(){ add_action("do_talk","talk"); }
