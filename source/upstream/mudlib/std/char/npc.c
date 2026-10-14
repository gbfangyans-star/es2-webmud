/*
 *  Package: NPC
 *  Summary: Non-player character.
 */

#include <ansi.h>
#include <dbase.h>
#include <localtime.h>
#include <command.h>
#include <skill.h>
#include <type.h>
#include <daemon.h>

inherit CHARACTER;
inherit F_CLEAN_UP;     // Only to clean up master copy of NPCs.

static mixed next_chat;
static int last_scheduled_time_tag = 0;

// NPC 強度（custom: NEW，見 /daemon/misc/npc_power.c）。
static string power_tier;
static int beast_strength;
static mapping manual_attr = ([]), manual_stat = ([]);
static int applying_power = 0;

int chat();

// -----------------------
// NPC 強度
// -----------------------

// set_power() : 設定 NPC 強度等級，"C"(雜兵)、"B"(一般)、"A"(菁英)、"S"(頭目)。
// 要在 setup() 之前呼叫；setup() 時依種族、職業、等級自動算出屬性與精氣神。
void set_power(string tier)
{
    string t;

    if( !(t = NPC_POWER_D->normalize_tier(tier)) )
        error("set_power: unknown power tier " + sprintf("%O", tier) + ".\n");
    power_tier = t;
}

string query_power() { return power_tier; }

// set_beast() : 野獸強度 1～10，數值表見 /daemon/race/beast.c。
// 和 set_power() 一樣在 setup() 之前呼叫，setup() 完成後套用。
void set_beast(int strength)
{
    if( strength < 1 || strength > 10 )
        error("set_beast: strength must be 1 to 10.\n");
    beast_strength = strength;
}

int query_beast() { return beast_strength; }

// create() 裡手動指定的屬性與精氣神上限，強度計算時保留不覆蓋。
int set_attr(string what, int value)
{
    if( !applying_power ) manual_attr[what] = 1;
    return ::set_attr(what, value);
}

int set_stat_maximum(string what, int val)
{
    if( !applying_power ) manual_stat[what] = 1;
    return ::set_stat_maximum(what, val);
}

void setup()
{
    if( power_tier && clonep(this_object()) ) {
        // 與 CHAR_D->setup_char() 相同的預設值，確保種族初始化已經完成。
        if( !query_race() ) set_race("human");
        if( !query_class() ) set_class("commoner");
        if( !query_level() ) set_level(1);

        applying_power = 1;
        NPC_POWER_D->apply_power(this_object(), power_tier, manual_attr, manual_stat);
        applying_power = 0;
    }
    ::setup();
    if( beast_strength ) {
        applying_power = 1;
        RACE_D("beast")->set_strength(this_object(), beast_strength);
        applying_power = 0;
    }
}

static void
heart_beat()
{
    mapping schedule;

    ::heart_beat();

    if( ! this_object() || ! living(this_object()) ) return;

    if( !is_busy() ) chat();

    if( living(this_object())
    &&	clonep(this_object())
    &&	mapp(schedule = query("schedule")) ) {
        mapping gt;
        int time_tag;

        gt = NATURE_D->game_time(1);
        time_tag = gt[LT_HOUR] * 100 + (gt[LT_MIN] / 10) * 10;
        if( time_tag != last_scheduled_time_tag ) {
            evaluate(schedule[time_tag]);
            last_scheduled_time_tag = time_tag;
        }
        if( !this_object() ) return;
    }
}

// 懸賞（bounty）由 CHAR_D->make_corpse() 發給擊殺者；這裡不再重複發放，
// 否則擊殺者會拿到兩倍。
void
die()
{
    ::die();
}

mixed
carry_object(string file)
{
    object ob;

    // Don't let master copy clone equips
    if( !clonep() ) return VOID_OB;

    if( !objectp(ob = new(file)) ) return 0;

    // Support of uniqueness.
    if( ob->violate_unique() ) ob = ob->create_replica();
        if( !ob ) return VOID_OB;

    ob->varify_template(this_object());
    ob->move(this_object());

    return ob;
}

object
carry_money(string type, int amount)
{
    object ob;

    ob = carry_object("/obj/money/" + type);
    if( !ob ) return 0;
    ob->set_amount(amount);
}

int is_chatting() { return functionp(next_chat) != 0; }

int is_npc() { return 1; }

void do_chat(mixed c) { next_chat = c; }

mixed
eval_chat(mixed chat)
{
    mixed ret;

    chat = evaluate(chat);
    switch(typeof(chat))
    {
    case STRING:
        say(CYN + chat + NOR);
        return 0;
    case ARRAY:
        if( !sizeof(chat) ) return 0;
        chat[0] =  eval_chat(chat[0]);
        return chat - ({ 0 });
    case FUNCTION:
        return chat;
    default:
        return 0;
    }
}

int
chat()
{
    string *msg;
    mixed ret;
    int chance, rnd;

    if( !environment() ) return 0;

    // Evaluate programmed chat first.
    if( next_chat ) {
        next_chat = eval_chat(next_chat);
        return 1;
    }

    // Else, do random chat if any.
    if( ! (chance = (int)query(is_fighting()? "chat_chance_combat": "chat_chance")) )
        return 0;

    if( arrayp(msg = query(is_fighting()? "chat_msg_combat": "chat_msg"))
    &&	sizeof(msg) ) {
        if( random(100) > chance ) return 0;
        rnd = random(sizeof(msg));
        if( stringp(msg[rnd]) )
            say(CYN + msg[rnd] + NOR);
        else if( functionp(msg[rnd]) )
            evaluate(msg[rnd]);
        return 1;
    }
}

// -----------------------
// Standard chat functions
// -----------------------

// random_move() : Move NPC randomly to adjacent room

int random_move()
{
    mapping exits;
    string *dirs;

    if( !mapp(exits = environment()->query("exits")) ) return 0;
    dirs = keys(exits);
    GO_CMD->main(this_object(), dirs[random(sizeof(dirs))]);
}

// cast_spell() : Cause the NPC to cast a specific spell

void cast_spell(string spell)
{
    string spell_skill;

    if( stringp(spell_skill = skill_mapped("spells")))
        SKILL_D(spell_skill)->cast_spell(this_object(), spell);
}

// conjure_magic() : Cuase the NPC to conjure a specific magic power

void conjure_magic(string magic)
{
    string magic_skill;

    if( stringp(magic_skill  = skill_mapped("magic")))
        SKILL_D(magic_skill)->conjure_magic(this_object(), magic);
}

void acupuncture_cauterization(string cauterization)
{
    string cauterization_skill;

    if( stringp(cauterization_skill  = skill_mapped("cauterization")))
        SKILL_D(cauterization_skill)->acupuncture_cauterization(this_object(), cauterization);
}

// exert_function() : Cause the NPC to exert a specific martial skill

int exert_function(string func)
{
    string force_skill;

    if( stringp(force_skill = skill_mapped("force")))
        SKILL_D(force_skill)->exert_function(this_object(), func);
}

// perform_action() : Cause the NPC to perform a specific function of a skill

int perform_action(string skill, string action)
{
    if( stringp(skill) && stringp(action) )
        SKILL_D(skill)->perform_action(this_object(),
                action, query_opponent());
}

// This overrides default activate_guard() in F_ATTACK.

void activate_guard(object target)
{
    kill_ob(target);
}

void do_heal()
{
#if 0
    heal_stat("gin", random(150));
    supplement_stat("gin", random(150));
    heal_stat("kee", random(150));
    supplement_stat("kee", random(150));
    heal_stat("sen", random(150));
    supplement_stat("sen", random(150));
    heal_stat("HP", random(20));
    supplement_stat("HP", random(20));
#endif
}

varargs void
improve_skill(string skill, int amount)
{

}

void
gain_score(string term, int amount)
{

}

