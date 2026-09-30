/* CUSTOM WEAPON CONDITION: 「雨毒」之毒 (rain_poison)
 *
 * 2 tick 發作一次，共 4 次。每次：gin 目前值 -8、實格 -4、kee 目前值 -8、實格 -4、sen 目前值 -2、實格 -1。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你覺得傷口處一陣麻癢，腦中一陣昏眩，顯然中了劇毒！"; }
int burst_ticks() { return 2; }
int burst_count() { return 4; }
mixed *burst_damage()
{
    // ({ 屬性, 實格扣, 目前值扣 })
    return ({
        ({ "gin", 4, 8 }),
        ({ "kee", 4, 8 }),
        ({ "sen", 1, 2 }),
    });
}
