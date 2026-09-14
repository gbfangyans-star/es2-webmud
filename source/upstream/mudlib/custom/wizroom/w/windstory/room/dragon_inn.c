#include <room.h>

#define TARGET_CLASS "fighter"

inherit INN;

void create()
{
    set("short", "龍門客棧");
    set("long", @LONG
推開厚重木門, 迎面便是燈火溫暖的大堂。幾張方桌沿著牆邊整齊排開, 
桌面留著淡淡酒香, 樑上懸掛的紅燈籠隨風輕晃。櫃臺後方陳列著一排
酒罈, 爐火與飯菜香氣從簾後緩緩飄來。往來旅客在此歇腳談天, 店小
二穿梭桌間招呼客人, 門外偶爾傳來馬蹄與風沙聲。
LONG
    );

    set("valid_startroom", 1);
    set("no_fight", 1);

    set("exits", ([
        "west" : __DIR__"inn_w",
    ]));

    create_door("west", "客棧大門", "east", DOOR_CLOSED);

    set("objects", ([
        "/d/snow/npc/waiter" : 1,
    ]));

    setup();
}

private string sign_rank(object player)
{
    string value;

    value = player->rank(0, 1);

    if (!stringp(value) || value == "")
        value = player->query_class();

    return value;
}

private void show_current_class(object player)
{
    tell_object(
        player,
        gender_self(player) + "已經是位"
        + sign_rank(player) + "了。\n"
    );
}

private void confirm_sign(string answer, object player)
{
    if (!objectp(player) || !userp(player))
        return;

    if (environment(player) != this_object())
        return;

    if (player->query_class() != "commoner") {
        show_current_class(player);
        return;
    }

    if (!stringp(answer))
        return;

    answer = lower_case(answer);

    if (answer != "y" && answer != "yes")
        return;

    player->set_class(TARGET_CLASS);
    player->save();

    tell_object(
        player,
        gender_self(player) + "現在是位"
        + sign_rank(player) + "了。\n"
    );
}

int do_sign(string arg)
{
    object player;

    player = this_player();

    if (!objectp(player) || !userp(player))
        return 0;

    if (player->query_class() != "commoner") {
        show_current_class(player);
        return 1;
    }

    tell_object(
        player,
        gender_self(player)
        + "目前是位平民, 是否要變更為武者？"
        + " Yes (Y) or No (N)："
    );

    input_to("confirm_sign", player);
    return 1;
}

void init()
{
    ::init();
    add_action("do_sign", "sign");
}
