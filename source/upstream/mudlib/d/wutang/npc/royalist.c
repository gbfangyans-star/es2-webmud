// /d/wutang/npc/royalist.c — 五堂鎮 NPC：趙欽差（依五堂鎮設計表）。

#include <npc.h>
inherit F_SOLDIER;

void create()
{
    seteuid(getuid());
    set_name("趙欽差", ({ "royalist", "zhao" }));
    set_race("human");
    set_class("soldier");
    set_level(1);
    set("age", 50);
    set("long", @LONG
趙欽差是奉皇命遊走各個城市鄉村探訪民間疾苦、收集奇文異事和懲治貪官污吏的。
現今他剛好行至五堂鎮，正在這裡休息並且寫密信給皇上訴說沿途所見所聞。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("B");
    setup();
}
