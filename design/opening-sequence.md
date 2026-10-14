# Opening sequence

## Goal
Script Balwyn's opening as recorded in the Story section of `design/Balwyn.md`:
- A slow-burn morning in the village.
- A Lumen grunt who stops the player heading east and sends them to Wheal Gwyn.
- The reopening announcement.
- The kitchen-table scene with the starter, Pokédex, Poké Balls, and journal.
- Nova's first battle.
- A village that has visibly changed afterwards, with the first knocking.

It turns Balwyn from an empty set into the game's first act, and closes the hole where the player can reach Route 1 without a Pokémon.

## Context
- **Maps exist:** `Balwyn` (exterior, Wheal Gwyn yard in the north-west with its fence on row 8 and warning sign at (6, 9)), `Balwyn_PlayersHouse_1F`/`_2F`, `Balwyn_House1` (blue roof), `Balwyn_House2` (cottage), and `Balwyn_Pub`. New games start in the 2F bedroom (`WarpToTruck` in `src/new_game.c`). Balwyn's road leaves east on rows 11–12 into `KerniaRoute1`.
- **No NPCs or story state yet.** All map scripts are empty apart from the two signs.
- **Story state:**
  - One var drives the opening: rename `VAR_UNUSED_0x404E` (in `include/constants/vars.h`) to something like `VAR_BALWYN_STATE`, with values from "morning" through "knocking heard".
  - Objects that appear or disappear (Nova, Kelyn, the crowd, grunts, the Poké Balls on the table) use `FLAG_HIDE_BALWYN_*` flags renamed from unused flags (`FLAG_UNUSED_0x021` onward). Their initial hidden state is set in `EventScript_ResetAllMapFlags` (`data/scripts/new_game.inc`), as vanilla does.
- **Engine pieces available:**
  - Map scripts: `ON_FRAME` / `ON_LOAD` / `ON_TRANSITION` tables, `coord_events` with var conditions, `applymovement`, and `setmetatile`.
  - `trainerbattle_earlyrival` (FireRed's Oak's Lab rival battle) continues the story whether the player wins or loses, with text for both outcomes.
  - FireRed's Oak's Lab (`PalletTown_ProfessorOaksLab_Frlg/scripts.inc`) has a "Poké Balls on a table" starter choice using `showmonpic` + yes/no + `givemon`.
  - Birch's Pokédex scene has the Pokédex unlock (`setflag FLAG_SYS_POKEDEX_GET`, `special SetUnlockedPokedexFlags`).
  - `Common_EventScript_OutOfCenterPartyHeal` is Mum's heal.
- **The journal** is a new key item: a constant at the end of the item enum (before `ITEMS_COUNT` in `include/constants/items.h`) and a `gItemsInfo` entry in `src/data/items.h` (pocket `POCKET_KEY_ITEMS`), borrowing the Old Sea Map's icon until it gets its own.
- **Nova's trainer** uses one of the 7 free trainer slots (`opponents.h`), with Pawmi Lv5 and Normal-type moves only (moves set explicitly in `trainers.party`).
- **Sprites:** vanilla stand-ins (decided).
  - Mum: `OBJ_EVENT_GFX_MOM` (her actual sprite, not a stand-in).
  - Nova: a polished trainer sprite, e.g. a Beauty or Lass.
  - Kelyn: a Scientist or an older man.
  - The grunts: `OBJ_EVENT_GFX_DEVON_EMPLOYEE`, a corporate company man. `OBJ_EVENT_GFX_WORKER_M` was tried, but FireRed-only sprites have no graphics in Emerald builds (they're inside `#if IS_FRLG` in `object_event_graphics_info_pointers.h`), so the grunt was invisible.
  - Pick stand-ins from the Emerald part of that table (before its `#if IS_FRLG`).
- **Lore rule** (`design/DESIGN.md`): every villager line tells part of Kernia's story, in light Cornish dialect, kept to one to three short pages.
- **Testing:** opening scripts are maps and dialogue, so they're tested by hand in mGBA (CLAUDE.md). The journal item is plain data and fits a `TEST` (TDD). Use mGBA save states at each phase's start to avoid replaying from a new game, and the debug menu (R+Start) to set the story var or flags when jumping ahead.

## Approach
`VAR_BALWYN_STATE` is the spine. Each scene is triggered by an `ON_FRAME` map script or a `coord_event` that checks the var, plays the scene, and advances it. Object visibility follows the hide flags, so each map shows the right cast for the current state. Scripts and text live in each map's `scripts.inc`. The phases follow the story's order because each scene's trigger depends on the previous one's state. The first phase also proves the var, flag, and trigger setup and immediately closes the empty-party hole. The villagers' "before" lore comes early, so the slow-burn village exists before the event interrupts it, and the "after" state comes last.

## Phases

### Phase 1 — Morning scene and the east-road block ✅
**Deliverable:** On a new game, Mum sets the scene the first time you come downstairs. You can roam Balwyn freely, but walking east on the road gets you stopped by a hi-vis Lumen grunt, who sends you to the event at Wheal Gwyn and turns you back. You can't reach Route 1.
**Verify:**
- `make -j$(nproc)` succeeds.
- Start a new game and go downstairs. Mum walks over and delivers the morning lines, only once (go up and down again to check).
- Walk east along rows 11–12. The grunt intercepts you before the map edge on either row, says their line, and you end up back west.
- Repeat it: it happens every time.
- Talking to Mum again gives a repeatable line.

**Work:**
- Rename `VAR_UNUSED_0x404E` → `VAR_BALWYN_STATE`, with its values documented next to it.
- Rename the first hide flags (the grunt) and set them in `EventScript_ResetAllMapFlags`.
- `Balwyn_PlayersHouse_1F`: a Mum object event and an `ON_FRAME` morning scene (state 0 → 1), plus her repeatable line.
- `Balwyn`: a grunt object event near the east exit and `coord_events` on the road (rows 11–12) that fire while the state is below "has starter". The grunt walks up, delivers the line, and the player is moved back west.

**Not yet:** the event itself (the grunt just points you to the mine), other villagers, and the starter.

### Phase 2 — The villagers before the event ✅
*Each villager has one plain script for now. The state branch is added in phase 6, when there are "after" lines to branch to.*
**Deliverable:** Balwyn feels lived in. The retired miner in the cottage, the young family in the blue house (dad and kid), and the pub landlord and a regular each have lore-rich "before" lines about the legends, the closed mines, and the Lumen visit.
**Verify:** Build, start a new game, and talk to every villager. Each line fits the lore rule (dialect, one to three short pages, nothing running off the box). The miner and the dad clearly sit on opposite sides of the Lumen divide.
**Work:**
- Object events and scripts in `Balwyn_House2` (miner), `Balwyn_House1` (dad, kid), and `Balwyn_Pub` (landlord, regular). Possibly one outdoor villager in `Balwyn`.
- Each villager's script branches on `VAR_BALWYN_STATE` from the start, with the after-event branch left for phase 6.
- Record the villagers (names, sides, key lore) in `design/Balwyn.md` Characters.

**Not yet:** "after" lines, villagers at the event, and visible village changes.

### Phase 3 — The Wheal Gwyn event
**Deliverable:** After the grunt sends you, walking up to the crowd at the Wheal Gwyn fence plays the announcement:
- Nova, with Pawmi, announces that Lumen is reopening Wheal Gwyn.
- The dad and the old miner react aloud.
- Kelyn asks their question about the legends, and Nova laughs it off.
- Kelyn walks you home, ending with you inside the house.

**Verify:** Build and start a new game, or load the phase 1 save state. Get turned back by the grunt, then walk to the mine. The crowd is visible only once the grunt has spoken to you, the scene plays through with sensible movement (no one walking through walls), and it ends with you in `Balwyn_PlayersHouse_1F` with the state advanced. Re-entering Balwyn doesn't replay it.
**Work:**
- Hide flags for the event cast (Nova, Kelyn, the dad and the miner at the event, extra grunts).
- A `coord_event` or object trigger in front of the fence.
- The cutscene script with movements and text, in `Balwyn/scripts.inc`.
- The grunt's line from phase 1 sets the state that reveals the crowd.
- Event music: a vanilla track.

**Not yet:** the starter (the scene ends at your door), the villagers' "after" lines, and the site hut and signs.

### Phase 4 — Kitchen table: starter, Pokédex, Poké Balls, and journal
**Deliverable:** Arriving home after the event, Kelyn and Mum are at the table:
- You choose Fletchling, Spheal, or Shinx from three Poké Balls.
- You receive the Pokédex and five Poké Balls.
- Mum hands over the grandparent's journal (a key item), and Kelyn recognises it.
- Mum now heals your team on request.

**Verify:**
- `make check TESTS="Journal"`: a new `TEST` checks the journal is a key item (`POCKET_KEY_ITEMS`, importance set). Write it first and watch it fail before adding the item.
- In mGBA, from a save state at the start of this phase:
  - Pick each starter in turn (reload between picks) and confirm the species and level.
  - Check that Pokédex is in the start menu, the Poké Balls are in the bag, and the journal is in Key Items with its description.
  - Talk to Mum and check that your team is healed.

**Work:**
- Journal item constant and `gItemsInfo` entry, plus its test in `test/`.
- `Balwyn_PlayersHouse_1F`:
  - Kelyn object and three Poké Ball objects on the table, shown by state.
  - An `ON_FRAME` scene, with each ball's script following FireRed's Oak's Lab pattern (`showmonpic`, yes/no, `givemon`) and hiding the balls once one is chosen.
  - The Pokédex unlock, `additem ITEM_POKE_BALL, 5`, the journal, and the state advance.
  - Mum's heal (`Common_EventScript_OutOfCenterPartyHeal`).
- The grunt's road block now lets you past (it checks "has starter"), or is hidden.

**Not yet:** Nova's battle (leaving the house is uneventful until phase 5), and Kelyn leaving town.

### Phase 5 — Nova's battle and the send-off
**Deliverable:** Stepping outside after the kitchen scene:
- Nova challenges you, with Pawmi Lv5 using Normal moves only.
- Win or lose, Nova has a line for that outcome, and the story continues.
- Nova heads east for Carnrudh, and Kelyn heads east for Truro, both walking off.
- You're free to leave Balwyn for Route 1.

**Verify:** Build, then from a save state before leaving the house:
- Win the battle and check Nova's win line plays.
- Reload, lose deliberately, and check the lose line plays, there's no whiteout to the house, and the scene continues.
- Both leave, and Route 1 is reachable.
- Re-entering Balwyn doesn't replay the scene.

**Work:**
- `TRAINER_NOVA_*` in `opponents.h` and its party in `trainers.party`, with explicit Normal-only moves.
- An `ON_FRAME` or `coord_event` scene outside the house door in `Balwyn`, using `trainerbattle_earlyrival` and win/lose text.
- Nova and Kelyn exit movements, then hide their flags and advance the state.
- Record Nova's first team in `design/Balwyn.md`.

**Not yet:** the village's "after" state and the knocking.

### Phase 6 — Balwyn afterwards, and the first knocking
**Deliverable:**
- Every villager has an "after" line reacting to the announcement.
- Wheal Gwyn visibly changes: grunts posted at the fence, Lumen signs, a site hut, and a "WHEAL GWYN REOPENS" notice.
- The first time you walk past the mine fence after the battle, you hear faint knocking, once.

**Verify:** Build, then from a save state after phase 5:
- Talk to every villager and check each has new text.
- Look at the yard: the grunts, signs, and hut are there, while on a fresh new game they're absent.
- Walk along the fence: the knocking plays once, and doesn't play again on a second pass or after re-entering the map.

**Work:**
- The "after" branches in every villager script.
- Posted grunts at Wheal Gwyn (shown by state, with lore lines in Lumen's PR voice).
- An `ON_LOAD` script in `Balwyn` that `setmetatile`s the site hut and signs into the yard once the state says so, with their sign `bg_events`.
- A `coord_event` along the fence for the knocking (sound and/or text, per the open question) that advances the state.
- Update `design/Balwyn.md` (tick the opening off Next steps).

**Not yet:** custom art (Nova, Kelyn, grunts, hut), and Balwyn's mid-game and endgame states.

## Open questions
- **Story var values:** settled in phase 1 as named constants `BALWYN_STATE_*` (0–6) at the end of `include/constants/vars.h`. Renumbering them is safe before release, so later phases can insert states.
- **The knocking (phase 6):** a sound effect, text only, or both. Vanilla has no knock sound, so candidates like `SE_DOOR` or `SE_BANG` need trying in-game.
- **Site hut and Lumen signs (phase 6):** whether vanilla tiles that fit `gTileset_General` + `gTileset_Dewford` will do, or custom tiles are needed. A render of candidates would settle it.
- **Starter level** (presumably 5, matching Nova's Pawmi), **Kelyn's exact question**, and **Nova's win and lose lines.** Draft them in phases 3 and 5 and review them in-game.
- **How the grunt turns the player back:** phase 1 walks them two tiles west. Change it if it feels wrong in-game.

## Rejected alternatives
- **Birch's bag starter screen (`ChooseStarter` / `src/starter_choose.c`):** it shows Birch's bag graphic with fixed Hoenn starters, and doesn't fit a kitchen table. FireRed's "balls on a table" pattern is pure scripting.
- **One phase per map:** the story's scenes cross maps (the event ends with you home, and the kitchen leads outside to Nova). Slicing by scene keeps each phase playable end to end.
- **Villagers last:** the slow-burn feel depends on them, and their scripts need the state branch from the start. Adding them early means every later phase is tested in a lived-in village.
- **A normal trainer battle for Nova:** losing would white out and send you home mid-scene. `trainerbattle_earlyrival` exists for exactly this.
