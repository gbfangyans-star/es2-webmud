# 李家村商品／物件功能清查

## 已由現有 canonical core 直接取得精確功能

### 白切肉 `/obj/food/pork`
- base_value 200
- base_weight 400
- heal_kee 10
- food_stuff 90

### 牛肉包子 `/obj/food/dumpling`
- base_value 10
- base_weight 60
- food_stuff 80

### 饅頭 `/obj/food/manto`
- base_value 10
- base_weight 100
- food_stuff 80

### 月餅 `/obj/food/mooncake`
- base_value 1
- base_weight 300
- food_stuff 140

### 烏心丹 `/obj/medication/black_pill`
實際 `stuff_ob()`：
- 飲水 -30
- 飽食 +5
- `damage_stat("sen", 1)`
- 神目前值 -4
- 精 +15
- 氣 +15
- 消耗 1 粒

### 山豬果 `/obj/medication/boar_berry`
實際 `stuff_ob()`：
- 飽食 +10
- 飲水 -20
- `heal_stat("sen", 15)`
- 神目前值 +10
- 消耗 1 顆

## 已知名稱但原完整功能仍缺
- 松柴：已恢復可攜帶／可堆疊；原煉丹燃料演算未假裝完成。
- 青銅丹鼎：已恢復容器；原配方容量、封印、熱量連動待復原。
- 青銅丹爐：已恢復容器；原 setup/dispose/ignite/heat 待復原。
- 小藥瓶：已恢復液體容器；原特殊用途待復原。
- 天靈清露：已恢復標準飲用；原特殊效果未杜撰。
