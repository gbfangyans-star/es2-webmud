/* CUSTOM WEAPON CONDITION: 百鬒寒鳩劍之毒 (hundred_poison)
 *
 * 3 tick 發作一次，共 3 次。每次：gin 目前值 -7、實格 -3、kee 目前值 -10、實格 -5、sen 目前值 -2、實格 -1。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你感到萬毒啐骨, 五臟六腑血氣翻騰！"; }
int burst_ticks() { return 3; }
int burst_count() { return 3; }
mixed *burst_damage()
{
    // ({ 屬性, 實格扣, 目前值扣 })
    return ({
        ({ "gin", 3, 7 }),
        ({ "kee", 5, 10 }),
        ({ "sen", 1, 2 }),
    });
}
