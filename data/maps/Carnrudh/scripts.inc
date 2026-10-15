Carnrudh_MapScripts::
	.byte 0

Carnrudh_EventScript_TownSign::
	msgbox Carnrudh_Text_TownSign, MSGBOX_SIGN
	end

Carnrudh_EventScript_GymSign::
	msgbox Carnrudh_Text_GymSign, MSGBOX_SIGN
	end

@ Stands in the gym doorway until Tanek comes back down from Carn Kowr.
Carnrudh_EventScript_GymBlocker::
	msgbox Carnrudh_Text_GymBlocker, MSGBOX_NPC
	end

Carnrudh_Text_TownSign:
	.string "CARNRUDH\n"
	.string "Under the red tor.\p"
	.string "Where the first steam engine\n"
	.string "ever ran on the road!$"

Carnrudh_Text_GymSign:
	.string "CARNRUDH POKéMON GYM\n"
	.string "LEADER: TANEK\p"
	.string "The fire in the boiler,\n"
	.string "the heart of the engine!$"

Carnrudh_Text_GymBlocker:
	.string "Gym's shut, my 'ansum. TANEK's\n"
	.string "gone up CARN KOWR with Lumen.\p"
	.string "They're measuring the tor for\n"
	.string "a quarry, so they say.\p"
	.string "Up the path north, if you want\n"
	.string "him. Mind the giant's stones!$"
