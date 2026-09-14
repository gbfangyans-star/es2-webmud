#include <armor.h>
inherit EQUIP; void create(){ set_name("狼皮披风",({"fur coat","coat"})); set_weight(3000); set("unit","件"); set("value",800); set("armor_type",TYPE_CLOAK); set("armor_prop/armor",4); setup(); }
