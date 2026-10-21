Porthliw_FishermansHouse_MapScripts::
	.byte 0

Porthliw_FishermansHouse_EventScript_Fisherman::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_FishermansHouse_EventScript_FishermanAfterOpening
	msgbox Porthliw_FishermansHouse_Text_Fisherman, MSGBOX_NPC
	end

Porthliw_FishermansHouse_EventScript_FishermanAfterOpening::
	msgbox Porthliw_FishermansHouse_Text_FishermanAfterOpening, MSGBOX_NPC
	end

Porthliw_FishermansHouse_EventScript_Girl::
	msgbox Porthliw_FishermansHouse_Text_Girl, MSGBOX_NPC
	end

Porthliw_FishermansHouse_Text_Fisherman:
	.string "Gull had my pasty off the harbour\n"
	.string "wall this morning. Bag and all.\p"
	.string "I only turned round to coil a rope.\n"
	.string "They're crafty, Porthliw gulls.$"

Porthliw_FishermansHouse_Text_FishermanAfterOpening:
	.string "Lumen's lot used to buy fish off\n"
	.string "the quay for their parties.\p"
	.string "Not since Enys had her say.\n"
	.string "Gulls still nick my pasties, mind.$"

Porthliw_FishermansHouse_Text_Girl:
	.string "Dad says wave your arms and the\n"
	.string "gulls go away.\p"
	.string "I waved and waved. One took my\n"
	.string "ice cream anyway.$"
