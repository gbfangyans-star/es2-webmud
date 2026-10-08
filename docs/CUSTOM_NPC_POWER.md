# NPC 強度設計（NPC Power Tiers）

> This is a WebMUD custom extension (NEW) and is **not** canonical `taedlar/es2_mudlib` content.
> 設計規則由使用者提供：各職業重要屬性排序、強度 C/B/A/S 與倍率、屬性上限 45。

## 用法

在 NPC 的 `create()` 裡，`setup()` 之前加一行 `set_power()`：

```c
set_race("blackteeth");
set_class("fighter");
set_level(10);
set_power("C");     // C 雜兵 / B 一般 / A 菁英 / S 頭目（也可寫中文）
setup();
```

沒有寫 `set_power()` 的 NPC 維持舊行為，完全不受影響。

現有 86 個 NPC 已依使用者確認的表格套用，清單見 `NPC_POWER_LIST.md`。

## 規則

| 強度 | 名稱 | 倍率 |
|---|---|---|
| C | 雜兵 | ×0.7 |
| B | 一般 | ×1.0 |
| A | 菁英 | ×1.2 |
| S | 頭目 | ×1.4 |

倍率只乘在「成長」的部分，不乘種族基礎值。

**屬性** = 種族初始化擲出的基礎值 + (等級−1) × 每級成長 × 倍率，最高 45。

| 職業 | 第 1 重要 | 第 2 重要 | 第 3 重要 |
|---|---|---|---|
| 武者 fighter | con | str | cor |
| 書生 scholar | int | dex | con |
| 軍人 soldier | str | cor | cps |
| 道士 taoist | wis | spi | int |
| 和尚 monk | spi | wis | int |
| 方士 alchemist | int | spi | str |
| 盜賊 thief | cor | dex | cps |
| 平民 commoner | （不偏重） | | |

每級成長：第 1 重要 0.43、第 2 重要 0.36、第 3 重要 0.29、其他屬性 0.10。
B 級的第 1 重要屬性大約在 LV70 時到達 45。

**精氣神上限** = 種族基礎值 + 模擬從 1 級升到目前等級的成長 × 倍率。每級成長
沿用各職業玩家升級公式（精 = 機敏/除數、氣 = 根骨/除數、神 = 靈性/除數），
除數與 `/daemon/class/*.c` 的 `advance_level()` 相同；平民沒有升級公式，用 5/5/5。

**手動指定優先**：`create()` 裡用 `set_attr()` 或 `set_stat_maximum()` 指定的項目
保留不覆蓋，例如想讓某個 NPC 力氣特別大，照樣寫 `set_attr("str", 40);`。

## 實測（Neolith 實際載入）

- 黑齒族武者 LV10 C 級：con 18～19、str 18、cor 17～18、精 ≈ 55、氣 ≈ 76、神 ≈ 10。
- 人類道士 LV70 S 級，手動 str 40、氣 999：wis/spi/int 皆 45（到頂），str 40 與氣 999 保留。

## 檔案

- `source/upstream/mudlib/daemon/misc/npc_power.c` —— 計算規則與數值表（NPC_POWER_D）。
- `source/upstream/mudlib/std/char/npc.c` —— `set_power()`、`query_power()`，`setup()` 時套用。
- `source/upstream/mudlib/include/daemon.h` —— `NPC_POWER_D` 定義。
- `source/upstream/mudlib/adm/etc/preload` —— 開機預先載入 NPC_POWER_D。
