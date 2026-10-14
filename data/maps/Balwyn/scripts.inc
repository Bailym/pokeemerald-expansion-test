Balwyn_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Balwyn_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Balwyn_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Balwyn_OnFrame
	.byte 0

Balwyn_OnFrame:
	map_script_2 VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER, Balwyn_EventScript_NovaBattle
	.2byte 0

Balwyn_OnLoad:
	call_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_EventScript_ShowMineWorks
	end

@ After the announcement, Lumen has opened the middle of the Wheal Gwyn fence (posted grunts stand in the gap)
@ and put up a notice board by the path.
Balwyn_EventScript_ShowMineWorks::
	setmetatile 5, 8, 0x148, TRUE
	setmetatile 6, 8, 0x14A, TRUE
	setmetatile 7, 8, 0x001, FALSE
	setmetatile 8, 8, 0x001, FALSE
	setmetatile 9, 8, 0x148, TRUE
	setmetatile 10, 8, 0x14A, TRUE
	setmetatile 10, 9, 0x37B, TRUE
	return

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
	@ The village gathers at Wheal Gwyn, so the event cast appears there and the villagers leave home.
	clearflag FLAG_HIDE_BALWYN_EVENT_CAST
	setflag FLAG_HIDE_BALWYN_VILLAGERS_HOME
	addobject LOCALID_BALWYN_NOVA
	addobject LOCALID_BALWYN_PAWMI
	addobject LOCALID_BALWYN_EVENT_GRUNT
	addobject LOCALID_BALWYN_EVENT_TREVE
	addobject LOCALID_BALWYN_EVENT_WENNA
	addobject LOCALID_BALWYN_EVENT_JACCA
	addobject LOCALID_BALWYN_EVENT_KELYN
	return

Balwyn_EventScript_RoadGruntSpeechRepeat::
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_EventScript_RoadGruntSafetyFirst
	msgbox Balwyn_Text_RoadGruntRepeat, MSGBOX_DEFAULT
	closemessage
	return

Balwyn_EventScript_RoadGruntSafetyFirst::
	msgbox Balwyn_Text_RoadGruntSafetyFirst, MSGBOX_DEFAULT
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

Balwyn_Text_RoadGruntSafetyFirst:
	.string "Safety first! Wild Pokémon on\n"
	.string "the road. Not without your own!$"

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

@ The event cast is only visible during the announcement, which starts before the player can reach them.
Balwyn_EventScript_EventCast::
	end

@ Lumen's announcement at the Wheal Gwyn fence. Triggers sit east of the crowd (x 13) and along the road in front of it (row 12).
@ Each mine-event trigger walks the player into the crowd at (9, 11): onto row 11, which the crowd leaves clear, then along it.
Balwyn_EventScript_MineEventAt_13_9::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_13_9
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_13_10::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_13_10
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_13_11::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_13_11
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_13_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_13_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_5_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_5_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_6_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_6_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_7_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_7_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_8_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_8_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_9_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_9_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_10_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_10_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_11_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_11_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_EventScript_MineEventAt_12_12::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_Movement_JoinCrowdFrom_12_12
	waitmovement 0
	goto Balwyn_EventScript_MineEvent

Balwyn_Movement_JoinCrowdFrom_13_9:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_13_10:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_13_11:
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_13_12:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_5_12:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_6_12:
	walk_up
	walk_right
	walk_right
	walk_right
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_7_12:
	walk_up
	walk_right
	walk_right
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_8_12:
	walk_up
	walk_right
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_9_12:
	walk_up
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_10_12:
	walk_up
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_11_12:
	walk_up
	walk_left
	walk_left
	face_up
	step_end

Balwyn_Movement_JoinCrowdFrom_12_12:
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

Balwyn_EventScript_MineEvent::
	applymovement LOCALID_BALWYN_NOVA, Balwyn_Movement_SpeakDown
	waitmovement 0
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaIntro, MSGBOX_DEFAULT
	applymovement LOCALID_BALWYN_PAWMI, Balwyn_Movement_Hop
	playmoncry SPECIES_PAWMI, CRY_MODE_NORMAL
	waitmovement 0
	waitmoncry
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaAnnouncement, MSGBOX_DEFAULT
	applymovement LOCALID_BALWYN_EVENT_TREVE, Balwyn_Movement_SpeakUp
	waitmovement 0
	setspeaker SP_NAME_TREVE
	msgbox Balwyn_Text_TreveReacts, MSGBOX_DEFAULT
	applymovement LOCALID_BALWYN_EVENT_WENNA, Balwyn_Movement_Hop
	waitmovement 0
	setspeaker SP_NAME_WENNA
	msgbox Balwyn_Text_WennaReacts, MSGBOX_DEFAULT
	applymovement LOCALID_BALWYN_EVENT_JACCA, Balwyn_Movement_SpeakUp
	waitmovement 0
	setspeaker SP_NAME_JACCA
	msgbox Balwyn_Text_JaccaMutters, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BALWYN_EVENT_KELYN, Balwyn_Movement_KelynStepForward
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_Text_KelynQuestion, MSGBOX_DEFAULT
	applymovement LOCALID_BALWYN_NOVA, Balwyn_Movement_SpeakDown
	waitmovement 0
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaLaughsOff, MSGBOX_DEFAULT
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaSignOff, MSGBOX_DEFAULT
	closemessage
	@ Kelyn comes round from the stage to stand beside the player at (10, 11).
	applymovement LOCALID_BALWYN_EVENT_KELYN, Balwyn_Movement_KelynToPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_Text_KelynToPlayer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_BALWYN_EVENT_CAST
	clearflag FLAG_HIDE_BALWYN_VILLAGERS_HOME
	clearflag FLAG_HIDE_BALWYN_HOUSE_KELYN
	clearflag FLAG_HIDE_BALWYN_MINE_GRUNTS
	setvar VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE
	@ Kelyn walks the player home; the kitchen-table scene picks up inside, just above the doormat.
	warp MAP_BALWYN_PLAYERS_HOUSE_1F, 8, 7
	waitstate
	releaseall
	end

Balwyn_Movement_KelynToPlayer:
	walk_down
	walk_down
	walk_left
	walk_left
	face_left
	step_end

Balwyn_Movement_SpeakDown:
	walk_in_place_faster_down
	step_end

Balwyn_Movement_SpeakUp:
	walk_in_place_faster_up
	step_end

Balwyn_Movement_Hop:
	jump_in_place_down
	step_end

Balwyn_Movement_KelynStepForward:
	walk_up
	face_left
	step_end

Balwyn_Movement_FacePlayer:
	face_player
	step_end

Balwyn_Text_NovaIntro:
	.string "Hey hey, Balwyn! I'm Nova, and\n"
	.string "this is my partner, Pawmi!$"

Balwyn_Text_NovaAnnouncement:
	.string "Lumen is so proud to share some\n"
	.string "huge news with you today...\p"
	.string "We're reopening Wheal Gwyn!\n"
	.string "Real jobs, right here at home!\p"
	.string "Lumen is bringing the mines\n"
	.string "home! Clean, safe, and modern!$"

Balwyn_Text_TreveReacts:
	.string "Jobs? Here in Balwyn? Now\n"
	.string "you're talking!$"

Balwyn_Text_WennaReacts:
	.string "Nova! Nova! Over here!\n"
	.string "I love you, Pawmi!$"

Balwyn_Text_JaccaMutters:
	.string "Wheal Gwyn was sealed for a\n"
	.string "reason, boy. You mark me.$"

Balwyn_Text_KelynQuestion:
	.string "Professor Kelyn. I study the\n"
	.string "old legends. If I may...\p"
	.string "The miners who sealed Wheal Gwyn\n"
	.string "spoke of the Bucca below.\p"
	.string "Has Lumen given any thought\n"
	.string "to what sleeps down there?$"

Balwyn_Text_NovaLaughsOff:
	.string "Ha ha! Ghost stories? We've got\n"
	.string "engineers, not piskies!\p"
	.string "The only spirit down there is\n"
	.string "team spirit! Right, Balwyn?$"

Balwyn_Text_NovaSignOff:
	.string "Sign-ups open soon! Thanks,\n"
	.string "Balwyn! Lumen loves you!$"

Balwyn_Text_KelynToPlayer:
	.string "You must be {PLAYER}. You've\n"
	.string "your Grampy's look about you.\p"
	.string "Walk with me to your mum's?\n"
	.string "I've something for you.$"

@ Stepping out of the house with a starter (to (7, 18)), Nova is waiting below with Pawmi and challenges the player.
@ trainerbattle_earlyrival continues either way; VAR_RESULT is TRUE if the player lost (and the team is healed).
Balwyn_EventScript_NovaBattle::
	lockall
	applymovement LOCALID_BALWYN_SENDOFF_NOVA, Common_Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_earlyrival TRAINER_NOVA_BALWYN, RIVAL_BATTLE_HEAL_AFTER, Balwyn_Text_NovaDefeated, Balwyn_Text_NovaVictory
	goto_if_eq VAR_RESULT, TRUE, Balwyn_EventScript_NovaWon
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaAfterPlayerWon, MSGBOX_DEFAULT
	goto Balwyn_EventScript_NovaSendOff

Balwyn_EventScript_NovaWon::
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaAfterPlayerLost, MSGBOX_DEFAULT
Balwyn_EventScript_NovaSendOff::
	setspeaker SP_NAME_NOVA
	msgbox Balwyn_Text_NovaOffToCarnrudh, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BALWYN_SENDOFF_NOVA, Balwyn_Movement_NovaLeavesEast
	applymovement LOCALID_BALWYN_SENDOFF_PAWMI, Balwyn_Movement_PawmiLeavesEast
	waitmovement 0
	removeobject LOCALID_BALWYN_SENDOFF_NOVA
	removeobject LOCALID_BALWYN_SENDOFF_PAWMI
	applymovement LOCALID_BALWYN_SENDOFF_KELYN, Common_Movement_FaceRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_Text_KelynGoodbye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BALWYN_SENDOFF_KELYN, Balwyn_Movement_KelynLeavesEast
	waitmovement 0
	removeobject LOCALID_BALWYN_SENDOFF_KELYN
	setflag FLAG_HIDE_BALWYN_SENDOFF
	setvar VAR_BALWYN_STATE, BALWYN_STATE_NOVA_BATTLED
	releaseall
	end

@ East along row 19 (and 20 for Pawmi) until off-screen.
Balwyn_Movement_NovaLeavesEast:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Balwyn_Movement_PawmiLeavesEast:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Balwyn_Movement_KelynLeavesEast:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Balwyn_Text_NovaChallenge:
	.string "Hey, it's the local kid! You got\n"
	.string "a Pokémon? Nice!\p"
	.string "How about a quick battle? The\n"
	.string "cameras would love it!$"

Balwyn_Text_NovaDefeated:
	.string "Whoa, nice! The fans are gonna\n"
	.string "love this!$"

Balwyn_Text_NovaVictory:
	.string "And that's how Lumen does it!\n"
	.string "No hard feelings, local!$"

Balwyn_Text_NovaAfterPlayerWon:
	.string "You're a natural! You'll do well\n"
	.string "in the gym challenge, local.$"

Balwyn_Text_NovaAfterPlayerLost:
	.string "Don't sweat it! Everyone starts\n"
	.string "somewhere. Even me!$"

Balwyn_Text_NovaOffToCarnrudh:
	.string "Pawmi and I are off to Carnrudh.\n"
	.string "See you at the gym!$"

Balwyn_Text_KelynGoodbye:
	.string "Well fought, {PLAYER}.\p"
	.string "I must get back to my lab in\n"
	.string "Treveur. Come and find me there.\p"
	.string "And keep that journal close,\n"
	.string "won't you?$"

@ Lumen's notice board only exists once the announcement has happened (see Balwyn_EventScript_ShowMineWorks).
Balwyn_EventScript_LumenNotice::
	goto_if_lt VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_EventScript_RoadBlockEnd
	msgbox Balwyn_Text_LumenNotice, MSGBOX_SIGN
	end

Balwyn_EventScript_MineGrunt1::
	msgbox Balwyn_Text_MineGrunt1, MSGBOX_NPC
	end

Balwyn_EventScript_MineGrunt2::
	msgbox Balwyn_Text_MineGrunt2, MSGBOX_NPC
	end

@ The first time the player comes near the Wheal Gwyn fence after Nova's send-off, they hear the Knockers.
Balwyn_EventScript_FirstKnocking::
	lockall
	delay 30
	playse SE_WALL_HIT
	waitse
	delay 24
	playse SE_WALL_HIT
	waitse
	delay 24
	playse SE_WALL_HIT
	waitse
	delay 30
	msgbox Balwyn_Text_KnockKnock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	msgbox Balwyn_Text_KnockingFromTheMine, MSGBOX_DEFAULT
	msgbox Balwyn_Text_GruntPipes, MSGBOX_DEFAULT
	closemessage
	setvar VAR_BALWYN_STATE, BALWYN_STATE_KNOCKING_HEARD
	releaseall
	end

Balwyn_Text_LumenNotice:
	.string "WHEAL GWYN REOPENS!\n"
	.string "A Lumen heritage project.\p"
	.string "Bringing the mines home.\n"
	.string "Clean. Safe. Modern.$"

Balwyn_Text_MineGrunt1:
	.string "Wheal Gwyn's in safe hands now!\n"
	.string "Our engineers are surveying.\p"
	.string "Site's closed to the public for\n"
	.string "now, though. Safety first!$"

Balwyn_Text_MineGrunt2:
	.string "Funny old place, this. The lads\n"
	.string "hear tapping down there, nights.\p"
	.string "Probably just the pipes.$"

Balwyn_Text_KnockKnock:
	.string "...tok... tok... tok...$"

Balwyn_Text_KnockingFromTheMine:
	.string "The tapping seems to come from\n"
	.string "deep inside Wheal Gwyn...$"

Balwyn_Text_GruntPipes:
	.string "There it goes again. Must be\n"
	.string "the pipes. ...Right?$"
