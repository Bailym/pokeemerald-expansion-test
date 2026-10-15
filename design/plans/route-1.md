# Route 1

## Goal
Build the first route east out of Balwyn: a walkable moorland lane with wild Pokémon, a couple of items, and the first trainers. This gives the player somewhere to go after the opening and somewhere to catch their first Pokémon. The road continues towards Carnrudh, the first gym town (inspired by Camborne / Redruth), which will connect at the route's east end once it exists. Once the route is in, TestTown and TestRoute have no remaining purpose and can be retired.

## Context
- `Balwyn` (24×24, `gTileset_General` + `gTileset_Dewford`, `MAP_TYPE_TOWN`, no connections yet) has its road leaving the east edge on rows 11–12 (`design/Balwyn.md`).
- **Connections and tilesets:** the game draws the strip of the neighbouring map visible across a connection using the *current* map's tilesets. So Route 1 should share Balwyn's tilesets (`gTileset_General` + `gTileset_Dewford`). If it can't, it at least needs to keep secondary-tileset blocks away from the shared edge, or the seam shows garbage. Grass, trees, ledges, paths, sea, and cliffs are all primary (`gTileset_General`); verified IDs are in Claude's memory notes from the Balwyn build.
- **Naming:** map `KerniaRoute1` → `MAP_KERNIA_ROUTE1`, layout `LAYOUT_KERNIA_ROUTE1` (`KerniaRoute1_Layout`), in `gMapGroup_KerniaTownsAndRoutes`. Plain `MAP_ROUTE1` / `LAYOUT_ROUTE1` belong to FireRed's Route 1, whose folder is `Route1_Frlg` but whose IDs have no suffix. This was discovered when phase 1's first build failed; see CLAUDE.md for the rule. FireRed's `MAPSEC_ROUTE_1` ("ROUTE 1") already exists and can supply the name popup.
- **Precedent:** `TestRoute` has a working connection (to TestTown, `"direction": "down"`) and a wild encounter entry in `src/data/wild_encounters.json` (`base_label` `gTestRoute`, 12 `land_mons` slots).
- **Trainers:** IDs are `#define`d in `include/constants/opponents.h`, with parties in `src/data/trainers.party`. Emerald uses 855 of `MAX_TRAINERS_COUNT_EMERALD` 864, so there's room for 9 new trainers before that limit needs raising (which costs save-block space).
- **Items:** item balls and hidden items need a `FLAG_ITEM_*` / hidden-item flag each, taken from unused flag slots in `include/constants/flags.h`.
- **No starter yet:** there's no opening sequence, so the player can walk onto the route with an empty party. Testing encounters and trainers needs a Pokémon from the debug menu (R+Start). Blocking the exit until the starter is received is the opening sequence's job.
- Maps are tested by hand in mGBA with a **new game**. After on-disk edits, reload the project in Porymap before saving there.
- **Real-world inspiration:** the West Penwith moors east of St Just: a lane between hedges and drystone walls across gorse and heather, with old engine houses on the skyline.

## Approach
Generate the layout by script (as with Balwyn's exterior), copying vanilla block patterns so collision and elevation are right. Render it to PNG to check before handing over, then fine-tune in Porymap. Route 1 is 24 tiles tall so the road lines up with Balwyn's rows 11–12 at offset 0, and about 40–50 tiles wide. Balwyn gets a `right` connection to `MAP_KERNIA_ROUTE1`, and Route 1 gets a matching `left` connection back. Each later phase adds one kind of content on top of the walkable lane: grass and encounters, then items and a sign, then trainers. The last phase removes the test maps. The route's own decisions go in a new `design/Route1.md`, mirroring `design/Balwyn.md`.

## Phases

### Phase 1 — Walk from Balwyn onto Route 1 and back ✅
**Deliverable:** The player walks east off Balwyn along the road, onto Route 1 with a "ROUTE 1" popup, along a lane to the east edge, and back into Balwyn with a "BALWYN" popup. Both maps scroll seamlessly across the join.
**Verify:** `make -j$(nproc)` succeeds. In mGBA, start a new game, leave the house, and walk east along rows 11–12. Check the following:
- The popup appears on crossing, and there's no visible seam or garbled tiles on either side of the join.
- The lane is bounded so you can't walk off it into trees or onto the map edge.
- The road ends at the east edge.
- Walking back west returns you to Balwyn.

Reopen Porymap and check that the connection shows on both maps.
**Work:**
- Script `data/layouts/KerniaRoute1/map.bin` + `border.bin` (48×24): Balwyn's sand road continues as a hedged lane for 10 tiles, then a grass corridor winds north, south, and north through woodland, and the sand road resumes at the east edge (rows 11–12). The cliff and the sea carry on from Balwyn before giving way to trees, and the border is trees. The sand path tileset has no corner pieces, so the bends are grass. Render to PNG and review. Trees use vanilla's edge tiles (trunk tile `0x1E4`/`0x1E5` for the last tree above walkable ground, crown tips `0x1CE`/`0x1CF` above), because the dense-forest bottom tile draws over the player. Balwyn's trees beside its road got the same fix.
- Add `LAYOUT_KERNIA_ROUTE1` to `layouts.json`, `data/maps/KerniaRoute1/map.json` (`MAP_TYPE_ROUTE`, `MUS_ROUTE101`, `WEATHER_SUNNY`, `MAPSEC_ROUTE_1`, `show_map_name: true`), an empty `scripts.inc` and its include in `data/event_scripts.s`, and `KerniaRoute1` appended to `gMapGroup_KerniaTownsAndRoutes`.
- Add connections: Balwyn `right` → `MAP_KERNIA_ROUTE1` (offset 0) and Route 1 `left` → `MAP_BALWYN` (offset 0).
- Start `design/Route1.md` (overview, inspiration, map notes). In `design/Balwyn.md`, update the connection notes.

**Not yet:** tall grass and wild Pokémon, items, signs, trainers, ledges, the town at the east end (the road just stops at the map edge), and any custom tiles (engine houses).

### Phase 2 — Tall grass and wild Pokémon ✅
*Partly checked in-game: one wild encounter, triggered with an empty party, which the game allowed. The full species and level check is still to do.*

**Deliverable:** Tall-grass patches along the route trigger wild battles with early-game Pokémon at levels 2–4. Grass outside the patches never does.
**Verify:** Build, start a new game, and give yourself a Pokémon from the debug menu (R+Start). Walk around in the tall grass until you've had several battles. Check that every species is on the table and the levels are between 2 and 4. Walk the lane and short grass for a while and check that no battles happen.
**Work:**
- Add tall-grass patches to the layout: at least one the lane forces you through, and others to the side for players who want to train. Re-render and review.
- Add a `MAP_KERNIA_ROUTE1` entry to `src/data/wild_encounters.json` (`base_label` `gKerniaRoute1`, 12 `land_mons` slots, encounter rate ~20 like Route 101) using the agreed species list (see Open questions).
- Record the encounter table in `design/Route1.md`.

**Not yet:** water/fishing encounters, Overworld (visible) Pokémon (moor-only by design), and per-time-of-day tables.

### Phase 3 — Route sign, items, and a ledge shortcut ✅
**Deliverable:** A route sign at the Balwyn end, a visible item ball and a hidden item to find, and a one-way ledge that lets the player hop back towards Balwyn quickly.
**Verify:** Build and start a new game, then check each of these:
- Read the sign.
- Pick up the item ball. Leave and re-enter the map, and check that it doesn't come back.
- Find the hidden item by pressing A on its tile. Check that it only gives the item once.
- Check that the ledge can be jumped down but not climbed back up.

**Work:**
- Sign `bg_event` and text in `KerniaRoute1/scripts.inc`, naming the gym town if that's been decided (see Open questions).
- Item ball object event and hidden item `bg_event`, using new item and hidden-item flags from unused slots in `flags.h`. Early items such as a Potion and Poké Balls.
- Add ledge blocks to the layout.

**Not yet:** berry trees and lore landmarks (the journal tie-ins come later).

### Phase 4 — First trainers ✅
**Deliverable:** Two trainers on the route spot the player, walk up, battle, and stay defeated afterwards.
**Verify:** Build, start a new game, and give yourself a Pokémon (debug menu). Walk into each trainer's line of sight and check that they spot you (the "!" appears), walk to you, and battle with the parties in `trainers.party`. After winning, talk to them again and check you get the post-battle line, not a second battle. Then reload the save and check that they're still defeated.
**Work:**
- Add two new `TRAINER_*` IDs in `opponents.h` (bumping `TRAINERS_COUNT_EMERALD`), and their parties (levels 3–5) in `src/data/trainers.party`. Trainer names must be ≤10 characters, Cornish-flavoured for locals (DESIGN.md).
- Add trainer object events (trainer type, sight range) and `trainerbattle_single` scripts with intro, defeat, and post-battle text in `KerniaRoute1/scripts.inc`.
- Record the trainers in `design/Route1.md`.

**Not yet:** rematches, Match Call, double battles, and any Lumen-themed trainers (they can come once the opening sequence introduces Lumen).

### Phase 5 — Retire TestTown and TestRoute ✅
*The groups were deleted, not kept as placeholders. Kernia's groups each moved up by two (Balwyn's is now 75), so start a new game. `FLAG_RECEIVED_TEST_TOWN_POKEMON` went back to `FLAG_UNUSED_0x020`, and the test town's popup-style entries were removed from `src/map_name_popup.c`.*
**Deliverable:** The test maps are gone, and the game builds and plays exactly as before.
**Verify:** `make clean-generated && make -j$(nproc)` succeeds. Check that `grep -rn "TEST_TOWN\|TEST_ROUTE\|TestTown\|TestRoute" data src include` finds nothing. Start a new game and walk Balwyn → Route 1 → back. Check that Porymap opens the project with no missing-map errors.
**Work:**
- Remove `TestTown`, `TestTown_House1_1F`, and `TestRoute`: their map and layout folders, `layouts.json` entries, `event_scripts.s` includes, the `gTestRoute` encounter entry, and the `MAPSEC_TEST_TOWN` / `MAPSEC_TEST_ROUTE` sections.
- Handle their map groups (`gMapGroup_MyTownsAndRoutes`, `gMapGroup_IndoorTestTown`); see Open questions.
- Update CLAUDE.md's map-naming note about the early test maps, and remove the "Retire TestTown…" step from `design/Balwyn.md`.

**Not yet:** n/a. This is the final cleanup.

## Open questions
- **Route length and shape:** 40–50 tiles wide is a guess for a first route. Adjust after walking it in phase 1.

## Rejected alternatives
- **Grow TestRoute into Route 1:** its connection goes down to TestTown, it uses the Petalburg secondary tileset (seam risk with Balwyn), and its encounter table is a grab-bag including Dialga. Starting clean is less work than unpicking it.
- **A new `MAPSEC_KERNIA_ROUTE_1`:** it would duplicate FireRed's existing "ROUTE 1" section for no gain. A Kernia region map doesn't exist yet, so map positions don't matter.
- **Hand-drawing the layout in Porymap from scratch:** fine for tweaks, but the scripted build with a PNG preview worked well for Balwyn, keeps collision correct, and lets the first pass be reviewed before you open Porymap.
- **Wild encounters and trainers in phase 1:** both need a Pokémon to test and design decisions (species, levels) that phase 1 doesn't. Keeping the walkable lane separate proves the connection on its own.
