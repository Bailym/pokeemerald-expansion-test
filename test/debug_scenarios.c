#include "global.h"
#include "test/test.h"
#include "debug_scenarios.h"
#include "event_data.h"
#include "item.h"
#include "new_game.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/vars.h"

// Each scenario runs on top of a fresh new game, the same as when play.py boots one.
static void StartScenario(u32 scenario)
{
    NewGameInitData();
    RunScenario(scenario);
}

TEST("Scenario balwyn_done: the Balwyn opening is finished")
{
    StartScenario(SCENARIO_BALWYN_DONE);

    const u32 expectedBalwynState = BALWYN_STATE_KNOCKING_HEARD;
    const u32 actualBalwynState = VarGet(VAR_BALWYN_STATE);
    EXPECT_EQ(actualBalwynState, expectedBalwynState);
    EXPECT(FlagGet(FLAG_SYS_POKEMON_GET));
    EXPECT(FlagGet(FLAG_SYS_POKEDEX_GET));
    EXPECT(FlagGet(FLAG_HIDE_BALWYN_ROAD_GRUNT));
    EXPECT(FlagGet(FLAG_HIDE_BALWYN_SENDOFF));
    EXPECT(FlagGet(FLAG_HIDE_BALWYN_EVENT_CAST));
    EXPECT(!FlagGet(FLAG_HIDE_BALWYN_MINE_GRUNTS));
    EXPECT(CheckBagHasItem(ITEM_GRAMPYS_JOURNAL, 1));
}

TEST("Scenario balwyn_done: the player has a starter")
{
    StartScenario(SCENARIO_BALWYN_DONE);

    const u32 expectedPartySize = 1;
    const u32 actualPartySize = CalculatePlayerPartyCount();
    EXPECT_EQ(actualPartySize, expectedPartySize);
    const u32 expectedStarter = SPECIES_SPHEAL;
    const u32 actualStarter = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES);
    EXPECT_EQ(actualStarter, expectedStarter);
}

TEST("Scenario balwyn_done: the player starts outside their house in Balwyn")
{
    StartScenario(SCENARIO_BALWYN_DONE);

    const u32 expectedMapGroup = MAP_GROUP(MAP_BALWYN);
    const u32 expectedMapNum = MAP_NUM(MAP_BALWYN);
    const u32 expectedX = 7;
    const u32 expectedY = 18;
    EXPECT_EQ(gSaveBlock1Ptr->location.mapGroup, expectedMapGroup);
    EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, expectedMapNum);
    EXPECT_EQ(gSaveBlock1Ptr->pos.x, expectedX);
    EXPECT_EQ(gSaveBlock1Ptr->pos.y, expectedY);
}
