#include <armor.h>
inherit F_CLOTH;
void create(){
 set_name("布衣", "cloth");
 set_weight(1000); setup_cloth();
 set("unit","件"); set("value",0); set("wear_as","cloth");
 set("apply_armor/cloth", ([ "armor":1 ]));
 setup();
}
