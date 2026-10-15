CarnKowr_Peak_MapScripts::
	.byte 0

@ Talk-only until phase 4 of design/plans/carnrudh.md adds Peran's battle.
CarnKowr_Peak_EventScript_Peran::
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_Peran, MSGBOX_NPC
	end

CarnKowr_Peak_EventScript_Tanek::
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_Tanek, MSGBOX_NPC
	end

CarnKowr_Peak_EventScript_Well::
	msgbox CarnKowr_Peak_Text_Well, MSGBOX_SIGN
	end

CarnKowr_Peak_EventScript_WellSign::
	msgbox CarnKowr_Peak_Text_WellSign, MSGBOX_SIGN
	end

CarnKowr_Peak_EventScript_SurveySign::
	msgbox CarnKowr_Peak_Text_SurveySign, MSGBOX_SIGN
	end

CarnKowr_Peak_Text_Peran:
	.string "Survey's in progress. Keep\n"
	.string "behind the line, please.\p"
	.string "Solid granite, this tor, top to\n"
	.string "bottom. I grew up under it.\p"
	.string "About time it did some work.$"

CarnKowr_Peak_Text_Tanek:
	.string "A challenger? Gym can wait.\p"
	.string "Lumen reckon there's a hundred\n"
	.string "jobs in this hill. A hundred!\p"
	.string "That's a hundred families who\n"
	.string "won't have to move away.$"

CarnKowr_Peak_Text_Well:
	.string "A deep hollow in the granite,\n"
	.string "brimming with rainwater.\p"
	.string "Folk call it the GIANT'S WELL.$"

CarnKowr_Peak_Text_SurveySign:
	.string "LUMEN SURVEY SITE\n"
	.string "No entry beyond this point.\p"
	.string "Heritage granite for a\n"
	.string "greener tomorrow!$"

CarnKowr_Peak_Text_WellSign:
	.string "THE GIANT'S WELL\n"
	.string "One of CARN KOWR's four stones.$"
