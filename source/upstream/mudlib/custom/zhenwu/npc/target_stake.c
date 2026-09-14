#include <npc.h>
#include <ansi.h>
inherit F_VILLAGER;

private string *training_hit_msg = ({
    HIY "你這一擊結結實實落在假人身上，木樁發出沉悶的「砰」聲。\n" NOR,
    HIY "假人被打得微微一震，粗麻與木屑簌簌落下，隨即又穩穩立住。\n" NOR,
    HIY "你的招式正中假人，樁身傳來厚實的撞擊聲，卻沒有絲毫損壞。\n" NOR,
    HIY "拳腳兵刃落在假人身上，只留下一聲低沉悶響，假人依舊紋絲不動。\n" NOR,
    HIY "你準確擊中假人，木樁輕輕晃了一下，像是在默默承受下一輪操練。\n" NOR,
    HIY "這一招毫無偏差地命中假人，校場上響起清楚的木石撞擊聲。\n" NOR
});

void create()
{
    set_name("假人", ({"target stake","stake","假人"}));
    set_race("human");
    set_class("commoner");
    set_level(20);
    set("civilized", 1);
    set("training_dummy", 1);
    set("long", "這是一具軍營內供新兵練武的粗麻木樁，樁身佈滿刀痕與箭孔。它被牢牢固定在地面，不會還手，也不會因操練而損壞，正適合反覆磨練基本招式。\n");
    setup();
}

int accept_fight(object who) { return 1; }

/* Training target never retaliates. */
void fight_ob(object ob) { }
void kill_ob(object ob) { }

/* Training target never dodges or parries. */
int defend(int ability, int strength, object from) { return 0; }
int absorb(int ability, int strength, object from) { return 0; }
int resist_damage(int damage, object from_ob) { return 0; }

/* Return a positive hit so hit-triggered learned EXP is awarded, but do not
 * change kee/HP/effective stats. */
varargs int receive_damage(int damage, object from, object attacker)
{
    if( damage < 1 ) damage = 1;
    if( objectp(environment()) )
        message_vision(training_hit_msg[random(sizeof(training_hit_msg))], this_object());
    return damage;
}

void die() { }
