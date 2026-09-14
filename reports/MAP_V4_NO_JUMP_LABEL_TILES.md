# Map V4 no-jump / label-tile patch

- Room prose is no longer allowed to move the map marker after exact WEBHUD room-path tracking starts.
- Duplicate room names can therefore no longer cause a temporary false location followed by a delayed correction.
- All visible room names are rendered as two-character labels inside fixed 34x22 room tiles.
- Map spacing increased to 54x46 to prevent label collisions.
- Topology cache key bumped to v2.fixed so stale V3 browser topology cannot contaminate this test.
- WEBHUD remains authoritative and can correct the marker when a movement command actually fails.
