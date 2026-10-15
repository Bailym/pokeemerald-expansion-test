Carnrudh_MapScripts::
	.byte 0

Carnrudh_EventScript_TownSign::
	msgbox Carnrudh_Text_TownSign, MSGBOX_SIGN
	end

Carnrudh_EventScript_GymSign::
	msgbox Carnrudh_Text_GymSign, MSGBOX_SIGN
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
