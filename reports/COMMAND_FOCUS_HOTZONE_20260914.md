# Command Focus Hot-Zone

Base: ES2_WebMUD_v3.20.77_MAP_V7_READONLY_WORLD.zip

Changed only the Web UI input-focus behavior:

- Clicking non-interactive space anywhere in `.console-panel` focuses `#command`.
- This includes the large transcript/console area and command-bar background.
- Real buttons/links/form controls retain their normal click behavior.
- Selecting terminal text does not forcibly steal the selection on click completion.
- `focus({preventScroll:true})` avoids viewport jumps where supported.
- Browser cache token bumped to `mapv7-focuszone1`.
- MAP V7 readonly world/map logic is unchanged.

Validation:
- `node --check web/app.js`: PASS
- Static handler assertions: PASS
