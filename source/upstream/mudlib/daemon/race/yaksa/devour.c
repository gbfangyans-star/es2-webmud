/* CUSTOM RACE COMMAND: yaksa devour */
#include <ansi.h>
inherit F_CLEAN_UP;

#define TICK_SECONDS 2

private void create() { seteuid(getuid()); }

// 吞食期間以 call_out 每 tick 吞一口，保持載入。
int clean_up() { return 1; }

private int rnd(int n) { return n > 0 ? random(n) : 0; }

private void stop_devour(object me) {
    if (objectp(me)) me->delete_temp("yaksa_devour");
}

// 永久增加精氣神最大值，並同時補上目前值，讓增加的部分立即可用。
private void grow(object me, string stat, int n) {
    if (n < 1) return;
    me->advance_stat(stat, n);
    me->heal_stat(stat, n);
    me->supplement_stat(stat, n);
}

// 吞完玩家鬼魂：依原始種族資料給予永久加成（取消反噬）。
private void reward_player(object me, int ghost_gin) {
    int count, big, gin, kee, sen, mine;

    count = me->query("yaksa/devoured_players");
    me->add("yaksa/devoured_players", 1);

    mine = me->query_stat_maximum("gin");
    if (me->query_stat_maximum("kee") > mine) mine = me->query_stat_maximum("kee");
    if (ghost_gin >= mine) {
        tell_object(me, "這個鬼魂的精氣比你還強，你沒能從中得到任何好處。\n");
        return;
    }

    // 前 10 次必定大幅增加；之後機率 = 10 / (10 + random(吞食次數))。
    big = count < 10 || random(10 + rnd(count)) < 10;
    if (big) {
        gin = 1 + ghost_gin / 40;
        kee = 1 + rnd(ghost_gin / 40);
        sen = 1 + rnd(ghost_gin / 80);
    } else {
        gin = 1 + random(2);
        kee = random(2);
        sen = 0;
    }
    grow(me, "gin", gin);
    grow(me, "kee", kee);
    grow(me, "sen", sen);
    tell_object(me, HIG "你的精增加了 " + gin + " 點"
        + (kee ? "、氣增加了 " + kee + " 點" : "")
        + (sen ? "、神增加了 " + sen + " 點" : "") + "！\n" NOR);
}

private void finish(object me, object victim, int total) {
    int ghost_gin;

    message_vision(HIR "$N張口一吸，將$n最後一縷魂魄吞進肚裡！\n" NOR, me, victim);
    ghost_gin = me->query_temp("yaksa_devour/ghost_gin");
    stop_devour(me);

    if (userp(victim)) {
        // 夜叉族的鬼魂，精以兩倍計算。
        if (victim->query_race() == "yaksa") ghost_gin *= 2;
        victim->die();
        CHAR_D->make_mist(victim);
        reward_player(me, ghost_gin);
        return;
    }

    // 鬼魂類 NPC：吞多少補多少精、神（目前值與受損的最大值）。
    me->heal_stat("gin", total);
    me->supplement_stat("gin", total);
    me->heal_stat("sen", total);
    me->supplement_stat("sen", total);
    tell_object(me, HIG "吞下的鬼氣補回了你的精神。\n" NOR);
    destruct(victim);
}

void devour_tick(object me, object victim, int serial) {
    int bite, left, total;

    if (!objectp(me) || me->query_temp("yaksa_devour/serial") != serial) return;
    if (!objectp(victim) || environment(victim) != environment(me)
    ||  victim->query("life_form") != "ghost"
    ||  !living(me) || me->is_fighting() || me->query("life_form") == "ghost") {
        stop_devour(me);
        tell_object(me, "你停止了吞食。\n");
        return;
    }

    // 每口吞食量 = 膽識 x 機敏 + random(自己的精)，從鬼魂的精扣除。
    bite = me->query_attr("cor") * me->query_attr("dex") + rnd(me->query_stat("gin"));
    left = victim->query_stat("gin");
    if (bite > left) bite = left;
    total = me->query_temp("yaksa_devour/total") + bite;
    me->set_temp("yaksa_devour/total", total);

    if (left - bite <= 0) {
        victim->set_stat_current("gin", 0);
        finish(me, victim, total);
        return;
    }
    victim->set_stat_current("gin", left - bite);
    message_vision(HIM "$N大口吞食著$n的魂魄，$n的身形越來越淡了....\n" NOR, me, victim);

    // 鬼魂對吞食完全沒有防禦能力，吞食期間雙方都無法行動。
    me->start_busy(1);
    victim->start_busy(1);
    call_out("devour_tick", TICK_SECONDS, me, victim, serial);
}

int main(object me, string arg) {
    object victim;
    int serial;

    if (me->query_race() != "yaksa") return notify_fail("你不是夜叉，無法吞食鬼魂。\n");
    if (me->query("life_form") == "ghost") return notify_fail("你自己已經是鬼魂了。\n");
    if (me->query_temp("yaksa_devour")) return notify_fail("你正在吞食鬼魂。\n");
    if (me->is_busy()) return notify_fail("你正忙著。\n");
    if (me->is_fighting()) return notify_fail("戰鬥中無法吞食鬼魂。\n");
    if (!arg || !objectp(victim = present(arg, environment(me)))
    ||  !victim->is_character() || victim == me || !victim->visible(me))
        return notify_fail("你要吞食誰？\n");
    if (victim->query("life_form") != "ghost") return notify_fail("你只能吞食鬼魂。\n");
    if (wizardp(victim)) return notify_fail("你無法吞食巫師。\n");
    if (environment(me)->query("no_fight")) return notify_fail("這裡不能吞食鬼魂。\n");

    serial = time() + random(100000);
    me->set_temp("yaksa_devour", ([ "serial": serial, "total": 0,
        "ghost_gin": victim->query_stat("gin") ]));
    message_vision(HIR "$N張開血盆大口，一把抓住$n，開始吞食$n的魂魄！\n" NOR, me, victim);
    tell_object(victim, HIR "你被夜叉抓住，完全無法抵抗！\n" NOR);
    devour_tick(me, victim, serial);
    return 1;
}

int help(object me) {
    write(@HELP
指令格式：devour <鬼魂>

夜叉吞食鬼魂（鬼魂 NPC 或死去玩家的鬼魂）。鬼魂完全無法抵抗，每 tick 吞一口，
每口吞食量 = 膽識 x 機敏 + random(精)，從鬼魂的精扣除，扣到 0 即吞完。
吞食期間無法行動；戰鬥、離開房間或鬼魂消失時中斷。

- 吞鬼魂 NPC：鬼魂被吃掉，吞多少補多少精、神（目前值與受損的最大值）。
- 吞玩家鬼魂：對方魂飛魄散，保留帳號與上線時數，須重新創造角色。
  若鬼魂的精比自己精、氣的最大值中較高者還低，永久增加精氣神最大值：
  精 1+對方精/40、氣 1+random(對方精/40)、神 1+random(對方精/80)。
  吞夜叉族的鬼魂時，對方的精以兩倍計算。前 10 次必定大幅增加，之後大幅
  增加的機率為 10/(10+random(吞食次數))，否則只增加精 1~2、氣 0~1。
HELP);
    return 1;
}
