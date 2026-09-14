def followups(skill, ratio, first_damage, target_alive=True):
    if skill < 90 or ratio <= 70: return 0
    first=1
    if first_damage <= 0 or not target_alive: return first
    return 2

def test_five_virtual_players():
    players=[
      ("虎一",89,100,50,True,0),
      ("虎二",90,70,50,True,0),
      ("虎三",90,71,0,True,1),
      ("虎四",120,100,30,True,2),
      ("虎五",140,100,80,False,1),
    ]
    for _,skill,ratio,dmg,alive,want in players:
        assert followups(skill,ratio,dmg,alive)==want
