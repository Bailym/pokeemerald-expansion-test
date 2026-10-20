Porthliw_Gym_MapScripts::
	.byte 0

Porthliw_Gym_EventScript_Statue::
	lockall
	goto_if_set FLAG_BADGE02_GET, Porthliw_Gym_EventScript_StatueCertified
	msgbox Porthliw_Gym_Text_Statue, MSGBOX_DEFAULT
	releaseall
	end

Porthliw_Gym_EventScript_StatueCertified::
	msgbox Porthliw_Gym_Text_StatueCertified, MSGBOX_DEFAULT
	releaseall
	end

Porthliw_Gym_Text_Statue:
	.string "PORTHLIW POKéMON GYM$"

Porthliw_Gym_Text_StatueCertified:
	.string "PORTHLIW POKéMON GYM\p"
	.string "ENYS'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
