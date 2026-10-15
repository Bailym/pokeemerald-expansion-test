#ifndef GUARD_DEBUG_SCENARIOS_H
#define GUARD_DEBUG_SCENARIOS_H

#include "constants/debug_scenarios.h"

#if DEBUG_SCENARIOS
extern const volatile u8 gBootScenario;

void CB2_BootScenario(void);
void RunScenario(u32 scenario);
#endif // DEBUG_SCENARIOS

#endif // GUARD_DEBUG_SCENARIOS_H
