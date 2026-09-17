/*---
description: UTF-8 utilities
author: Annihilator <taedlar@gmail.com>
---*/

varargs string cjk_wrap (string str, int width, int indent, int first_line_indent) {
    string* mbch;
    string result = "";
    int line_length = first_line_indent;
    int prev_char_width = 0;

    if (!width || width < 1)
        return str;
    mbch = explode (str, ""); // [NEOLITH-EXTENSION] explode to array of utf-8 characters
    foreach (string ch in mbch) {
        int char_width = (strlen (ch) > 1) ? 2 : 1; // CJK multi-byte chars are double width
        if (ch == "\n" || ch == "\r") {
            if (indent < 0) {
                result += ch;
                line_length = 0;
                continue; // preserve existing newlines if indent is negative
            }
            if (prev_char_width > 1)
                continue; // skip newlines immediately following multi-byte characters to avoid breaking them
            ch = " "; // treat newlines as spaces for wrapping purposes
        }
        prev_char_width = char_width;
        if (char_width > 1 || ch == " ") { // break on spaces and multi-byte characters
            if (line_length + char_width > width) {
                result += "\n";
                if (indent > 0)
                    result += repeat_string (" ", indent);
                line_length = indent;
            }
        }
        if (ch == " " && line_length == 0)
            continue; // skip leading spaces
        result += ch;
        if (ch == "\t")
            line_length += 8 - (line_length % 8); // tab stops every 8 characters
        else
            line_length += char_width;
    }

    return result;
}

// cjk_pad()
// NEW（非原始 ES2 內容，用來讓中英夾雜文字對齊成整齊欄位）
//
// Pads str with spaces to reach `width` visual columns, counting CJK
// multi-byte characters as width 2 (matching cjk_wrap()'s own rule) instead
// of raw byte/character count, so %-Ns style sprintf padding does not go
// ragged when a string mixes Chinese and ASCII. If str is already >= width,
// it is returned unchanged (never truncated). right_align pads on the left
// instead of the right.
varargs string cjk_pad (string str, int width, int right_align) {
    string* mbch;
    int w, pad;

    mbch = explode (str, "");
    w = 0;
    foreach (string ch in mbch)
        w += (strlen (ch) > 1) ? 2 : 1;

    pad = width - w;
    if (pad <= 0) return str;

    return right_align
        ? repeat_string (" ", pad) + str
        : str + repeat_string (" ", pad);
}
