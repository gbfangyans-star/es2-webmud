/*---
description: 茅山道法【奇門術】（mao-shan mysticism）。幻霧觀法術，enable 在法術（magic）上，以 conjure 施展。
             memory 記憶、recall 翔空、collect 集靈、slave 通靈、devour 噬魂。
             記憶、集靈耗神 5；其他不耗神，但要消耗一張少陰符。
             設計見 docs/martial_arts/幻霧觀_茅山奇術與奇門術.md。
---*/
#include <ansi.h>

inherit SKILL;

#define SCROLL  "/custom/item/scroll/yin"
#define FACTION "taoist.huanwu"

string type() { return "magic"; }
int valid_enable(string usage) { return usage == "magic"; }

/* 受陰魂控制的 NPC（所有施法者共用一份名單），由 guard_puppets() 每 2 秒帶動一次。 */
static object *puppets = ({});

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("mao-shan mysticism");
    setup();
}

/* 學習條件：幻霧觀弟子、茅山奇術 100 級。 */
int valid_learn(object me)
{
    if( me->query("custom_faction") != FACTION )
        return notify_fail("你不是幻霧觀弟子﹐無緣參習奇門術。\n");
    if( me->query_skill("taoism of darkness", 1) < 100 )
        return notify_fail("你的茅山奇術尚未大成﹐參不透奇門術的玄機。\n");
    return 1;
}

/* 練成 20 級。 */
int query_entry_level() { return 20; }

void skill_completed(object me, string skill)
{
    tell_object(me, HIK "你將奇門遁法的口訣默誦再三﹐隱隱覺得天地間的陰氣都在指尖流轉。\n" NOR);
}

// ------------------------------------------------------------------
// 法術資料（使用者定案，2026-10-24）
// ------------------------------------------------------------------

/* 法術：可用等級、耗神、要不要少陰符、停頓、層級（算點數用）、名稱。 */
mapping SPELLS = ([
    "memory":  ({  0, 5, 0, 1, 1, "記憶之術" }),
    "recall":  ({  0, 0, 1, 2, 2, "翔空之術" }),
    "collect": ({  0, 5, 0, 1, 1, "集靈之術" }),
    "slave":   ({ 30, 0, 1, 2, 3, "通靈之術" }),
    "devour":  ({ 60, 0, 1, 1, 3, "噬魂之術" }),
]);

/* 施法點數（照茅山法術）：
 * 基本法術：((random(靈性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1)
 * 奇門術：((random(悟性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1) */
void magic_gain(object me, int tier)
{
    int spi, intel;

    if( !userp(me) ) return;
    spi = me->query_attr("spi");
    intel = me->query_attr("int");
    if( spi < 1 ) spi = 1;
    if( intel < 1 ) intel = 1;
    me->improve_skill_exact("magic",
        ((random(spi) + 1) * (random(spi) + 1) + random(spi)) * (random(tier) + 1));
    me->improve_skill_exact("mao-shan mysticism",
        ((random(intel) + 1) * (random(spi) + 1) + random(spi)) * (random(tier) + 1));
}

object find_scroll(object me)
{
    foreach(object ob in all_inventory(me))
        if( base_name(ob) == SCROLL ) return ob;
    return 0;
}

// ------------------------------------------------------------------
// 顯示：敘述灰色、法術名稱青色；排版照天師咒術
// （起手一行、空行、效果、空行、結果）。
// ------------------------------------------------------------------

void say_line(object me, object target, string msg)
{
    message_vision(HIK + msg + NOR "\n", me, target, 1);
}

void blank(object me)
{
    message_vision("\n", me, 0, 1);
}

void start_line(object me, object target, string spell)
{
    say_line(me, target, "$N手捏法訣﹐口中念念有詞﹐開始施展「" NOR CYN + SPELLS[spell][5]
        + NOR HIK "」 ....");
    blank(me);
}

// ------------------------------------------------------------------
// 記憶之術、翔空之術
// ------------------------------------------------------------------

int do_memory(object me)
{
    object env = environment(me);

    if( clonep(env) )
        return notify_fail("此地方位變幻不定﹐記不下來。\n");
    me->set("mysticism/memory", base_name(env));
    start_line(me, 0, "memory");
    say_line(me, 0, "$N屈指在地上畫了一道符紋﹐那符紋閃了一閃便隱入土中。");
    blank(me);
    tell_object(me, HIK "你將此地的方位牢牢記在心裡。\n" NOR);
    return 1;
}

object recall_room(object me)
{
    string file;
    object room;

    if( !stringp(file = me->query("mysticism/memory")) ) return 0;
    if( catch(room = load_object(file)) ) return 0;
    return room;
}

int check_recall(object me)
{
    object room;

    if( !me->query("mysticism/memory") )
        return notify_fail("你心中沒有記下任何地方﹐不知該往何處去。\n");
    // 自己在打，或有人正在打自己，都算交手中。
    if( me->is_fighting()
    ||  sizeof(filter(all_inventory(environment(me)), (: living($1) && $1->is_fighting($(me)) :))) )
        return notify_fail("你正與人交手﹐靜不下心來駕馭陰風。\n");
    if( !(room = recall_room(me)) )
        return notify_fail("你記下的那處地方已經無從尋覓了。\n");
    if( room == environment(me) )
        return notify_fail("你此刻就在記下的地方。\n");
    if( room->query("no_magic") )
        return notify_fail("那處地方佈有禁制﹐陰風飛不進去。\n");
    return 1;
}

int do_recall(object me)
{
    object room = recall_room(me);

    start_line(me, 0, "recall");
    say_line(me, 0, "$N將少陰符往頭頂一拋﹐身子隨著一陣陰風拔地而起﹐轉眼不見了。");
    blank(me);
    if( !me->move(room) ) {
        tell_object(me, HIK "陰風打了個旋又將你放了下來﹐終究沒能飛走。\n" NOR);
        return 0;
    }
    message("vision", HIK "一陣陰風捲過﹐" + me->name() + "的身影從風中落了下來。\n" NOR,
        environment(me), ({ me }));
    tell_object(me, HIK "陰風散去﹐你已落在記下的地方。\n" NOR);
    return 1;
}

// ------------------------------------------------------------------
// 集靈之術：分解一具 NPC 屍體得一個陰魂；陰魂數不超過靈性（含裝備）。
// ------------------------------------------------------------------

object find_corpse(object me, object target)
{
    if( objectp(target) ) return target;
    foreach(object ob in all_inventory(environment(me)))
        if( ob->is_corpse() ) return ob;
    return 0;
}

int check_collect(object me, object corpse)
{
    if( !objectp(corpse) || !corpse->is_corpse() || environment(corpse) != environment(me) )
        return notify_fail("這不是屍體﹐收不出陰魂來。\n");
    if( corpse->query("player_corpse") )
        return notify_fail("這人的魂魄早已離體﹐收不出陰魂來。\n");
    if( me->query("mysticism/ghosts") >= me->query_attr("spi") )
        return notify_fail("你袖中陰魂已多﹐再收只怕鎮壓不住。\n");
    return 1;
}

int do_collect(object me, object corpse)
{
    start_line(me, corpse, "collect");
    say_line(me, corpse, "$N蹲在$n旁邊低誦咒文﹐屍身漸漸化作一縷黑煙﹐被$N收入袖中。");
    blank(me);
    foreach(object ob in all_inventory(corpse))
        ob->move(environment(me));
    destruct(corpse);
    me->add("mysticism/ghosts", 1);
    tell_object(me, HIK "你袖中如今鎮著" + chinese_number(me->query("mysticism/ghosts"))
        + "縷陰魂。\n" NOR);
    return 1;
}

// ------------------------------------------------------------------
// 通靈之術：陰魂附上 NPC 的身體，讓它保護施法者。
// 成功：random(奇門術 ÷ 3) > 對方等級；失敗只停頓，少陰符照用、陰魂不扣。
// 最多控制 奇門術 ÷ 40 + 1 個（最多 6 個）；至死方休，施法者離開遊戲就散去。
// ------------------------------------------------------------------

object puppet_master(object ob)
{
    object master;

    if( !objectp(ob) ) return 0;
    master = ob->query_temp("mysticism/master");
    return objectp(master) ? master : 0;
}

object *query_puppets(object me)
{
    puppets = filter(puppets, (: objectp($1) :));
    return filter(puppets, (: puppet_master($1) == $(me) :));
}

int max_puppets(object me)
{
    int n = me->query_skill("mao-shan mysticism", 1) / 40 + 1;
    return n > 6 ? 6 : n;
}

int check_slave(object me, object target)
{
    if( !objectp(target) || target == me || !living(target)
    ||  environment(target) != environment(me) )
        return notify_fail("這裡沒有可施法的對象。\n");
    if( userp(target) || target->query_race() == "beast" )
        return notify_fail("對方魂魄自主﹐陰魂附不上去。\n");
    if( target->query("training_dummy") )
        return notify_fail("這木頭疙瘩沒有魂魄可供陰魂棲身。\n");
    // 商人、師父、別人召喚出來的東西不能控制。
    if( function_exists("deliver_merchandise", target)
    ||  function_exists("accept_apprentice", target)
    ||  target->query("maoshan_owner") )
        return notify_fail("對方身上似有護持﹐陰魂附不上去。\n");
    if( puppet_master(target) == me )
        return notify_fail(target->name() + "早已受你的陰魂驅使。\n");
    if( puppet_master(target) )
        return notify_fail(target->name() + "身上已附著別人的陰魂﹐奪不過來。\n");
    if( me->query("mysticism/ghosts") < 1 )
        return notify_fail("你袖中沒有可以驅使的陰魂。\n");
    if( sizeof(query_puppets(me)) >= max_puppets(me) )
        return notify_fail("你的心神已經驅使不了更多的陰魂了。\n");
    return 1;
}

void release_puppet(object ob)
{
    if( !objectp(ob) ) return;
    ob->delete_temp("mysticism/master");
    ob->set_leader(ob->query_temp("mysticism/old_leader"));
    ob->delete_temp("mysticism/old_leader");
    if( environment(ob) )
        message_vision(HIK "$N身子一顫﹐一縷黑氣自頭頂飄散﹐眼神漸漸恢復了清明。\n" NOR, ob);
}

/* 每 2 秒：施法者不在了就散去；跟不上施法者就追過去；施法者在打誰就一起撲上去。 */
void guard_puppets()
{
    object master;

    puppets = filter(puppets, (: objectp($1) :));
    foreach(object ob in puppets) {
        if( !objectp(ob) ) continue;
        master = puppet_master(ob);
        if( !master ) {
            release_puppet(ob);
            puppets -= ({ ob });
            continue;
        }
        if( !living(ob) || !environment(master) ) continue;
        // 不對施法者與同一位施法者的其他傀儡出手。
        foreach(object other in ({ master }) + query_puppets(master)) {
            if( other == ob ) continue;
            if( ob->is_fighting(other) ) ob->remove_killer(other);
            if( other->is_fighting(ob) ) other->remove_killer(ob);
        }
        if( environment(master) != environment(ob) ) {
            if( ob->move(environment(master)) )
                message_vision(HIK "$N腳步僵直地跟了上來﹐默默站到$n身後。\n" NOR, ob, master);
            continue;
        }
        foreach(object enemy in master->query_enemy()) {
            if( !objectp(enemy) || enemy == ob || environment(enemy) != environment(ob) ) continue;
            if( puppet_master(enemy) == master ) continue;
            if( !ob->is_fighting(enemy) ) {
                ob->kill_ob(enemy);
                enemy->kill_ob(ob);
            }
        }
    }
    remove_call_out("guard_puppets");
    if( sizeof(puppets) ) call_out("guard_puppets", 2);
}

int do_slave(object me, object target)
{
    int sk = me->query_skill("mao-shan mysticism", 1);

    start_line(me, target, "slave");
    say_line(me, target, "$N咬破指尖在少陰符上一點﹐將符紙往$n額頭一拍﹐一縷黑氣順勢鑽了進去。");
    blank(me);
    if( random(sk / 3 + 1) <= target->query_level() ) {
        say_line(me, target, "$n猛地甩了甩頭﹐將那縷黑氣逼了出來。");
        return 0;
    }

    me->add("mysticism/ghosts", -1);
    target->remove_all_killer();
    me->remove_killer(target);
    target->set_temp("mysticism/master", me);
    target->set_temp("mysticism/old_leader", target->query_leader());
    target->set_leader(me);
    puppets = filter(puppets, (: objectp($1) :)) + ({ target });
    say_line(me, target, "$n渾身一震﹐眼神變得空洞呆滯﹐默默走到$N身後站定。");
    remove_call_out("guard_puppets");
    call_out("guard_puppets", 2);
    return 1;
}

// ------------------------------------------------------------------
// 噬魂之術：犧牲一個傀儡，氣、神各回復 傀儡目前的氣 × 奇門術 ÷ 200；
// 傀儡化成飛灰，不留屍體、不給經驗，身上的東西掉在地上。
// ------------------------------------------------------------------

object find_puppet(object me, object target)
{
    if( objectp(target) ) return puppet_master(target) == me ? target : 0;
    foreach(object ob in query_puppets(me))
        if( environment(ob) == environment(me) ) return ob;
    return 0;
}

int do_devour(object me, object target)
{
    int n;

    n = target->query_stat("kee") * me->query_skill("mao-shan mysticism", 1) / 200;
    start_line(me, target, "devour");
    say_line(me, target, "$N朝$n一招手﹐$n的魂魄連同陰魂一起被抽了出來﹐吸入$N口中。");
    blank(me);
    say_line(me, target, "$n的軀殼頹然倒地﹐化成一堆飛灰。$N臉上泛起一陣青氣﹐精神為之一振。");
    if( n > 0 ) {
        me->supplement_stat("kee", n);
        me->supplement_stat("sen", n);
    }
    puppets -= ({ target });
    target->remove_all_killer();
    foreach(object ob in all_inventory(target)) {
        if( ob->query("equipped") ) ob->unequip();
        ob->move(environment(me));
    }
    destruct(target);
    return 1;
}

// ------------------------------------------------------------------
// 施法
// ------------------------------------------------------------------

int conjure_magic(object me, string spell, object target)
{
    object scroll;
    int sk, ok;

    if( !me->query_skill("mao-shan mysticism", 1) && !me->query_learn("mao-shan mysticism") )
        return notify_fail("你還沒學會奇門術。\n");
    if( !stringp(spell) || undefinedp(SPELLS[spell]) )
        return notify_fail("指令格式﹕conjure <法術名稱> [on <對象>]\n");
    sk = me->query_skill("mao-shan mysticism", 1);
    if( sk < SPELLS[spell][0] )
        return notify_fail("你的奇門術火候未到﹐還施展不了這道法術。\n");

    switch( spell ) {
    case "recall":
        if( !check_recall(me) ) return 0;
        break;
    case "collect":
        target = find_corpse(me, target);
        if( !check_collect(me, target) ) return 0;
        break;
    case "slave":
        if( !check_slave(me, target) ) return 0;
        break;
    case "devour":
        if( !(target = find_puppet(me, target)) )
            return notify_fail("你身邊沒有受陰魂驅使的軀殼。\n");
        break;
    }

    if( SPELLS[spell][2] && !(scroll = find_scroll(me)) )
        return notify_fail("你身上沒有少陰符﹐無從施展奇門術。\n");
    if( me->query_stat("sen") < SPELLS[spell][1] )
        return notify_fail("你心神渙散﹐無法施展奇門術。\n");

    if( spell == "memory" && !do_memory(me) ) return 0;
    if( SPELLS[spell][1] ) me->consume_stat("sen", SPELLS[spell][1]);
    if( scroll ) scroll->add_amount(-1);

    switch( spell ) {
    case "memory":  ok = 1; break;
    case "recall":  ok = do_recall(me); break;
    case "collect": ok = do_collect(me, target); break;
    case "slave":   ok = do_slave(me, target); break;
    case "devour":  ok = do_devour(me, target); break;
    }

    me->start_busy(SPELLS[spell][3]);
    if( ok ) magic_gain(me, SPELLS[spell][4]);
    else me->set_temp("conjure/failed", 1);
    return 1;
}
