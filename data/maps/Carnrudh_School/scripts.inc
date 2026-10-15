Carnrudh_School_MapScripts::
	.byte 0

Carnrudh_School_EventScript_PupilBoy::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_School_EventScript_PupilBoyFestival
	msgbox Carnrudh_School_Text_PupilBoy, MSGBOX_NPC
	end

Carnrudh_School_EventScript_PupilBoyFestival::
	msgbox Carnrudh_School_Text_PupilBoyFestival, MSGBOX_NPC
	end

Carnrudh_School_EventScript_PupilGirl::
	msgbox Carnrudh_School_Text_PupilGirl, MSGBOX_NPC
	end

@ The teacher gives a Hard Stone once, after the tor is saved.
Carnrudh_School_EventScript_Teacher::
	lock
	faceplayer
	goto_if_lt VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_School_EventScript_TeacherBefore
	goto_if_set FLAG_RECEIVED_HARD_STONE_CARNRUDH, Carnrudh_School_EventScript_TeacherAfter
	msgbox Carnrudh_School_Text_TeacherGift, MSGBOX_DEFAULT
	giveitem ITEM_HARD_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_HARD_STONE_CARNRUDH
	msgbox Carnrudh_School_Text_TeacherExplainHardStone, MSGBOX_DEFAULT
	release
	end

Carnrudh_School_EventScript_TeacherBefore::
	msgbox Carnrudh_School_Text_TeacherBefore, MSGBOX_DEFAULT
	release
	end

Carnrudh_School_EventScript_TeacherAfter::
	msgbox Carnrudh_School_Text_TeacherAfter, MSGBOX_DEFAULT
	release
	end

Carnrudh_School_EventScript_Blackboard::
	msgbox Carnrudh_School_Text_Blackboard, MSGBOX_SIGN
	end

Carnrudh_School_Text_PupilBoy:
	.string "I'm drawing the PUFFING BUCCA\n"
	.string "for the parade!$"

Carnrudh_School_Text_PupilBoyFestival:
	.string "My drawing's in the parade!$"

Carnrudh_School_Text_PupilGirl:
	.string "Did you know? Tinners stuck\n"
	.string "candles on their hats with clay!$"

Carnrudh_School_Text_TeacherBefore:
	.string "Welcome to the old MINERS'\n"
	.string "SCHOOL. It's all history now.\p"
	.string "CAP'N PENHALLOW himself studied\n"
	.string "here, you know.$"

Carnrudh_School_Text_TeacherGift:
	.string "You saved the tor! Here, a bit\n"
	.string "of it for you.$"

Carnrudh_School_Text_TeacherExplainHardStone:
	.string "That's a HARD STONE. Granite\n"
	.string "from CARN KOWR, near enough.$"

Carnrudh_School_Text_TeacherAfter:
	.string "The tor's in the history books\n"
	.string "now, thanks to you.$"

Carnrudh_School_Text_Blackboard:
	.string "A chalk drawing of a steam\n"
	.string "engine, labelled PUFFING BUCCA.\p"
	.string "Underneath: CAP'N JOWAN\n"
	.string "PENHALLOW, ENGINEER.$"
