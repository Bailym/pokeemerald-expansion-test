CarnKowr_MapScripts::
	.byte 0

@ The giant's stones. Phase 3 of design/plans/carnrudh.md adds the riddle order.
CarnKowr_EventScript_Hand::
	msgbox CarnKowr_Text_Hand, MSGBOX_SIGN
	end

CarnKowr_EventScript_Cradle::
	msgbox CarnKowr_Text_Cradle, MSGBOX_SIGN
	end

CarnKowr_EventScript_Head::
	msgbox CarnKowr_Text_Head, MSGBOX_SIGN
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
