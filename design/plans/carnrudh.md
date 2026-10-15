# Carnrudh

## Goal
Build Carnrudh, the first gym town, and Carn Kowr, the tor above it, as designed in `design/Carnrudh.md`. The player arrives off Route 1, finds the gym shut, climbs Carn Kowr and solves Grampy's Journal's riddle of the giant's stones, beats Lumen's grunts and Peran, then takes on Tanek for badge 1. This is the game's first full town, with the first Pokémon Center, Mart, gym, and badge.

## Context
- Route 1's east edge has the sand road on rows 11–12 (from x 40), ready for a `right` connection (`design/Route1.md`). Route 1 uses `gTileset_General` + `gTileset_Dewford`, and the game draws the neighbouring map across a connection with the *current* map's tilesets. So Carnrudh should share them, or keep secondary-tileset blocks away from its west edge.
- Pokémon Center and Mart exteriors are in `gTileset_General`, and Dewford's gym exterior is in `gTileset_Dewford`, so a stand-in town needs no new tiles. Check this against a render in phase 1. The engine-house gym exterior needs custom tiles (not in this plan).
- Interiors use the shared vanilla layouts: `LAYOUT_POKEMON_CENTER_1F` / `_2F` and `LAYOUT_MART` (see `OldaleTown_PokemonCenter_1F`: `setrespawn HEAL_LOCATION_*` in `ON_TRANSITION`, nurse via `Common_EventScript_PkmnCenterNurse`). Heal locations are in `src/data/heal_locations.json`. Gym pattern: `RustboroCity_Gym/scripts.inc` (`setflag FLAG_BADGE01_GET`, `giveitem` the TM).
- **Trainer limit:** IDs 855–857 are taken (Jory, Tamsin, Nova), and `TRAINERS_COUNT_EMERALD` is 858 of `MAX_TRAINERS_COUNT_EMERALD` 864, so only 6 are free. Trainer flags run from `TRAINER_FLAGS_START` (0x500) and `SYSTEM_FLAGS` follows straight after, so raising the limit shifts every system flag (new game needed) and grows the flags array in the save. This plan needs at least 4 grunts + Peran + Tanek + 2 gym trainers = 8.
- **Grampy's Journal** (`ITEM_GRAMPYS_JOURNAL`) is a key item with `ItemUseOutOfBattle_CannotUse`, so it can't be read from the Bag yet.
- **Story state:** follows Balwyn's pattern, a single `VAR_CARNRUDH_STATE` with `CARNRUDH_STATE_*` values in story order (`include/constants/vars.h`), plus `FLAG_HIDE_*` flags for objects that come and go.
- Naming per CLAUDE.md: `Carnrudh` / `MAP_CARNRUDH` / `LAYOUT_CARNRUDH` / `MAPSEC_CARNRUDH` in `gMapGroup_KerniaTownsAndRoutes`; `CarnKowr` / `MAP_CARN_KOWR` (the climb) and `CarnKowr_Peak` / `MAP_CARN_KOWR_PEAK` (the summit), both in `MAPSEC_CARN_KOWR`; interiors (`Carnrudh_PokemonCenter_1F`, `Carnrudh_Mart`, `Carnrudh_Gym`, …) in a new `gMapGroup_IndoorCarnrudh` appended to the end of `group_order`.
- Maps, scripts, and dialogue are tested by hand in mGBA with a new game (CLAUDE.md). Give yourself Pokémon with the debug menu (R+Start), and warp straight to Carnrudh to skip the opening.

## Approach
Same as Balwyn and Route 1: generate the exterior layouts by script, copying vanilla block patterns so collision and elevation are right, render them to PNG for review, then fine-tune in Porymap. Phase 1 makes Carnrudh a working stop (arrive, heal, shop). Each later phase adds one step of the story, in the order the player meets it. A new `VAR_CARNRUDH_STATE` moves from "arrived" through "riddle read", "stones done", and "tor done" to "badge won", and the town's map scripts read it to show or hide the gym blocker, the tor cast, and the festival. The riddle runs on its own progress var, so a wrong stone can reset it. The trainer limit gets raised in its own step at the start of phase 4, before any new IDs go in, so a save or flag problem shows up on its own.

## Phases

### Phase 1 — Arrive in Carnrudh, heal, and shop ✅
**Deliverable:** The player walks east off Route 1 into Carnrudh with a "CARNRUDH" popup and no seam at the join. They can heal at the Pokémon Center, use the PC, buy from the Mart, and white out back to Carnrudh's Center.
**Verify:** `make -j$(nproc)` succeeds. In mGBA, start a new game and warp to Route 1 (debug menu), then walk east along rows 11–12. Check the following:
- The popup appears, and there are no garbled tiles either side of the join.
- The Center nurse heals, and the PC works.
- The Mart sells early stock.
- Losing a battle (debug: a weak Pokémon in the grass on Route 1) returns you to Carnrudh's Center.
- The west branch, the east road, and the north path are bounded (trees or fences), so you can't walk off the map.

Reopen Porymap and check that both connections show.
**Work:**
- Script `data/layouts/Carnrudh/map.bin` + `border.bin` with `gTileset_General` + `gTileset_Dewford`. Its height and offset line Route 1's road up with the town's main street. Lay out the Center, the Mart, a stand-in gym building (Dewford's), and spaces for the miners' school, two houses, and the pasty shop, plus a path north towards Carn Kowr and edges reserved for the south-west route and the east road. Render to PNG and review.
- `layouts.json`, `data/maps/Carnrudh/map.json` (`MAP_TYPE_CITY`, town music such as `MUS_RUSTBORO`, `MAPSEC_CARNRUDH`), `scripts.inc`, `event_scripts.s` include, and the group entry. Add `MAPSEC_CARNRUDH` to the region map sections.
- Connections: Route 1 `right` → `MAP_CARNRUDH`, Carnrudh `left` → `MAP_KERNIA_ROUTE1`, with matching offsets.
- `Carnrudh_PokemonCenter_1F` / `_2F` and `Carnrudh_Mart` using the shared layouts, in the new `gMapGroup_IndoorCarnrudh`. Add `HEAL_LOCATION_CARNRUDH` and `setrespawn`. The Mart gets an early stock (Poké Balls, Potions, Antidotes, Paralyze Heals).
- A town sign. Fill in `design/Carnrudh.md`'s map notes and warp table. Update `design/Route1.md`'s connection notes.

**Not yet:** the other buildings' doors (no warps), the gym interior, Carn Kowr, story state, townsfolk, the festival, and fly (it needs a badge and a region map anyway).

### Phase 2 — The gym is shut; climb to Carn Kowr's peak
**Deliverable:** The gym door is blocked, with a line saying Tanek is up on Carn Kowr with Lumen. The path north leads up Carn Kowr's climb, a walkable heath tor with three of the giant's stones, and on to the peak, where the fourth stone (the Well) sits by Lumen's survey camp with Peran and Tanek (talk-only for now).
**Verify:** Build, start a new game, and warp to Carnrudh. Check the following:
- Try the gym door: you're turned back with the "Tanek's on the tor" line.
- Walk north onto the climb ("CARN KOWR" popup, no seam), up onto the peak (no seam), and back down to town.
- Tall grass on the climb gives wild battles. The peak has none.
- Each of the four stones can be inspected and has a placeholder description.
- On the peak, Peran and Tanek each have a line.

**Work:**
- Add `VAR_CARNRUDH_STATE` and `CARNRUDH_STATE_*` (`ARRIVED` first) in `vars.h`, in an unused var slot.
- Gym blocker in Carnrudh (an NPC or a sign in the doorway), shown or hidden by state.
- Generate both layouts with scripts in `tools/kernia/`, sharing Carnrudh's tilesets so both joins draw cleanly:
  - `CarnKowr`: heath and granite outcrops, with a path winding up from the town to a gap at the top edge. The Hand, Head, and Cradle are `bg_event`s along it, placed so the path doesn't visit them in riddle order.
  - `CarnKowr_Peak`: the summit, with the Well (`bg_event`), a survey camp and drill site beside it, and stand-ins for the castle folly and monument if vanilla tiles fit.
- Maps, layouts, `MAPSEC_CARN_KOWR`, and the `up`/`down` connections (Carnrudh ↔ climb ↔ peak). Wild encounters only on the climb (`gCarnKowr`, early levels, a slightly different table from Route 1).
- Peak objects: Peran (stand-in sprite), Tanek (stand-in sprite), and survey kit. Hidden with `FLAG_HIDE_*` once the tor is done.
- Record the tor in `design/Carnrudh.md`.

**Not yet:** the riddle and stone order, the peak's gate, the grunts, battles, and the proof.

### Phase 3 — The journal's riddle of the stones
**Deliverable:** On reaching Carn Kowr, the player opens Grampy's Journal and reads a verse naming the stones in order. A grunt at the top of the climb keeps the player off the peak until the Hand, Head, and Cradle are done in order. Then the Well on the peak completes the riddle and shows the proof that the tor is an ancient monument. A wrong stone resets the order with a hint pointing back to the verse.
**Verify:** Build, start a new game, and warp to Carnrudh. Check the following:
- The journal scene plays once on first entering Carn Kowr.
- Inspecting the stones in the wrong order (e.g. Head first) gives the hint and resets.
- The grunt at the top of the climb turns you back until Hand → Head → Cradle are done, then lets you through.
- The Well on the peak completes the riddle and shows the proof text.
- Afterwards the stones have "done" lines, and leaving and re-entering keeps it solved.
- The verse can be re-read (see Work).

**Work:**
- A scripted journal reading (`ON_FRAME` or a trigger at the tor's entrance) that moves the state to `RIDDLE_READ`, plus a way to read it again. The simplest is a line at the first stone, or a trigger.
- A progress var for the stone order, with each stone's script checking and advancing it, or resetting it with the hint. On the last stone (the Well), move to `STONES_DONE`.
- The peak's gate: a grunt (not a trainer yet) at the top of the climb, who stands aside once the first three stones are done.
- Write the verse and the proof text (see Open questions), in Grampy's voice and following DESIGN.md's lore and brevity rules.

**Not yet:** grunts guarding the stones, Peran, and the gym opening. Reading the journal from the Bag is not part of this plan (see Rejected alternatives).

### Phase 4 — Beat Lumen's grunts and Peran
**Deliverable:** A grunt guards each stone on the climb and battles the player before the stone can be inspected, and the gate grunt battles the player before letting them onto the peak. After the riddle, Peran battles the player on the peak, then walks off with his "it's what's under it" line. Tanek is left shaken but loyal and heads down to the gym, and the gym blocker is gone.
**Verify:** First, after raising the trainer limit: `make -j$(nproc)` and `make check` both pass. In mGBA, start a new game and check that the opening still works (the Balwyn states and Nova's battle). Then, with a Pokémon from the debug menu, check the following:
- Each grunt spots you and battles, and you can't reach their stone (or the peak) until they're beaten. They stay beaten after a reload.
- Peran only engages once the Well is done, and battles at a level a starter can beat.
- After the battle, Peran and Tanek's scene plays and they leave the peak.
- Back in town, the gym door is open.

**Work:**
- Raise `MAX_TRAINERS_COUNT_EMERALD` (e.g. 864 → 896) in `opponents.h`, and update the overflow note. Confirm that the build's save-size asserts still pass, and note the system-flag shift in `design/Carnrudh.md`.
- Four grunt trainers and Peran in `opponents.h` and `src/data/trainers.party` (levels 5–8, see Open questions). Three guard the stones on the climb, and the fourth replaces phase 3's gate grunt at the top of the climb. Trainer object events with sight lines that cover each approach. `trainerbattle_single` scripts in Lumen's PR voice, with lore lines.
- Peran's battle and the walk-off scene (`applymovement`, `removeobject`, set the tor-cast hide flag), Tanek's line, and the state set to `TOR_DONE`. Hide the gym blocker based on state.
- Record the trainers in `design/Carnrudh.md`.

**Not yet:** the gym interior, the festival, and Peran's later appearances.

### Phase 5 — Tanek's gym and badge 1
**Deliverable:** The player enters Tanek's gym, beats its trainers and Tanek, and gets badge 1 and a Fire TM. The gym's trainers and Tanek have post-battle lines, and Tanek's includes the "shaken but loyal" doubt.
**Verify:** Build and start a new game. Get to `TOR_DONE` (play through, or use debug to set the var and flags), then check the following:
- Enter the gym and beat its trainers and Tanek.
- The badge appears on the trainer card, and the TM is in the bag.
- Talking to Tanek again gives the post-battle line, not a rematch, and this survives a reload.

**Work:**
- `Carnrudh_Gym`: a stand-in interior copied from a vanilla gym layout (a boiler-room look as close as vanilla tiles allow), with its door warp from the town.
- Two gym trainers and Tanek (Fire, levels ~8–12, see Open questions) in `opponents.h`/`trainers.party`, using the leader class and a stand-in sprite.
- Gym script: Tanek's intro, defeat, `setflag FLAG_BADGE01_GET`, `giveitem` a Fire TM (e.g. Incinerate or Flame Charge), post-battle lines, and the state set to `BADGE_WON`. Gym statue lines that change with the badge.
- Record the gym in `design/Carnrudh.md`.

**Not yet:** a gym puzzle (the trainers are simply placed in a line for now), the engine-house exterior and custom tiles, and Nova in Carnrudh.

### Phase 6 — Townsfolk and steam-engine day
**Deliverable:** Carnrudh feels lived in. The miners' school, two houses, and the pasty shop open, and each townsperson has lore-rich lines that change once the tor is saved. After the tor is done the festival is visibly on: crowds, an engine on show, and festival lines.
**Verify:** Build and start a new game. Before `TOR_DONE`, talk to everyone in town and in each interior. Each line fits the lore rule (dialect, one to three short pages, nothing running off the box), and the town is clearly preparing for the festival. Then set `TOR_DONE` (play through or debug) and check that the festival NPCs have appeared and the lines have changed.
**Work:**
- Interiors for the miners' school, two houses, and the pasty shop, copied from vanilla interiors, with door warps.
- Townsfolk object events and scripts with "before" and "festival" lines, chosen by state. Townsfolk cover folklore, mining heritage, Lumen's jobs (Tamsin's brother), and the inventor.
- Festival dressing: extra NPCs and an engine on show, shown with `FLAG_HIDE_*` flags. `setmetatile` for bunting or stalls if vanilla tiles fit.
- Record the characters and festival in `design/Carnrudh.md`.

**Not yet:** custom art (engine house, Peran, Tanek), the south-west route and the east-road blocker's story, and Nova.

## Open questions
- **The riddle verse and the proof** (needed for phase 3): what the last stone shows (a Neolithic carving, a date, or a marking). I can draft the verse for review.
- **Levels** (needed for phase 4): grunts 5–7, Peran ~8, gym trainers ~8–10, and Tanek ~11–12 is a guess. Decide against Route 1's levels (2–5) and Nova's Lv5.
- **The inventor's and festival's names** (needed for phase 6, and for any town signs before that).
- **Nova:** said "see you at the gym", so where is Nova in Carnrudh, and is there a battle? It doesn't block any phase. It can slot into phase 5 or 6 once it's decided.
- **The gym puzzle:** left out of phase 5. A boiler-room puzzle (e.g. steam vents or valves) could be its own later phase.
- **The east-road blocker and the south-west route:** phase 1 only reserves their edges.

## Rejected alternatives
- **Reusing vanilla Hoenn trainer IDs instead of raising the limit:** the vanilla maps still build and reference them, so renaming them means touching unrelated scripts. Raising the limit once is cleaner, and new games are expected at this stage anyway.
- **Making Grampy's Journal readable from the Bag now:** it's a feature for the whole game (every revealed location), not just Carnrudh. A scripted reading on the tor keeps this plan self-contained, and the Bag version can come later and reuse the verse.
- **Building the gym first:** it's the payoff, but it's blocked in the story until the tor is done, so building it first means testing it through debug flags. Building in story order lets each phase be played straight through.
- **Carn Kowr as one map:** the climb (puzzle and trainers) and the peak (the camp, Peran, and the scene) do different jobs. Two maps keep each smaller to generate and review, let the peak's scene scripts run only there, and make reaching the summit feel like arriving somewhere.
- **All four stones on the climb:** simpler, but the proof and Peran's battle would happen apart. With the Well beside the drill site, the proof turns up under Peran's nose and leads straight into the battle.
- **Riddle and grunts in one phase:** the stone-order logic is the riskiest script. Getting it right without trainer sight lines in the way keeps each one easier to debug.
