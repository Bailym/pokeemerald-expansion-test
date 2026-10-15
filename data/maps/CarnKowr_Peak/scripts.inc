CarnKowr_Peak_MapScripts::
	.byte 0

@ Talk-only until phase 4 of design/plans/carnrudh.md adds Peran's battle.
CarnKowr_Peak_EventScript_Peran::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE, CarnKowr_Peak_EventScript_PeranAfterProof
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_Peran, MSGBOX_NPC
	end

@ After the proof (or after losing to him), talking to Peran starts his battle.
CarnKowr_Peak_EventScript_PeranAfterProof::
	lockall
	faceplayer
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranInMyWay, MSGBOX_DEFAULT
	closemessage
	goto CarnKowr_Peak_EventScript_PeranBattle

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

CarnKowr_Peak_EventScript_Proof::
	msgbox CarnKowr_Peak_Text_WellDrains, MSGBOX_DEFAULT
	msgbox CarnKowr_Peak_Text_Carvings, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_STONES_DONE
	playse SE_PIN
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, Common_Movement_ExclamationMark
	waitmovement 0
	call CarnKowr_Peak_EventScript_PeranStepsUp
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranWeathering, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CARN_KOWR_PEAK_TANEK, Common_Movement_FaceLeft
	waitmovement 0
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_TanekSomebodyMadeThat, MSGBOX_DEFAULT
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranInMyWay, MSGBOX_DEFAULT
	closemessage
	goto CarnKowr_Peak_EventScript_PeranBattle

@ The Well is read from (20, 8) or (21, 8), and Peran stands at (20, 9): he steps under the
@ player if needed and looks up at them, and the player turns round to face him.
CarnKowr_Peak_EventScript_PeranStepsUp::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 20, CarnKowr_Peak_EventScript_PeranFacesUp
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, Common_Movement_WalkRight
	waitmovement 0
CarnKowr_Peak_EventScript_PeranFacesUp::
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, Common_Movement_FaceUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

@ Peran's first battle. Afterwards he lets slip what Lumen are really after and walks off,
@ and Tanek, shaken, follows him down to open the gym.
CarnKowr_Peak_EventScript_PeranBattle::
	trainerbattle_no_intro TRAINER_PERAN_CARN_KOWR, CarnKowr_Peak_Text_PeranDefeat
	setspeaker SP_NAME_PERAN
	msgbox CarnKowr_Peak_Text_PeranUnderIt, MSGBOX_DEFAULT
	closemessage
	getobjectxy LOCALID_CARN_KOWR_PEAK_PERAN, CURRENT_POSITION, VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 21, CarnKowr_Peak_EventScript_PeranLeavesFromRight
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, CarnKowr_Peak_Movement_PeranLeaves
	goto CarnKowr_Peak_EventScript_PeranGone

CarnKowr_Peak_EventScript_PeranLeavesFromRight::
	applymovement LOCALID_CARN_KOWR_PEAK_PERAN, CarnKowr_Peak_Movement_PeranLeavesFromRight
CarnKowr_Peak_EventScript_PeranGone::
	waitmovement 0
	removeobject LOCALID_CARN_KOWR_PEAK_PERAN
	applymovement LOCALID_CARN_KOWR_PEAK_TANEK, Common_Movement_FacePlayer
	waitmovement 0
	setspeaker SP_NAME_TANEK
	msgbox CarnKowr_Peak_Text_TanekLoyal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CARN_KOWR_PEAK_TANEK, CarnKowr_Peak_Movement_TanekLeaves
	waitmovement 0
	removeobject LOCALID_CARN_KOWR_PEAK_TANEK
	setflag FLAG_HIDE_CARN_KOWR_PEAK_CAST
	setflag FLAG_HIDE_CARNRUDH_GYM_BLOCKER
	setflag FLAG_HIDE_CARNRUDH_SURVEY_WORKER
	clearflag FLAG_HIDE_CARNRUDH_FESTIVAL
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE
	releaseall
	end

@ Both head down the stairs at x 22-23 and off the bottom of the peak. Peran starts at (20, 9),
@ or at (21, 9) if he stepped under the player.
CarnKowr_Peak_Movement_PeranLeaves:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CarnKowr_Peak_Movement_PeranLeavesFromRight:
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CarnKowr_Peak_Movement_TanekLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

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

CarnKowr_Peak_Text_PeranDefeat:
	.string "Fine. Have your hill.$"

CarnKowr_Peak_Text_PeranUnderIt:
	.string "Keep your stones. The granite\n"
	.string "was only ever the top layer.\p"
	.string "It's not what's on the hill.\n"
	.string "It's what's under it.$"

CarnKowr_Peak_Text_TanekLoyal:
	.string "Lumen dropped the quarry, just\n"
	.string "like that…\p"
	.string "They'll bring the jobs somewhere\n"
	.string "else, that's all. They will.\p"
	.string "I'd best open the gym. Come and\n"
	.string "find me, challenger.$"

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
