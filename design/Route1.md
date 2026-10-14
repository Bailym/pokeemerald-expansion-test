# Route 1

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The first route, running east from Balwyn towards the first gym town (Camborne / Redruth).
- A moorland lane: it leaves the village between hedges with the cliffs to the north and the sea to the south, then winds inland through woodland and heath.

## Inspiration

- The West Penwith moors east of St Just: lanes between hedges and drystone walls, gorse and heather, and old engine houses on the skyline.

## Map notes

- Map `KerniaRoute1` (`MAP_KERNIA_ROUTE1`), layout `LAYOUT_KERNIA_ROUTE1` (48×24, `gTileset_General` + `gTileset_Dewford`, the same as Balwyn so the join draws cleanly). Region map section `MAPSEC_ROUTE_1` (FireRed's, shown as "ROUTE 1"). Group `gMapGroup_KerniaTownsAndRoutes`.
- Named `KerniaRoute1` because plain `MAP_ROUTE1` / `LAYOUT_ROUTE1` belong to FireRed's Route 1.
- Music `MUS_ROUTE101`, weather `WEATHER_SUNNY`. Border is trees.
- Connections: `left` to `MAP_BALWYN` (offset 0). The east edge's sand road (rows 11–12, from x 40) is where the first gym town will connect.
- Layout:
  - x 0–9: a hedged sand lane continuing Balwyn's road, with the cliff band above and the shore below, as in Balwyn.
  - From x 10: the lane opens into a meadow, then a grass corridor winds north, south, and north again through woodland, and the sand road resumes at x 40.
  - The sand path tileset has no corner pieces, so the bends are grass.
  - The cliff ends at x 10 with a straight edge against the trees. It could be softened by hand.

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

## Open questions

- The first gym town's name, for the route sign.

## Next steps

- See `route-1.md` for the phase plan: sign, items, and ledge, then trainers.
