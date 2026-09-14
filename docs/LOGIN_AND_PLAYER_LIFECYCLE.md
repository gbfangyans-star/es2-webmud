# Login and player lifecycle, source-only notes

Canonical source: `taedlar/es2_mudlib` main only.

Observed directly in `/mudlib/obj/login.c`, `/mudlib/adm/daemons/logind.c`, and `/mudlib/obj/user.c`:

- `obj/login.c` is the connection/login object and delegates the login state machine to `LOGIN_D`.
- Existing saved IDs are restored and prompted for a hidden password; a successful password path calls `authorize()` and then enters the world.
- A new ID is explicitly confirmed before creation.
- New password minimum length is 5 characters and password confirmation is required.
- Email may be supplied or `none`; the daemon validates an entered address and caps it at 64 characters.
- Character creation then selects race (`human` or `avatar` in the observed switch), appearance gender (`female`, `male`, or `unknown-gender`), creates the body from the race's default body (falling back to USER_OB), sets race/gender, initializes it, and asks for a display name.
- `obj/user.c` inherits CHARACTER plus autoload/edit/flag/input/more/save features. Its setup restores autoload and conditions and checks death/stat state. Its heartbeat updates age, and disconnect handling stops fighting and remembers the last location.

Browser policy:

The web client does not replace this state machine. It transports the original prompts and responses. It only masks the HTML command input when it recognizes password prompts that are literal strings in the allowed source.
