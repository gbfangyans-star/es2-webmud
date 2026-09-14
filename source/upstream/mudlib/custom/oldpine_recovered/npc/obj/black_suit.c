#include <armor.h>
inherit EQUIP; void create(){ set_name("夜行衣",({"black suit","suit"})); set_weight(1200); set("unit","件"); set("value",300); set("armor_type",TYPE_CLOTH); set("armor_prop/armor",2); set("wear_msg","$N穿上一套$n。\n"); setup(); }
