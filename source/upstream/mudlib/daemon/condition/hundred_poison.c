/* CUSTOM WEAPON CONDITION: 百鬒寒鳩劍之毒 (hundred_poison)
 *
 * 3 tick 發作一次，共 3 次。每次：gin 最大值 -7、目前值 -3、kee 最大值 -10、目前值 -5、sen 最大值 -2、目前值 -1。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你感到萬毒啐骨, 五臟六腑血氣翻騰！"; }
int burst_ticks() { return 3; }
int burst_count() { return 3; }
mixed *burst_damage()
{
    return ({
        ({ "gin", 7, 3 }),
        ({ "kee", 10, 5 }),
        ({ "sen", 2, 1 }),
    });
}
