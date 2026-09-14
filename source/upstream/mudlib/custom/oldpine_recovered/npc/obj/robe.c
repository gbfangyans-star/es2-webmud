#include <armor.h>
inherit EQUIP;
/* Archaeology staging only: historical display name is not trusted after encoding damage. No room/NPC spawns this object. */
void create(){ set_name("历史法袍（隔离）",({"legacy robe","robe"})); set_weight(1000); set("unit","件"); set("value",10000); set("armor_type",TYPE_CLOTH); set("armor_prop/armor",2); set("armor_prop/spells",3); setup(); }
