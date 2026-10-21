#include "global.h"
#include "wild_encounter.h"
#include "constants/map_groups.h"
#include "test/test.h"

TEST("Porthliw's harbour can be fished")
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PORTHLIW);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PORTHLIW);

    EXPECT(DoesCurrentMapHaveFishingMons());
}
