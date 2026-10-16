#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "party_menu.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("Route 2's old bull Seel is a lone Lv12 Seel with Mystic Water, Ice Body and Aqua Jet")
{
    struct Pokemon *actualSeel = &gParties[B_TRAINER_OPPONENT_A][0];

    // A Pokémon left over in the enemy party from an earlier battle mustn't join the wild battle.
    RUN_OVERWORLD_SCRIPT(
        createmon 1, 1, SPECIES_WOBBUFFET, 5;
        call KerniaRoute2_EventScript_SetUpOldBullSeal;
    );

    const enum Species expectedSpecies = SPECIES_SEEL;
    const u32 expectedLevel = 12;
    const enum Item expectedItem = ITEM_MYSTIC_WATER;
    const enum Ability expectedAbility = ABILITY_ICE_BODY;
    const enum Species expectedSecondSlot = SPECIES_NONE;
    enum Species actualSpecies = GetMonData(actualSeel, MON_DATA_SPECIES);
    u32 actualLevel = GetMonData(actualSeel, MON_DATA_LEVEL);
    enum Item actualItem = GetMonData(actualSeel, MON_DATA_HELD_ITEM);
    enum Ability actualAbility = GetMonAbility(actualSeel);
    enum Species actualSecondSlot = GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_SPECIES);

    EXPECT_EQ(actualSpecies, expectedSpecies);
    EXPECT_EQ(actualLevel, expectedLevel);
    EXPECT_EQ(actualItem, expectedItem);
    EXPECT_EQ(actualAbility, expectedAbility);
    EXPECT(MonKnowsMove(actualSeel, MOVE_AQUA_JET));
    EXPECT_EQ(actualSecondSlot, expectedSecondSlot);
}

TEST("Catching Route 2's old bull Seel hides it and remembers the catch")
{
    gBattleOutcome = B_OUTCOME_CAUGHT;

    RUN_OVERWORLD_SCRIPT(
        call KerniaRoute2_EventScript_RecordOldBullOutcome;
    );

    EXPECT(FlagGet(FLAG_HIDE_KERNIA_ROUTE2_OLD_BULL));
    EXPECT(FlagGet(FLAG_CAUGHT_KERNIA_ROUTE2_SEEL));
}

TEST("Beating or running from Route 2's old bull Seel hides it without a catch")
{
    u32 outcome;
    PARAMETRIZE { outcome = B_OUTCOME_WON; }
    PARAMETRIZE { outcome = B_OUTCOME_RAN; }
    gBattleOutcome = outcome;

    RUN_OVERWORLD_SCRIPT(
        call KerniaRoute2_EventScript_RecordOldBullOutcome;
    );

    EXPECT(FlagGet(FLAG_HIDE_KERNIA_ROUTE2_OLD_BULL));
    EXPECT(!FlagGet(FLAG_CAUGHT_KERNIA_ROUTE2_SEEL));
}
