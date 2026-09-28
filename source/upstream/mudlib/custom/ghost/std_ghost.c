/* CUSTOM GHOST NPC BASE: 鬼魂類 NPC（魂魄狀態），以人類為基礎。
 *
 * 只有陰陽眼（apply/vision_of_ghost）看得見；一般攻擊會從身上穿透。
 * 每 10 tick 隨機說一句台詞，每 15 tick 隨機移動一次（1 tick = 一次心跳 2 秒）。
 * 夜叉可以 devour 吞食。
 */
#include <ansi.h>

inherit NPC;

#define CHAT_TICKS  10
#define MOVE_TICKS  15

static int ghost_ticks;

// 子類別在 create() 最後呼叫：設定魂魄狀態與精、神。
void setup_ghost(int gin, int sen)
{
    // 計數器從隨機位置起跳，同時生出的鬼魂才不會同時說話、同時移動。
    ghost_ticks = random(CHAT_TICKS * MOVE_TICKS);

    set_race("human");
    set("life_form", "ghost");
    set("attitude", "peaceful");
    setup();

    set_stat_maximum("gin", gin);
    set_stat_effective("gin", gin);
    set_stat_current("gin", gin);
    set_stat_maximum("sen", sen);
    set_stat_effective("sen", sen);
    set_stat_current("sen", sen);
}

static void heart_beat()
{
    string *msg;

    ::heart_beat();
    if( !this_object() || !living(this_object()) || !environment() ) return;
    if( is_busy() || is_fighting() ) return;

    ghost_ticks++;
    if( ghost_ticks % CHAT_TICKS == 0
    &&  arrayp(msg = query("ghost_chat")) && sizeof(msg) )
        say(CYN + msg[random(sizeof(msg))] + NOR);
    if( ghost_ticks % MOVE_TICKS == 0 )
        random_move();
}

int accept_fight(object who)
{
    return 0;
}
