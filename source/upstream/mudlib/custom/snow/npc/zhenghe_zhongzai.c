/* CUSTOM SNOW ROCK-PAPER-SCISSORS EASTER EGG
 * WebMUD extension. Not part of taedlar/es2_mudlib canonical content.
 */
#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

private string display_name()
{
    return HIY "正禾老變態" NOR HIC "［中仔］" NOR;
}

void create()
{
    set_name(display_name(),
        ({ "zhenghe", "zhongzai", "中仔", "正禾老變態" }));
    set("title", HIY "正禾老變態" NOR);
    set("nickname", HIC "［中仔］" NOR);
    set_race("human");
    set_level(1);
    set("age", 46);
    set("long",
        "他蹲在七彩石旁，右手一下握拳、一下攤掌，似乎逮到誰都想猜上幾拳。\n");
    setup();
}

void init()
{
    add_action("do_rps", "猜拳");
    add_action("do_rps", "rps");
}

private int hand_value(string hand)
{
    if (hand == "剪刀" || hand == "scissors") return 0;
    if (hand == "石頭" || hand == "rock") return 1;
    if (hand == "布" || hand == "paper") return 2;
    return -1;
}

private string hand_name(int hand)
{
    switch(hand) {
    case 0: return "剪刀";
    case 1: return "石頭";
    default: return "布";
    }
}

private void reward_coin(object me)
{
    object money;

    money = new("/obj/money/coin");
    if (!money) return;
    money->set_amount(50);
    if (!money->move(me))
        money->move(environment(me));
}

private void pinch_penalty(object me)
{
    int gin_loss, kee_loss, sen_loss;

    gin_loss = me->query_stat("gin") / 10;
    kee_loss = me->query_stat("kee") / 10;
    sen_loss = me->query_stat("sen") / 10;

    if (gin_loss > 0) me->consume_stat("gin", gin_loss, this_object());
    if (kee_loss > 0) me->consume_stat("kee", kee_loss, this_object());
    if (sen_loss > 0) me->consume_stat("sen", sen_loss, this_object());
}

int do_rps(string arg)
{
    object me;
    int mine, his, result;

    me = this_player();
    mine = hand_value(arg);

    if (mine < 0)
        return notify_fail("猜拳請輸入：猜拳 剪刀、猜拳 石頭、或猜拳 布。\n");

    his = random(3);

    tell_object(me,
        display_name() + "喊道：「剪刀、石頭、布！」\n\n"
        "你出了：" + HIW + hand_name(mine) + NOR + "\n"
        "中仔出了：" + HIW + hand_name(his) + NOR + "\n\n");

    result = (mine - his + 3) % 3;

    if (result == 1) {
        tell_object(me,
            HIG "你贏了！" NOR "\n\n"
            + display_name() + "不情不願地掏出五十文錢。\n"
            "「嘖！拿去啦，再來啊！」\n\n"
            + HIY "你獲得了 50 文錢。" NOR "\n");
        reward_coin(me);
        return 1;
    }

    if (result == 2) {
        tell_object(me,
            HIR "你輸了！" NOR "\n\n"
            + display_name() + "突然怪笑一聲，伸手往你胸口狠狠捏了一把！\n"
            "你渾身一震，只覺得精氣神都被捏散了幾分。\n\n"
            + HIR "你的精、氣、神各減少 10%。" NOR "\n");
        pinch_penalty(me);
        return 1;
    }

    tell_object(me,
        HIW "平手！" NOR "\n\n"
        + display_name() + "瞪了你一眼：「再來！」\n"
        "本局沒有任何獎勵或懲罰。\n");
    return 1;
}
