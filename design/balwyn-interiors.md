# Balwyn interiors

## Goal
Give all four Balwyn buildings a walkable interior with working door warps in both directions, so the village is fully explorable. This is the groundwork for the opening sequence: the parent, the journal, and the pub's role as the community hub all need rooms to happen in.

## Context
- `Balwyn` exists (24×24, `gTileset_General` + `gTileset_Dewford`) with no warps, NPCs, or signs. New games spawn outside the player's house at (7, 18) (`WarpToTruck` in `src/new_game.c`).
- Door tiles are already in the layout: the Dewford-style animated door `0x225` at (15, 9), (7, 17), and (17, 17), and the TestTown-style door `0x021` at (19, 9). All have collision 1, the same as vanilla doors, so they only need a warp event on top.
- `TestTown_House1_1F` and `gMapGroup_IndoorTestTown` are the only custom interior precedent. Its 5×5 layout uses the wrong primary tileset (`gTileset_General`), so copy vanilla interiors instead.
- Conventions (CLAUDE.md): interiors go in a new `gMapGroup_IndoorBalwyn`, appended to the end of `group_order` in `data/maps/map_groups.json` and never reordered. Map names are `Balwyn_<Building>`, layouts `<MapName>_Layout`, and every interior uses `MAPSEC_BALWYN`.
- Interiors use `MAP_TYPE_INDOOR`, `WEATHER_NONE`, `MUS_LITTLEROOT`, `show_map_name: false`, and no cycling or escaping, like vanilla Littleroot houses.
- Build: `make -j$(nproc)`. Test manually in mGBA with a **new game** (old saves keep stale map state). After on-disk edits, reload the project in Porymap before saving there.

## Approach
For each building, copy a vanilla interior layout into its own `data/layouts/Balwyn_<X>/` folder, so it can be customised later without touching vanilla maps that share it. Then add a map JSON and an empty `scripts.inc`, and register the map in `layouts.json`, `map_groups.json`, and `data/event_scripts.s`. Warps are paired: the outdoor door warp points at the interior's doormat warp, and the interior's doormat warps (usually two tiles wide) point back at the outdoor door's warp index. Warp indices in `Balwyn/map.json` are positional, so add them in a fixed order and don't reorder them later. Each phase delivers empty rooms that can be walked through; NPCs, dialogue, and furnishing changes belong to the opening-sequence work.

| Building | Outdoor door | Interior map | Copy layout from |
|---|---|---|---|
| Player's house | (7, 17) | `Balwyn_PlayersHouse_1F` / `_2F` | `LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F` / `_2F` (11×9 / 9×8, `gTileset_BrendansMaysHouse`) |
| Neighbour's house | (15, 9) | `Balwyn_House1` | `LAYOUT_HOUSE3` (Dewford House 1, 10×8) |
| Cottage | (19, 9) | `Balwyn_House2` | `LAYOUT_HOUSE4` (Dewford House 2, 10×9) |
| Pub | (17, 17) | `Balwyn_Pub` | `LAYOUT_LILYCOVE_CITY_COVE_LILY_MOTEL_1F` (12×9, reception counter as the bar) |

## Phases

### Phase 1 — Walk into and out of the player's house ✅
**Deliverable:** On a new game, the player walks through the door at (7, 17) into a ground floor and back out onto the step at (7, 18).
**Verify:** `make -j$(nproc)` succeeds. In mGBA, start a new game, enter the house (the door animates), walk around inside, and leave by the doormat. Check that you come out at (7, 18) facing south. Reopen Porymap and check that `Balwyn_PlayersHouse_1F` appears under `gMapGroup_IndoorBalwyn`.
**Work:**
- Add `gMapGroup_IndoorBalwyn` to `map_groups.json` (appended at the end) containing `Balwyn_PlayersHouse_1F`.
- Copy the Brendan 1F blockdata and border into `data/layouts/Balwyn_PlayersHouse_1F/` and add `LAYOUT_BALWYN_PLAYERS_HOUSE_1F` to `layouts.json`.
- Add `data/maps/Balwyn_PlayersHouse_1F/map.json` with doormat warps at (8, 8)/(9, 8) pointing to `MAP_BALWYN` warp 0, plus an empty `scripts.inc`, and include it in `data/event_scripts.s`.
- In `Balwyn/map.json`, add warp 0 at (7, 17) pointing to `MAP_BALWYN_PLAYERS_HOUSE_1F` warp 0.

**Not yet:** the stairs (the vanilla stair tile stays but leads nowhere), the parent NPC, the spawn point change, and the other three buildings.

### Phase 2 — Upstairs bedroom, and new games start in it
**Deliverable:** The player's house has a 2F bedroom reached by the stairs, and a new game starts there instead of outside.
**Verify:** Build. Start a new game: you should appear in the bedroom, walk down the stairs to 1F, back up, then down and out the door. Check that the 1F stair warp lands you on the 2F stairs and the 2F stair warp lands you on the 1F stairs.
**Work:**
- Copy the Brendan 2F layout to `Balwyn_PlayersHouse_2F`, add the map to `gMapGroup_IndoorBalwyn`, and register it as in phase 1.
- Pair the stair warps: 1F (8, 2) ↔ 2F (7, 1).
- Point `WarpToTruck` at `MAP_BALWYN_PLAYERS_HOUSE_2F` (somewhere in the middle of the room, not on furniture). Remove the "temporary" spawn note in `design/Balwyn.md`.

**Not yet:** the bedroom PC, the clock, and any vanilla furniture interactions (the tiles are just decoration with no `bg_events`), and the mailbox.


### Phase 3 — The two neighbours' houses
**Deliverable:** The blue-roof neighbour's house and the red-roof cottage can be walked into and out of.
**Verify:** Build, start a new game, and go in and out of each door at (15, 9) and (19, 9). The cottage's `0x021` door doesn't animate the same way as the others; check that the warp still fires and the player comes out on (19, 10).
**Work:**
- Copy `LAYOUT_HOUSE3` → `Balwyn_House1` and `LAYOUT_HOUSE4` → `Balwyn_House2`, and register both maps.
- Add outdoor warps 1 and 2 at (15, 9) and (19, 9), and the matching doormat warps in each interior.

**Not yet:** who lives there, and whether either house is boarded up or left empty (open question). If one ends up locked, its door gets a script instead of a warp later.

### Phase 4 — The pub
**Deliverable:** The pub at (17, 17) opens into a room with a bar counter.
**Verify:** Build, start a new game, and go in and out of the pub. Check that the counter blocks movement and the room reads as a pub rather than a motel reception. If it doesn't, swap in a different vanilla layout before moving on.
**Work:**
- Copy the Cove Lily Motel 1F layout → `Balwyn_Pub` and register the map.
- Add outdoor warp 3 at (17, 17) and the matching doormat warps.
- Leave the motel's stair tile with no warp event (or swap it for wall/floor) so it isn't a dead end.
- Update `design/Balwyn.md` Map notes: list the interiors and the warp index order, and tick off the "Create the four interiors" next step.

**Not yet:** pub NPCs, bartender dialogue, the pub sign's text (a separate next step), and any custom pub tiles.

## Open questions
- **Is the neighbour's house or the cottage empty or boarded up?** This doesn't block phase 3, but a boarded-up house might have a locked door script instead of a warp.
- **Pub layout fit:** whether the motel reception reads as a bar is only settled by seeing it in-game (phase 4's verify step).

## Rejected alternatives
- **Point the maps at shared vanilla layouts (`LAYOUT_HOUSE3` etc.) instead of copying them:** less work, but any Porymap edit to a Balwyn room would also change every vanilla map using that layout, and the names wouldn't follow the `<MapName>_Layout` convention.
- **Build on `TestTown_House1_1F`:** it's 5×5 with an outdoor primary tileset, and it's due to be retired.
- **Generate interior blockdata by script, like the Balwyn exterior:** vanilla interiors already have correct collision, elevation, and exit tiles. Copying them is faster and less error-prone, and custom furnishing can come later in Porymap.
- **Do all four interiors in one pass:** the first one proves the group, registration, and warp pairing. After that the rest are mechanical, but one mistake in a big batch is harder to find.
