CarnKowr_MapScripts::
	.byte 0

@ Grampy's verse plays once, on first stepping onto the climb from Carnrudh.
CarnKowr_EventScript_JournalTrigger::
	lockall
	msgbox CarnKowr_Text_OpenJournal, MSGBOX_DEFAULT
	call CarnKowr_EventScript_Verse
	msgbox CarnKowr_Text_VerseAfterword, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_RIDDLE_READ
	releaseall
	end

CarnKowr_EventScript_Verse::
	msgbox CarnKowr_Text_VerseIntro, MSGBOX_DEFAULT
	msgbox CarnKowr_Text_Verse, MSGBOX_DEFAULT
	return

@ The giant's stones, inspected in the verse's order: Hand, Head, Cradle, then the Well
@ on the peak (see design/Carnrudh.md). Inspecting the stone just done again is harmless.
CarnKowr_EventScript_Hand::
	lockall
	msgbox CarnKowr_Text_Hand, MSGBOX_DEFAULT
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_RIDDLE_READ, CarnKowr_EventScript_HandInOrder
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_HAND_DONE, CarnKowr_EventScript_StoneEnd
	goto CarnKowr_EventScript_OutOfOrder

CarnKowr_EventScript_HandInOrder::
	msgbox CarnKowr_Text_HandInOrder, MSGBOX_DEFAULT
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_HAND_DONE
	goto CarnKowr_EventScript_StoneEnd

CarnKowr_EventScript_Head::
	lockall
	msgbox CarnKowr_Text_Head, MSGBOX_DEFAULT
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_HAND_DONE, CarnKowr_EventScript_HeadInOrder
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_HEAD_DONE, CarnKowr_EventScript_StoneEnd
	goto CarnKowr_EventScript_OutOfOrder

CarnKowr_EventScript_HeadInOrder::
	msgbox CarnKowr_Text_HeadInOrder, MSGBOX_DEFAULT
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_HEAD_DONE
	goto CarnKowr_EventScript_StoneEnd

CarnKowr_EventScript_Cradle::
	lockall
	msgbox CarnKowr_Text_Cradle, MSGBOX_DEFAULT
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_HEAD_DONE, CarnKowr_EventScript_CradleInOrder
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE, CarnKowr_EventScript_StoneEnd
	goto CarnKowr_EventScript_OutOfOrder

CarnKowr_EventScript_CradleInOrder::
	msgbox CarnKowr_Text_CradleInOrder, MSGBOX_DEFAULT
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE
	goto CarnKowr_EventScript_StoneEnd

@ A wrong stone hints at the one that should have come next and resets the order. Once the
@ Cradle is done, only the Well is left, so a climb stone just hints without undoing the gate.
CarnKowr_EventScript_OutOfOrder::
	goto_if_lt VAR_CARNRUDH_STATE, CARNRUDH_STATE_RIDDLE_READ, CarnKowr_EventScript_StoneEnd
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE, CarnKowr_EventScript_StoneEnd
	msgbox CarnKowr_Text_NothingHappens, MSGBOX_DEFAULT
	switch VAR_CARNRUDH_STATE
	case CARNRUDH_STATE_RIDDLE_READ, CarnKowr_EventScript_HintHand
	case CARNRUDH_STATE_HAND_DONE, CarnKowr_EventScript_HintHead
	case CARNRUDH_STATE_HEAD_DONE, CarnKowr_EventScript_HintCradle
	msgbox CarnKowr_Text_HintWell, MSGBOX_DEFAULT
	goto CarnKowr_EventScript_StoneEnd

CarnKowr_EventScript_HintHand::
	msgbox CarnKowr_Text_HintHand, MSGBOX_DEFAULT
	goto CarnKowr_EventScript_ResetOrder

CarnKowr_EventScript_HintHead::
	msgbox CarnKowr_Text_HintHead, MSGBOX_DEFAULT
	goto CarnKowr_EventScript_ResetOrder

CarnKowr_EventScript_HintCradle::
	msgbox CarnKowr_Text_HintCradle, MSGBOX_DEFAULT
	goto CarnKowr_EventScript_ResetOrder

CarnKowr_EventScript_ResetOrder::
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_RIDDLE_READ
	msgbox CarnKowr_Text_ReadAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CarnKowr_EventScript_StoneEnd
	call CarnKowr_EventScript_Verse
	goto CarnKowr_EventScript_StoneEnd

CarnKowr_EventScript_StoneEnd::
	closemessage
	releaseall
	end

@ The peak's gate: until the Cradle is done, the grunt in the gap at the top of the climb
@ turns the player back. Phase 4 of design/plans/carnrudh.md makes him a trainer.
CarnKowr_EventScript_GateTrigger::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE, CarnKowr_EventScript_GateTriggerEnd
	lockall
	playse SE_PIN
	applymovement LOCALID_CARN_KOWR_GATE_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CARN_KOWR_GATE_GRUNT, Common_Movement_FaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox CarnKowr_Text_GateClosed, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	applymovement LOCALID_CARN_KOWR_GATE_GRUNT, Common_Movement_FaceDown
	waitmovement 0
	releaseall
CarnKowr_EventScript_GateTriggerEnd::
	end

CarnKowr_EventScript_GateGrunt::
	lock
	faceplayer
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE, CarnKowr_EventScript_GateOpen
	msgbox CarnKowr_Text_GateClosed, MSGBOX_DEFAULT
	release
	end

CarnKowr_EventScript_GateOpen::
	msgbox CarnKowr_Text_GateOpen, MSGBOX_DEFAULT
	release
	end

@ Name signs beside the stones.
CarnKowr_EventScript_HandSign::
	msgbox CarnKowr_Text_HandSign, MSGBOX_SIGN
	end

CarnKowr_EventScript_CradleSign::
	msgbox CarnKowr_Text_CradleSign, MSGBOX_SIGN
	end

CarnKowr_EventScript_HeadSign::
	msgbox CarnKowr_Text_HeadSign, MSGBOX_SIGN
	end

CarnKowr_Text_Hand:
	.string "A slab of granite, split into\n"
	.string "five long fingers.\p"
	.string "Folk call it the GIANT'S HAND.$"

CarnKowr_Text_Cradle:
	.string "A granite slab with a hollow\n"
	.string "worn in it, like a cot.\p"
	.string "Folk call it the GIANT'S CRADLE.$"

CarnKowr_Text_Head:
	.string "A great round boulder, perched\n"
	.string "on the slope like a head.\p"
	.string "Folk call it the GIANT'S HEAD.$"

CarnKowr_Text_HandSign:
	.string "THE GIANT'S HAND\n"
	.string "One of CARN KOWR's four stones.$"

CarnKowr_Text_CradleSign:
	.string "THE GIANT'S CRADLE\n"
	.string "One of CARN KOWR's four stones.$"

CarnKowr_Text_HeadSign:
	.string "THE GIANT'S HEAD\n"
	.string "One of CARN KOWR's four stones.$"

CarnKowr_Text_OpenJournal:
	.string "{PLAYER} opened the journal to a\n"
	.string "page marked CARN KOWR.$"

CarnKowr_Text_VerseIntro:
	.string "“The rhyme Mam taught me on the\n"
	.string "way up, every Whitsun:$"

CarnKowr_Text_Verse:
	.string "Shake the giant by the hand,\n"
	.string "bow where his great head stands.\p"
	.string "Rock his cradle, soft and low,\n"
	.string "then drink his well, and know.”$"

CarnKowr_Text_VerseAfterword:
	.string "“Mam said the giants carved\n"
	.string "their names in the well.\p"
	.string "Never saw it. Always full of\n"
	.string "rain.”$"

CarnKowr_Text_HandInOrder:
	.string "You clasp the stone's cold\n"
	.string "fingers.$"

CarnKowr_Text_HeadInOrder:
	.string "You bow your head to the giant.$"

CarnKowr_Text_CradleInOrder:
	.string "You give the slab a gentle push.\n"
	.string "It rocks, just slightly.$"

CarnKowr_Text_NothingHappens:
	.string "Nothing happens.\p"
	.string "{PLAYER} checked the journal.$"

CarnKowr_Text_HintHand:
	.string "The rhyme starts with\n"
	.string "a greeting.$"

CarnKowr_Text_HintHead:
	.string "After a handshake… a bow.$"

CarnKowr_Text_HintCradle:
	.string "Something to rock, soft and low.$"

CarnKowr_Text_HintWell:
	.string "Last of all, a drink.$"

CarnKowr_Text_ReadAgain:
	.string "Better start again from the top.\p"
	.string "Read the rhyme again?$"

CarnKowr_Text_GateClosed:
	.string "Hi there! The summit's closed\n"
	.string "for a Lumen heritage survey.\p"
	.string "Why not enjoy the lovely old\n"
	.string "stones on the way up?$"

CarnKowr_Text_GateOpen:
	.string "Seen all the stones? Super!\p"
	.string "Our survey team's at the summit.\n"
	.string "Do say hello!$"
