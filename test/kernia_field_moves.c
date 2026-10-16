#include "global.h"
#include "event_data.h"
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
