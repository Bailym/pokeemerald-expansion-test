Balwyn_House1_MapScripts::
	.byte 0

Balwyn_House1_EventScript_Treve::
	setspeaker SP_NAME_TREVE
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_House1_EventScript_TreveAfter
	msgbox Balwyn_House1_Text_Treve, MSGBOX_NPC
	end

Balwyn_House1_EventScript_TreveAfter::
	msgbox Balwyn_House1_Text_TreveAfter, MSGBOX_NPC
	end

Balwyn_House1_EventScript_Wenna::
	setspeaker SP_NAME_WENNA
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_House1_EventScript_WennaAfter
	msgbox Balwyn_House1_Text_Wenna, MSGBOX_NPC
	end

Balwyn_House1_EventScript_WennaAfter::
	msgbox Balwyn_House1_Text_WennaAfter, MSGBOX_NPC
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

Balwyn_House1_Text_TreveAfter:
	.string "Jobs, right here in Balwyn!\n"
	.string "I've put my name down already.\p"
	.string "Old Jacca can grumble all he\n"
	.string "likes. We've a family to feed.$"

Balwyn_House1_Text_WennaAfter:
	.string "Nova waved at me! Right at me!\n"
	.string "I'm going to be just like Nova!$"
