Balwyn_Pub_MapScripts::
	.byte 0

Balwyn_Pub_EventScript_Morwenna::
	setspeaker SP_NAME_MORWENNA
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_Pub_EventScript_MorwennaAfter
	msgbox Balwyn_Pub_Text_Morwenna, MSGBOX_NPC
	end

Balwyn_Pub_EventScript_MorwennaAfter::
	msgbox Balwyn_Pub_Text_MorwennaAfter, MSGBOX_NPC
	end

@ The bar's counter tiles aren't MB_COUNTER, so a bg_event on the counter lets the player talk to Morwenna across it.
Balwyn_Pub_EventScript_MorwennaAcrossCounter::
	lockall
	applymovement LOCALID_BALWYN_PUB_MORWENNA, Common_Movement_FaceDown
	waitmovement 0
	setspeaker SP_NAME_MORWENNA
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_Pub_EventScript_MorwennaAfterAcrossCounter
	msgbox Balwyn_Pub_Text_Morwenna, MSGBOX_DEFAULT
	releaseall
	end

Balwyn_Pub_EventScript_MorwennaAfterAcrossCounter::
	msgbox Balwyn_Pub_Text_MorwennaAfter, MSGBOX_DEFAULT
	releaseall
	end

Balwyn_Pub_EventScript_Regular::
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_Pub_EventScript_RegularAfter
	msgbox Balwyn_Pub_Text_Regular, MSGBOX_NPC
	end

Balwyn_Pub_EventScript_RegularAfter::
	msgbox Balwyn_Pub_Text_RegularAfter, MSGBOX_NPC
	end

Balwyn_Pub_Text_Morwenna:
	.string "Welcome to the Knocker's Arms,\n"
	.string "my 'ansum. Oldest pub in Balwyn.\p"
	.string "Named for the Knockers, it is.\n"
	.string "The little folk down the mines.\p"
	.string "Miners always left 'em a bit of\n"
	.string "pasty crust. For luck, see.$"

Balwyn_Pub_Text_Regular:
	.string "My granfer went overseas\n"
	.string "when the mines here shut.\p"
	.string "Half of Balwyn did. Cousin\n"
	.string "Jacks, they called 'em.\p"
	.string "Now it's the young 'uns going\n"
	.string "up-country. Same story, see.$"

Balwyn_Pub_Text_MorwennaAfter:
	.string "Lumen's all anyone's talking\n"
	.string "about. Trade's booming, mind.\p"
	.string "But the old miners aren't happy.\n"
	.string "Say the mine's best left be.$"

Balwyn_Pub_Text_RegularAfter:
	.string "Lumen jobs, eh? Might be my\n"
	.string "grandkids won't have to leave.\p"
	.string "Or might be they're digging up\n"
	.string "more than tin. Who's to say?$"
