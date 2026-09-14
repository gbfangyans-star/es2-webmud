#include <armor.h>
inherit F_HEAD_EQ;
void create(){
 set_name("毛皮帽", ({"fur hat","hat"}));
 set_weight(1000); setup_head_eq();
 set("value",50); set("wear_as","head_eq");
 set("apply_armor/head_eq", ([ "armor":1 ]));
 setup();
}
