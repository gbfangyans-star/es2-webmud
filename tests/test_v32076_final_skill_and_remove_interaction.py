from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
def text(p): return (ROOT/p).read_text(encoding="utf-8")

def test_interaction_panel_and_webhud_action_feed_are_removed():
    html=text("web/index.html")
    app=text("web/app.js")
    css=text("web/styles.css")
    hud=text("source/upstream/mudlib/cmds/usr/webhud.c")
    assert "場景互動" not in html
    assert "interactionBody" not in html and "interactionBody" not in app
    assert "renderInteractions" not in app
    assert "contextState.interactions" not in app
    assert "context-interaction-card" not in css
    assert "@@WEBHUD|ACT" not in hud
    assert "emit_interactions" not in hud

def test_chat_combat_inventory_status_map_remain():
    html=text("web/index.html")
    app=text("web/app.js")
    hud=text("source/upstream/mudlib/cmds/usr/webhud.c")
    assert "contextChatLog" in html
    assert "contextBody" in html
    assert "inventoryPanel" in app
    assert "bindCommandButtons(contextBody)" in app
    assert "@@WEBHUD|INVBEGIN" in hud
    assert "@@WEBHUD|ROOM" in hud
    assert "@@WEBHUD|EXIT" in hud
    assert "emit_side" in hud

def test_final_skill_stack_keeps_old_neolith_compat_and_special_progression():
    skill=text("source/upstream/mudlib/feature/char/skill.c")
    combatd=text("source/upstream/mudlib/adm/daemons/combatd.c")
    tiger=text("source/upstream/mudlib/daemon/skill/tiger-force.c")
    assert "varargs int query_attr(string attr, int raw);" in skill
    assert "varargs void advance_skill(string skill, int amount);" in skill
    assert 'call_other(daemon, \"skill_improved\", this_object(), skill);' in skill
    assert "apply_restored_skill_progression(skill);" in skill
    assert 'if( skill == "tiger-steps" ) return 120;' in skill
    assert 'skill == "tiger-blade" || skill == "sanmeendo"' in skill
    assert 'me->improve_skill_exact("tiger-force", exp);' in combatd
    assert 'me->improve_skill_exact("tiger-blade", exp);' in combatd
    assert 'me->improve_skill_exact("sanmeendo", exp);' in combatd
    assert "void skill_improved(object me, string sk)" in tiger
    assert "void skill_advanced(object me, string sk)" in tiger
    assert "while( level < 200 )" in tiger
