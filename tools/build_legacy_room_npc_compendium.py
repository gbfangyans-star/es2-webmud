#!/usr/bin/env python3
"""Organize legacy ES2 reference captures into rooms (by area) and NPC descriptions.

Input: the extracted `es2-reference.rar` (branch `gbfangyans-star-info`), i.e. a
directory containing es2tips/, japentery/, vovo2000-29232/, es2mud/, es2_pal/.

    python3 tools/build_legacy_room_npc_compendium.py <extracted-dir>

Outputs:
    docs/LEGACY_ROOM_NPC_COMPENDIUM.md
    catalog/legacy_room_npc_compendium.json

Areas are not part of in-game room output, so they are inferred (room name,
post title, description text) and every inferred area records its basis.
"""
import glob
import json
import os
import re
import sys
from collections import OrderedDict, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ------------------------------------------------------------------ areas
# Known legacy place names -> canonical area name. Longest match wins.
PLACES = {
    "雪亭鎮": "雪亭鎮", "雪亭": "雪亭鎮", "飲風客棧": "雪亭鎮",
    "李家村": "李家村",
    "五堂鎮": "五堂鎮", "五堂別館": "五堂鎮", "醇雨樓": "五堂鎮", "和豐當鋪": "五堂鎮",
    "鯉君渡": "五堂鎮", "景隆錢莊": "五堂鎮",
    "老松林": "老松林", "迷霧森林": "迷霧森林", "幻霧森林": "幻霧森林",
    "振武軍營": "振武軍營", "振武軍": "振武軍營", "點兵臺": "振武軍營", "校場": "振武軍營",
    "京畿": "京畿", "後海": "京畿", "百里香": "京畿", "小樓客店": "京畿", "京城": "京畿",
    "斐縣": "斐縣", "悅客來客棧": "斐縣", "錢記酒樓": "斐縣", "清風茶行": "斐縣",
    "婁縣": "婁縣", "甘泉茶館": "婁縣",
    "水嵐縣": "水嵐縣", "五陵客棧": "水嵐縣",
    "兆隱縣": "兆隱縣", "兆隱": "兆隱縣", "天仁客棧": "兆隱縣", "老王燒烤": "兆隱縣",
    "文國縣": "文國縣", "天風客棧": "文國縣", "清水鄉": "文國縣",
    "衛國鎮": "衛國鎮",
    "龍安鎮": "龍安鎮", "龍安": "龍安鎮",
    "康平村": "康平村",
    "雪山": "雪山", "雪嶺": "雪山",
    "百花村": "百花村",
    "平陽山": "平陽山", "平陽寨": "平陽山",
    "虎刀門": "虎刀門",
    "風城": "風城", "春風客棧": "風城",
    "天山": "天山",
    "碧幽部落": "碧幽部落", "碧幽亭": "碧幽部落",
    "水月村": "水月村", "福安客棧": "水月村",
    "紫煙鎮": "紫煙鎮", "紫煙小棧": "紫煙鎮",
    "羅城": "羅城",
    "赤魈村": "赤魈村", "赤魈客棧": "赤魈村",
    "羿水小魚村": "羿水小魚村", "小魚村": "羿水小魚村",
    "天寒村": "天寒村", "域水客棧": "天寒村",
    "喬陰縣": "喬陰縣", "喬陰": "喬陰縣",
    "冷梅莊": "冷梅莊", "雪吟莊": "雪吟莊", "漕幫": "漕幫", "黃家鏢局": "黃家鏢局",
    "古劍門": "古劍門", "上清觀": "上清觀", "太乙觀": "太乙觀", "白象寺": "白象寺",
    "寶蓮寺": "寶蓮寺", "青邪宮": "青邪宮", "青邪山": "青邪山", "隱教": "隱教",
    "逆靈宮": "逆靈宮", "八寶樓": "八寶樓", "陷空島": "陷空島", "黑風寨": "黑風寨",
    "武陀灸堂": "武陀灸堂", "哭笑門": "哭笑門", "古墓場": "古墓場", "百藥谷": "百藥谷",
    "檒城": "檒城", "步玄派": "步玄派", "滄盲派": "滄盲派", "茅山": "茅山",
    "白虎堂": "白虎堂", "老劍山": "老劍山", "鬼洞": "鬼洞", "夜神殿": "夜神殿",
    "蟠龍殿": "蟠龍殿", "神域": "神域", "靈雲觀": "靈雲觀", "冷府": "冷府",
    "考選室": "京畿", "天邪國": "天邪國", "野羊山": "野羊山", "季縣": "季縣",
    "桐城": "桐城", "名山書肆": "名山書肆", "儒林書坊": "儒林書坊", "狀元堂": "狀元堂",
    "京畿神社": "京畿", "雪吟山莊": "雪吟莊", "焱硝山": "焱硝山", "黃家鏢": "黃家鏢局",
    "黑風道": "黑風寨", "血絕門": "血絕門", "喬陰縣城": "喬陰縣",
    "巫山": "巫山", "雲棧": "雲棧市集", "天靈山": "天靈山", "擘雲大澤": "擘雲大澤", "羿水": "羿水",
    "黑石山": "黑石山", "三煙谷": "三煙谷", "彤雲寺": "彤雲寺", "鎮天神廟": "鎮天神廟",
    "銅佛寺": "銅佛寺", "尚書府": "尚書府", "吏部尚書": "尚書府", "史部尚書": "尚書府",
    "黃家大院": "黃家鏢局", "臥虎樓": "臥虎樓", "孟家": "孟家祖墳", "水月瀑布": "水月村",
    "平波湖": "平波湖", "武威營": "武威營", "綠林大盜": "綠林大盜總部", "柳家": "柳家",
    "丱天樹": "丱天樹",
}
PLACE_KEYS = sorted(PLACES, key=len, reverse=True)


def find_place(text):
    if not text:
        return None
    best = None
    for k in PLACE_KEYS:
        i = text.find(k)
        if i >= 0 and (best is None or i < best[0]):
            best = (i, k)
    return PLACES[best[1]] if best else None


# ------------------------------------------------------------------ text normalizing

ANSI = re.compile(r"\x1b?\[[0-9;]*m|\x1b\[[0-9;]*[A-Za-z]")


def read_text(path):
    raw = open(path, "rb").read()
    for enc in ("utf-8", "big5hkscs", "cp950"):
        try:
            txt = raw.decode(enc)
            break
        except UnicodeDecodeError:
            continue
    else:
        txt = raw.decode("big5hkscs", errors="replace")
    txt = ANSI.sub("", txt).replace("\r\n", "\n").replace("\r", "\n")
    txt = txt.replace("　", "  ").replace("\xa0", " ")
    return txt


def undouble(lines):
    """Blog captures put a blank line after every line; collapse that."""
    nonblank = [i for i, l in enumerate(lines) if l.strip()]
    if len(nonblank) < 6:
        return lines
    followed = sum(1 for i in nonblank if i + 1 < len(lines) and not lines[i + 1].strip())
    if followed / len(nonblank) < 0.8:
        return lines
    out, i = [], 0
    while i < len(lines):
        if lines[i].strip():
            out.append(lines[i])
            i += 1
            continue
        j = i
        while j < len(lines) and not lines[j].strip():
            j += 1
        if j - i >= 2 or j >= len(lines):
            out.append("")
        i = j
    return out


# ------------------------------------------------------------------ sources

def iter_sources(base):
    def front(txt):
        m = re.match(r"#\s*(.+)\n", txt)
        title = m.group(1).strip() if m else ""
        url = re.search(r"^- URL:\s*(\S+)", txt, re.M)
        body = txt.split("\n---\n", 1)[1] if "\n---\n" in txt[:2000] else txt
        return title, (url.group(1) if url else ""), body

    for p in sorted(glob.glob(os.path.join(base, "es2tips/posts/*/post.txt"))):
        t, u, b = front(read_text(p))
        yield {"source": "es2tips", "key": os.path.basename(os.path.dirname(p)), "title": t, "url": u, "body": b}
    for p in sorted(glob.glob(os.path.join(base, "japentery/posts/*/post.txt"))):
        t, u, b = front(read_text(p))
        yield {"source": "japentery", "key": os.path.basename(os.path.dirname(p)), "title": t, "url": u, "body": b}
    for p in sorted(glob.glob(os.path.join(base, "es2mud/pages/*/page.txt"))):
        t, u, b = front(read_text(p))
        yield {"source": "es2mud", "key": os.path.basename(os.path.dirname(p)), "title": t, "url": u, "body": b}
    for p in sorted(glob.glob(os.path.join(base, "vovo2000-29232/posts/*/*.txt"))):
        txt = read_text(p)
        lines = txt.split("\n")
        title = lines[1].strip() if len(lines) > 1 else ""
        yield {"source": "vovo2000", "key": os.path.relpath(p, os.path.join(base, "vovo2000-29232/posts")),
               "title": title, "url": "", "body": txt}
    for p in sorted(glob.glob(os.path.join(base, "es2_pal/*"))):
        name = os.path.basename(p)
        yield {"source": "es2_pal", "key": name, "title": os.path.splitext(name)[0], "url": "", "body": read_text(p)}


# ------------------------------------------------------------------ parsing

HEADER = re.compile(r"^\s{0,2}(?P<short>[^\s>].{0,24}?) -(?:\s+(?P<path>/\S+))?\s*$")
EXIT = re.compile(r"^\s*這裡(?:明顯的出口|唯一的出口|沒有任何明顯的出路)")
OCCUPANT = re.compile(r"^\s{1,4}(?P<text>[^\s(（].*?[(（](?P<id>[A-Za-z][^()（）]*)[)）].*?)\s*$")
AGE = re.compile(r"(看起來|外表看起來|年紀)(約[一二三四五六七八九十百千]+多歲|不到十歲)")
CARRY = re.compile(r"^\s*(他|她|牠|它)身上帶著[﹕:：]\s*$")
ITEM = re.compile(r"^\s{1,6}(?P<mark>[ˇＶV√□]?)\s*(?P<name>[^\s(（][^(（]*?)\s*[(（](?P<id>[^()（）]+)[)）]\s*$")
NOT_SHORT = re.compile(r"[，。、！？：﹕,]|^\d|^[A-Za-z0-9 ,]+$")


NOISE = re.compile(r"^\s*([=\-─—_*#@]{3,}|.*<--|.*-->|.*=>|[a-z]+(\s|$)|.*[(（][A-Za-z][^()（）]*[)）]\s*$"
                   r"|.*(說道|說著|說)[：:])")


def is_noise(line, title=""):
    t = line.strip()
    return bool(NOISE.match(line)) or (title and norm(t) and norm(t) in norm(title))


def split_occupant(text):
    m = re.match(r"^(?P<pre>.*?)(?P<name>[^\s「」]+)\s*[(（](?P<id>[^()（）]+)[)）](?P<post>.*)$", text)
    if not m:
        return None
    text = re.sub(r"\s*(<[^>]*>|\[[^\]]*\])\s*$", "", text.strip())
    text = re.sub(r"\s*(<[^>]*>|\[[^\]]*\])\s*$", "", text)
    text = re.sub(r"\s+(?=[(（])", "", text)
    return {"display": text.strip(), "name": m.group("name"), "id": m.group("id").strip(),
            "prefix": m.group("pre").strip(), "suffix": m.group("post").strip()}


def parse_rooms(lines):
    rooms = []
    i = 0
    while i < len(lines):
        m = HEADER.match(lines[i])
        if not m or NOT_SHORT.search(m.group("short")):
            i += 1
            continue
        # description must start on the next line (indented) and an exit line must follow
        j = i + 1
        desc = []
        exit_line = None
        while j < len(lines) and j - i <= 40:
            ln = lines[j]
            if EXIT.match(ln):
                exit_line = ln.strip()
                # exits can wrap onto following line
                while "。" not in exit_line and j + 1 < len(lines) and lines[j + 1].strip() \
                        and not OCCUPANT.match(lines[j + 1]) and not lines[j + 1].strip().endswith(" -"):
                    j += 1
                    exit_line += lines[j].strip()
                break
            if HEADER.match(ln.strip()) and ln.strip().endswith(" -"):
                break
            if not ln.strip() and desc and j + 1 < len(lines) and not lines[j + 1].startswith(" "):
                break
            desc.append(ln)
            j += 1
        if exit_line is None or not "".join(desc).strip():
            i += 1
            continue
        occ = []
        k = j + 1
        while k < len(lines):
            om = OCCUPANT.match(lines[k])
            if not om or EXIT.match(lines[k]):
                break
            o = split_occupant(om.group("text"))
            if o and not ("的屍體" in o["display"] or "Corpse of" in o["display"]):
                occ.append(o)
            k += 1
        long_lines = [l.rstrip() for l in desc]
        while long_lines and not long_lines[0].strip():
            long_lines.pop(0)
        while long_lines and not long_lines[-1].strip():
            long_lines.pop()
        # later paragraphs indented 4 spaces are dynamic extras (time of day, weather, signs)
        extra = []
        for idx in range(1, len(long_lines)):
            if re.match(r"^\s{3,}\S", long_lines[idx]):
                extra = [l.strip() for l in long_lines[idx:] if l.strip()]
                long_lines = long_lines[:idx]
                break
        rooms.append({"short": m.group("short").strip(), "path": m.group("path"),
                      "long": "\n".join(long_lines), "extra": extra, "exits": exit_line,
                      "occupants": occ, "line": i,
                      "context": "\n".join(l for l in lines[max(0, i - 8):i]
                                           if not (EXIT.match(l) or OCCUPANT.match(l)))})
        i = k
    return rooms


def parse_npc_looks(lines, title=""):
    """Find `look <npc>` outputs: description + age line (+ inventory)."""
    looks = []
    used_carry = set()
    consumed = set()
    for i, ln in enumerate(lines):
        end = i
        if i in consumed:
            continue
        if not AGE.search(ln):
            if ("看起來" in ln or "屬於" in ln) and not ln.rstrip().endswith("。") and i + 1 < len(lines) \
                    and AGE.search(ln.strip() + lines[i + 1].strip()):
                consumed.add(i + 1)
                end = i + 1
            else:
                continue
        age_line = ln.strip() if end == i else ln.strip() + "\n" + lines[end].strip()
        # description = contiguous non-blank lines above, stopping at room/occupant/prompt lines
        j = i - 1
        desc = []
        while j >= 0 and lines[j].strip():
            l = lines[j]
            if EXIT.match(l) or OCCUPANT.match(l) or l.lstrip().startswith(">") or HEADER.match(l) \
                    or ITEM.match(l) or CARRY.match(l) or AGE.search(l) or is_noise(l, title):
                break
            desc.insert(0, l.strip())
            j -= 1
        # if the age line sits after a blank, description may be the paragraph above
        if not desc and j >= 1 and not lines[j].strip():
            k = j - 1
            while k >= 0 and lines[k].strip() and not (EXIT.match(lines[k]) or OCCUPANT.match(lines[k])
                                                      or lines[k].lstrip().startswith(">") or AGE.search(lines[k])
                                                      or ITEM.match(lines[k]) or HEADER.match(lines[k])
                                                      or is_noise(lines[k], title)):
                desc.insert(0, lines[k].strip())
                k -= 1
        inv = []
        k = end + 1
        while k < len(lines) and not lines[k].strip():
            k += 1
        k_carry = k
        if k < len(lines) and CARRY.match(lines[k]):
            carry_hdr = lines[k].strip()
            k += 1
            while k < len(lines):
                if not lines[k].strip():
                    # allow a single blank between items
                    if k + 1 < len(lines) and ITEM.match(lines[k + 1]) and lines[k + 1].lstrip()[:1] in "ˇＶV√":
                        k += 1
                        continue
                    break
                im = ITEM.match(lines[k])
                if not im:
                    break
                inv.append({"equipped": bool(im.group("mark")), "name": im.group("name").strip(),
                            "id": im.group("id").strip()})
                k += 1
        else:
            carry_hdr = None
        if carry_hdr:
            used_carry.add(k_carry)
        looks.append({"line": i, "desc": desc, "age_line": age_line, "carry_header": carry_hdr,
                      "inventory": inv, "name_hint": None})
    # inventories with no age line (e.g. undead/beasts): description is the paragraph above
    for i, ln in enumerate(lines):
        if not CARRY.match(ln) or i in used_carry:
            continue
        desc, j = [], i - 1
        while j >= 0 and lines[j].strip() and not (EXIT.match(lines[j]) or OCCUPANT.match(lines[j])
                                                   or lines[j].lstrip().startswith(">") or is_noise(lines[j], title)):
            desc.insert(0, lines[j].strip())
            j -= 1
        hint = None
        while j >= 0 and not lines[j].strip():
            j -= 1
        if j >= 0:
            m = re.match(r"^\s*([^\s：:]{2,5})[：:]", lines[j])
            if m:
                hint = m.group(1)
        inv, k = [], i + 1
        while k < len(lines) and ITEM.match(lines[k]):
            im = ITEM.match(lines[k])
            inv.append({"equipped": bool(im.group("mark")), "name": im.group("name").strip(),
                        "id": im.group("id").strip()})
            k += 1
        if desc and hint:
            looks.append({"line": i, "desc": desc, "age_line": "", "carry_header": ln.strip(),
                          "inventory": inv, "name_hint": hint})
    return looks


def npc_name_from_age_line(age_line, known):
    for n in sorted(known, key=len, reverse=True):
        if age_line.startswith(n):
            return n
    m = re.match(r"^(.{1,6}?)(?:看起來|長得|外表|屬於|生得|一臉|身材|體格|神情|面容|臉上|雙眼|目光|似乎|頗|是)", age_line)
    return m.group(1) if m else None


# ------------------------------------------------------------------ main

def norm(s):
    return re.sub(r"\s+", "", s or "")


def fmt_room(r):
    out = ["%s -" % r["short"]]
    for idx, ln in enumerate(r["long"].split("\n")):
        out.append(ln if idx else ("    " + ln.strip()))
    for x in r.get("extra", []):
        out.append("    " + x)
    out.append("    " + r["exits"])
    for o in r["occupants"]:
        out.append("  " + o["display"])
    return "\n".join(out)


def fmt_look(lk):
    out = list(lk["desc"])
    if lk["age_line"]:
        out.append(lk["age_line"])
    if lk["inventory"]:
        out.append(lk["carry_header"] or "他身上帶著﹕")
        for it in lk["inventory"]:
            out.append("%s%s(%s)" % ("  ˇ" if it["equipped"] else "   ", it["name"], it["id"]))
    return "\n".join(out)


def main(base):
    rooms = OrderedDict()      # key -> room
    npcs = OrderedDict()       # (name,id) -> npc
    docs = list(iter_sources(base))

    # pass 1: rooms
    per_doc = []
    known_names = set()
    for d in docs:
        lines = undouble(d["body"].split("\n"))
        rs = parse_rooms(lines)
        per_doc.append((d, lines, rs))
        for r in rs:
            for o in r["occupants"]:
                known_names.add(o["name"])

    for d, lines, rs in per_doc:
        src = {"source": d["source"], "title": d["title"], "url": d["url"], "key": d["key"]}
        title_area = find_place(d["title"])
        looks = parse_npc_looks(lines, d["title"])
        # attach looks to npcs
        doc_npcs = {}
        for r in rs:
            for o in r["occupants"]:
                doc_npcs.setdefault(o["name"], o)
        for lk in looks:
            name = lk["name_hint"] or npc_name_from_age_line(lk["age_line"], set(doc_npcs) | known_names)
            if not name:
                continue
            occ = doc_npcs.get(name)
            nid = occ["id"] if occ else None
            if not nid:
                # find id from any room occupant across corpus later
                nid = None
            key = name
            e = npcs.setdefault(key, {"name": name, "ids": OrderedDict(), "displays": OrderedDict(),
                                      "looks": [], "rooms": OrderedDict(), "sources": OrderedDict(),
                                      "areas": OrderedDict()})
            if nid:
                e["ids"][nid] = 1
            if occ:
                e["displays"][occ["display"]] = 1
            sig = norm("".join(lk["desc"]) + lk["age_line"])
            for idx, x in enumerate(e["looks"]):
                if norm("".join(x["desc"]) + x["age_line"]) == sig:
                    if len(lk["inventory"]) > len(x["inventory"]):
                        e["looks"][idx] = lk
                    break
            else:
                e["looks"].append(lk)
            e["sources"][d["title"] or d["key"]] = src
            if title_area:
                e["areas"][title_area] = "文章標題"

        for r in rs:
            key = (r["short"], norm(r["long"]))
            if key not in rooms:
                area, basis = None, None
                a = find_place(r["short"])
                if a:
                    area, basis = a, "房名"
                if not area and title_area:
                    area, basis = title_area, "文章標題「%s」" % d["title"]
                if not area:
                    a = find_place(r["long"])
                    if a:
                        area, basis = a, "房間敘述內文"
                rooms[key] = {"short": r["short"], "long": r["long"], "exits": r["exits"],
                              "extra": r["extra"], "doc_area_hint": None,
                              "path": r["path"], "occupants": OrderedDict(), "sources": OrderedDict(),
                              "area": area or "未能判定", "area_basis": basis or "—"}
            room = rooms[key]
            room["sources"][d["title"] or d["key"]] = src
            room.setdefault("contexts", []).append(r["context"])
            for o in r["occupants"]:
                room["occupants"].setdefault(o["display"], o)
                if o["name"] in npcs:
                    npcs[o["name"]]["rooms"][(r["short"], key[1])] = room
                    npcs[o["name"]]["ids"][o["id"]] = 1
                    npcs[o["name"]]["displays"][o["display"]] = 1

    # second linking pass: occupants whose look appeared in another document
    for key, room in rooms.items():
        for disp, o in room["occupants"].items():
            if o["name"] in npcs:
                npcs[o["name"]]["rooms"][(room["short"], key[1])] = room
                npcs[o["name"]]["ids"][o["id"]] = 1
                npcs[o["name"]]["displays"][disp] = 1
    # fallback area inference for rooms still unknown
    for room in rooms.values():
        if room["area"] != "未能判定":
            continue
        for o in room["occupants"].values():
            e = npcs.get(o["name"])
            if not e:
                continue
            a = find_place("".join("".join(lk["desc"]) for lk in e["looks"]))
            if a:
                room["area"], room["area_basis"] = a, "房內 NPC「%s」的敘述" % e["name"]
                break
        if room["area"] == "未能判定":
            a = find_place("\n".join(room.get("contexts", [])))
            if a:
                room["area"], room["area_basis"] = a, "擷取紀錄中房間前後的文字"
    for e in npcs.values():
        for room in e["rooms"].values():
            if room["area"] != "未能判定":
                e["areas"].setdefault(room["area"], "所在房間")
        if not e["areas"]:
            pl = find_place("".join("".join(lk["desc"]) for lk in e["looks"]))
            if pl:
                e["areas"][pl] = "NPC 敘述"

    write_outputs(rooms, npcs)


def area_sort_key(a):
    return (a == "未能判定", a)


def write_outputs(rooms, npcs):
    by_area = defaultdict(list)
    for r in rooms.values():
        by_area[r["area"]].append(r)
    areas = sorted(by_area, key=area_sort_key)

    md = ["# 舊有資料：房間與 NPC 敘述整理", "",
          "> 來源：`es2-reference.rar`（分支 `gbfangyans-star-info`）中 es2tips、japentery、vovo2000、es2mud、es2_pal 的遊戲畫面紀錄。",
          "> 由 `tools/build_legacy_room_npc_compendium.py` 自動擷取；房間與 NPC 敘述保留原文，只去除色碼與部落格的隔行空白。",
          "> **區域**不在遊戲畫面中，依序以「房名 → 文章標題 → 房間敘述 → 房內 NPC 的敘述 → 紀錄中房間前後文字」出現的地名推定，",
          "> 每個房間都列出判定依據；判定不了的歸入「未能判定」。地名只照原文歸類，不推測其上層區域（例如「雪吟莊」不併入其他城鎮）。",
          "> 房間內列出的是擷取當下畫面上的人物/物品（可能含當時在場的玩家）；多份紀錄的同一房間已合併，屍體與「<昏迷不醒>」等狀態已移除。",
          "> 房間敘述後縮排的「現在是正午時分…」等句子是擷取當時的時間/天氣，不屬於固定敘述。", "",
          "## 總覽", "", "| 區域 | 房間數 | 有人物的房間 |", "|---|---:|---:|"]
    for a in areas:
        md.append("| %s | %d | %d |" % (a, len(by_area[a]), sum(1 for r in by_area[a] if r["occupants"])))
    md.append("| **合計** | **%d** | **%d** |" % (len(rooms), sum(1 for r in rooms.values() if r["occupants"])))
    md += ["", "NPC 敘述共 %d 位（其中 %d 位能對應到房間）。" % (
        len(npcs), sum(1 for e in npcs.values() if e["rooms"])), ""]

    shown = set()
    for a in areas:
        md += ["## %s" % a, ""]
        for r in sorted(by_area[a], key=lambda x: x["short"]):
            md.append("### %s" % r["short"])
            md.append("")
            md.append("- 區域判定依據：%s" % r["area_basis"])
            md.append("- 出處：" + "；".join("%s〈%s〉" % (s["source"], t) for t, s in r["sources"].items()))
            md.append("")
            md.append("```text")
            md.append(fmt_room({"short": r["short"], "long": r["long"], "exits": r["exits"],
                                "extra": r["extra"],
                                "occupants": list(r["occupants"].values())}))
            md.append("```")
            md.append("")
            descs = [(o, npcs[o["name"]]) for o in r["occupants"].values() if o["name"] in npcs]
            if descs:
                md.append("**NPC 敘述：**")
                md.append("")
                done = set()
                for o, e in descs:
                    if e["name"] in done:
                        continue
                    done.add(e["name"])
                    shown.add(e["name"])
                    md.append("- **%s**" % o["display"])
                    md.append("")
                    for lk in e["looks"]:
                        md.append("  ```text")
                        for ln in fmt_look(lk).split("\n"):
                            md.append("  " + ln)
                        md.append("  ```")
                        md.append("")

    rest = [e for e in npcs.values() if e["name"] not in shown]
    if rest:
        md += ["## 未對應到房間的 NPC 敘述", "",
               "資料中有 NPC 的 look 畫面，但沒有一起擷取到所在房間。區域依文章標題推定。", ""]
        by_a = defaultdict(list)
        for e in rest:
            by_a[next(iter(e["areas"]), "未能判定")].append(e)
        for a in sorted(by_a, key=area_sort_key):
            md += ["### %s" % a, ""]
            for e in sorted(by_a[a], key=lambda x: x["name"]):
                disp = next(iter(e["displays"]), None) or (
                    "%s(%s)" % (e["name"], next(iter(e["ids"]))) if e["ids"] else e["name"])
                md.append("- **%s**　出處：%s" % (disp, "；".join(
                    "%s〈%s〉" % (s["source"], t) for t, s in e["sources"].items())))
                md.append("")
                for lk in e["looks"]:
                    md.append("  ```text")
                    for ln in fmt_look(lk).split("\n"):
                        md.append("  " + ln)
                    md.append("  ```")
                    md.append("")

    # index
    md += ["## NPC 索引", "", "| NPC | 區域 | 所在房間 |", "|---|---|---|"]
    for e in sorted(npcs.values(), key=lambda x: (next(iter(x["areas"]), "~"), x["name"])):
        disp = next(iter(e["displays"]), None) or e["name"]
        md.append("| %s | %s | %s |" % (disp, "、".join(e["areas"]) or "未能判定",
                                         "、".join(OrderedDict.fromkeys(k[0] for k in e["rooms"])) or "—"))
    md.append("")

    with open(os.path.join(ROOT, "docs", "LEGACY_ROOM_NPC_COMPENDIUM.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(md))

    js = {"rooms": [], "npcs": []}
    for r in rooms.values():
        js["rooms"].append({"area": r["area"], "area_basis": r["area_basis"], "short": r["short"],
                            "long": r["long"], "exits": r["exits"],
                            "occupants": [o["display"] for o in r["occupants"].values()],
                            "sources": list(r["sources"].values())})
    for e in npcs.values():
        js["npcs"].append({"name": e["name"], "ids": list(e["ids"]), "displays": list(e["displays"]),
                           "areas": list(e["areas"]),
                           "rooms": list(OrderedDict.fromkeys(k[0] for k in e["rooms"])),
                           "looks": [fmt_look(lk) for lk in e["looks"]],
                           "sources": list(e["sources"].values())})
    with open(os.path.join(ROOT, "catalog", "legacy_room_npc_compendium.json"), "w", encoding="utf-8") as f:
        json.dump(js, f, ensure_ascii=False, indent=2)
    print("rooms=%d areas=%d npcs=%d (linked %d)" % (len(rooms), len(areas), len(npcs),
                                                     sum(1 for e in npcs.values() if e["rooms"])))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    main(sys.argv[1])
