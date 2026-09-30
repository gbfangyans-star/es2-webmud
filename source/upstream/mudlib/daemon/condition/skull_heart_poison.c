/* CUSTOM WEAPON CONDITION: 萬骨枯心之毒 (skull_heart_poison)
 *
 * 2 tick 發作一次，共 4 次。每次：gin 最大值 -5、目前值 -3、kee 最大值 -8、目前值 -5、sen 最大值 -2、目前值 -1。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你的傷口已經麻木了，沒有任何反應！"; }
int burst_ticks() { return 2; }
int burst_count() { return 4; }
mixed *burst_damage()
{
    return ({
        ({ "gin", 5, 3 }),
        ({ "kee", 8, 5 }),
        ({ "sen", 2, 1 }),
    });
}
