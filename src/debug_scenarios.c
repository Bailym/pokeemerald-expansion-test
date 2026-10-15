#include "global.h"
#include "debug_scenarios.h"
#include "main.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"

#if DEBUG_SCENARIOS

extern const u8 DebugScenario_BalwynDone[];

// play.py writes a scenario ID into this byte in a copy of the ROM. Volatile stops the compiler
// folding in SCENARIO_NONE, so the patched value is what the game actually reads.
const volatile u8 gBootScenario = SCENARIO_NONE;

static const u8 *const sScenarioScripts[SCENARIOS_COUNT] =
{
    [SCENARIO_BALWYN_DONE] = DebugScenario_BalwynDone,
};

// Called in place of the intro once the copyright screen has faded out; CB2_NewGame then runs
// the scenario. Mirrors CB2_SkipToNewGame in src/quickstart.c.
void CB2_BootScenario(void)
{
    static const u8 sText_PlayerName[] = _("KERNOW");

    if (UpdatePaletteFade())
        return;

    gSaveBlock2Ptr->playerGender = MALE;
    StringCopy_PlayerName(gSaveBlock2Ptr->playerName, sText_PlayerName);
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetTasks();
    SetMainCallback2(CB2_NewGame);
}

// Runs on top of NewGameInitData: the scenario script sets the story state and calls setwarp,
// then the player is moved there in place of the new game's bedroom.
void RunScenario(u32 scenario)
{
    if (scenario == SCENARIO_NONE || scenario >= SCENARIOS_COUNT)
        return;

    RunScriptImmediately(sScenarioScripts[scenario]);
    WarpIntoMap();
}

#endif // DEBUG_SCENARIOS
