# v3.20.59 技能 learned 公式落地

依使用者回傳 R 表與後續確認：
- D = clamp(對手人物等級 - 玩家人物等級, 2, 10)
- 所有除法整數截斷。
- dodge/parry/tiger-steps：成功防禦後才計算 learned。
- unarmed / blade / twohanded blade / secondhand blade / tiger-blade / sanmeendo：成功造成傷害後計算 learned。
- force：每個瘋虎功 exercise tick 依 random(CON) + random(CPS) * floor(INT/7)。
- tiger-force：成功命中時依 (random(INT)+1)*floor(INT/7)+random(CPS)。
- 共用 learned 門檻：1-60=100, 61-90=125, 91-120=150, 121-160=175, 161-180=200, 181-200=250，門檻=Lv^2*基數。
- tiger-force 專用門檻：20-100=100, 101-140=150, 141-180=200, 181-200=250。
- tiger-force Lv100 STR+1/COR+1；Lv140 COR+2；141-160 每級 gin+3/kee+4；161+ 每級 gin+1/kee+1。
- 使用 improve_skill_exact 避免舊核心額外套用人物等級 random 倍率。
