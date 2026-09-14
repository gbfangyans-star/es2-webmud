/* CUSTOM HOME SYSTEM
 * WebMUD extension. Not part of taedlar/es2_mudlib canonical content.
 */
#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

object home_owner;

void set_home_owner(object ob) { home_owner = ob; }

void create() {
    set_name(HIY "家園管家" NOR, ({ "home butler", "butler", "家園管家", "管家" }));
    set_race("human");
    set_level(1);
    set("age", 50);
    setup();
}

string long(int raw) {
    int rooms, price;
    string s;

    if (!home_owner) return "一名負責管理私人家園的管家。\n";
    rooms = (int)home_owner->query("custom_home/rooms");
    if (rooms < 0) rooms = 0;
    if (rooms > 10) rooms = 10;

    s = "一名衣著整齊的管家，負責替你管理與擴建私人家園。\n";
    s += sprintf("目前已開發房間：%d / 10\n", rooms);
    if (rooms < 10) {
        price = (rooms + 1) * 10;
        s += sprintf(HIY "下一間開發費用：%d gold\n" NOR, price);
        s += HIG "房型與增建申請請查看大廳的家園告示板（look board）。\n" NOR;
    } else {
        s += HIG "目前可開發的十間房間已全部完成。\n" NOR;
    }
    return s;
}

void init() {
    ::init();
}
