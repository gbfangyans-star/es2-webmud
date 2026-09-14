# Runtime Local Map Contract (CUSTOM UI extension)

Gameplay authority remains the LPC room. `webhud` only reports read-only room topology.

Optional room properties:
- `map/area`: display area name, e.g. `老松林`.
- `map/layer`: topology layer, e.g. `地面`, `洞穴`, `樹上`, `二樓`.
- `map/mode`: set to `maze` when unknown runtime destinations must not be revealed before exploration.

Rules:
1. Current player room is always centered.
2. Only rooms on the current layer are placed on the 7x7 plane.
3. `up`, `down`, non-compass and cross-layer exits are listed separately as ▲, ▼, ◇ transitions.
4. In `maze` mode, destinations not visited in the current exploration state render as `？？？`.
5. When a maze room's authoritative runtime exit signature changes, explored maze visibility is invalidated so an old reset topology is not presented as current truth.
6. Runtime `ROOM/EXIT/MAPMETA` data wins over seeded/static graph data.
7. Rooms without metadata remain ordinary ground-layer rooms for backward compatibility.
