/* CUSTOM WEAPON CONDITION: 萬骨枯心之毒 (skull_heart_poison)
 *
 * 2 tick 發作一次，共 4 次。每次：gin 目前值 -5、實格 -3、kee 目前值 -8、實格 -5、sen 目前值 -2、實格 -1。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你的傷口已經麻木了，沒有任何反應！"; }
int burst_ticks() { return 2; }
int burst_count() { return 4; }
mixed *burst_damage()
{
    // ({ 屬性, 實格扣, 目前值扣 })
    return ({
        ({ "gin", 3, 5 }),
        ({ "kee", 5, 8 }),
        ({ "sen", 1, 2 }),
    });
}
