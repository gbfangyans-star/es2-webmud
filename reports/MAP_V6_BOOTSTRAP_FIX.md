# MAP V6 bootstrap fix

Source base: user-uploaded `ES2_WebMUD_v3.20.77_MAP_V5_FIXED_WORLD_TEST(1).zip`.

## Root cause addressed
V5 cleared `currentRoomId` on WebSocket connect, while normal HUD polling required `currentRoomId` to already exist. If room-name guessing did not resolve a unique room, the exact `webhud` room path was never requested, leaving the map permanently at `等待辨識所在房間`.

## V6 changes
- Added a one-shot exact-room bootstrap when real room output is detected.
- Bootstrap may issue `webhud` before `currentRoomId` exists, but only after room-like output and never during password input.
- `@@WEBHUD|ROOM` immediately establishes the exact LPC room path and starts normal background HUD polling.
- Successful or timed-out bootstrap clears bootstrap state safely.
- Map HUD now visibly shows `MAP V6 固定全圖｜等待定位` before room detection.
- Browser cache-busting updated to `app.js?v=mapv6-bootstrapfix`.
- Map topology cache key bumped to V6.

## Validation
- `node --check web/app.js`: PASS.
- Existing `world_static_map.json` preserved unchanged.
- No MUD LPC content altered in this patch.
