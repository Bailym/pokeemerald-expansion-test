Balwyn_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Balwyn_PlayersHouse_1F_OnFrame
	.byte 0

Balwyn_PlayersHouse_1F_OnFrame:
	map_script_2 VAR_BALWYN_STATE, BALWYN_STATE_NEW_GAME, Balwyn_PlayersHouse_1F_EventScript_MorningScene
	.2byte 0

@ Mum spots the player coming downstairs, walks over from the sink, and sets the scene for the day.
Balwyn_PlayersHouse_1F_EventScript_MorningScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_BALWYN_PLAYERS_HOUSE_1F_MUM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BALWYN_PLAYERS_HOUSE_1F_MUM, Balwyn_PlayersHouse_1F_Movement_MumToStairs
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumMorning, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BALWYN_PLAYERS_HOUSE_1F_MUM, Balwyn_PlayersHouse_1F_Movement_MumToSink
	waitmovement 0
	setvar VAR_BALWYN_STATE, BALWYN_STATE_MORNING_DONE
	releaseall
	end

Balwyn_PlayersHouse_1F_EventScript_Mum::
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumKelyn, MSGBOX_NPC
	end

@ The stairs step the player down to (8, 3) on arrival, so Mum stops just below them at (8, 4).
Balwyn_PlayersHouse_1F_Movement_MumToStairs:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	face_up
	step_end

Balwyn_PlayersHouse_1F_Movement_MumToSink:
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_PlayersHouse_1F_Text_MumMorning:
	.string "Morning, love! You're up late.\n"
	.string "Breakfast's gone cold, mind.\p"
	.string "There's a right fuss in the\n"
	.string "village today. Lumen's here.\p"
	.string "Some big announcement, they\n"
	.string "reckon. Half of Balwyn's out.\p"
	.string "And Professor Kelyn's in town,\n"
	.string "your Grampy's old friend.\p"
	.string "Go on, have a wander. Say hello\n"
	.string "to the neighbours for me.$"

Balwyn_PlayersHouse_1F_Text_MumKelyn:
	.string "Kelyn used to sit up with Grampy\n"
	.string "till all hours, telling stories.\p"
	.string "Knockers and piskies and all\n"
	.string "sorts. You'll like Kelyn.$"
