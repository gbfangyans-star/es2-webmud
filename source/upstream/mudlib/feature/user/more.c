/*---
description: text pager, used to display long text in pages.
author: Annihilator <taedlar@gmail.com>
---*/
#include <ansi.h>

private int i, matched, match_line, tmp_line;
private string pattern;

private int justify_next_line (int line, int total, int page_size) {
    if (line < 0)
        line = 0; // first page
    else if (line > total - page_size)
        line = total - page_size; // last page
    return line;
}

/* [NEOLITH-EXTENSION]
 *
 * The `input_prompt` apply will recognize the pager by callback function name "more"
 * and write the pager prompt to the user.
 */
void more (string cmd, string *text, int line) {
    int page_size = this_object()->query("page_size") || 22;

    /* HELP pager: only next/previous are pager controls.  Anything else is a
     * normal player command, so HELP never traps the character in a menu. */
    switch (cmd) {
    case "2": case "b": case KEY_PAGE_UP:
        more (" ", text, justify_next_line (line - 2*page_size, sizeof(text), page_size));
        return;
    case "": case "1": case " ": case KEY_PAGE_DOWN:
        line = justify_next_line (line, sizeof(text), page_size);
        write (HOME CLR + implode (text[line .. line + page_size - 1], "\n"));
        line += page_size;
        input_to ("more", text, line);
        return;
    default:
        /* Release input_to before dispatching, otherwise the next command can
         * be swallowed by the pager again. */
        if (stringp(cmd) && cmd != "")
            command(cmd);
        return;
    }
}
/*
 * Start the pager with the given text.
 */
varargs void start_more (mixed msg, int start_line) {
    if (stringp (msg))
        msg = explode (msg, "\n");
    else if (!arrayp (msg))
        error ("Invalid argument to start_more: expected string or array of strings.");
    more (" ", msg, start_line ? start_line : 0);
}

void start_more_if_needed (mixed msg) {
    if (stringp (msg))
        msg = explode (msg, "\n");
    else if (!arrayp (msg))
        error ("Invalid argument to start_more_if_needed: expected string or array of strings.");
    int page_size = this_object()->query("page_size") || 22;
    if (sizeof (msg) > page_size)
        start_more (msg);
    else
        write (implode (msg, "\n") + "\n");
}
