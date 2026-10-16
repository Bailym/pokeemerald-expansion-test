# HM-free field moves

## Goal
Make Kernia's field abilities (Rock Smash, Fly, Cut, Flash, Surf, Strength, Rock Climb, Dive, Waterfall) work for any party once the right badge is won, with no Pokémon needing to know the move, as designed in `design/DESIGN.md` ("Field moves"). Each unlock is signposted by the leader, a system message, and a hint at the obstacle. Fly opens from the Town Map, which Kelyn now gives in Balwyn. The HM moves become ordinary TMs. It comes before Porthliw, whose badge unlocks Fly.

## Context
- **Badge gates already exist:** `gFieldMoveInfo` in `src/field_move.c` gives each move a badge (`.arg`) checked by `IsFieldMoveUnlocked` (`include/field_move.h`), with the locked message `gText_CantUseUntilNewBadge`. Today's badges are vanilla's (Cut 1, Flash 2, Rock Smash 3, Strength 4, Surf 5, Fly 6, Dive 7, Waterfall 8). Rock Climb is off (`OW_ROCK_CLIMB_FIELD_MOVE` in `include/config/overworld.h`) and has no badge.
- **The "a Pokémon must know it" checks:**
  - The `checkfieldmove` script command (`src/scrcmd.c`) finds the first party Pokémon that knows the move and returns its slot in `VAR_RESULT` (`PARTY_SIZE` if none). Its badge check is off by default: only Cut, Rock Smash and Strength pass `TRUE`.
  - Every overworld use goes through it: `data/scripts/field_move_scripts.inc` (Cut tree, Rock Smash rock, Strength boulder, Waterfall, Dive, Rock Climb) and `data/scripts/surf.inc`.
  - Surf has an extra C gate, `PartyHasMonWithSurf` (`src/field_player_avatar.c`), in `src/field_control_avatar.c`, which badge-checks Surf, Waterfall, Dive and Rock Climb before running their scripts.
- **The field effects show a Pokémon:**
  - They read that party slot from `gFieldEffectArguments[0]` (`FldEff_FieldMoveShowMonInit` in `src/field_effect.c`; Strength also takes the nickname).
  - With no Pokémon knowing the move the slot is 6, which reads past the party into the opponent's.
  - Fly already has a skip, `gSkipShowMonAnim`. The others (`CreateFieldMoveTask` in `src/fldeff_rocksmash.c` for Cut, Rock Smash, Strength and Flash, plus Surf, Waterfall, Dive and Rock Climb in `field_effect.c`) need one.
- **Fly without a Pokémon is half-built:**
  - `ITEM_TOWN_MAP` opens `FieldInitRegionMap` (`src/field_region_map.c`), where R on a flyable town flies with `gSkipShowMonAnim` set. That path is behind `OW_FLAG_POKE_RIDER`, which is 0 (off).
  - A destination needs four things: a case in `GetMapsecType` (`src/region_map.c`, via a `FLAG_VISITED_*`), a `sFlyLocations` entry, a `sMapHealLocations` entry, and a place on the region map grid (`src/data/region_map/region_map_layout.h`, with x/y in `region_map_sections.json`).
  - `sMapHealLocations` ends at `MAPSEC_EMBER_SPA`, before the Kernia sections, so they'd read past its end.
  - Kernia has no visited flags, its sections have no x/y, and only Carnrudh has a heal location (`HEAL_LOCATION_CARNRUDH`); Balwyn has none.
- **Flash** has no overworld trigger at all: only the party menu. Dark maps are `"requires_flash": true`, and no Kernia map is dark yet.
- **HMs are their own list:** `FOREACH_HM` in `include/constants/tms_hms.h` drives the HM items (`src/data/items.h`, `ITEM_HM_*`), `IsMoveHM` and the "can't forget" rule (`P_CAN_FORGET_HIDDEN_MOVE`, off), and the HM labels and icons. Teachable learnsets treat TMs and HMs alike, so moving the moves into `FOREACH_TM` (TM52 onward) doesn't change who can learn them. About 52 `ITEM_HM*` references need updating (vanilla maps, FRLG item balls, `test/bag.c`), and `make firered` shares this code.
- **Kernia so far:**
  - Kelyn gives the Pokédex and Poké Balls in `Balwyn_PlayersHouse_1F_EventScript_StarterHandover`, then Mum gives Grampy's Journal.
  - Tanek gives badge 1 in `Carnrudh_Gym_EventScript_TanekDefeated`.
  - The `balwyn_done` story part (`data/scripts/debug_scenarios.inc`) mirrors the starter kit.
  - Breakable rocks are `OBJ_EVENT_GFX_BREAKABLE_ROCK` objects running `EventScript_RockSmash`.
- **Tests:**
  - `RUN_OVERWORLD_SCRIPT` (see `test/kernia_route2.c`) can run scripts and check flags and `VAR_RESULT`. `FIELD_MOVE_*` is a C enum the test asm can't see, so tests need the value exported in `include/test/overworld_script.h` or a C-level check.
  - No test covers field moves yet. Scenario tests (`test/debug_scenarios.c`) cover story state.
- Everything here sits behind one Kernia config switch, so vanilla's behaviour and the FireRed build stay as they are when it's off.

## Approach
A config switch (say `OW_FIELD_MOVES_NEED_NO_MON` in `include/config/overworld.h`, on for Kernia) changes three things:
- **The checks:** `checkfieldmove` and `PartyHasMonWithSurf` succeed when the move's badge is won, whatever the party knows, returning a "no Pokémon" result rather than a slot.
- **The scripts:** the field-move scripts read that result and use the badge-only text ("{PLAYER} smashed the rock!" rather than "{STR_VAR_1} used ROCK SMASH!").
- **The effects:** they skip the show-Pokémon step whenever there's no slot, as Fly already does with `gSkipShowMonAnim`.

Kernia's badges go into `gFieldMoveInfo`. A shared `EventScript_FieldMoveUnlocked` script plays a jingle and prints the system message, and gym leaders call it after their badge line. Each slice is proven first with a Kernia obstacle the player can reach in a scenario. Moves with no Kernia map yet are checked on vanilla maps through the debug menu.

## Phases

### Phase 1 — Smash a rock with no Pokémon that knows Rock Smash ✅
*(As built: `OW_FIELD_MOVES_BADGE_ONLY` (`(!IS_FRLG)`) in `include/config/overworld.h`. Kernia's badges go into `gFieldMoveInfo` through a `FIELD_MOVE_BADGE(kernia, vanilla)` macro. `checkfieldmove` returns `FIELD_MOVE_USER_NONE` (7) for unlocked badge-gated moves whatever the party knows, and `PARTY_SIZE` without the badge even when the script skips the badge check. Always-unlocked moves like Secret Power are unchanged. `EventScript_RockSmash` has a badge-only branch ("Smash it?", the smash sound, then the rock-break movement, skipping the show-Pokémon effect), and the Kernia hint before the badge. The first rock is on Route 2 at (3, 30), guarding a Revive at (3, 29). Its grass patch was moved so the rock isn't on tall grass, and it needs `FLAG_TEMP_11` or it respawns as the camera moves. Four tests in `test/kernia_field_moves.c`, written first. The FireRed build fails, but on master too (the Kernia layouts lack `border_width`); see the open questions.)*
**Deliverable:** With badge 1, the player can break a Kernia rock even though no party Pokémon knows Rock Smash. The prompt asks first, the rock breaks with no Pokémon shown, and the item behind it can be picked up. Without badge 1, the rock hints that a badge would help. The engine change is in place for every move, but only Rock Smash is wired up.
**Verify:**
- `make check TESTS="test/kernia_field_moves.c"`: tests written first pass. With badge 1 and a party without Rock Smash, the Rock Smash check succeeds and reports no Pokémon. Without badge 1 it fails. A Pokémon that does know Rock Smash makes no difference.
- `make check` (full) passes, and `make firered` still builds (switch off there).
- mGBA, `play.py route2_bay` (badge 1, no Pokémon knows Rock Smash): walk to the new rock, say yes, and it breaks cleanly (no garbled sprite, no Pokémon pop-up), and stays broken after a reload. `play.py balwyn_done` (no badge): if the rock is reachable before badge 1, it gives the hint.
**Work:**
- The config switch, and Kernia's badges in `gFieldMoveInfo` (`src/field_move.c`): Rock Smash 1, Fly 2, Cut and Flash 3, Surf 4, Strength 5, Dive 6, Waterfall 8. Rock Climb's badge (5) goes in phase 4.
- `ScrCmd_checkfieldmove` (`src/scrcmd.c`): with the switch on, badge only, for badge-gated moves only (Secret Power and the other always-unlocked ones still need a Pokémon). Return `FIELD_MOVE_USER_NONE` (7, in `include/constants/field_move.h`), not a slot. Until phase 4, the other badge moves' scripts don't handle that result, but none of their badges (3+) can be won yet.
- No field effect change for Rock Smash: its badge-only branch plays the smash sound and goes straight to the rock-break movement, skipping `FLDEFF_USE_ROCK_SMASH` and its show-Pokémon step. (The plan first had `CreateFieldMoveTask` skip it; the script route is smaller.)
- `EventScript_RockSmash` (`data/scripts/field_move_scripts.inc`): the badge-only branch, its prompt text, and the hint before the badge.
- One breakable rock on a built Kernia map (Route 2's beach or lower terraces is easiest to reach in a scenario), hiding an item behind it, with an item flag.
- `test/kernia_field_moves.c`, exporting the field move values to the test asm if needed.

**Not yet:** the unlock cues, the other retrofit rocks, any other move, and the Town Map.

### Phase 2 — Badge 1 tells you about Rock Smash, and pays off
**Deliverable:**
- **The cues:** winning badge 1 now ends with Tanek's Rock Smash line and the system message ("You can now use ROCK SMASH outside of battle!" with a jingle).
- **The rocks:** a few more optional rocks on maps already built (Carn Kowr, Route 1, Route 2) hide items or a shortcut.
**Verify:**
- `make check TESTS="Scenario"` still passes.
- mGBA, `play.py carnrudh_gym`: beat Tanek. Badge, Tanek's lines, then the unlock message with its jingle, then Flame Charge as before. Lose to him once too: nothing new plays.
- With `route2_bay` or `carnrudh_badge1`, break each new rock once. Each item can be taken once, also after a reload.
- Re-run the TestGuide's Carnrudh gym checks, since the scene changed.
**Work:**
- A shared `EventScript_FieldMoveUnlocked` (in `data/scripts/`), taking the move name: the jingle, then the message.
- `Carnrudh_Gym_EventScript_TanekDefeated`: Tanek's line, then the shared script, before Flame Charge.
- 2–3 rocks on Carn Kowr, Route 1 and Route 2, each with an item flag. Each rock needs its own `FLAG_TEMP_*` (unused on that map), as vanilla's do: with flag `0`, `removeobject` doesn't stick and the rock respawns as soon as the camera moves. Re-run `check_levels.py` for maps with levels.
- Docs: each area doc's map notes, `TestGuide.md` (a Rock Smash check per area, and the gym scene).

**Not yet:** Fly, the Town Map, other moves, and HMs as TMs.

### Phase 3 — Fly from the Town Map
**Deliverable:**
- **The Town Map:** Kelyn gives it with the starter kit, and it shows a stand-in region map with Balwyn, Carnrudh and Carn Kowr placed.
- **Flying:** with badge 2, pressing R on a visited town flies there, with no Pokémon shown. Before badge 2 it's only a map.
**Verify:**
- `make check TESTS="Scenario"`: `balwyn_done` and every scenario after it have the Town Map, and the tests check for it.
- `make check TESTS="test/kernia_field_moves.c"`: Fly is unlocked only with badge 2.
- mGBA, a new game: Kelyn's handover gives the Town Map, with the scene otherwise unchanged.
- `play.py route2_bay`: use the Town Map. You see Kernia's towns, and R does nothing.
- Then set badge 2 with the debug menu (R+Start). R on Carnrudh flies there, and on Balwyn flies home. Leaving the map with B returns to the bag, not the party menu.
**Work:**
- `Balwyn_PlayersHouse_1F_EventScript_StarterHandover`: `giveitem ITEM_TOWN_MAP` after the Poké Balls, with a Kelyn line. `DebugScenarioStory_BalwynDone`: `additem ITEM_TOWN_MAP`.
- **A Fly gate:** `OW_FLAG_POKE_RIDER` swapped for (or given) a check that badge 2 is won with the switch on (`src/field_region_map.c`).
- **Visited flags:** `FLAG_VISITED_BALWYN` and `FLAG_VISITED_CARNRUDH` (free flags), set on entering each town (`ON_TRANSITION` map scripts), and in the story parts.
- **Region map wiring:** `GetMapsecType` cases, `sFlyLocations` entries, and `sMapHealLocations` entries for the Kernia sections (fixes the read past the end). Carn Kowr stays a route, not a fly point.
- **A Balwyn heal location** (outside the house; the respawn is home with Mum) in `src/data/heal_locations.json`.
- **The stand-in map:** Kernia's sections placed on a reused vanilla region map image (x/y in `region_map_sections.json`, cells in `region_map_layout.h`). Add the real map to `design/CustomArt.md`.
- Docs: `DESIGN.md`, `Balwyn.md` (the Town Map), TestGuide (the Town Map and Fly).

**Not yet:** Porthliw as a fly point (Porthliw's plan adds its section, visited flag, and Enys's unlock cue), and other moves.

### Phase 4 — Cut, Strength, Surf, Waterfall, Dive and Rock Climb with no Pokémon
**Deliverable:** Every obstacle-based field move works on a party that doesn't know it, once its Kernia badge is won, with the ask-first prompt, no Pokémon shown, and the hint before the badge. This covers cutting a tree, pushing a boulder, surfing from a level-3 shore, climbing a waterfall, diving, and climbing a rock face.
**Verify:**
- `make check TESTS="test/kernia_field_moves.c"`: a test per move. Unlocked only at its Kernia badge, regardless of moves known.
- `make check` (full) passes, and `make firered` builds.
- mGBA, with badges set and a party that knows none of these moves:
  - **Kernia:** Surf off Route 2's beach (badge 4) reaches the offshore Seel rocks, and it's refused before badge 4.
  - **Vanilla maps, via debug warp:** a Cut tree (Route 104), a Strength boulder, a waterfall, a Dive spot (Route 124), and a Rock Climb wall if one exists. Each works with no Pokémon shown and no garbled sprite. Each refuses with the hint before its badge.
**Work:**
- `PartyHasMonWithSurf` (`src/field_player_avatar.c`): badge-only with the switch on.
- The scripts: `EventScript_CutTree`, `EventScript_StrengthBoulder`, `EventScript_UseWaterfall`, `EventScript_UseDive`, `EventScript_UseDiveUnderwater`, `EventScript_UseRockClimb` (`field_move_scripts.inc`), and `EventScript_UseSurf` (`surf.inc`). Each gets badge-only text and hints.
- The effects: skip the show-Pokémon step with no slot in `FldEff_UseSurf`, Waterfall, Dive and Rock Climb (`field_effect.c`). `FldEff_UseStrength` gets badge-only text instead of the nickname.
- Rock Climb: turn on `OW_ROCK_CLIMB_FIELD_MOVE` and gate it on badge 5.
- Flash, as settled by the open question below.

**Not yet:** HMs as TMs, and unlock cues for badges 3–8 (each gym's own plan adds its leader's line and the shared message).

### Phase 5 — HM moves become ordinary TMs
**Deliverable:** No HM discs exist. Cut, Fly, Surf, Strength, Flash, Rock Smash, Waterfall and Dive are TM52–TM59, shown and used like any TM, and any move can be forgotten.
**Verify:**
- `make check` (full) passes, with `test/bag.c` updated for the new TM items.
- `make` and `make firered` both build.
- mGBA, with the debug menu's give-item: a TM Surf shows as a TM in the bag (TM icon, "TM5x" label), teaches a Pokémon that can learn Surf, and the Pokémon can then forget Surf (e.g. by learning a new move at level-up).
**Work:**
- `include/constants/tms_hms.h`: the eight moves move from `FOREACH_HM` to the end of `FOREACH_TM` (`FOREACH_HM` empty). Make sure an empty list still compiles in `include/item.h` and `src/item.c`.
- `src/data/items.h`: the `ITEM_HM_*` entries become `ITEM_TM_*` (replacing the `ITEM_TM52`–`59` placeholders), with TM prices and descriptions.
- Every `ITEM_HM*` reference (vanilla map scripts, FRLG item balls, `test/bag.c`, `test/random_mon_generator.h`) moves to the TM names.
- `P_CAN_FORGET_HIDDEN_MOVE` set to `TRUE`.
- `DESIGN.md`: where each new TM is found, left to the areas that place them.

**Not yet:** placing the new TMs in Kernia (each area's plan), and the real region map art.

## Open questions
- **The FireRed build** is broken on master: none of the Kernia layouts have the `border_width` field FireRed's mapjson needs. Until it's fixed or dropped, the phases' "`make firered` still builds" checks can't pass. Decide whether Kernia keeps FireRed building (a small separate fix) or is Emerald-only (drop those checks).
- **Flash with no Pokémon:** there's no overworld trigger to hang it on. Three options:
  - Dark maps light up on entry once badge 3 is won.
  - Entering a dark map asks "Light the way?".
  - It's left until Kernia has a dark map.

  Settle by phase 4. No Kernia map is dark yet.
- **The stand-in region map image:** which vanilla map to reuse, and where Balwyn, Carnrudh and Carn Kowr sit on it. Settle at the start of phase 3. Rendering a couple of candidates would help.
- **Where the retrofit rocks go**, and what they hide (an item, a shortcut, a hidden cove). Settle at the start of phase 2.
- **Balwyn's fly point:** outside the player's house, or by the village sign. Settle in phase 3.
- **Unlock cues for badges 3–8:** each gym's plan adds its leader's line. The shared script and message come from phase 2.

## Rejected alternatives
- **Classic HMs, or forgettable HMs:** the user chose badge-only unlocks, with no Pokémon needed and no HM slaves.
- **Story unlocks (a miner's pick, a boat lift):** more scenes to write; badges keep it simple and predictable.
- **Showing the lead Pokémon in the animation:** the user chose no Pokémon shown, which also avoids picking a slot for a Pokémon that can't learn the move.
- **Fly from a start-menu entry or a key item:** the Town Map already has a fly-on-R path, and the user chose it.
- **Fly at badge 3 to give time for a real region map:** a stand-in map keeps Fly with Enys's Flying badge.
- **Hard-coding the change with no config switch:** a switch keeps vanilla and FireRed unchanged and makes the change easy to review.
