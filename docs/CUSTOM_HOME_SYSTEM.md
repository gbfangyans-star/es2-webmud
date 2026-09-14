# Custom Home System

> This is a WebMUD custom extension and is **not** canonical `taedlar/es2_mudlib` content.

## Phase 1

- Snow Inn (`/d/snow/inn_hall`) contains `家園傳送師` (`home teleporter`).
- `home` teleports a player into a freshly-instanced private `家園大廳`.
- Only the owning player may enter that hall instance.
- The hall contains:
  - `私人儲物箱`: 200 object-stack slots, no weight limit because stored contents are serialized into player save data instead of physically carried.
  - `家園管家`: develops up to 10 future rooms.
- Room development prices: 10/20/.../100 gold for rooms 1..10.
- Developed room count is saved in `custom_home/rooms` on the player.
- Storage is saved in `custom_home/storage` on the player. Common item identity, stack amount and autoload string are preserved.
- Future room purposes are intentionally unspecified until the user supplies them.

## Snow Inn custom easter egg

- `三屆打手槍冠軍［鐵手］林楓炎` is a custom NPC in the inn.
- Title, nickname and personal name use ANSI colors.
- Looking at him makes him say: `小子，要來場酣暢淋漓的打手槍比賽嗎？`
- Each developed room is immediately enterable with `enter <1-10>` and uses a generic private room shell until a future purpose is assigned.
