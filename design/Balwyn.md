# Balwyn

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The player's hometown: a quiet former tin-mining village in the far west of Kernia, where the game starts.
- Name: bal (Cornish for mine) + gwyn (white, blessed).
- Faded since the mines closed: empty and boarded-up houses, young people leaving. This is why Lumen's promises of jobs appeal here.

## Inspiration

- A composite of the far-west mining coast: St Just, Pendeen, and Botallack.

## Story

- Opening:
  1. Lumen's PR team arrives in the village with big promises, with Nova as its face. The player meets Nova here.
  2. Professor Kelyn, an old friend of the grandparent, is also visiting, researching the grandparent's legends, and is skeptical of Lumen.
  3. After Lumen's event, Kelyn gives the player their starter: Fletchling, Spheal, or Shinx.
  4. As the player leaves, their parent hands them the grandparent's journal of legends and mine maps.
- The player's family are miners. The grandparent, an old miner who knew the legends, passed away before the game starts.
- The deepest old mine, where Bucca sleeps, is visible from day one: an engine house on the cliffs just outside the village, its entrance fenced off and sealed. After badge 8 the player returns home for the climax there.

## Locations

- A small village of four buildings either side of the road east, on a headland: cliffs to the north, sea to the west and south.
- North of the road:
  - A neighbour's house (blue roof).
  - A small cottage (red roof).
  - The mine yard in the north-west corner (see below).
- South of the road, reached by a lane branching off the main road:
  - Player's house (west).
  - The old miners' pub (east), The Knocker's Arms: the community hub, where locals talk about the mines, the legends, and Lumen.
- The deepest old mine, Wheal Gwyn ("white mine", echoing the village's name), under the cliffs in the north-west corner: a fenced-off yard with the sealed entrance and a warning sign outside the fence.
- Only two neighbours' homes, so the "faded" feel has to come from these two and from NPC dialogue rather than rows of empty houses.
- No Pokémon Center and no lab; the parent heals the player's team.

## Characters

- Parent: at home; heals the player's team and gives them the journal as they leave.
- Professor Kelyn (visiting).
- Nova and Lumen's PR team (visiting, opening only).

## Connections

- One route east, towards Camborne / Redruth (gym 1).

## Map notes

- Map `Balwyn` (`MAP_BALWYN`), layout `LAYOUT_BALWYN` (24×24, `gTileset_General` + `gTileset_Dewford`), region map section `MAPSEC_BALWYN`, outdoor maps group `gMapGroup_KerniaTownsAndRoutes`.
- Music `MUS_LITTLEROOT`, weather `WEATHER_SUNNY` (not `WEATHER_SUNNY_CLOUDS`, whose cloud shadows streak across the buildings). Border is plain sea (`0x170`) to match the shoreline water.
- Interiors are in their own group, `gMapGroup_IndoorBalwyn`, each with its own layout copied from a vanilla interior. The door warps on `Balwyn` are numbered in the order below; don't reorder them, because each interior's doormat warps back to that number.

| Warp | Building | Door | Interior map | Copied from |
|---|---|---|---|---|
| 0 | Player's house | (7, 17) | `Balwyn_PlayersHouse_1F` + `Balwyn_PlayersHouse_2F` (bedroom; stairs 1F (8, 2) ↔ 2F (7, 1)) | Brendan's house |
| 1 | Neighbour's house | (15, 9) | `Balwyn_House1` | Dewford House 1 |
| 2 | Cottage | (19, 9) | `Balwyn_House2` | Dewford House 2 |
| 3 | Pub | (17, 17) | `Balwyn_Pub` (bar counter across the back right with bookshelves behind as bottle shelves, two tables on the left) | Composed from Trainer Fan Club / Dewford Hall pieces |

- Signs (`bg_events`, scripts in `Balwyn/scripts.inc`): the Wheal Gwyn warning sign at (6, 9), and The Knocker's Arms sign at (20, 17), whose "Leave a crust for the Knockers!" foreshadows the pasty-crust offering at the climax.
- The road leaves the east edge on rows 11–12, where the first route will connect. Until then the road runs into the sea border.
- New-game spawn point (`WarpToTruck` in `src/new_game.c`): (4, 4) in the bedroom, `Balwyn_PlayersHouse_2F`.
- Mine placeholder: an adit (Granite Cave's entrance tile, from Route 106) cut into the cliff at (6, 4), with a gravel apron and a boulder. It sits in a yard in the north-west corner, closed off by the sea to the west, trees to the east, and a picket fence across the front (row 8), with a warning sign outside at (6, 9). The adit tile also has collision set. To open the mine later, remove part of the fence (or replace it with a scripted barrier) and add a warp on the adit. A proper engine house needs custom tiles.

## Open questions

- Who lives in the neighbour's house and the cottage, and is either of them empty or boarded up?
- Where in the village Lumen's opening event takes place (e.g. on the road outside the pub).
- Whether the player's house gets a mailbox.

## Next steps

- Script the opening sequence (Lumen's event, Kelyn and the starter, the parent and the journal).
- Build the first route east and connect it on rows 11–12.
- Retire TestTown and TestRoute (and the TestTown house interior) once Balwyn and the first route replace them.
