Carnrudh_House1_MapScripts::
	.byte 0

Carnrudh_House1_EventScript_Mum::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_House1_EventScript_MumFestival
	msgbox Carnrudh_House1_Text_Mum, MSGBOX_NPC
	end

Carnrudh_House1_EventScript_MumFestival::
	msgbox Carnrudh_House1_Text_MumFestival, MSGBOX_NPC
	end

Carnrudh_House1_EventScript_Boy::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_House1_EventScript_BoyFestival
	msgbox Carnrudh_House1_Text_Boy, MSGBOX_NPC
	end

Carnrudh_House1_EventScript_BoyFestival::
	msgbox Carnrudh_House1_Text_BoyFestival, MSGBOX_NPC
	end

Carnrudh_House1_Text_Mum:
	.string "My husband reads Lumen's job\n"
	.string "ads every night.\p"
	.string "Half the town's for the quarry,\n"
	.string "half's against. Tidy mess.$"

Carnrudh_House1_Text_MumFestival:
	.string "No quarry, no jobs. But the\n"
	.string "tor's still there.\p"
	.string "I don't know whether to laugh\n"
	.string "or cry, my lover.$"

Carnrudh_House1_Text_Boy:
	.string "A giant sleeps on CARN KOWR.\n"
	.string "Grampy says so!\p"
	.string "His HAND, his HEAD, his CRADLE…\n"
	.string "they're all up there!$"

Carnrudh_House1_Text_BoyFestival:
	.string "The giant's real! They found\n"
	.string "his writing in the WELL!$"
