/*---
description: Save and restore LPC objects.
author: Annihilator <taedlar@gmail.com>
---*/

int save() {
    string file;

    // always use the UID for security check, never trust the euid of the object.
    seteuid (getuid());
    if (geteuid() == "guest")
        return 0;

    if (stringp(file = this_object()->query_save_file())) {
        assure_file(file);
        return save_object (file);
    }
    return 0;
}

int restore() {
    string file;

    seteuid (getuid());
    if (stringp (file = this_object()->query_save_file())) {
        int ok = restore_object (file, 1);
        // 武功代碼更名後，舊存檔的技能換成新代碼（見 /feature/char/skill.c）。
        if (ok && function_exists ("migrate_skill_ids", this_object()))
            this_object()->migrate_skill_ids();
        return ok;
    }
    return 0;
}
