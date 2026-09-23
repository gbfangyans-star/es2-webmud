#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【百家譯典】", ({ "Compendium of Translations", "compendium of translations", "compendium-of-translations", "compendium", "translations", "book", "【百家譯典】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "匯集各家典籍的譯文與註解，對照原句說明不同用法，幫助讀者通曉較深的篇章。\n");
    set("required/skill", (["literate": 75]));
    set("content", (["literate": 200]));
    setup();
}
