# Route 1

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The first route, running east from Balwyn towards Carnrudh, the first gym town (inspired by Camborne / Redruth).
- A moorland lane: it leaves the village between hedges with the cliffs to the north and the sea to the south, then winds inland through woodland and heath.

## Inspiration

- The West Penwith moors east of St Just: lanes between hedges and drystone walls, gorse and heather, and old engine houses on the skyline.

## Map notes

- Map `KerniaRoute1` (`MAP_KERNIA_ROUTE1`), layout `LAYOUT_KERNIA_ROUTE1` (48×24, `gTileset_General` + `gTileset_Dewford`, the same as Balwyn so the join draws cleanly). Region map section `MAPSEC_ROUTE_1` (FireRed's, shown as "ROUTE 1"). Group `gMapGroup_KerniaTownsAndRoutes`.
- Named `KerniaRoute1` because plain `MAP_ROUTE1` / `LAYOUT_ROUTE1` belong to FireRed's Route 1.
- Music `MUS_ROUTE101`, weather `WEATHER_SUNNY`. Border is trees.
- Connections: `left` to `MAP_BALWYN` (offset 0), and `right` to `MAP_CARNRUDH` (offset -1), whose main street (rows 12–13) continues the east edge's sand road (rows 11–12, from x 40).
- Layout:
  - x 0–9: a hedged sand lane continuing Balwyn's road, with the cliff band above and the shore below, as in Balwyn.
  - From x 10: the lane opens into a meadow, then a grass corridor winds north, south, and north again through woodland, and the sand road resumes at x 40.
  - The sand path tileset has no corner pieces, so the bends are grass.
  - The cliff ends at x 10 with a straight edge against the trees. It could be softened by hand.

## Sign, items, and ledge

- Route sign at (10, 10), where the lane opens into the meadow: "ROUTE 1 / ← BALWYN   CARNRUDH →".
- Item ball: a Poké Ball in the meadow's dead-end corner at (10, 13) (`FLAG_ITEM_KERNIA_ROUTE1_POKE_BALL`, renamed from `FLAG_UNUSED_0x468`).
- Rock Smash: a breakable rock at (11, 9), just above the route sign, guards a Super Potion in the one-tile nook at (10, 9) (`FLAG_ITEM_KERNIA_ROUTE1_SUPER_POTION`, 0x479). It needs badge 1, so it's a reason to come back from Carnrudh. The rock's flag is `FLAG_TEMP_11`.
- Hidden item: a Potion at (10, 5) in the ledge nook (`FLAG_HIDDEN_ITEM_KERNIA_ROUTE1_POTION`, renamed from `FLAG_UNUSED_0x264`; hidden-item flags must be ≥ `FLAG_HIDDEN_ITEMS_START`).
- Ledge: a nook off the top corridor (x 10–13, rows 5–7) with a south-facing ledge across row 8 (`0x0D5`/`0x087`/`0x0D6`). It's a one-way hop down into the meadow on the way back to Balwyn. The ledge blocks the nook from the meadow, so the first-bend tall grass still can't be avoided going east.

## Wild Pokémon

- Galar's UK-inspired wildlife, matching the British-wildlife starters, with Wingull for the coast and Gossifleur as an early Grass type (there's no Grass starter).
- Tall grass only (`src/data/wild_encounters.json`, `gKerniaRoute1`, encounter rate 20), levels 2–4:

| Pokémon | Levels | Chance |
|---|---|---|
| Skwovet | 2–4 | 30% |
| Rookidee | 2–4 | 25% |
| Wooloo | 2–4 | 14% |
| Nickit | 2–4 | 11% |
| Gossifleur | 2–3 | 10% |
| Blipbug | 2–4 | 6% |
| Wingull | 3–4 | 4% |

- Tall grass patches:
  - Two span the whole path, so the player has to walk through them: the first bend north (x 14–17, rows 6–8) and the leg heading south (x 24–27, rows 10–13).
  - Two are optional side areas: the meadow's dead-end corner (x 10–13, row 13) and the bottom leg (x 29–33, rows 15–16, with the path clear on rows 17–18).

## Trainers

| Trainer | Where | Team | Lore |
|---|---|---|---|
| Youngster Jory (`TRAINER_JORY`) | (16, 10), at the first bend, facing south across the lane, sight 3 | Skwovet Lv4 | His grampy hears the Knockers in Wheal Gwyn and leaves pasty crust by the mine fence for them. |
| Lass Tamsin (`TRAINER_TAMSIN`) | (35, 9), at the top of the last leg, facing south, sight 4 | Rookidee Lv4, Wooloo Lv5 | Her brother has gone to Carnrudh for a Lumen job. Lumen's posters say "Bringing the mines home!", but her mam reckons some holes are best left shut. |

- IDs 855–856 in `include/constants/opponents.h` (`TRAINERS_COUNT_EMERALD` is now 857, which leaves room for 7 more before the 864 limit).

## Open questions

- None at the moment.

