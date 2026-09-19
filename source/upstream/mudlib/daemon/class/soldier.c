#include <ansi.h>

inherit F_DBASE;

// commoner.c/fighter.c leave this empty since query_rank() is read-only and
// never needs to write back to a player. advance_level() below calls
// ob->set_stat_maximum(), which is a nomask/USER_PROTECT()'d function on the
// player object -- it only accepts callers whose euid matches the player's
// own (or ROOT/DOMAIN/MUDLIB). Without this seteuid(), this daemon's euid
// stays unset ("NONAME"), the protection check fails, an error is thrown,
// and everything after that call in advance_level() -- and in gain_score()
// itself, which is what actually increments the player's level -- silently
// never runs. That was the root cause of "level-up message fires but the
// level never advances."
static void create() { seteuid(getuid()); }

string query_rank(object obj, string politeness)
{
    if (!politeness) return "軍人";

    switch (politeness) {
        case "self":
            return "小的";
        case "respectful":
            return "軍爺";
        case "rude":
        default:
            return "大兵";
    }
}

// Per-race multiplier on the leveling thresholds below, as a percentage
// (100 = human baseline). Races not listed here have not had their
// coefficient designed yet -- add them once they are, they default to
// 100% (human baseline) until then.
private mapping race_level_coef = ([
    "human"      : 100,
    "dingling"   :  95,
    "jiaojao"    :  95,
    "woochan"    : 100,
    "rainner"    : 100,
    "yenhold"    : 115,
    "blackteeth" : 120,
    "yaksa"      : 140,
    "mailk"      : 150,
    "headless"   : 160,
    "ashura"     : 180,
]);

private int race_coef(object ob)
{
    int coef;
    coef = race_level_coef[ob->query_race()];
    return coef ? coef : 100;
}

// Leveling thresholds: 兵刃精熟(weapon mastery) and 實戰經驗(combat) both need
// (LV-1)^2*2*100 accumulated score to REACH level LV; 戰場功勳(military
// service, earned by killing bandit-type NPCs) needs (LV-30)^2*100 once LV
// is past 30, nothing before that. Both are then scaled by the character's
// race coefficient. cur_lv is the character's CURRENT level -- the
// threshold set here is always for cur_lv+1, the level they're working
// toward next.
void set_next_target(object ob, int cur_lv)
{
    int lv, coef;

    if (cur_lv < 1) cur_lv = 1;
    lv = cur_lv + 1;
    coef = race_coef(ob);

    ob->set_target_score("weapon mastery", (lv-1) * (lv-1) * 2 * 100 * coef / 100);
    ob->set_target_score("combat", (lv-1) * (lv-1) * 2 * 100 * coef / 100);
    ob->set_target_score("military service", lv > 30 ? (lv-30) * (lv-30) * 100 * coef / 100 : 0);
}

void initialize(object ob)
{
    set_next_target(ob, ob->query_level());
}

// advance_level() runs *before* gain_score() increments the player's level,
// so query_level() here is still the level the character is leaving --
// set_next_target() turns that into the threshold for the level they're
// about to become.
void advance_level(object ob)
{
    int gin_gain, kee_gain, sen_gain;

    gin_gain = (int)ob->query_attr("dex") / 3 + random(3) - 1;
    kee_gain = (int)ob->query_attr("con") / 3 + random(3) - 1;
    sen_gain = (int)ob->query_attr("spi") / 8 + random(3) - 1;
    if (gin_gain < 0) gin_gain = 0;
    if (kee_gain < 0) kee_gain = 0;
    if (sen_gain < 0) sen_gain = 0;

    ob->set_stat_maximum("gin", (int)ob->query_stat_maximum("gin") + gin_gain);
    ob->set_stat_maximum("kee", (int)ob->query_stat_maximum("kee") + kee_gain);
    ob->set_stat_maximum("sen", (int)ob->query_stat_maximum("sen") + sen_gain);

    tell_object(ob, HIY "常年的軍旅操練讓你的精氣神更加充沛！\n" NOR);

    set_next_target(ob, ob->query_level());
}
