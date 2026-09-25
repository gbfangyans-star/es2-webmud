/* CUSTOM A-H RACE CONDITION: headless sorrow/rite dance (repeats each tick) */
#include <ansi.h>
#include <condition.h>
inherit CONDITION;

#define TICK_SECONDS 2
#define DANCE_CMD "/daemon/race/headless/dance"

private void create() {
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("headless_ritual");
}

// One effect per tick (one 2-second heartbeat), driven by a call_out chain
// tied to the data's serial. Keep this daemon loaded while chains may be
// pending.
int clean_up() { return 1; }

private string *sorrow_msg = ({
    HIB "$N踏著沉緩的步伐，手中斧頭低低揮舞，彷彿在悼念逝去的戰友。\n" NOR,
    HIB "$N仰身長嘆，斧頭隨著哀傷的舞步緩緩劃過身前。\n" NOR,
    HIB "$N的舞步時而踉蹌、時而沉重，悲愴之意溢於言表。\n" NOR,
});

private string *rite_msg = ({
    HIG "$N繞著圈子揮舞斧頭，口中念念有詞，彷彿在向遠古的神靈祈求。\n" NOR,
    HIG "$N將斧頭高舉過頂，踏著祭舞的節拍重重頓足。\n" NOR,
    HIG "$N的祭舞越跳越快，斧光在身周化成一圈淡淡的光暈。\n" NOR,
});

private void lower(object me, string stat, int amount) {
    int cur = me->query_stat(stat);
    // 少量減少，但不會因此把目前值扣到 0 以下而昏倒。
    if (amount > cur - 1) amount = cur - 1;
    if (amount > 0) me->consume_stat(stat, amount, me);
}

// One application of the dance's effect.
void ritual_effect(object me, string mode) {
    string *stats = ({ "gin", "kee", "sen" });
    string pick, s;

    pick = stats[random(3)];
    if (mode == "sorrow") {
        me->supplement_stat(pick, 3 + random(3));
        foreach (s in stats) if (s != pick) lower(me, s, 1 + random(2));
        lower(me, "food", 1);
        lower(me, "water", 1);
    } else {
        switch (pick) {
        case "gin": me->supplement_stat("gin", 2 + random(2)); break;
        case "kee": me->supplement_stat("kee", 3 + random(3)); break;
        default:    me->supplement_stat("sen", 1 + random(2)); break;
        }
    }
}

void ritual_tick(object me, int serial) {
    mapping data;
    if (!objectp(me)) return;
    data = me->query_condition("headless_ritual");
    if (!mapp(data) || data["serial"] != serial) return;

    if (!living(me) || me->is_fighting() || environment(me) != data["room"]
    ||  !DANCE_CMD->wielding_axe(me)) {
        me->delete_condition("headless_ritual");
        message_vision("$N停下了舞步。\n", me);
        return;
    }

    message_vision((data["mode"] == "sorrow" ? sorrow_msg : rite_msg)[random(3)], me);
    ritual_effect(me, data["mode"]);

    // Mutate in place: set_condition() would unapply/apply and start a
    // second chain.
    data["duration"] -= 1;
    if (data["duration"] < 1) {
        me->delete_condition("headless_ritual");
        message_vision("$N收斧而立，結束了這一段舞蹈。\n", me);
        return;
    }
    call_out("ritual_tick", TICK_SECONDS, me, serial);
}

void condition_apply(object me, string cnd, mixed data) {
    if (!mapp(data)) return;
    // After a relogin the dancer is no longer where the dance started, so a
    // restored ritual simply ends on its first tick.
    call_out("ritual_tick", TICK_SECONDS, me, data["serial"]);
}

void condition_unapply(object me, string cnd, mixed data) { }

void condition_update(object me, string cnd, mixed data) {
    if (!living(me) || !mapp(data) || data["duration"] < 1) me->delete_condition(cnd);
}
