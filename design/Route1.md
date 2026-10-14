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

## Open questions

- Which wild Pokémon live here (before tall grass is added).
- The first gym town's name, for the route sign.

## Next steps

- See `route-1.md` for the phase plan: tall grass and wild Pokémon, then sign, items, and ledge, then trainers.
