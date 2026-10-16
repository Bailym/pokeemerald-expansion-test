#include "global.h"
#include "event_data.h"
#include "field_effect.h"
#include "field_move.h"
#include "item.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "constants/field_effects.h"
#include "overworld.h"
#include "region_map.h"
#include "constants/map_groups.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/field_move.h"

// The test scripts are inline asm, which can't see C enums or stringify their values, so the
// values are written out here and checked against the enum.
STATIC_ASSERT(FIELD_MOVE_ROCK_SMASH == 2, FieldMoveRockSmashValue);
STATIC_ASSERT(FIELD_MOVE_SURF == 4, FieldMoveSurfValue);
asm(".set FIELD_MOVE_ROCK_SMASH, 2\n"
    ".set FIELD_MOVE_SURF, 4\n");

TEST("Rock Smash can be used with badge 1 when no Pokémon knows it")
{
    FlagSet(FLAG_BADGE01_GET);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_SPHEAL, 10;
        checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE;
    );

    const u32 expectedResult = FIELD_MOVE_USER_NONE;
    u32 actualResult = VarGet(VAR_RESULT);
    EXPECT_EQ(actualResult, expectedResult);
}

TEST("Rock Smash can't be used without badge 1, even by a Pokémon that knows it")
{
    FlagClear(FLAG_BADGE01_GET);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_SPHEAL, 10, move1=MOVE_ROCK_SMASH;
        checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE;
    );

    const u32 expectedResult = PARTY_SIZE;
    u32 actualResult = VarGet(VAR_RESULT);
    EXPECT_EQ(actualResult, expectedResult);
}

TEST("A Pokémon that knows Rock Smash isn't shown using it")
{
    FlagSet(FLAG_BADGE01_GET);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_SPHEAL, 10, move1=MOVE_ROCK_SMASH;
        checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE;
    );

    const u32 expectedResult = FIELD_MOVE_USER_NONE;
    u32 actualResult = VarGet(VAR_RESULT);
    EXPECT_EQ(actualResult, expectedResult);
}

TEST("Field move checks that skip the badge check still need the badge")
{
    // Surf's script checks with no badge check, as the badge is checked in C before it runs.
    FlagClear(FLAG_BADGE04_GET);
    FlagClear(FLAG_BADGE05_GET);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_SPHEAL, 10, move1=MOVE_SURF;
        checkfieldmove FIELD_MOVE_SURF;
    );

    const u32 expectedResult = PARTY_SIZE;
    u32 actualResult = VarGet(VAR_RESULT);
    EXPECT_EQ(actualResult, expectedResult);
}

// Opening the Town Map draws the region map for the current map's section, so every outdoor
// Kernia map must be on the Kernia (Hoenn-slot) region map, not Kanto's.
TEST("Kernia's outdoor maps open the Town Map on Kernia's region map")
{
    u32 mapGroup = 0, mapNum = 0;
    PARAMETRIZE { mapGroup = MAP_GROUP(MAP_BALWYN);       mapNum = MAP_NUM(MAP_BALWYN); }
    PARAMETRIZE { mapGroup = MAP_GROUP(MAP_KERNIA_ROUTE1); mapNum = MAP_NUM(MAP_KERNIA_ROUTE1); }
    PARAMETRIZE { mapGroup = MAP_GROUP(MAP_CARNRUDH);     mapNum = MAP_NUM(MAP_CARNRUDH); }
    PARAMETRIZE { mapGroup = MAP_GROUP(MAP_CARN_KOWR);    mapNum = MAP_NUM(MAP_CARN_KOWR); }
    PARAMETRIZE { mapGroup = MAP_GROUP(MAP_KERNIA_ROUTE2); mapNum = MAP_NUM(MAP_KERNIA_ROUTE2); }

    const enum RegionMapType expectedRegionMap = REGION_MAP_HOENN;
    u32 mapSec = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->regionMapSectionId;
    enum RegionMapType actualRegionMap = GetRegionMapType(mapSec);
    EXPECT_EQ(actualRegionMap, expectedRegionMap);
}

TEST("Flying from the Town Map needs badge 2")
{
    FlagClear(FLAG_BADGE02_GET);
    EXPECT(!CanFlyFromRegionMap());

    FlagSet(FLAG_BADGE02_GET);
    EXPECT(CanFlyFromRegionMap());
}

TEST("Each field move unlocks at its Kernia badge and not before")
{
    enum FieldMove fieldMove = 0;
    u32 badgeFlag = 0;
    PARAMETRIZE { fieldMove = FIELD_MOVE_ROCK_SMASH; badgeFlag = FLAG_BADGE01_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_FLY;        badgeFlag = FLAG_BADGE02_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_CUT;        badgeFlag = FLAG_BADGE03_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_FLASH;      badgeFlag = FLAG_BADGE03_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_SURF;       badgeFlag = FLAG_BADGE04_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_STRENGTH;   badgeFlag = FLAG_BADGE05_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_ROCK_CLIMB; badgeFlag = FLAG_BADGE05_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_DIVE;       badgeFlag = FLAG_BADGE06_GET; }
    PARAMETRIZE { fieldMove = FIELD_MOVE_WATERFALL;  badgeFlag = FLAG_BADGE08_GET; }

    for (u32 flag = FLAG_BADGE01_GET; flag <= FLAG_BADGE08_GET; flag++)
        FlagSet(flag);
    FlagClear(badgeFlag);
    EXPECT(!IsFieldMoveUnlocked(fieldMove));

    FlagSet(badgeFlag);
    EXPECT(IsFieldMoveUnlocked(fieldMove));
}

TEST("Surf can be used with badge 4 when no Pokémon knows it")
{
    ZeroPlayerPartyMons();
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_SPHEAL, 10;
    );

    FlagClear(FLAG_BADGE04_GET);
    EXPECT(!PartyHasMonWithSurf());

    FlagSet(FLAG_BADGE04_GET);
    EXPECT(PartyHasMonWithSurf());
}

TEST("No Pokémon is shown using a field move when there's no party slot")
{
    gFieldEffectArguments[0] = FIELD_MOVE_USER_NONE;

    FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);

    EXPECT(!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON));
}

TEST("Dark maps light up with badge 3")
{
    gMapHeader.cave = TRUE;
    FlagClear(FLAG_SYS_USE_FLASH);

    FlagClear(FLAG_BADGE03_GET);
    SetDefaultFlashLevel();
    const u32 expectedDarkLevel = gMaxFlashLevel - 1;
    u32 actualDarkLevel = gSaveBlock1Ptr->flashLevel;
    EXPECT_EQ(actualDarkLevel, expectedDarkLevel);

    FlagSet(FLAG_BADGE03_GET);
    SetDefaultFlashLevel();
    const u32 expectedLitLevel = 1; // The same light as using Flash.
    u32 actualLitLevel = gSaveBlock1Ptr->flashLevel;
    EXPECT_EQ(actualLitLevel, expectedLitLevel);
    EXPECT(FlagGet(FLAG_SYS_USE_FLASH));
}

TEST("The former HM moves are ordinary moves that can be forgotten")
{
    enum Move move = MOVE_NONE;
    PARAMETRIZE { move = MOVE_CUT; }
    PARAMETRIZE { move = MOVE_FLY; }
    PARAMETRIZE { move = MOVE_SURF; }
    PARAMETRIZE { move = MOVE_STRENGTH; }
    PARAMETRIZE { move = MOVE_FLASH; }
    PARAMETRIZE { move = MOVE_ROCK_SMASH; }
    PARAMETRIZE { move = MOVE_WATERFALL; }
    PARAMETRIZE { move = MOVE_DIVE; }

    EXPECT(!IsMoveHM(move));
    EXPECT(!CannotForgetMove(move));
}

TEST("TM Surf is an ordinary TM that teaches Surf")
{
    const enum Move expectedMove = MOVE_SURF;
    enum Move actualMove = GetItemTMHMMoveId(ITEM_TM_SURF);
    EXPECT_EQ(actualMove, expectedMove);
    EXPECT_LE(GetItemTMHMIndex(ITEM_TM_SURF), NUM_TECHNICAL_MACHINES);
    // The old HM name still works, for vanilla scripts that give it.
    EXPECT_EQ(ITEM_HM_SURF, ITEM_TM_SURF);
}
