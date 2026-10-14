# Balwyn

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The player's hometown: a quiet former tin-mining village in the far west of Kernia, where the game starts.
- Name: bal (Cornish for mine) + gwyn (white, blessed).
- Faded since the mines closed: empty and boarded-up houses, young people leaving. This is why Lumen's promises of jobs appeal here.

## Inspiration

- A composite of the far-west mining coast: St Just, Pendeen, and Botallack.

## Story

- Opening: a slow-burn village. The player is free to wander Balwyn and pick up lore from every villager before the story starts.
  1. Morning: the player wakes in their bedroom. Downstairs, Mum sets the scene: Lumen's people are in the village today, and Kelyn, Grampy's old friend, is visiting.
  2. Free roam: the player can talk to everyone. The two neighbours show the village's divide over Lumen (see Characters).
  3. Trigger: heading east towards Route 1, the player is stopped by a hi-vis Lumen grunt and sent to the event at Wheal Gwyn. This is also what keeps the player off Route 1 without a Pokémon.
  4. The event, at the Wheal Gwyn fence:
     - Nova announces that Lumen is reopening Wheal Gwyn, with jobs right here in Balwyn.
     - The villagers react aloud: the hopeful dad from the blue house, and the old miner muttering.
     - Kelyn asks one public question about the old legends, and Nova laughs it off.
  5. The kitchen table: Kelyn walks the player home. With Mum there, they talk about the grandparent.
     - Kelyn gives the starter (Fletchling, Spheal, or Shinx), the Pokédex, and a few Poké Balls.
     - Mum hands over the grandparent's journal of legends and mine maps, and Kelyn recognises them.
  6. Nova battle: outside the house, Nova challenges the player, all smiles for the cameras.
     - Pawmi is Lv5 with only Normal-type moves, so it's fair against every starter (Electric would beat Fletchling and Spheal). Its Electric moves come later as Nova's team grows.
     - Win or lose, the story continues, and Nova has a line for each.
  7. Wrap-up:
     - Nova heads for Carnrudh ("see you at the gym"), and Kelyn returns to her lab in Treveur.
     - The grunts stay posted at the mine.
     - The first time the player passes the mine fence afterwards, they hear faint knocking: the first hint of Bucca.
- After the announcement:
  - Every villager has a "before" and an "after" line.
  - The village visibly changes: Lumen signs, a site hut at Wheal Gwyn, a "WHEAL GWYN REOPENS" notice, and grunts at the fence.
- The player's family are miners. The grandparent, an old miner who knew the legends, passed away before the game starts.
- The deepest old mine, where Bucca sleeps, is visible from day one: an engine house on the cliffs just outside the village, its entrance fenced off and sealed. After badge 8 the player returns home for the climax there.

- At the event:
  - Kelyn introduces herself as a professor who studies the old legends, and asks about "the Bucca below" that the miners who sealed Wheal Gwyn spoke of.
  - Nova: "We've got engineers, not piskies! The only spirit down there is team spirit!"
  - Lumen's slogan: "bringing the mines home", with "clean, safe, and modern" mining.

- At the kitchen table:
  - Kelyn says Grampy wrote to her often about the player, hoping they'd see Kernia with Pokémon.
  - Kelyn's starter lines: Fletchling, "the robin. Bold as brass, and loyal with it". Spheal, "a seal pup from the coves. Gentle, but tough". Shinx, "a wildcat cub. Folk say a great beast roams the moor..." (the Beast of Bodmin).
  - The player gets the starter at Lv5, the Pokédex, 5 Poké Balls, and Grampy's Journal from Mum. Kelyn: "There's more to it than stories."

- Nova's first battle (`TRAINER_NOVA_BALWYN`, class Rival, Rich Boy pic): Pawmi Lv5 with Scratch and Growl only. Nova calls the player "local" and plays to the cameras ("And that's how Lumen does it!").
- Kelyn's goodbye invites the player to her lab in Treveur.

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
- No Pokémon Center and no lab; Mum heals the player's team.

## Characters

- Mum: at home; sets the scene in the morning, heals the player's team, and gives them the journal at the kitchen table.
- Cottage (red roof): Old Jacca, a retired miner. He worked Wheal Gwyn with Grampy forty years ago and heard the Knockers tapping down there. Keeper of the legends, against reopening the mine ("some things should stay asleep").
- Neighbour's house (blue roof): Treve, out of work since the last mine shut, first in the queue for Lumen's jobs rather than moving up-country. His daughter Wenna is a Nova fan with a Pawmi plushie she wants signed.
- Professor Kelyn (visiting): sceptical of Lumen. Gives the starter, Pokédex, and Poké Balls, then returns to her lab in Treveur.
- Nova and Lumen's PR team (visiting for the opening). A hi-vis grunt redirects the player to the event, and grunts stay posted at Wheal Gwyn afterwards.
- The Knocker's Arms: Morwenna, the landlady, behind the bar. She explains the pub's name and the miners' custom of leaving pasty crust for the Knockers. A regular at the bar tells how his granfer emigrated overseas when the mines shut (the "Cousin Jacks"), and how the young now leave for up-country.
- Sprites: vanilla Emerald stand-ins (FireRed sprites are invisible in Emerald builds).
  - Old Jacca: `OLD_MAN`. Treve: `MAN_3`. Wenna: `LITTLE_GIRL`. Morwenna: `WOMAN_2`. The regular: `MAN_4`. The road grunt: `DEVON_EMPLOYEE`.
  - Nova: `RICH_BOY`, with Pawmi beside him as `OBJ_EVENT_GFX_SPECIES(PAWMI)`. Kelyn: `EXPERT_F`. The event grunt: `DEVON_EMPLOYEE`.
- The bar counter isn't `MB_COUNTER`, so a `bg_event` on the counter tile in front of Morwenna lets the player talk to her across it.

## Connections

- One route east, Route 1 (`KerniaRoute1`, see `Route1.md`), towards Carnrudh (gym 1, inspired by Camborne / Redruth).

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
- The road leaves the east edge on rows 11–12 and continues onto Route 1 (`right` connection to `MAP_KERNIA_ROUTE1`, offset 0). The two maps share tilesets so the join draws cleanly.
- New-game spawn point (`WarpToTruck` in `src/new_game.c`): (4, 4) in the bedroom, `Balwyn_PlayersHouse_2F`.
- Mine placeholder: an adit (Granite Cave's entrance tile, from Route 106) cut into the cliff at (6, 4), with a gravel apron and a boulder. It sits in a yard in the north-west corner, closed off by the sea to the west, trees to the east, and a picket fence across the front (row 8), with a warning sign outside at (6, 9). The adit tile also has collision set. To open the mine later, remove part of the fence (or replace it with a scripted barrier) and add a warp on the adit. A proper engine house needs custom tiles.

## Open questions

- Kelyn's exact question at the event, and Nova's win and lose lines.
- The knocking: a sound effect, text only ("...knock... knock..."), or both.
- Lumen signs and the site hut: whether vanilla tiles will do or custom tiles are needed.
- Whether the player is referred to by name or gender (Mum is decided: she's "Mum", with `OBJ_EVENT_GFX_MOM`).
- How many other villagers there are beyond the two households (e.g. pub landlord and regulars).
- The starter level (presumably 5), and whether the player's house gets a mailbox.

## Next steps

- Script the opening sequence (see Story). The grunt's block must stop the player leaving for Route 1 before they have a starter: wild battles in Route 1's tall grass start even with an empty party (seen in testing).
