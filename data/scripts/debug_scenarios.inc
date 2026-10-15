@ Playtest starting points, run on top of a new game by RunScenario (src/debug_scenarios.c) and
@ loaded with tools/playtest/play.py. Each scenario calls a story part, then adds a fitting team
@ (see test/debug_scenarios.c) and a starting point. Story parts only set flags, vars and story
@ items, and each calls the one before it, so the story builds up in order. Everything ends with
@ "return": called directly, that stops the script like "end" does.

@ The Balwyn opening is done: Spheal chosen, Nova beaten, and the knocking heard.
DebugScenarioStory_BalwynDone:
	setvar VAR_BALWYN_STATE, BALWYN_STATE_KNOCKING_HEARD
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_HIDE_BALWYN_EVENT_CAST
	setflag FLAG_HIDE_BALWYN_HOUSE_KELYN
	setflag FLAG_HIDE_BALWYN_ROAD_GRUNT
	setflag FLAG_HIDE_BALWYN_SENDOFF
	clearflag FLAG_HIDE_BALWYN_MINE_GRUNTS
	settrainerflag TRAINER_NOVA_BALWYN
	setvar VAR_STARTER_MON, 1
	additem ITEM_POKE_BALL, 5
	additem ITEM_GRAMPYS_JOURNAL
	return

@ Route 1's trainers and item are done, and Carnrudh's Pokémon Center has been visited.
DebugScenarioStory_CarnrudhArrived:
	call DebugScenarioStory_BalwynDone
	settrainerflag TRAINER_JORY
	settrainerflag TRAINER_TAMSIN
	setflag FLAG_ITEM_KERNIA_ROUTE1_POKE_BALL
	additem ITEM_POKE_BALL
	setrespawn HEAL_LOCATION_CARNRUDH
	return

@ Grampy's verse has been read on the first step onto Carn Kowr.
DebugScenarioStory_CarnrudhRiddle:
	call DebugScenarioStory_CarnrudhArrived
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_RIDDLE_READ
	return

@ The Hand, Head and Cradle grunts are beaten and their stones read in order.
DebugScenarioStory_CarnrudhCradle:
	call DebugScenarioStory_CarnrudhRiddle
	settrainerflag TRAINER_CARN_KOWR_GRUNT_HAND
	settrainerflag TRAINER_CARN_KOWR_GRUNT_HEAD
	settrainerflag TRAINER_CARN_KOWR_GRUNT_CRADLE
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE
	return

@ The gate grunt is beaten and the peak is open. Reading the Well plays the proof, which sets
@ STONES_DONE itself and leads straight into Peran's battle.
DebugScenarioStory_CarnrudhWell:
	call DebugScenarioStory_CarnrudhCradle
	settrainerflag TRAINER_CARN_KOWR_GRUNT_GATE
	return

@ Peran is beaten and has left the peak with Tanek: the gym is open and the festival is on.
DebugScenarioStory_CarnrudhTorDone:
	call DebugScenarioStory_CarnrudhWell
	settrainerflag TRAINER_PERAN_CARN_KOWR
	setflag FLAG_HIDE_CARN_KOWR_PEAK_CAST
	setflag FLAG_HIDE_CARNRUDH_GYM_BLOCKER
	setflag FLAG_HIDE_CARNRUDH_SURVEY_WORKER
	clearflag FLAG_HIDE_CARNRUDH_FESTIVAL
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE
	return

@ Back in town, the engineman has had the player pull the engine's whistle and given them Charcoal.
DebugScenarioStory_CarnrudhGym:
	call DebugScenarioStory_CarnrudhTorDone
	additem ITEM_CHARCOAL
	setflag FLAG_RECEIVED_CHARCOAL_CARNRUDH
	return

@ The gym trainers and Tanek are beaten: badge 1 and TM51 Flame Charge.
DebugScenarioStory_CarnrudhBadge1:
	call DebugScenarioStory_CarnrudhGym
	settrainerflag TRAINER_CARNRUDH_GYM_STOKER
	settrainerflag TRAINER_CARNRUDH_GYM_BAL_MAIDEN
	settrainerflag TRAINER_TANEK
	setflag FLAG_BADGE01_GET
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_BADGE_WON
	additem ITEM_TM_FLAME_CHARGE
	setflag FLAG_RECEIVED_TM_FLAME_CHARGE
	return

@ Outside the house in Balwyn, ready for Route 1.
DebugScenario_BalwynDone::
	call DebugScenarioStory_BalwynDone
	givemon SPECIES_SPHEAL, 6
	setwarp MAP_BALWYN, 7, 18
	return

@ Outside Carnrudh's Pokémon Center, with a Rookidee from Route 1.
DebugScenario_CarnrudhArrived::
	call DebugScenarioStory_CarnrudhArrived
	givemon SPECIES_SPHEAL, 8
	givemon SPECIES_ROOKIDEE, 6
	additem ITEM_POTION, 3
	setwarp MAP_CARNRUDH, 19, 11
	return

@ Just past the verse trigger at the foot of Carn Kowr.
DebugScenario_CarnrudhRiddle::
	call DebugScenarioStory_CarnrudhRiddle
	givemon SPECIES_SPHEAL, 8
	givemon SPECIES_ROOKIDEE, 6
	additem ITEM_POTION, 3
	setwarp MAP_CARN_KOWR, 14, 37
	return

@ Just below the gate grunt's trigger at the top of the climb, with a Rolycoly from Carn Kowr.
DebugScenario_CarnrudhCradle::
	call DebugScenarioStory_CarnrudhCradle
	givemon SPECIES_SPHEAL, 9
	givemon SPECIES_ROOKIDEE, 7
	givemon SPECIES_ROLYCOLY, 6
	additem ITEM_POTION, 3
	setwarp MAP_CARN_KOWR, 22, 2
	return

@ In front of the Well on the peak, with Peran just below: read the Well for the proof and his battle.
DebugScenario_CarnrudhWell::
	call DebugScenarioStory_CarnrudhWell
	givemon SPECIES_SPHEAL, 10
	givemon SPECIES_ROOKIDEE, 8
	givemon SPECIES_ROLYCOLY, 7
	additem ITEM_POTION, 3
	setwarp MAP_CARN_KOWR_PEAK, 20, 8
	return

@ On the peak in front of the drained Well, with Peran and Tanek gone: walk down to town for the
@ engineman's welcome.
DebugScenario_CarnrudhTorDone::
	call DebugScenarioStory_CarnrudhTorDone
	givemon SPECIES_SPHEAL, 12
	givemon SPECIES_ROOKIDEE, 10
	givemon SPECIES_ROLYCOLY, 9
	additem ITEM_POTION, 5
	setwarp MAP_CARN_KOWR_PEAK, 20, 8
	return

@ Outside the gym door in Carnrudh, with the festival on.
DebugScenario_CarnrudhGym::
	call DebugScenarioStory_CarnrudhGym
	givemon SPECIES_SPHEAL, 13
	givemon SPECIES_ROOKIDEE, 11
	givemon SPECIES_ROLYCOLY, 10
	additem ITEM_POTION, 5
	setwarp MAP_CARNRUDH, 8, 10
	return

@ Outside the gym door in Carnrudh, with badge 1.
DebugScenario_CarnrudhBadge1::
	call DebugScenarioStory_CarnrudhBadge1
	givemon SPECIES_SPHEAL, 14
	givemon SPECIES_ROOKIDEE, 12
	givemon SPECIES_ROLYCOLY, 11
	additem ITEM_POTION, 3
	setwarp MAP_CARNRUDH, 8, 10
	return
