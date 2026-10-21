Porthliw_Studio_MapScripts::
	.byte 0

Porthliw_Studio_EventScript_Painter::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_Studio_EventScript_PainterAfterOpening
	msgbox Porthliw_Studio_Text_Painter, MSGBOX_NPC
	end

Porthliw_Studio_EventScript_PainterAfterOpening::
	msgbox Porthliw_Studio_Text_PainterAfterOpening, MSGBOX_NPC
	end

Porthliw_Studio_EventScript_Sitter::
	msgbox Porthliw_Studio_Text_Sitter, MSGBOX_NPC
	end

Porthliw_Studio_Text_Painter:
	.string "Lumen want my big seascape for\n"
	.string "their new office in Treveur.\p"
	.string "Good money, and the rent's due.\n"
	.string "I haven't said yes. Yet.$"

Porthliw_Studio_Text_PainterAfterOpening:
	.string "After Enys spoke, I sent Lumen's\n"
	.string "cheque back.\p"
	.string "Rent's still due, mind.\n"
	.string "Felt proper good, though.$"

Porthliw_Studio_Text_Sitter:
	.string "I'm sitting for a portrait.\n"
	.string "Three hours, no moving!\p"
	.string "And the light keeps changing, so\n"
	.string "he keeps starting again…$"
