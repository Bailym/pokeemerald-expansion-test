# Playtest scenarios

## Goal
One command opens mGBA with the player already at a chosen point in the story, with fitting flags, team and items, so you can test a phase by hand without replaying from the start or setting flags in the debug menu. "Carnrudh before the festival with a fitting team" becomes `play carnrudh_pre_festival`. The scenarios replace the manual jump table in `design/TestGuide.md`.

## Context
- **mGBA 0.10.5 on Windows** (`C:\Program Files\mGBA\mGBA.exe`), with the repo in WSL2. WSL can start `mGBA.exe` directly (Windows interop), with paths passed through `wslpath -w`.
- `make` writes `pokeemerald.map`, which has the address of every ROM symbol. Patching a ROM byte outside the header doesn't affect any checksum mGBA checks.
- A plain `make` build counts as non-release: `DISABLED_ON_RELEASE` features such as `DEBUG_OVERWORLD_MENU` are on, so the scenario code can use the same guard and stay out of `make release`.
- New games go through `CB2_NewGame` (`src/overworld.c:1941`) → `NewGameInitData` (`src/new_game.c:161`), which resets flags, runs `EventScript_ResetAllMapFlags` and calls `WarpToTruck` (Balwyn 2F bedroom). `RunScriptImmediately` (`src/script.c:362`) runs a script to completion with no field context. `RUN_OVERWORLD_SCRIPT` in tests uses it too, which means scenario scripts can be unit tested.
- Story state is `VAR_BALWYN_STATE` (`0x404E`, `BALWYN_STATE_*`) and `VAR_CARNRUDH_STATE` (`0x4083`, `CARNRUDH_STATE_*`), plus Kernia flags `0x21`–`0x2B`. TestGuide lines 105–110 already list the flag and var combinations for each jump point.

## Approach
- **Scenarios are event scripts** in `data/scripts/debug_scenarios.inc`. They use ordinary macros (`setvar`, `setflag`, `givemon`, `additem`, `setwarp`), and each one `call`s the scenario before it, so the story builds up in a chain.
- **The ROM has one patchable byte.** It holds a `const volatile u8 gBootScenario = SCENARIO_NONE;` in ROM.
- **The copyright screen checks it at boot.** If it's set, the game skips the intro to `CB2_BootScenario`, which sets a default player name and gender (like `src/quickstart.c`) and hands over to the normal `CB2_NewGame`. Right after `NewGameInitData`, `CB2_NewGame` calls `RunScenario(gBootScenario)`. That runs the script, then warps to wherever its `setwarp` pointed, and does nothing when the byte is 0.
- **The launcher does the rest.** `tools/playtest/play.py <scenario>` looks up `gBootScenario` in `pokeemerald.map`, copies the ROM to a play folder on the Windows side, writes the scenario ID into the copy, and starts `mGBA.exe` on it.
- **Benefits:** no rebuild per scenario, no Lua, and the real `pokeemerald.gba` is never touched, so a normal launch still shows the normal intro.

## Phases

### Phase 1 — One command boots into one scenario ✅
*(As built: `CB2_NewGame` is hooked instead of copied, so a scenario boot goes through the same new-game path as normal play. The `.inc` is included with an assembler `.if DEBUG_SCENARIOS`, because the C preprocessor doesn't know `TRUE` in `.s` files. Scenarios end in `return`, which stops the script when it's run directly and works with `call` when they're chained.)*
**Deliverable:** `python3 tools/playtest/play.py balwyn_done` opens mGBA with no intro. The player is outside the house in Balwyn after the opening (`BALWYN_STATE_KNOCKING_HEARD`), with a starter in the party.
**Verify:**
- `make check TESTS="Scenario"`: a new `test/debug_scenarios.c` runs the scenario script with `RunScriptImmediately` and checks the var, the party species and level, and the warp destination.
- `make && python3 tools/playtest/play.py balwyn_done`: mGBA opens in Balwyn's overworld. The debug menu (R+Start → flags/vars) shows `VAR_BALWYN_STATE` = 6.
- Opening `pokeemerald.gba` normally still plays the intro.
- `make release` builds, and `nm` shows no `gBootScenario`.
**Work:**
- `include/config/debug.h`: add `DEBUG_SCENARIOS DISABLED_ON_RELEASE`.
- `include/constants/debug_scenarios.h`: `SCENARIO_NONE`, `SCENARIO_BALWYN_DONE`. The launcher reads names and IDs from this file.
- `src/debug_scenarios.c`: `gBootScenario`, the ID → script table, `CB2_BootScenario` and `RunScenario`.
- `src/intro.c` (`CB2_InitCopyrightScreenAfterBootup`): after the save loads, jump to `CB2_BootScenario` if `gBootScenario` is set.
- `src/overworld.c` (`CB2_NewGame`): call `RunScenario(gBootScenario)` after `NewGameInitData`.
- `data/scripts/debug_scenarios.inc`, included from `data/event_scripts.s`: `DebugScenario_BalwynDone`.
- `tools/playtest/play.py`: name → ID, symbol → ROM offset, copy and patch, launch with `wslpath -w`. `--list` prints the scenarios.
**Not yet:** any Carnrudh scenarios, and docs beyond a `--help`.

### Phase 2 — Carnrudh scenarios
**Deliverable:** Scenarios for every row of the TestGuide jump table, chained from `balwyn_done` to `carnrudh_badge1`, each with a fitting team and items. `carnrudh_pre_festival` is one of them. TestGuide points to the scenarios instead of listing manual flag settings.
**Verify:**
- `make check TESTS="Scenario"`: one test per scenario checks its vars and flags, the party levels within the expected range, and the warp map.
- You load `carnrudh_pre_festival` and one other with `play.py`. Each starts where TestGuide says, with the NPCs and blockers in the right state.
**Work:**
- `data/scripts/debug_scenarios.inc`: `carnrudh_arrived`, `carnrudh_riddle`, `carnrudh_cradle` (gate and peak), `carnrudh_pre_festival`, `carnrudh_gym` (`TOR_DONE`, festival on), `carnrudh_badge1`. Each one `call`s the one before.
- Teams: species from the routes reached so far (`wild_encounters.json`) plus the starter. Levels from the next big fight's `.party` entries (a little under the ace). Default level-up moves unless a fight calls for something.
- `design/TestGuide.md`: replace the jump table with the scenario list and the command to run.
- `tools/playtest/README.md`: how a description ("X, before Y, fitting team") becomes a scenario (flags from the area's design doc, levels from the next fight, keep the chain in story order), and the rule that new story vars or flags get added to the relevant scenario in the same phase.
- Memory note so future sessions know scenarios exist and keep them current.
**Not yet:** a debug menu "Scenarios" entry (the follow-up after this plan).

## Open questions
- ~~**What does "before the festival" mean?**~~ Settled: on the peak before the Peran fight (`STONES_DONE`, the Well drained). `carnrudh_gym` covers the festival being on.
- **Default player:** name `KERNOW` and male, unless you'd rather pick. A scenario could override either.
- **Where does the play folder go?** On the Windows side, e.g. `C:\Users\Baily\AppData\Local\kernia-playtest`, so mGBA isn't loading over `\\wsl.localhost`. Saving in the game writes a `.sav` there, never in the repo. Each launch makes a fresh new game regardless.

## Rejected alternatives
- **Lua bridge that writes the ID at boot:** it needs `--script` on the command line (possibly 0.11-only) or a manual script load each time. Patching the ROM copy needs neither.
- **Picking the scenario at build time (`make SCENARIO=…`):** it means a rebuild for each starting point, and a ROM that's easy to forget is patched.
- **Generating `.sav` files or writing game state into memory:** both are tied to the save layout and checksums, which already changed once for the trainer limit. Running scenarios through the game's own script commands stays correct when the code changes.
- **Claude driving mGBA (button presses, screenshots):** not needed for now. Phase 1 doesn't rule it out later.
