#include <ansi.h>

inherit F_DBASE;

// Player stat setters require the class daemon to have its own effective uid.
static void create() { seteuid(getuid()); }

string query_rank(object ob, string politeness)
{
    if( !politeness ) return "道士";
    switch(politeness) {
    case "self": return "貧道";
    case "respectful": return "道長";
    default: return "道士";
    }
}

// Race 基數 as a percentage (100 = human baseline), read from the race
// daemon's "commoner_score_base"; only scales character level-up thresholds.
private int race_coef(object ob)
{
    int coef;
    coef = RACE_D(ob->query_race())->query("commoner_score_base");
    return coef > 0 ? coef : 100;
}

// cur_lv is the level being left; thresholds target cur_lv + 1.
void set_next_target(object ob, int cur_lv)
{
    int lv, n, coef;

    if( cur_lv < 1 ) cur_lv = 1;
    lv = cur_lv + 1;
    n = lv - 1;
    coef = race_coef(ob);

    ob->set_target_score("survive", n*n*100 * coef / 100);
    ob->set_target_score("magic", n*n*150 * coef / 100);
    ob->set_target_score("spell mastery",
        lv > 10 ? (lv-10)*(lv-10)*100 * coef / 100 : 0);
    ob->set_target_score("combat",
        lv > 11 ? (lv-11)*(lv-11)*100 * coef / 100 : 0);
}

// 計入咒術道行的技能：基本咒術（spells），以及能裝在「咒術」上的門派咒術
// （天師道法四系、茅山咒術等）；之後新增的門派咒術自動納入。
int is_spell_school(string skill)
{
    object d;

    if( !stringp(skill) ) return 0;
    if( skill == "spells" ) return 1;
    d = SKILL_D(skill);
    if( !objectp(d) || !function_exists("valid_enable", d) ) return 0;
    return d->valid_enable("spells") ? 1 : 0;
}

int spell_mastery_score(object ob)
{
    mapping skills;
    string sk;
    int lv, total;

    /* 咒術道行（使用者定案，2026-10-23）：
     * 基本咒術與門派咒術（天師道法四系、茅山咒術）都算，從第 1 級開始，
     * 升到第 sk 級給 sk×30。一項練到 L 級累計 = 15 × L × (L + 1)，各項加總。 */
    if( !mapp(skills = ob->query_skills()) ) return 0;
    foreach(sk, lv in skills) {
        if( lv < 1 || !is_spell_school(sk) ) continue;
        total += 15 * lv * (lv + 1);
    }
    return total;
}

void refresh_spell_mastery(object ob)
{
    int score;

    if( ob->query_class() != "taoist" ) return;
    score = spell_mastery_score(ob);
    if( ob->query_score("spell mastery") == score ) return;
    ob->set("score/spell mastery", score);
    ob->gain_score("spell mastery", 0);
}
void initialize(object ob)
{
    set_next_target(ob, ob->query_level());
    ob->set("score/spell mastery", spell_mastery_score(ob));
}

void advance_level(object ob)
{
    int gin_gain, kee_gain, sen_gain;

    gin_gain = ob->query_attr("dex", 1) / 4 + random(3) - 1;
    kee_gain = ob->query_attr("con", 1) / 4 + random(3) - 1;
    sen_gain = ob->query_attr("spi", 1) / 3 + random(3) - 1;

    ob->set_stat_maximum("gin", ob->query_stat_maximum("gin") + gin_gain);
    ob->set_stat_maximum("kee", ob->query_stat_maximum("kee") + kee_gain);
    ob->set_stat_maximum("sen", ob->query_stat_maximum("sen") + sen_gain);

    tell_object(ob, HIY "你對天地氣機的體悟更深，精氣神隨之增長。\n" NOR);
    // advance_level() 在等級加 1 之前執行，新等級是 query_level() + 1。
    set_next_target(ob, ob->query_level() + 1);
    ob->set("score/spell mastery", spell_mastery_score(ob));
}