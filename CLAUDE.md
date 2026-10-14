# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`pokeemerald-expansion` (RHH) is a GBA ROM hack base built on pret's `pokeemerald` decompilation. It is C (gnu17) compiled with the modern `arm-none-eabi-gcc` toolchain, plus ARM assembly/macro scripts and many data files that are converted into C headers at build time. It also supports building FireRed/LeafGreen variants from the same source.

## Commands

```sh
make -j$(nproc)                  # Build pokeemerald.gba (Emerald)
make firered -j$(nproc)          # Build FireRed variant (also: leafgreen); objects go to build/<name>/
make debug -j$(nproc)            # -Og -g build for debugging
make release -j$(nproc)          # Optimized build, NDEBUG, LTO (see config.mk)
make clean                       # Full clean (tools, generated files, assets)
make tidy                        # Remove build outputs only (faster rebuild than clean)
make clean-generated             # Delete auto-generated headers so they regenerate

make check -j$(nproc)                       # Run the full test suite headlessly in mgba-rom-test
make check TESTS="Stun Spore"               # Run tests whose name starts with / contains the string, or by filename
make pokeemerald-test.elf TESTS="Spikes"    # Build a test ELF to open in mGBA and watch tests run
```

`TESTS` must use double quotes. The build prints EWRAM/IWRAM/ROM usage at link time; watch those when adding data.

## Architecture

### Generated files — edit the source, not the output
Many headers are produced by the build and are gitignored. Editing them directly is lost on the next build:

| Edit this | Generates | Via |
|---|---|---|
| `src/data/*.party`, `test/battle/*.party` | matching `.h` (e.g. `src/data/trainers.h`) | `tools/trainerproc` (`trainer_rules.mk`) |
| `src/data/wild_encounters.json` | `src/data/wild_encounters.h`, `include/constants/wild_encounter.h` | `tools/wild_encounters/*.py` |
| `data/maps/*/map.json`, `data/layouts/` | map `.inc` files, `include/constants/map_groups.h`, `layouts.h`, `map_event_ids.h` | `tools/mapjson` (`map_data_rules.mk`) |
| `data/script_cmd_table.inc` | `include/constants/script_commands.h` | `tools/misc/make_scr_cmd_constants.py` |
| `all_learnables.json` + `tools/learnset_helpers` | `src/data/pokemon/teachable_learnsets.h`, `src/data/tutor_moves.h` | Python learnset helpers |
| heal locations / region map JSON | corresponding `.h` | `tools/jsonproc` (`json_data_rules.mk`) |

Graphics (`.png` → `.4bpp`/`.gbapal`/`.smol`/`.lz`) are converted by `tools/gbagfx` and `tools/compresSmol` per `graphics_file_rules.mk`; source files reference the converted paths via `INCBIN`.

### Configuration
Feature toggles live in `include/config/*.h` (`battle.h`, `pokemon.h`, `overworld.h`, `general.h`, `ai.h`, `debug.h`, …). Many mechanics are generation-selectable with values like `GEN_3`…`GEN_9`, defaulting to `GEN_LATEST` (defined in `include/config/general.h`). Code branches on these with `B_*`/`P_*`/`OW_*` macros, so behavior changes should usually respect the relevant config rather than hardcode one generation. `include/config/test.h` overrides settings for the test build (`TESTING=1`).

### Game data is table-driven
- Species: `src/data/pokemon/species_info/gen_N_families.h` (one `gSpeciesInfo` entry per species/form, including graphics, evolutions, learnsets pointers); level-up learnsets in `src/data/pokemon/level_up_learnsets/`.
- Moves: `src/data/moves_info.h` (`gMovesInfo`). Each move has an `.effect` (`EFFECT_*`), which maps through `src/data/battle_move_effects.h` (`gBattleMoveEffects`) to a battle script in `data/battle_scripts_1.s`.
- Abilities, items, hold effects, types: `src/data/abilities.h`, `items.h`, `hold_effects.h`, `types_info.h`.
- Access data through getter functions (e.g. `GetMoveEffect(move)`) rather than indexing tables directly when a getter exists.

### Battle engine
Battle flow is driven by `src/battle_main.c`, which runs battle scripts (assembled macros in `data/battle_scripts_*.s`, macros in `asm/macros/battle_script.inc`) whose commands are implemented in `src/battle_script_commands.c`. Logic is split across `battle_util.c`, `battle_move_resolution.c`, `battle_end_turn.c`, `battle_switch_in.c`, `battle_stat_change.c`, `battle_hold_effects.c`, and gimmick files (`battle_terastal.c`, `battle_dynamax.c`, `battle_z_move.c`, `battle_gimmick.c`). Per-battler input/output goes through controllers (`battle_controller_*.c`). Trainer AI is in `battle_ai_*.c` (see `docs/tutorials/ai_*.md`).

### Overworld scripts and maps
Event scripts are assembler macro files (`data/scripts/`, `data/maps/<Map>/scripts.inc`) using macros from `asm/macros/event.inc`, assembled after the C preprocessor and `tools/preproc` (which handles string encoding via `charmap.txt`).

### Tests
Tests are C files under `test/` built into a separate ROM and run in `mgba-rom-test` (in parallel via `mgba-rom-test-hydra`). Battle tests use `SINGLE_BATTLE_TEST`/`DOUBLE_BATTLE_TEST` with `GIVEN` / `WHEN` / `SCENE` blocks and an `ASSUMPTIONS` block that skips (rather than fails) tests when a hacker has changed underlying data. The runner rigs RNG so moves hit, don't crit, and always proc secondary effects unless specified. Full guide: `docs/tutorials/how_to_testing_system.md`. Test-only trainers live in `test/battle/trainer_control.party`.

## Conventions (from `docs/STYLEGUIDE.md`)
- `PascalCase` functions and structs, `camelCase` variables/fields, `g` prefix for globals, `s` prefix for statics, `CAPS_WITH_UNDERSCORES` for macros/constants.
- 4 spaces in `.c`/`.h`; tabs in `.s` and `.inc` files.
- Braces on their own line (Allman); `switch` cases aligned with the `switch`.
- Comments explain *why*, are capitalized, and end with a period.

### Map naming (custom maps in this hack)
Mostly vanilla's naming, but towns and cities are just their name, with no `Town`/`City` suffix:
- Towns and cities: `<Name>` (PascalCase), e.g. `Balwyn` → `MAP_BALWYN`. Routes: `KerniaRoute<N>` → `MAP_KERNIA_ROUTE<N>`, layout `LAYOUT_KERNIA_ROUTE<N>` (plain `MAP_ROUTE<N>`/`LAYOUT_ROUTE<N>` are taken by FireRed's routes 1–25 and Emerald's 101–134; FireRed map IDs mostly have no `_FRLG` suffix even though their folders do). The in-game name stays "ROUTE <N>" via `MAPSEC_ROUTE_<N>`.
- Interiors: prefixed with their town, `_` between parts, floors as `_1F`/`_B1F` (e.g. `Balwyn_PlayersHouse_1F`, `Balwyn_Pub`).
- Layouts: `<MapName>_Layout` → `LAYOUT_<NAME>`. Region map sections: `MAPSEC_<NAME>` (e.g. `MAPSEC_BALWYN`).
- Groups: Kernia's outdoor maps go in `gMapGroup_KerniaTownsAndRoutes`; each town's interiors get their own `gMapGroup_Indoor<Name>` (e.g. `gMapGroup_IndoorBalwyn`). Append new groups to the end of `group_order` in `data/maps/map_groups.json`, never reorder (group numbers are saved data). The early test maps (`TestTown`, `TestRoute`) predate this and sit in `gMapGroup_MyTownsAndRoutes`.
- No `_Frlg` suffix; that marks FireRed/LeafGreen maps only.
- Renaming a map also means updating its layout, constants, and any references (e.g. the new-game spawn point).

### Testing approach (this hack)
Use TDD (failing test first, then implement) where it's straightforward and worthwhile; don't force it otherwise.
- Good fit: battle mechanics (moves, abilities, items, config changes) via `SINGLE_BATTLE_TEST`/`DOUBLE_BATTLE_TEST`, C logic via `TEST`, script commands via `RUN_OVERWORLD_SCRIPT`.
- Poor fit, test manually in mGBA instead (R+Start opens the debug menu): maps, layouts, warps, NPC placement, graphics/UI, and map scripts with dialogue — the test runner doesn't load maps or simulate input.
- Iterate with `make check TESTS="..."`; run the full `make check` before committing mechanic changes.

## Contributing upstream
PRs to RHH target `master` only for bug fixes present on master, docs-only, or tests-only changes; everything else targets `upcoming` (`CONTRIBUTING.md`). Version migration scripts for downstream hacks are in `migration_scripts/`.
