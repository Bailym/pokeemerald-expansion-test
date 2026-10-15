# Carnrudh

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The first gym town, at the east end of Route 1. Gym 1: Tanek, Fire, backs Lumen.
- Name: carn (rocky hill or tor) + rudh (red), "red tor".
- A festival town: its steam-engine day celebrates a local inventor whose engine first ran here. The player arrives while the town is setting up for it.
- Above the town to the north is Carn Kowr, the giant's tor, where Lumen are surveying for a granite quarry. The town's quest happens there, and it has to be done before the gym.

## Inspiration

- Camborne / Redruth: Trevithick Day (a steam-engine parade with dancing), Camborne's old mining school, and Redruth's miners' exchange.
- Carn Kowr is Carn Brea, the hill between the two towns. The real hill has a Neolithic hill enclosure, a castle folly, a granite monument to a mine-owning family, and named giant's boulders (the Giant's Hand, Head, Cradle, and Well).
- The festival's engine is after Trevithick's *Puffing Devil* (1801) and the folk song "Going up Camborne Hill, coming down".

## Story

1. Arrival: the player comes in off Route 1 to a town hanging bunting and polishing engines for steam-engine day. Lumen's job offers are the talk of the town (Tamsin's brother came here for one, see `Route1.md`).
2. The gym is shut. Tanek is up on Carn Kowr with Lumen's survey team, backing their plan for a granite quarry. He believes in the jobs (see Characters).
3. The riddle: Grampy's Journal has a verse about the giant's stones on Carn Kowr. This is the journal's first real use after the opening.
4. Carn Kowr: the player climbs the tor and inspects the giant's stones in the order the verse names them (Hand, Head, Cradle, Well). Inspecting the wrong one resets the order and gives a hint. A Lumen grunt guards each stone, and the player has to beat them to reach it.
5. The proof: the last stone shows that the tor is an ancient monument (a carving or a marking; see Open questions), which gives the locals grounds to stop the quarry.
6. Peran: at the summit, the player battles Peran, Lumen's Chief Engineer, in his first appearance. He's a local and knows the tor. Afterwards he just moves on, letting slip that the granite was never the real prize ("It's not what's on the hill. It's what's under it.").
7. Tanek is shaken but loyal: he's uneasy that Lumen gave up the jobs so easily, but tells himself they'll bring the work somewhere else. This plants the doubt behind his remorse line after Bucca's rampage. He goes back down and opens the gym.
8. Steam-engine day: with the tor saved, the festival runs, and the gym is open.

- Lumen's threat on the tor is purely industrial and in the open. Their real aim stays hidden; the tor only hints that they want something deeper.

## Locations

### Carnrudh

- Pokémon Center and Mart.
- Gym: Tanek's Fire gym, in a restored engine house, with boilers, pistons, and steam vents.
- The miners' school / exchange: an old mining school or miners' exchange hall, with lore about the trade.
- A couple of houses and a pasty shop, for townsfolk lore (the pasty crust ties in with the Knockers custom).
- Before the quest the town is setting up the festival (bunting, engines being polished). Afterwards it's in full swing.

### Carn Kowr

- A separate map north of Carnrudh: the giant's tor, with heath, gorse, and granite.
- The four giant's stones (Hand, Head, Cradle, Well), each guarded by a grunt.
- Lumen's survey on the summit: Peran, the survey kit, and Tanek.
- Early game, so no field moves: the puzzle is the riddle order, not boulders.

## Characters

- Tanek, the Fire gym leader. A local who watched the town die, and backs anything that brings work back, even a quarry on the tor. After Peran walks away he's shaken but stays loyal.
- Peran, Lumen's Chief Engineer (see `DESIGN.md`): first appears on Carn Kowr. The local who sold out. He knows the tor and leads the survey. The player battles him at the summit.
- Lumen grunts: hi-vis survey team, one at each stone.
- Nova: said "see you at the gym" in Balwyn, so Nova is somewhere in Carnrudh (see Open questions).
- Townsfolk: the festival crowd, the miners' school, the pasty shop, and the houses, all with lore lines (folklore, mining heritage, and the divide over Lumen's jobs).

## Connections

- West: Route 1 (`KerniaRoute1`), which comes in on its east edge (rows 11–12, from x 40).
- North: Carn Kowr.
- South-west: a route to gym 2 (St Ives / Penzance).
- East: the road to Treveur, blocked until badge 2.

## Map notes

- Map `Carnrudh` (`MAP_CARNRUDH`), layout `LAYOUT_CARNRUDH` (32×30, `gTileset_General` + `gTileset_Dewford`, the same as Route 1 so the join draws cleanly), region map section `MAPSEC_CARNRUDH`, outdoor maps group `gMapGroup_KerniaTownsAndRoutes`. Interiors are in `gMapGroup_IndoorCarnrudh`.
- Music `MUS_RUSTBORO`, weather `WEATHER_SUNNY`. Border is trees.
- Connections: `left` to `MAP_KERNIA_ROUTE1` (offset 1): the main street (rows 12–13) continues Route 1's road (its rows 11–12).
- Layout (stand-in vanilla buildings until custom art exists), generated by `tools/kernia/gen_carnrudh.py` (re-running it overwrites any Porymap edits):
  - Main street east–west on rows 12–13, ending at x 27 against the trees. The east road to Treveur is reserved in the tree band at x 28–31.
  - North of the street: the gym (Dewford's building, x 5–10, rows 5–9) and its sign at (11, 9), the Pokémon Center (x 18–21, rows 7–10), and the Mart (x 23–26, rows 7–10).
  - The path north to Carn Kowr runs up x 14–15 to the top edge (no connection yet).
  - South of the street: house 1 (x 9–12, rows 16–19), the pasty shop (the red cottage, x 16–19, rows 16–19), the miners' school (the wide house, x 21–25, rows 16–19), and house 2 (x 9–12, rows 21–24).
  - The south-west route's path runs down x 6–7 to the bottom edge (no connection yet).
  - Town sign at (4, 11), at the west entrance.
- Door warps on `Carnrudh` are numbered in the order below. Don't reorder them, because each interior's doormat warps back to that number.

| Warp | Building | Door | Interior map | Layout |
|---|---|---|---|---|
| 0 | Pokémon Center | (19, 10) | `Carnrudh_PokemonCenter_1F` + `_2F` (vanilla's link-club floor) | `LAYOUT_POKEMON_CENTER_1F` / `_2F` |
| 1 | Mart | (24, 10) | `Carnrudh_Mart` | `LAYOUT_MART` |

- The gym, houses, pasty shop, and school doors have no warps yet. Their doors are at the gym (8, 9), house 1 (10, 19), the pasty shop (17, 19), the school (23, 19), and house 2 (10, 24).
- `HEAL_LOCATION_CARNRUDH` is (19, 11), outside the Center's door. The Center sets it as the respawn point.
- The Mart sells Poké Balls, Potions, Antidotes, Paralyze Heals, and Awakenings.
- Carn Kowr: map `CarnKowr` (`MAP_CARN_KOWR`), `MAPSEC_CARN_KOWR`.
- The Route 1 join draws the neighbouring map with the *current* map's tilesets, so Carnrudh should share Route 1's (`gTileset_General` + `gTileset_Dewford`), or keep secondary-tileset blocks away from the west edge.
- Trainer IDs: there's room for only 7 more before the 864 limit (`Route1.md`). The grunts, Peran, the gym's trainers, Tanek, and Carnrudh's trainers will go over that, so `MAX_TRAINERS_COUNT_EMERALD` will need raising (it costs save-block space).

## Open questions

- The inventor's Kernia name, and the festival's name.
- What the proof on the last stone is: a Neolithic carving, a date, or a marking.
- The journal's riddle verse.
- Where Nova is, and whether there's a rival battle in Carnrudh.
- Peran's team and levels, the grunts' teams, and Tanek's team.
- The gym's puzzle and its trainers.
- What blocks the east road to Treveur until badge 2.
- Whether the miners' school has a move tutor or any other function.
- The town's layout and size.

## Next steps

- Plan the build in phases (`design/plans/carnrudh.md`).
