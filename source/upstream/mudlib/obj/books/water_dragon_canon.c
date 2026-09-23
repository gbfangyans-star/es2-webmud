#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name(BLU "【水龍經】" NOR, ({ "Water Dragon Canon", "water dragon canon", "water-dragon-canon", "water", "dragon", "canon", "book", "【水龍經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "依山川水勢尋訪龍脈，記載水流曲直與地形聚散，推演其對五行陰陽的影響。\n");
    set("required/skill", (["literate": 120, "archaic attainment": 90]));
    set("content", (["mysticism": 160]));
    setup();
}
