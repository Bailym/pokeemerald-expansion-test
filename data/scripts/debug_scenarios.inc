@ Playtest starting points, run on top of a new game by RunScenario (src/debug_scenarios.c) and
@ loaded with tools/playtest/play.py. Each scenario calls the one before it, so the story builds up
@ in order, and ends with "return": called directly, that stops the script like "end" does.

@ The Balwyn opening is done: Spheal chosen, Nova beaten, and the knocking heard. Outside the house.
DebugScenario_BalwynDone::
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
	givemon SPECIES_SPHEAL, 6
	additem ITEM_POKE_BALL, 5
	additem ITEM_GRAMPYS_JOURNAL
	setwarp MAP_BALWYN, 7, 18
	return
