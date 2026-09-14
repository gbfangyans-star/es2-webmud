#include <ansi.h>
inherit SKILL;

mapping *actions = ({
(["action":"$N踏前一步，手中$w順勢揚起，使出三門刀法「開門見山」，刀鋒由上而下直取$n中門，勁風隨刀勢壓落，逼向$n的$l。","attack":6,"force":1,"defense":4,"damage_type":"割傷"]),
(["action":"$N身形微側，手中$w貼著腰際迴旋，使出三門刀法「迴門藏鋒」，原本收斂的刀光忽從側面翻出，沿一道弧線疾削$n的$l。","attack":8,"force":0,"defense":6,"damage_type":"割傷"]),
(["action":"$N看準$n招勢將盡，腳下一錯，使出三門刀法「側門截勢」，手中$w斜斜挑起，旋即順著來勢橫斬，封住退路直逼$n的$l。","attack":7,"force":2,"defense":5,"damage_type":"割傷"]),
(["action":"$N猛然沉肩進身，使出三門刀法「中門破陣」，手中$w沒有半分花巧，迎著$n正面疾斬而去，刀勢越走越沉，直取$n的$l。","attack":10,"force":3,"defense":2,"damage_type":"割傷"]),
(["action":"$N刀勢看似已老，身形忽然向後一撤，使出三門刀法「反門回刃」，手腕翻轉間$w逆勢捲回，寒光貼身掠過再疾削$n的$l。","attack":5,"force":2,"defense":8,"damage_type":"割傷"]),
(["action":"$N腳踏三方，手中$w忽左忽右，使出三門刀法「三門齊開」，刀光接連從中門、側門與反門襲來，三股刀勢匯成寒芒斬向$n的$l。","attack":9,"force":4,"defense":4,"damage_type":"割傷"]),
});
private void create(){ seteuid(getuid()); DAEMON_D->register_skill_daemon("sanmeendo"); setup(); }
int valid_enable(string usage){ return usage=="blade"; }
void attack_using(object me, object opponent, object weapon){ if(opponent) COMBAT_D->fight(me,opponent,"sanmeendo",actions[random(sizeof(actions))],weapon); }
