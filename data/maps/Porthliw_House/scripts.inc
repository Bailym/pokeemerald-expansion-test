Porthliw_House_MapScripts::
	.byte 0

Porthliw_House_EventScript_OldWoman::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_House_EventScript_OldWomanAfterOpening
	msgbox Porthliw_House_Text_OldWoman, MSGBOX_NPC
	end

Porthliw_House_EventScript_OldWomanAfterOpening::
	msgbox Porthliw_House_Text_OldWomanAfterOpening, MSGBOX_NPC
	end

Porthliw_House_EventScript_OldMan::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_House_EventScript_OldManAfterOpening
	msgbox Porthliw_House_Text_OldMan, MSGBOX_NPC
	end

Porthliw_House_EventScript_OldManAfterOpening::
	msgbox Porthliw_House_Text_OldManAfterOpening, MSGBOX_NPC
	end

Porthliw_House_Text_OldWoman:
	.string "Lumen are paying for the gallery's\n"
	.string "big opening. Lovely of them.\p"
	.string "My husband says nothing's ever\n"
	.string "free. Grumpy old thing.$"

Porthliw_House_Text_OldWomanAfterOpening:
	.string "Our Enys gave Lumen what for at\n"
	.string "the gallery!\p"
	.string "The whole street heard by\n"
	.string "breakfast. Good on her.$"

Porthliw_House_Text_OldMan:
	.string "Painters been coming here since I\n"
	.string "was a boy. Emmets, we called 'em.\p"
	.string "Now half the town's painters.\n"
	.string "Can't move for easels.$"

Porthliw_House_Text_OldManAfterOpening:
	.string "Told you nothing's free, I did.\p"
	.string "Lumen's money bought one night's\n"
	.string "smiles. Didn't last till the wine\l"
	.string "ran out.$"
