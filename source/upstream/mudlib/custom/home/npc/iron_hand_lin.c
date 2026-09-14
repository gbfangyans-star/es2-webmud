/* CUSTOM SNOW INN EASTER EGG
 * WebMUD extension. Not part of taedlar/es2_mudlib canonical content.
 */
#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

void create() {
    set_name(HIC "林楓炎" NOR,
        ({ "lin fengyan", "lin", "iron hand", "鐵手" }));
    set("title", HIY "三屆打手槍冠軍" NOR);
    set("nickname", HIR "［鐵手］" NOR);
    set_race("human");
    set_level(1);
    set("age", 35);
    set("long", "他的雙手看起來異常結實，神情中帶著對自己紀錄的強烈自信。\n");
    setup();
}

string long(int raw) {
    command("say 小子，要來場酣暢淋漓的打手槍比賽嗎？");
    return "他雙手抱胸站在客棧一角，一副隨時準備接受挑戰的模樣。\n";
}
