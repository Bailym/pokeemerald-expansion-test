Porthliw_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Porthliw_OnTransition
	.byte 0

@ Porthliw can be flown to once visited (Town Map, badge 2).
Porthliw_OnTransition:
	setflag FLAG_VISITED_PORTHLIW
	end

Porthliw_EventScript_TownSign::
	msgbox Porthliw_Text_TownSign, MSGBOX_SIGN
	end

Porthliw_EventScript_GymSign::
	msgbox Porthliw_Text_GymSign, MSGBOX_SIGN
	end

@ The gym is shut until the gallery's opening night is over. Walking into a door warps before any
@ sign is read, so the note is a trigger on the step below the door that turns the player back.
Porthliw_EventScript_GymShut::
	lockall
	msgbox Porthliw_Text_GymDoorShut, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

Porthliw_EventScript_GallerySign::
	msgbox Porthliw_Text_GallerySign, MSGBOX_SIGN
	end

@ Every way in from Route 2 crosses column x 31 (rows 21-28), so the triggers there make sure the
@ player meets Enys before the gallery. She calls out from her easel at (29, 27), the player comes
@ over along x 31 to (31, 27), and she steps across to meet them at (30, 27).
Porthliw_EventScript_EnysCallsOut::
	lockall
	playse SE_PIN
	applymovement LOCALID_PORTHLIW_ENYS, Common_Movement_ExclamationMark
	waitmovement 0
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysCallsOut, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 21, Porthliw_EventScript_PlayerComesOverFrom21
	call_if_eq VAR_0x8005, 22, Porthliw_EventScript_PlayerComesOverFrom22
	call_if_eq VAR_0x8005, 23, Porthliw_EventScript_PlayerComesOverFrom23
	call_if_eq VAR_0x8005, 24, Porthliw_EventScript_PlayerComesOverFrom24
	call_if_eq VAR_0x8005, 25, Porthliw_EventScript_PlayerComesOverFrom25
	call_if_eq VAR_0x8005, 26, Porthliw_EventScript_PlayerComesOverFrom26
	call_if_eq VAR_0x8005, 27, Porthliw_EventScript_PlayerComesOverFrom27
	call_if_eq VAR_0x8005, 28, Porthliw_EventScript_PlayerComesOverFrom28
	applymovement LOCALID_PORTHLIW_ENYS, Porthliw_Movement_EnysComesOver
	waitmovement 0
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysIntro, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysGymShut, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysOnLumen, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysInvite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_ENYS, Porthliw_Movement_EnysBackToEasel
	waitmovement 0
	setvar VAR_PORTHLIW_STATE, PORTHLIW_STATE_MET_ENYS
	releaseall
	end

Porthliw_EventScript_PlayerComesOverFrom21::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown6
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom22::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown5
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom23::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown4
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom24::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown3
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom25::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown2
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom26::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerDown1
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom27::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerFaceEnys
	waitmovement 0
	return

Porthliw_EventScript_PlayerComesOverFrom28::
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Movement_PlayerUp1
	waitmovement 0
	return

@ The rows share one run of steps: each label starts that many steps short of row 27.
Porthliw_Movement_PlayerDown6:
	walk_down
Porthliw_Movement_PlayerDown5:
	walk_down
Porthliw_Movement_PlayerDown4:
	walk_down
Porthliw_Movement_PlayerDown3:
	walk_down
Porthliw_Movement_PlayerDown2:
	walk_down
Porthliw_Movement_PlayerDown1:
	walk_down
Porthliw_Movement_PlayerFaceEnys:
	face_left
	step_end

Porthliw_Movement_PlayerUp1:
	walk_up
	face_left
	step_end

Porthliw_Movement_EnysComesOver:
	walk_right
	step_end

Porthliw_Movement_EnysBackToEasel:
	walk_left
	face_down
	step_end

Porthliw_EventScript_Enys::
	lock
	faceplayer
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Text_EnysRepeat, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_ENYS, Common_Movement_FaceDown
	waitmovement 0
	release
	end

Porthliw_EventScript_GalleryStaff::
	lock
	faceplayer
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_EventScript_GalleryStaffAfterOpening
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_MET_ENYS, Porthliw_EventScript_GalleryStaffLetsIn
	msgbox Porthliw_Text_GalleryInvitationOnly, MSGBOX_DEFAULT
	release
	end

Porthliw_EventScript_GalleryStaffAfterOpening::
	msgbox Porthliw_Text_GalleryStaffAfterOpening, MSGBOX_DEFAULT
	release
	end

Porthliw_EventScript_GalleryStaffLetsIn::
	msgbox Porthliw_Text_GalleryGoOnIn, MSGBOX_DEFAULT
	release
	end

@ Stepping up to the gallery door before meeting Enys. Every way here crosses Enys's triggers
@ first, so this only guards against getting here another way.
Porthliw_EventScript_GalleryTurnedAway::
	lockall
	applymovement LOCALID_PORTHLIW_GALLERY_STAFF, Common_Movement_FaceRight
	waitmovement 0
	msgbox Porthliw_Text_GalleryInvitationOnly, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

@ After Barbara Hepworth's garden in St Ives.
Porthliw_EventScript_SculptureGardenSign::
	msgbox Porthliw_Text_SculptureGardenSign, MSGBOX_SIGN
	end

@ The statue in the harbour square, read from below its base.
Porthliw_EventScript_HarbourLight::
	msgbox Porthliw_Text_HarbourLight, MSGBOX_SIGN
	end

Porthliw_EventScript_Tourist::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_EventScript_TouristAfterOpening
	msgbox Porthliw_Text_Tourist, MSGBOX_NPC
	end

Porthliw_EventScript_TouristAfterOpening::
	msgbox Porthliw_Text_TouristAfterOpening, MSGBOX_NPC
	end

Porthliw_EventScript_Painter::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_EventScript_PainterAfterOpening
	msgbox Porthliw_Text_Painter, MSGBOX_NPC
	end

Porthliw_EventScript_PainterAfterOpening::
	msgbox Porthliw_Text_PainterAfterOpening, MSGBOX_NPC
	end

Porthliw_EventScript_Birdwatcher::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_EventScript_BirdwatcherAfterOpening
	msgbox Porthliw_Text_Birdwatcher, MSGBOX_NPC
	end

Porthliw_EventScript_BirdwatcherAfterOpening::
	msgbox Porthliw_Text_BirdwatcherAfterOpening, MSGBOX_NPC
	end

Porthliw_EventScript_Local::
	goto_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_EventScript_LocalAfterOpening
	msgbox Porthliw_Text_Local, MSGBOX_NPC
	end

Porthliw_EventScript_LocalAfterOpening::
	msgbox Porthliw_Text_LocalAfterOpening, MSGBOX_NPC
	end

Porthliw_Text_TownSign:
	.string "PORTHLIW\n"
	.string "The cove of colour.$"

Porthliw_Text_GymSign:
	.string "PORTHLIW POKéMON GYM\n"
	.string "LEADER: ENYS\p"
	.string "Wings over the bay,\n"
	.string "light in every colour!$"

Porthliw_Text_GymDoorShut:
	.string "The door's locked. There's a note\n"
	.string "pinned to it…\p"
	.string "“GYM SHUT for the gallery's\n"
	.string "opening night. - ENYS”$"

Porthliw_Text_GallerySign:
	.string "PORTHLIW GALLERY\n"
	.string "Grand opening night!\p"
	.string "Proudly sponsored by Lumen.$"

Porthliw_Text_SculptureGardenSign:
	.string "KERENSA'S GARDEN\p"
	.string "The sculptor KERENSA carved here\n"
	.string "for forty years.\p"
	.string "“The sea smooths every stone.\n"
	.string "I just help it along.”$"

Porthliw_Text_HarbourLight:
	.string "THE OLD HARBOUR LIGHT\p"
	.string "For a hundred years it guided\n"
	.string "the pilchard boats home.$"

Porthliw_Text_EnysCallsOut:
	.string "Oi! You with the POKéMON!\n"
	.string "Over here a minute!$"

Porthliw_Text_EnysIntro:
	.string "Sorry to holler. You walked\n"
	.string "right into my light!\p"
	.string "I'm Enys. I paint the gulls\n"
	.string "over the bay, when they sit still.$"

Porthliw_Text_EnysGymShut:
	.string "Here for the GYM, are you?\n"
	.string "That's mine, up the hill.\p"
	.string "It's shut tonight, I'm afraid.\n"
	.string "The gallery opens this evening.$"

Porthliw_Text_EnysOnLumen:
	.string "Sponsored by Lumen, mind.\n"
	.string "Their name on every poster.\p"
	.string "Funny how a mining firm's\n"
	.string "gone all keen on art.$"

Porthliw_Text_EnysInvite:
	.string "Come along anyway. I'll tell\n"
	.string "the door you're my guest.\p"
	.string "Might be worth watching.\n"
	.string "The GYM opens again after.$"

Porthliw_Text_EnysRepeat:
	.string "The gallery's just there. Tell\n"
	.string "the door Enys sent you.\p"
	.string "I'll finish these gulls first.\n"
	.string "Proper fidgets, they are.$"

Porthliw_Text_GalleryInvitationOnly:
	.string "Sorry, love. It's invitation\n"
	.string "only tonight.\p"
	.string "Lumen's orders, not mine.$"

Porthliw_Text_GalleryGoOnIn:
	.string "Enys's guest? Go on in,\n"
	.string "my 'ansum.$"

Porthliw_Text_Tourist:
	.string "Proper Cornish pasty, this!\n"
	.string "Going to eat it right here.\p"
	.string "Why's that gull looking at me\n"
	.string "like that?$"

Porthliw_Text_TouristAfterOpening:
	.string "That was my second pasty today.\n"
	.string "The gulls had both.\p"
	.string "I'm eating the next one in the\n"
	.string "POKéMON CENTER.$"

Porthliw_Text_Painter:
	.string "Lumen are paying for the opening,\n"
	.string "so there's free wine.\p"
	.string "Folk say they're buying us.\n"
	.string "I say the wine's still free.$"

Porthliw_Text_PainterAfterOpening:
	.string "You were there, weren't you?\p"
	.string "When Enys stood up, you could've\n"
	.string "heard a brush drop.$"

Porthliw_Text_Birdwatcher:
	.string "Enys paints these seabirds every\n"
	.string "morning from the harbour wall.\p"
	.string "You'll not see more gulls in one\n"
	.string "sky anywhere in Kernia.$"

Porthliw_Text_BirdwatcherAfterOpening:
	.string "Funny thing. The flocks won't fly\n"
	.string "east over the moor any more.\p"
	.string "They get halfway, then wheel\n"
	.string "back west. Every time.$"

Porthliw_Text_Local:
	.string "My brother's got a Lumen job up\n"
	.string "in Carnrudh. Sends money home.\p"
	.string "Not everyone here can live off\n"
	.string "paintings, you know.$"

Porthliw_Text_LocalAfterOpening:
	.string "Enys might be right about the\n"
	.string "light. I'm not saying she isn't.\p"
	.string "But the light don't pay my\n"
	.string "brother's rent, does it?$"

Porthliw_Text_GalleryStaffAfterOpening:
	.string "The sponsor's banners came down\n"
	.string "first thing this morning.\p"
	.string "Go on in. The paintings are still\n"
	.string "there, Lumen or no Lumen.$"
