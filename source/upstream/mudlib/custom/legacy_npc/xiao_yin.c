// /custom/legacy_npc/xiao_yin.c — 舊站 NPC：蕭尹（Xiao yin）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：漕幫；房間：房間內。
尚未製作的裝備（先空著）：纏布刀(Wrapped blade)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("蕭尹", ({ "xiao yin", "xiao", "yin" }));
    set("title", "漕幫總舵主");
    set_race("human");
    set_class("fighter");
    set_level(45);
    set("gender", "male");
    set("age", 65);
    set("long",
        "一個和藹可親的老年人，半白的髮絲睿智的面容，看來是個飽經風霜的人物，但\n"
        "看其精壯的身軀及微透紅光的臉龐，就可知道他一定是個武學根基深厚的高手，\n"
        "穿著長袍的他看來一派溫文，但接觸到他如鷹的眼神，不由得令你對他多了幾分\n"
        "敬畏，眼前這位長者，正是掌握了天朝水路交通的水路第一大幫漕幫傳說中的總\n"
        "舵主蕭尹。蕭尹與哭笑門門主劉乙忘玄為莫逆之交，相傳年輕時雙雄一見如故，\n"
        "於青邪山上暢談抱負及武學相談甚歡，蕭尹創漕幫之初劉乙忘玄相助甚多，而哭\n"
        "笑門在武林中的許多仇家莫名暴斃，據說也與漕幫脫不了關係，兩人之間或明或\n"
        "暗的存在著一種互利的合作關係。\n");
    set_power("A");
    setup();
}
