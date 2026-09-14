/*---
description: Input prompt for get_char() and input_to() carryover mapping.
author: Annihilator <taedlar@gmail.com>
---*/

#include <ansi.h>

/* [NEOLITH-EXTENSION]
 * Render option mappings as a browser/telnet-friendly numbered list.
 *
 * LOGIN_D uses ordinary input_to() for these menus, so players enter a
 * number and press Enter. cursor_translate() maps that number back to the
 * original canonical option value. This avoids VT100 cursor movement and
 * get_char() single-character transport during login/character creation.
 *
 * The pager branch below still retains its original get_char() controls.
 */
void input_prompt (mixed func, int flags, mixed data, mixed arg1) {
    if (mapp(data) && arrayp(data["options"]) && intp(data["cursor"])) {
        string prompt = data["prompt"] || "你的選擇：";
        int pos = 1;

        /* Browser/telnet compatible numbered menu. No VT100 cursor movement is
         * required: enter 1, 2, 3... and press Enter. The callback still uses
         * cursor_translate(), so canonical option values and rules are unchanged. */
        write ("\n" + prompt + "\n");

        /* Binary yes/no prompts are deliberately keyboard-first in WebMUD:
         * Y = yes, N = no. Other canonical option lists remain numbered. */
        if (sizeof(data["options"]) == 2
        &&  data["options"][0] == "Y) 是"
        &&  data["options"][1] == "N) 否") {
            write ("Y. 是\nN. 否\n請輸入 Y 或 N: ");
            return;
        }

        foreach (string opt in data["options"]) {
            string label = opt;
            if (opt == "human")
                label = "人類 (human)";
            else if (opt == "avatar")
                label = "化身神 (avatar)";
            else if (opt.len() > 2 && opt[1] == ')') {
                if (opt.len() > 3 && opt[2] == ' ')
                    label = opt[3..];
                else
                    label = opt[2..];
            }
            write (sprintf ("%d. %s\n", pos++, label));
        }
        write ("請輸入選項數字: ");
    }
    else if (func == "more" && arrayp (data) && intp (arg1)) {
        int page_size = this_object()->query("page_size") || 22;
        if (arg1 < 0)
            arg1 = 0;
        else if (arg1 > sizeof (data))
            arg1 = sizeof (data);
        // The pager has two arguments: the text array and the current line number.
        {
            int total_pages = (sizeof(data) + page_size - 1) / page_size;
            int current_page = (arg1 + page_size - 1) / page_size;
            if (current_page < 1) current_page = 1;
            if (current_page > total_pages) current_page = total_pages;
            printf (
                "\n" CLR BGRN "【 第 %d / %d 頁 】\n" NOR
                "1. 下一頁\n"
                "2. 上一頁\n"
                "請輸入選項數字，或直接輸入其他指令: ",
                current_page, total_pages
            );
        }
    }
}
