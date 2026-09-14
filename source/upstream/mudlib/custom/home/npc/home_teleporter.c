/* CUSTOM HOME SYSTEM
 * WebMUD extension. Not part of taedlar/es2_mudlib canonical content.
 */
#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

void create() {
    set_name(HIC "家園傳送師" NOR, ({ "home teleporter", "home_teleporter", "teleporter" }));
    set_race("human");
    set_level(1);
    set("age", 40);
    set("long",
        "一名掌握私人空間術法的傳送師，專門替旅人開啟只屬於自己的家園。\n"
        HIY "可進行的動作：\n"
        HIG "  [ 傳送至家園 ]" NOR "  指令：home\n");
    setup();
}

void init() {
    ::init();
    add_action("do_home", "home");
    add_action("do_home", "家園");
}

int do_home(string arg) {
    object me, hall;

    me = this_player();
    if (!me || !userp(me)) return 0;

    /* Do not steal the canonical wizard `home` command. Regular players may
     * still use `home`, while everyone can use the explicit Chinese verb. */
    if (query_verb() == "home" && wizardp(me)) return 0;

    hall = new("/custom/home/room/home_hall");
    if (!hall) return notify_fail("家園空間暫時無法開啟。\n");
    hall->set_home_owner(me);

    message_vision(HIC "$N抬起手，一道柔和的光芒在$n周圍展開。\n" NOR,
        this_object(), me);
    tell_object(me, HIW "你眼前景物一陣模糊，下一刻已踏入自己的家園。\n" NOR);
    me->move(hall);
    return 1;
}
