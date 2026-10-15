CarnKowr_Peak_MapScripts::
	.byte 0

@ Talk-only until phase 4 of design/plans/carnrudh.md adds Peran's battle.
CarnKowr_Peak_EventScript_Peran::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE, CarnKowr_Peak_EventScript_PeranAfterProof
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_Peran, MSGBOX_NPC
	end

CarnKowr_Peak_EventScript_PeranAfterProof::
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranInMyWay, MSGBOX_NPC
	end

CarnKowr_Peak_EventScript_Tanek::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE, CarnKowr_Peak_EventScript_TanekAfterProof
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_Tanek, MSGBOX_NPC
	end

CarnKowr_Peak_EventScript_TanekAfterProof::
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_TanekAfterProof, MSGBOX_NPC
	end

@ The last of the giant's stones. After the Hand, Head, and Cradle in order, it drains to show
@ the carvings: the proof that the tor is an ancient monument (see design/Carnrudh.md).
CarnKowr_Peak_EventScript_Well::
	lockall
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE, CarnKowr_Peak_EventScript_WellDrained
	msgbox CarnKowr_Peak_Text_Well, MSGBOX_DEFAULT
	goto_if_eq VAR_CARNRUDH_STATE, CARNRUDH_STATE_CRADLE_DONE, CarnKowr_Peak_EventScript_Proof
	closemessage
	releaseall
	end

CarnKowr_Peak_EventScript_WellDrained::
	msgbox CarnKowr_Peak_Text_WellDrained, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ Phase 4 of design/plans/carnrudh.md follows Peran's last line with his battle.
CarnKowr_Peak_EventScript_Proof::
	msgbox CarnKowr_Peak_Text_WellDrains, MSGBOX_DEFAULT
	msgbox CarnKowr_Peak_Text_Carvings, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE
	playse SE_PIN
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, Common_Movement_FacePlayer
	waitmovement 0
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranWeathering, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CARN_KOWR_PEAK_TANEK, Common_Movement_FacePlayer
	waitmovement 0
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_TanekSomebodyMadeThat, MSGBOX_DEFAULT
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranInMyWay, MSGBOX_DEFAULT
	closemessage
	releaseall
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

CarnKowr_Peak_Text_WellDrains:
	.string "You scoop up a handful of\n"
	.string "rainwater. The level drops…\p"
	.string "…and keeps dropping, draining\n"
	.string "through a crack in the granite.$"

CarnKowr_Peak_Text_Carvings:
	.string "Carved into the bottom of the\n"
	.string "basin: rings of little cups\l"
	.string "around a spiral.\p"
	.string "They're worn soft by thousands\n"
	.string "of years of rain.$"

CarnKowr_Peak_Text_WellDrained:
	.string "The basin is dry. Little cups\n"
	.string "ring a carved spiral.$"

CarnKowr_Peak_Text_PeranWeathering:
	.string "Weathering. Granite does that.$"

CarnKowr_Peak_Text_TanekSomebodyMadeThat:
	.string "That's no weathering, Peran.\p"
	.string "Somebody made that. By hand.$"

CarnKowr_Peak_Text_PeranInMyWay:
	.string "Then somebody's in my way.$"

CarnKowr_Peak_Text_TanekAfterProof:
	.string "Cups and rings, carved in rock…\n"
	.string "How long's that been up here?$"

CarnKowr_Peak_Text_SurveySign:
	.string "LUMEN SURVEY SITE\n"
	.string "No entry beyond this point.\p"
	.string "Heritage granite for a\n"
	.string "greener tomorrow!$"

CarnKowr_Peak_Text_WellSign:
	.string "THE GIANT'S WELL\n"
	.string "One of CARN KOWR's four stones.$"
