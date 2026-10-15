#ifndef GUARD_CONSTANTS_DEBUG_SCENARIOS_H
#define GUARD_CONSTANTS_DEBUG_SCENARIOS_H

// Starting points for playtesting, loaded with tools/playtest/play.py (see design/plans/playtest-scenarios.md).
// play.py reads the names and IDs from this file, so keep to one "#define SCENARIO_<NAME> <id>" per line.
#define SCENARIO_NONE                  0
#define SCENARIO_BALWYN_DONE           1
#define SCENARIO_CARNRUDH_ARRIVED      2
#define SCENARIO_CARNRUDH_RIDDLE       3
#define SCENARIO_CARNRUDH_CRADLE       4
#define SCENARIO_CARNRUDH_WELL         5
#define SCENARIO_CARNRUDH_TOR_DONE     6
#define SCENARIO_CARNRUDH_GYM          7
#define SCENARIO_CARNRUDH_BADGE1       8

#define SCENARIOS_COUNT                9

#endif // GUARD_CONSTANTS_DEBUG_SCENARIOS_H
