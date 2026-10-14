Balwyn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Balwyn_OnTransition
	.byte 0

Balwyn_OnTransition:
	call_if_ge VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER, Balwyn_EventScript_OpenRoadEast
	end

@ The road-block triggers only fire while VAR_TEMP_1 is 0.
Balwyn_EventScript_OpenRoadEast::
	setvar VAR_TEMP_1, 1
	return

@ A Lumen grunt turns the player back from the road east until they have a starter.
Balwyn_EventScript_RoadBlockTop::
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER, Balwyn_EventScript_RoadBlockEnd
	lockall
	playse SE_PIN
	applymovement LOCALID_BALWYN_ROAD_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	call Balwyn_EventScript_RoadGruntSpeech
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_PlayerBackWest
	waitmovement 0
	releaseall
	end

Balwyn_EventScript_RoadBlockBottom::
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER, Balwyn_EventScript_RoadBlockEnd
	lockall
	playse SE_PIN
	applymovement LOCALID_BALWYN_ROAD_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BALWYN_ROAD_GRUNT, Balwyn_Movement_GruntStepDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	call Balwyn_EventScript_RoadGruntSpeech
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_PlayerBackWest
	applymovement LOCALID_BALWYN_ROAD_GRUNT, Balwyn_Movement_GruntStepBackUp
	waitmovement 0
	releaseall
	end

Balwyn_EventScript_RoadBlockEnd::
	end

Balwyn_EventScript_RoadGrunt::
	lock
	faceplayer
	call Balwyn_EventScript_RoadGruntSpeech
	release
	end

Balwyn_EventScript_RoadGruntSpeech::
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_SENT_TO_MINE, Balwyn_EventScript_RoadGruntSpeechRepeat
	msgbox Balwyn_Text_RoadGruntSendToMine, MSGBOX_DEFAULT
	closemessage
	setvar VAR_BALWYN_STATE, BALWYN_STATE_SENT_TO_MINE
	return

Balwyn_EventScript_RoadGruntSpeechRepeat::
	msgbox Balwyn_Text_RoadGruntRepeat, MSGBOX_DEFAULT
	closemessage
	return

Balwyn_Movement_PlayerBackWest:
	walk_left
	walk_left
	step_end

Balwyn_Movement_GruntStepDown:
	walk_down
	step_end

Balwyn_Movement_GruntStepBackUp:
	walk_up
	face_down
	step_end

Balwyn_Text_RoadGruntSendToMine:
	.string "Hold up there! Road's closed\n"
	.string "for a bit, I'm afraid.\p"
	.string "It's a big day for Balwyn! Lumen\n"
	.string "has an exciting announcement.\p"
	.string "Everyone's meeting up at the old\n"
	.string "mine, Wheal Gwyn. Head on over!$"

Balwyn_Text_RoadGruntRepeat:
	.string "The announcement's up at Wheal\n"
	.string "Gwyn. You won't want to miss it!$"

Balwyn_EventScript_MineSign::
	msgbox Balwyn_Text_MineSign, MSGBOX_SIGN
	end

Balwyn_EventScript_PubSign::
	msgbox Balwyn_Text_PubSign, MSGBOX_SIGN
	end

Balwyn_Text_MineSign:
	.string "WHEAL GWYN\n"
	.string "DANGER! Old mine workings.\p"
	.string "Shafts and adits unsafe.\n"
	.string "Keep out by order of the parish.$"

Balwyn_Text_PubSign:
	.string "THE KNOCKER'S ARMS\n"
	.string "Free house, est. 1782.\p"
	.string "Pasties, ale, and old tales.\n"
	.string "Leave a crust for the Knockers!$"
