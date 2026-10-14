Balwyn_House1_MapScripts::
	.byte 0

Balwyn_House1_EventScript_Treve::
	setspeaker SP_NAME_TREVE
	msgbox Balwyn_House1_Text_Treve, MSGBOX_NPC
	end

Balwyn_House1_EventScript_Wenna::
	setspeaker SP_NAME_WENNA
	msgbox Balwyn_House1_Text_Wenna, MSGBOX_NPC
	end

Balwyn_House1_Text_Treve:
	.string "Morning! Lost my job when the\n"
	.string "last of the mines shut, I did.\p"
	.string "If Lumen's hiring, I'm first in\n"
	.string "the queue. We need the work.\p"
	.string "Better that than packing up and\n"
	.string "moving up-country like the rest.$"

Balwyn_House1_Text_Wenna:
	.string "Nova's here! Nova from the Lumen\n"
	.string "adverts! With the Pawmi!\p"
	.string "I've got the plushie and\n"
	.string "I'm getting it signed!$"
