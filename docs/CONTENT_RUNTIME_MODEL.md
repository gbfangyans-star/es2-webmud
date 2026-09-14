# Content vs Runtime Model

The catalog is an index of the canonical LPC tree, not a replacement runtime.

## Vendor
The allowed repository's `feature/npc/vendor.c` keeps a runtime stock mapping copied from `merchandise` during reset. Purchase validation checks stock and object IDs, price comes from the merchandise object's `value`, delivery clones the object, and liquid merchandise may be wrapped in a default container. The catalog therefore exposes:
- static merchandise definitions from NPC files
- `vendor` runtime trait when vendor behavior functions are present
- references from vendor -> merchandise item
- manual review for vendor-specific scripts

## Doors
`create_door()` calls are indexed with direction/name/opposite direction/state. A door whose direction has no matching room exit is flagged by the audit. The index does not simulate door state.

## Timed and command behavior
`call_out()` and `add_action()` are indexed as behavioral hooks. Their LPC handlers remain authoritative and are never transpiled into browser JavaScript.

## Items
The item browser shows only fields found in source: identity, value, weight, material, weapon type, required skills, study content, inheritance, and runtime traits. Unknown fields remain absent.

## Relationships
`reference_graph.json` connects rooms, objects, merchandise, equipment and other directly parseable references. Browser navigation can follow both incoming and outgoing references without inventing world coordinates.
