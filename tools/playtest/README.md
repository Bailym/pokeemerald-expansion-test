# Playtest scenarios

Boot mGBA straight into a point in the story, for testing by hand.

```sh
make
python3 tools/playtest/play.py --list
python3 tools/playtest/play.py carnrudh_pre_festival
```

With no scenario, `play.py` shows a numbered list to pick from. In VS Code, run the **Play scenario** task (Terminal → Run Task), which builds first and then asks.

`play.py` copies `pokeemerald.gba` to `%LOCALAPPDATA%\kernia-playtest\<scenario>.gba`, writes the scenario's ID into that copy's `gBootScenario` byte (found through `pokeemerald.map`), and opens mGBA on it. The game skips the intro, starts a new game as KERNOW, runs the scenario script, and warps there. The real ROM is untouched. Set `MGBA` if mGBA isn't at `C:\Program Files\mGBA\mGBA.exe`.

- Each launch deletes that scenario's old `.sav`, so it always starts fresh. Saving in the game is fine.
- Soft-resetting the copy runs the scenario again.
- Scenarios are on in plain and debug builds and off in `make release` (`DEBUG_SCENARIOS` in `include/config/debug.h`).

## How it fits together

| File | What's there |
|---|---|
| `data/scripts/debug_scenarios.inc` | Story parts (`DebugScenarioStory_*`) and scenarios (`DebugScenario_*`) |
| `include/constants/debug_scenarios.h` | `SCENARIO_*` IDs; `play.py` reads the names from here |
| `src/debug_scenarios.c` | ID → script table, the boot hook and `RunScenario` |
| `test/debug_scenarios.c` | One test per scenario: story state, team levels, start tile |

A **story part** sets only flags, vars, trainer flags and story items, and `call`s the part before it, so the story builds up in order. A **scenario** calls one story part, then gives a team and consumables, and ends with `setwarp`. Everything ends with `return`.

## Adding a scenario

Say the request is "X, before Y, with a fitting team".

1. **Story state.** Read the area's design doc and map scripts for every `setvar`, `setflag`/`clearflag`, trainer battle and `giveitem` between the last story part and the new point. Copy what the real scripts do, including hide flags for NPCs who appear or leave, and add it as a new story part that calls the previous one.
2. **Trainers.** `settrainerflag` every trainer the player has to beat to get there. Leave optional trainers unbeaten.
3. **Team.** Use the starter (Spheal) plus species from encounter tables of areas already reached (`src/data/wild_encounters.json`). Choose levels for the next big fight in `src/data/trainers.party`: the strongest Pokémon at that trainer's ace level up to two above, and nothing more than three below the ace. Default level-up moves unless a fight needs something.
4. **Start tile.** Choose a walkable tile with no object on it, next to what's being tested and off any trigger that would fire at once (unless that's the point). Check the collision bits in the layout's `map.bin` if unsure.
5. **Wire it up.** Add a `SCENARIO_*` ID (bump `SCENARIOS_COUNT`), its table entry and `extern` in `src/debug_scenarios.c`, and a test. Add the fight's ace level to the constants at the top of the test file, because the test build has its own trainer table.
6. **Docs.** Add a row to the Shortcuts table in `design/TestGuide.md`.

When a phase adds new story vars or flags, update the matching story part in the same phase so the later scenarios stay true to the game.
