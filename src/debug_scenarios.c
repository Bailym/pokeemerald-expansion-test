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
extern const u8 DebugScenario_CarnrudhArrived[];
extern const u8 DebugScenario_CarnrudhRiddle[];
extern const u8 DebugScenario_CarnrudhCradle[];
extern const u8 DebugScenario_CarnrudhWell[];
extern const u8 DebugScenario_CarnrudhTorDone[];
extern const u8 DebugScenario_CarnrudhGym[];
extern const u8 DebugScenario_CarnrudhBadge1[];
extern const u8 DebugScenario_Route2Summit[];
extern const u8 DebugScenario_Route2Bay[];
extern const u8 DebugScenario_PorthliwArrived[];
extern const u8 DebugScenario_PorthliwMetEnys[];
extern const u8 DebugScenario_PorthliwOpeningDone[];

// play.py writes a scenario ID into this byte in a copy of the ROM. Volatile stops the compiler
// folding in SCENARIO_NONE, so the patched value is what the game actually reads.
const volatile u8 gBootScenario = SCENARIO_NONE;

static const u8 *const sScenarioScripts[SCENARIOS_COUNT] =
{
    [SCENARIO_BALWYN_DONE]           = DebugScenario_BalwynDone,
    [SCENARIO_CARNRUDH_ARRIVED]      = DebugScenario_CarnrudhArrived,
    [SCENARIO_CARNRUDH_RIDDLE]       = DebugScenario_CarnrudhRiddle,
    [SCENARIO_CARNRUDH_CRADLE]       = DebugScenario_CarnrudhCradle,
    [SCENARIO_CARNRUDH_WELL]         = DebugScenario_CarnrudhWell,
    [SCENARIO_CARNRUDH_TOR_DONE]     = DebugScenario_CarnrudhTorDone,
    [SCENARIO_CARNRUDH_GYM]          = DebugScenario_CarnrudhGym,
    [SCENARIO_CARNRUDH_BADGE1]       = DebugScenario_CarnrudhBadge1,
    [SCENARIO_ROUTE2_SUMMIT]         = DebugScenario_Route2Summit,
    [SCENARIO_ROUTE2_BAY]            = DebugScenario_Route2Bay,
    [SCENARIO_PORTHLIW_ARRIVED]      = DebugScenario_PorthliwArrived,
    [SCENARIO_PORTHLIW_MET_ENYS]     = DebugScenario_PorthliwMetEnys,
    [SCENARIO_PORTHLIW_OPENING_DONE] = DebugScenario_PorthliwOpeningDone,
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

// A scenario's Pokémon stand in for ones the player caught early and raised. Gen 8+ obedience
// goes by the level a Pokémon was met at, so giving them at their full level would make them
// disobey before enough badges.
#define SCENARIO_MET_LEVEL 5

static void MakeScenarioPartyObey(void)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 metLevel = GetMonData(mon, MON_DATA_MET_LEVEL);
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && metLevel > SCENARIO_MET_LEVEL)
        {
            metLevel = SCENARIO_MET_LEVEL;
            SetMonData(mon, MON_DATA_MET_LEVEL, &metLevel);
        }
    }
}

// Runs on top of NewGameInitData: the scenario script sets the story state and calls setwarp,
// then the player is moved there in place of the new game's bedroom.
void RunScenario(u32 scenario)
{
    if (scenario == SCENARIO_NONE || scenario >= SCENARIOS_COUNT)
        return;

    RunScriptImmediately(sScenarioScripts[scenario]);
    MakeScenarioPartyObey();
    WarpIntoMap();
}

#endif // DEBUG_SCENARIOS
