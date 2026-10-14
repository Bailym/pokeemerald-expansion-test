Balwyn_House2_MapScripts::
	.byte 0

Balwyn_House2_EventScript_Jacca::
	setspeaker SP_NAME_JACCA
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_House2_EventScript_JaccaAfter
	msgbox Balwyn_House2_Text_Jacca, MSGBOX_NPC
	end

Balwyn_House2_EventScript_JaccaAfter::
	msgbox Balwyn_House2_Text_JaccaAfter, MSGBOX_NPC
	end

Balwyn_House2_Text_Jacca:
	.string "Your Grampy and me worked Wheal\n"
	.string "Gwyn together, forty year back.\p"
	.string "We'd hear the Knockers tapping\n"
	.string "down there. Never felt alone.\p"
	.string "Now Lumen want her open again.\n"
	.string "Some things should stay asleep.$"

Balwyn_House2_Text_JaccaAfter:
	.string "Reopening Wheal Gwyn... Your\n"
	.string "Grampy would turn in his grave.\p"
	.string "Mark my words, the Knockers\n"
	.string "won't stand for it.$"
