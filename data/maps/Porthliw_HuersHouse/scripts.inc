Porthliw_HuersHouse_MapScripts::
	.byte 0

Porthliw_HuersHouse_EventScript_Huer::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_HuersHouse_EventScript_HuerAfterOpening
	msgbox Porthliw_HuersHouse_Text_Huer, MSGBOX_NPC
	end

Porthliw_HuersHouse_EventScript_HuerAfterOpening::
	msgbox Porthliw_HuersHouse_Text_HuerAfterOpening, MSGBOX_NPC
	end

Porthliw_HuersHouse_EventScript_Granddaughter::
	msgbox Porthliw_HuersHouse_Text_Granddaughter, MSGBOX_NPC
	end

Porthliw_HuersHouse_Text_Huer:
	.string "I was Porthliw's last huer.\p"
	.string "Up on the cliff, I'd watch the bay\n"
	.string "for the pilchard shoals.\p"
	.string "When the water went red with 'em,\n"
	.string "I'd cry “HEVVA!” and out went\l"
	.string "the boats.\p"
	.string "Fifty years since I last cried it.$"

Porthliw_HuersHouse_Text_HuerAfterOpening:
	.string "Heard young Enys at the gallery.\n"
	.string "Says the sea's changing.\p"
	.string "I watched that bay forty year.\n"
	.string "She's right, my 'ansum.$"

Porthliw_HuersHouse_Text_Granddaughter:
	.string "Grandad says the old light on the\n"
	.string "headland brought the boats home\l"
	.string "for a hundred years.\p"
	.string "Lumen wanted their logo on it for\n"
	.string "the opening. Grandad wrote to the\l"
	.string "council. Three letters!$"
