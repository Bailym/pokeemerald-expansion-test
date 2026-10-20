#include "global.h"
#include "test/test.h"
#include "battle_setup.h"
#include "debug_scenarios.h"
#include "event_data.h"
#include "item.h"
#include "new_game.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/trainers.h"
#include "constants/vars.h"

// Each scenario runs on top of a fresh new game, the same as when play.py boots one.
static void StartScenario(u32 scenario)
{
    NewGameInitData();
    RunScenario(scenario);
}

static void ExpectStartsAt(u32 expectedMapGroup, u32 expectedMapNum, u32 expectedX, u32 expectedY)
{
    EXPECT_EQ(gSaveBlock1Ptr->location.mapGroup, expectedMapGroup);
    EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, expectedMapNum);
    EXPECT_EQ(gSaveBlock1Ptr->pos.x, expectedX);
    EXPECT_EQ(gSaveBlock1Ptr->pos.y, expectedY);
}

// Ace levels of the fights each scenario leads into, from src/data/trainers.party. The test build
// has its own trainer table, so they can't be read from gTrainers here.
#define TAMSIN_ACE_LEVEL           5 // Wooloo, the last Route 1 trainer.
#define GRUNT_HEAD_ACE_LEVEL       6 // Rolycoly, the strongest of the climb's grunts.
#define GRUNT_GATE_ACE_LEVEL       7 // Magnemite.
#define PERAN_ACE_LEVEL            8 // Drilbur.
#define TANEK_ACE_LEVEL           12 // Torkoal.
#define NOVA_ROUTE2_ACE_LEVEL     13 // Pawmi and Klink.
#define PASCOE_ACE_LEVEL          13 // Tentacool, the beach's sailor.
#define ENYS_ACE_LEVEL            16 // Cramorant, Porthliw's gym. Also stands in for the fight after it, still unbuilt.

// A fitting team for the fight a scenario leads into: the strongest Pokémon is at the trainer's
// ace level or up to two above, and nothing trails it by more than three.
static void ExpectTeamReadyFor(u32 aceLevel)
{
    const u32 partySize = CalculatePlayerPartyCount();
    u32 actualStrongestLevel = 0;
    u32 actualWeakestLevel = MAX_LEVEL;

    for (u32 i = 0; i < partySize; i++)
    {
        u32 level = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_LEVEL);
        actualStrongestLevel = max(actualStrongestLevel, level);
        actualWeakestLevel = min(actualWeakestLevel, level);
    }

    const u32 expectedStrongestMin = aceLevel;
    const u32 expectedStrongestMax = aceLevel + 2;
    const u32 expectedWeakestMin = aceLevel - 3;
    EXPECT_GE(actualStrongestLevel, expectedStrongestMin);
    EXPECT_LE(actualStrongestLevel, expectedStrongestMax);
    EXPECT_GE(actualWeakestLevel, expectedWeakestMin);
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
    EXPECT(CheckBagHasItem(ITEM_TOWN_MAP, 1));
    EXPECT(FlagGet(FLAG_VISITED_BALWYN));
}

TEST("Scenario balwyn_done: the player has a starter ready for Route 1")
{
    StartScenario(SCENARIO_BALWYN_DONE);

    const u32 expectedPartySize = 1;
    const u32 actualPartySize = CalculatePlayerPartyCount();
    EXPECT_EQ(actualPartySize, expectedPartySize);
    const u32 expectedStarter = SPECIES_SPHEAL;
    const u32 actualStarter = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES);
    EXPECT_EQ(actualStarter, expectedStarter);
    ExpectTeamReadyFor(TAMSIN_ACE_LEVEL);
}

TEST("Scenario balwyn_done: the player starts outside their house in Balwyn")
{
    StartScenario(SCENARIO_BALWYN_DONE);

    ExpectStartsAt(MAP_GROUP(MAP_BALWYN), MAP_NUM(MAP_BALWYN), 7, 18);
}

TEST("Scenario carnrudh_arrived: Route 1 is done and the player is outside Carnrudh's Pokémon Center")
{
    StartScenario(SCENARIO_CARNRUDH_ARRIVED);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_ARRIVED;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_JORY));
    EXPECT(HasTrainerBeenFought(TRAINER_TAMSIN));
    EXPECT(FlagGet(FLAG_HIDE_CARNRUDH_FESTIVAL));
    EXPECT(FlagGet(FLAG_VISITED_CARNRUDH));
    // Whiting out from here on goes to Carnrudh's Pokémon Center, not home.
    const u32 expectedRespawnMapGroup = MAP_GROUP(MAP_CARNRUDH);
    const u32 expectedRespawnMapNum = MAP_NUM(MAP_CARNRUDH);
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapGroup, expectedRespawnMapGroup);
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapNum, expectedRespawnMapNum);
    ExpectTeamReadyFor(GRUNT_HEAD_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARNRUDH), MAP_NUM(MAP_CARNRUDH), 19, 11);
}

TEST("Scenario carnrudh_riddle: the verse is read at the foot of Carn Kowr")
{
    StartScenario(SCENARIO_CARNRUDH_RIDDLE);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_RIDDLE_READ;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(!HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_HAND));
    ExpectTeamReadyFor(GRUNT_HEAD_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARN_KOWR), MAP_NUM(MAP_CARN_KOWR), 14, 37);
}

TEST("Scenario carnrudh_cradle: the three stones are done and the gate grunt is waiting")
{
    StartScenario(SCENARIO_CARNRUDH_CRADLE);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_CRADLE_DONE;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_HAND));
    EXPECT(HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_HEAD));
    EXPECT(HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_CRADLE));
    EXPECT(!HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_GATE));
    ExpectTeamReadyFor(GRUNT_GATE_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARN_KOWR), MAP_NUM(MAP_CARN_KOWR), 22, 2);
}

TEST("Scenario carnrudh_well: the gate grunt is beaten and reading the Well starts the proof")
{
    StartScenario(SCENARIO_CARNRUDH_WELL);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_CRADLE_DONE;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_CARN_KOWR_GRUNT_GATE));
    EXPECT(!HasTrainerBeenFought(TRAINER_PERAN_CARN_KOWR));
    EXPECT(!FlagGet(FLAG_HIDE_CARN_KOWR_PEAK_CAST));
    EXPECT(!FlagGet(FLAG_HIDE_CARNRUDH_SURVEY_WORKER));
    EXPECT(FlagGet(FLAG_HIDE_CARNRUDH_FESTIVAL));
    ExpectTeamReadyFor(PERAN_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARN_KOWR_PEAK), MAP_NUM(MAP_CARN_KOWR_PEAK), 20, 8);
}

TEST("Scenario carnrudh_tor_done: Peran is beaten and the player is still on the peak")
{
    StartScenario(SCENARIO_CARNRUDH_TOR_DONE);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_TOR_DONE;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_PERAN_CARN_KOWR));
    EXPECT(FlagGet(FLAG_HIDE_CARN_KOWR_PEAK_CAST));
    EXPECT(FlagGet(FLAG_HIDE_CARNRUDH_GYM_BLOCKER));
    EXPECT(!FlagGet(FLAG_HIDE_CARNRUDH_FESTIVAL));
    EXPECT(FlagGet(FLAG_HIDE_CARNRUDH_SURVEY_WORKER));
    EXPECT(!FlagGet(FLAG_RECEIVED_CHARCOAL_CARNRUDH));
    EXPECT(!CheckBagHasItem(ITEM_CHARCOAL, 1));
    ExpectTeamReadyFor(TANEK_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARN_KOWR_PEAK), MAP_NUM(MAP_CARN_KOWR_PEAK), 20, 8);
}

TEST("Scenario carnrudh_gym: Peran is beaten, the festival is on and the gym is open")
{
    StartScenario(SCENARIO_CARNRUDH_GYM);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_TOR_DONE;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_PERAN_CARN_KOWR));
    EXPECT(FlagGet(FLAG_HIDE_CARN_KOWR_PEAK_CAST));
    EXPECT(FlagGet(FLAG_HIDE_CARNRUDH_GYM_BLOCKER));
    EXPECT(!FlagGet(FLAG_HIDE_CARNRUDH_FESTIVAL));
    EXPECT(FlagGet(FLAG_RECEIVED_CHARCOAL_CARNRUDH));
    EXPECT(CheckBagHasItem(ITEM_CHARCOAL, 1));
    EXPECT(!FlagGet(FLAG_BADGE01_GET));
    ExpectTeamReadyFor(TANEK_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARNRUDH), MAP_NUM(MAP_CARNRUDH), 8, 10);
}

TEST("Scenario carnrudh_badge1: Tanek is beaten, with badge 1 and TM51")
{
    StartScenario(SCENARIO_CARNRUDH_BADGE1);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_BADGE_WON;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(HasTrainerBeenFought(TRAINER_TANEK));
    EXPECT(HasTrainerBeenFought(TRAINER_CARNRUDH_GYM_STOKER));
    EXPECT(HasTrainerBeenFought(TRAINER_CARNRUDH_GYM_BAL_MAIDEN));
    EXPECT(FlagGet(FLAG_BADGE01_GET));
    EXPECT(FlagGet(FLAG_RECEIVED_TM_FLAME_CHARGE));
    EXPECT(CheckBagHasItem(ITEM_TM_FLAME_CHARGE, 1));
    ExpectTeamReadyFor(TANEK_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_CARNRUDH), MAP_NUM(MAP_CARNRUDH), 8, 10);
}

TEST("Scenario route2_summit: below the summit with the way up cleared and Nova's shoot still on")
{
    StartScenario(SCENARIO_ROUTE2_SUMMIT);

    const u32 expectedCarnrudhState = CARNRUDH_STATE_BADGE_WON;
    const u32 actualCarnrudhState = VarGet(VAR_CARNRUDH_STATE);
    EXPECT_EQ(actualCarnrudhState, expectedCarnrudhState);
    EXPECT(FlagGet(FLAG_BADGE01_GET));
    EXPECT(HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_HIKER));
    EXPECT(HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_BIRD_KEEPER));
    EXPECT(!HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_PICNICKER));
    EXPECT(!HasTrainerBeenFought(TRAINER_NOVA_ROUTE2));
    EXPECT(!FlagGet(FLAG_HIDE_KERNIA_ROUTE2_SHOOT));
    EXPECT(!FlagGet(FLAG_RECEIVED_OLD_ROD));
    EXPECT(!FlagGet(FLAG_HIDE_KERNIA_ROUTE2_OLD_BULL));
    EXPECT(FlagGet(FLAG_HIDE_KERNIA_ROUTE2_KEEPER_HOME));
    ExpectTeamReadyFor(NOVA_ROUTE2_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_KERNIA_ROUTE2), MAP_NUM(MAP_KERNIA_ROUTE2), 24, 18);
}

TEST("Scenario route2_bay: Nova and the way down are done, with the beach still to do")
{
    StartScenario(SCENARIO_ROUTE2_BAY);

    EXPECT(HasTrainerBeenFought(TRAINER_NOVA_ROUTE2));
    EXPECT(FlagGet(FLAG_HIDE_KERNIA_ROUTE2_SHOOT));
    EXPECT(HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_HIKER));
    EXPECT(HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_BIRD_KEEPER));
    EXPECT(HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_PICNICKER));
    EXPECT(!HasTrainerBeenFought(TRAINER_KERNIA_ROUTE2_SAILOR));
    EXPECT(!FlagGet(FLAG_RECEIVED_OLD_ROD));
    EXPECT(!FlagGet(FLAG_HIDE_KERNIA_ROUTE2_OLD_BULL));
    EXPECT(FlagGet(FLAG_HIDE_KERNIA_ROUTE2_KEEPER_HOME));
    ExpectTeamReadyFor(PASCOE_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_KERNIA_ROUTE2), MAP_NUM(MAP_KERNIA_ROUTE2), 15, 35);
}

TEST("Scenario porthliw_arrived: just in from Route 2's beach, with Porthliw visited and its gym shut")
{
    StartScenario(SCENARIO_PORTHLIW_ARRIVED);

    const u32 expectedPorthliwState = PORTHLIW_STATE_ARRIVED;
    const u32 actualPorthliwState = VarGet(VAR_PORTHLIW_STATE);
    EXPECT_EQ(actualPorthliwState, expectedPorthliwState);
    EXPECT(FlagGet(FLAG_VISITED_PORTHLIW));
    EXPECT(HasTrainerBeenFought(TRAINER_NOVA_ROUTE2));
    EXPECT(!FlagGet(FLAG_BADGE02_GET));
    EXPECT(CheckBagHasItem(ITEM_TOWN_MAP, 1));
    ExpectTeamReadyFor(ENYS_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_PORTHLIW), MAP_NUM(MAP_PORTHLIW), 40, 31);
}

TEST("Scenario porthliw_met_enys: on the harbourfront after Enys's invitation, before the opening")
{
    StartScenario(SCENARIO_PORTHLIW_MET_ENYS);

    const u32 expectedPorthliwState = PORTHLIW_STATE_MET_ENYS;
    const u32 actualPorthliwState = VarGet(VAR_PORTHLIW_STATE);
    EXPECT_EQ(actualPorthliwState, expectedPorthliwState);
    EXPECT(FlagGet(FLAG_VISITED_PORTHLIW));
    EXPECT(!FlagGet(FLAG_BADGE02_GET));
    ExpectTeamReadyFor(ENYS_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_PORTHLIW), MAP_NUM(MAP_PORTHLIW), 30, 27);
}

TEST("Scenario porthliw_opening_done: outside the gallery after the opening night, with the gym open")
{
    StartScenario(SCENARIO_PORTHLIW_OPENING_DONE);

    const u32 expectedPorthliwState = PORTHLIW_STATE_OPENING_DONE;
    const u32 actualPorthliwState = VarGet(VAR_PORTHLIW_STATE);
    EXPECT_EQ(actualPorthliwState, expectedPorthliwState);
    EXPECT(FlagGet(FLAG_HIDE_PORTHLIW_OPENING));
    EXPECT(FlagGet(FLAG_HIDE_PORTHLIW_HARBOUR_ENYS));
    EXPECT(!FlagGet(FLAG_BADGE02_GET));
    ExpectTeamReadyFor(ENYS_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_PORTHLIW), MAP_NUM(MAP_PORTHLIW), 28, 26);
}

TEST("Scenario porthliw_gym: inside Enys's studio with the gym still to do")
{
    StartScenario(SCENARIO_PORTHLIW_GYM);

    const u32 expectedPorthliwState = PORTHLIW_STATE_OPENING_DONE;
    const u32 actualPorthliwState = VarGet(VAR_PORTHLIW_STATE);
    EXPECT_EQ(actualPorthliwState, expectedPorthliwState);
    EXPECT(!HasTrainerBeenFought(TRAINER_PORTHLIW_GYM_SKETCHER));
    EXPECT(!HasTrainerBeenFought(TRAINER_PORTHLIW_GYM_PAINTER));
    EXPECT(!HasTrainerBeenFought(TRAINER_ENYS));
    EXPECT(!FlagGet(FLAG_BADGE02_GET));
    ExpectTeamReadyFor(ENYS_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_PORTHLIW_GYM), MAP_NUM(MAP_PORTHLIW_GYM), 16, 20);
}

TEST("Scenario porthliw_badge2: Enys is beaten, with badge 2 and TM40")
{
    StartScenario(SCENARIO_PORTHLIW_BADGE2);

    const u32 expectedPorthliwState = PORTHLIW_STATE_BADGE_WON;
    const u32 actualPorthliwState = VarGet(VAR_PORTHLIW_STATE);
    EXPECT_EQ(actualPorthliwState, expectedPorthliwState);
    EXPECT(HasTrainerBeenFought(TRAINER_PORTHLIW_GYM_SKETCHER));
    EXPECT(HasTrainerBeenFought(TRAINER_PORTHLIW_GYM_PAINTER));
    EXPECT(HasTrainerBeenFought(TRAINER_ENYS));
    EXPECT(FlagGet(FLAG_BADGE02_GET));
    EXPECT(FlagGet(FLAG_RECEIVED_TM_AERIAL_ACE));
    EXPECT(CheckBagHasItem(ITEM_TM_AERIAL_ACE, 1));
    ExpectTeamReadyFor(ENYS_ACE_LEVEL);
    ExpectStartsAt(MAP_GROUP(MAP_PORTHLIW), MAP_NUM(MAP_PORTHLIW), 21, 7);
}

// Pokémon in a scenario stand in for ones the player raised, so they must obey: they're the
// player's own, and met at or below the badge level limit (Gen 8+ obedience goes by met level).
TEST("Every scenario's Pokémon obey the player")
{
    u32 scenario = 0;
    for (u32 i = SCENARIO_NONE + 1; i < SCENARIOS_COUNT; i++)
        PARAMETRIZE { scenario = i; }

    StartScenario(scenario);

    u32 expectedMaxMetLevel = 10;
    for (u32 flag = FLAG_BADGE01_GET; flag <= FLAG_BADGE07_GET; flag++)
    {
        if (FlagGet(flag))
            expectedMaxMetLevel += 10;
    }
    for (u32 i = 0; i < CalculatePlayerPartyCount(); i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 actualMetLevel = GetMonData(mon, MON_DATA_MET_LEVEL);
        EXPECT(!IsTradedMon(mon));
        EXPECT_LE(actualMetLevel, expectedMaxMetLevel);
    }
}
