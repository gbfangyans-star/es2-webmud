/* 「穿靈」 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("「穿靈」", ({ "celestial sword", "sword" }));
    set_weight(2600);
    init_damage(1, 15, 40, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "此劍便是傳說中的聖劍「穿靈」。此劍自於蘭淳焉劈開聖木將其取出後﹐因沾\n"
            "染人間邪氣而幻化為參龍『麒麟』﹐妖蛇『鳳凰』﹐朱雀『白虎』和玄武『青\n"
            "龍』四把妖劍散落世間。而今經歷天靈山祭劍臺血刃上古八大魔獸﹐破盡纏繞\n"
            "聖劍四週的八股妖氣﹐聖劍「穿靈」終於重現人世。然而﹐說不清為甚麼你總\n"
            "還覺得聖劍「穿靈」的真正力量還沒有完全展現出來。\n");
        set("apply_weapon/sword", ([
            "wittiness": 10,
        ]));
    }
    setup();
}
