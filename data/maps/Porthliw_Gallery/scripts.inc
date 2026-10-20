Porthliw_Gallery_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Porthliw_Gallery_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Porthliw_Gallery_OnFrame
	.byte 0

@ The two guests who stay after the opening stand in the crowd until then, and with the
@ paintings after it.
Porthliw_Gallery_OnTransition:
	call_if_ge VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE, Porthliw_Gallery_EventScript_GuestsToPaintings
	end

Porthliw_Gallery_EventScript_GuestsToPaintings::
	setobjectxyperm LOCALID_PORTHLIW_GALLERY_BEAUTY, 5, 2
	setobjectmovementtype LOCALID_PORTHLIW_GALLERY_BEAUTY, MOVEMENT_TYPE_FACE_UP
	setobjectxyperm LOCALID_PORTHLIW_GALLERY_ARTIST, 3, 7
	setobjectmovementtype LOCALID_PORTHLIW_GALLERY_ARTIST, MOVEMENT_TYPE_FACE_UP
	return

Porthliw_Gallery_OnFrame:
	map_script_2 VAR_PORTHLIW_STATE, PORTHLIW_STATE_MET_ENYS, Porthliw_Gallery_EventScript_OpeningNight
	.2byte 0

@ The opening night plays on first coming in after meeting Enys. The player joins the back of the
@ crowd at (11, 11). Sloane speaks from (11, 7), Enys answers from the side, and Sloane leaves past
@ the player. Then Enys heads for the gym, and the crowd thins out to the two guests who stay.
Porthliw_Gallery_EventScript_OpeningNight::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Porthliw_Gallery_Movement_PlayerJoinsCrowd
	waitmovement 0
	setspeaker SP_NAME_SLOANE
	msgbox Porthliw_Gallery_Text_SloaneWelcome, MSGBOX_DEFAULT
	setspeaker SP_NAME_SLOANE
	msgbox Porthliw_Gallery_Text_SloanePitch, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_GALLERY_ENYS, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_PORTHLIW_GALLERY_BEAUTY, Common_Movement_FaceRight
	applymovement LOCALID_PORTHLIW_GALLERY_GENTLEMAN, Common_Movement_FaceRight
	applymovement LOCALID_PORTHLIW_GALLERY_ARTIST, Common_Movement_FaceRight
	applymovement LOCALID_PORTHLIW_GALLERY_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gallery_Text_EnysClosures, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gallery_Text_EnysLight, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gallery_Text_EnysStones, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_GALLERY_GENTLEMAN, Common_Movement_ExclamationMark
	applymovement LOCALID_PORTHLIW_GALLERY_WOMAN, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Porthliw_Gallery_Text_GuestsMutter, MSGBOX_DEFAULT
	closemessage
	setspeaker SP_NAME_SLOANE
	msgbox Porthliw_Gallery_Text_SloaneReply, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_GALLERY_SLOANE, Porthliw_Gallery_Movement_SloaneToPlayer
	waitmovement 0
	setspeaker SP_NAME_SLOANE
	msgbox Porthliw_Gallery_Text_SloaneToPlayer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PORTHLIW_GALLERY_SLOANE, Porthliw_Gallery_Movement_SloaneLeaves
	waitmovement 0
	removeobject LOCALID_PORTHLIW_GALLERY_SLOANE
	applymovement LOCALID_PORTHLIW_GALLERY_ENYS, Porthliw_Gallery_Movement_EnysToPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gallery_Text_EnysToPlayer, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_PORTHLIW_GALLERY_ENYS
	removeobject LOCALID_PORTHLIW_GALLERY_GENTLEMAN
	removeobject LOCALID_PORTHLIW_GALLERY_WOMAN
	setobjectxy LOCALID_PORTHLIW_GALLERY_BEAUTY, 5, 2
	turnobject LOCALID_PORTHLIW_GALLERY_BEAUTY, DIR_NORTH
	setobjectxy LOCALID_PORTHLIW_GALLERY_ARTIST, 3, 7
	turnobject LOCALID_PORTHLIW_GALLERY_ARTIST, DIR_NORTH
	setflag FLAG_HIDE_PORTHLIW_OPENING
	setflag FLAG_HIDE_PORTHLIW_HARBOUR_ENYS
	setvar VAR_PORTHLIW_STATE, PORTHLIW_STATE_OPENING_DONE
	fadescreen FADE_FROM_BLACK
	releaseall
	end

Porthliw_Gallery_Movement_PlayerJoinsCrowd:
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

@ Down the gap between the front guests, stopping in front of the player.
Porthliw_Gallery_Movement_SloaneToPlayer:
	walk_down
	walk_down
	walk_down
	step_end

Porthliw_Gallery_Movement_SloaneLeaves:
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

Porthliw_Gallery_Movement_EnysToPlayer:
	walk_down
	walk_down
	walk_left
	step_end

Porthliw_Gallery_EventScript_Beauty::
	msgbox Porthliw_Gallery_Text_Beauty, MSGBOX_NPC
	end

Porthliw_Gallery_EventScript_Artist::
	msgbox Porthliw_Gallery_Text_Artist, MSGBOX_NPC
	end

Porthliw_Gallery_Text_SloaneWelcome:
	.string "Good evening, Porthliw!\n"
	.string "What a turnout.\p"
	.string "I'm Sloane, Head of PR at\n"
	.string "Lumen. Thank you for coming!$"

Porthliw_Gallery_Text_SloanePitch:
	.string "At Lumen, we're proud to be\n"
	.string "friends of the arts.\p"
	.string "Together, we're lighting up\n"
	.string "Kernia's creative coast!\p"
	.string "And with new jobs in Carnrudh,\n"
	.string "the future's never looked brighter.$"

Porthliw_Gallery_Text_EnysClosures:
	.string "Brighter? Funny word for it.\p"
	.string "Lumen shut Carnrudh's east road\n"
	.string "for their trucks.\p"
	.string "Didn't ask a soul first, mind.$"

Porthliw_Gallery_Text_EnysLight:
	.string "Painters come here for the light.\n"
	.string "For the wild coast.\p"
	.string "And it's going dull out east,\n"
	.string "under all their dust and drills.$"

Porthliw_Gallery_Text_EnysStones:
	.string "And I hear they were “surveying”\n"
	.string "Carn Kowr's giant's stones…\p"
	.string "…right up till some kid turned up\n"
	.string "and spoiled it for them.$"

Porthliw_Gallery_Text_GuestsMutter:
	.string "She's right, you know…\n"
	.string "Never thought of it like that.$"

Porthliw_Gallery_Text_SloaneReply:
	.string "Passion! Isn't that what art's\n"
	.string "all about? Lovely.\p"
	.string "Do enjoy the paintings, everyone.\n"
	.string "Lumen's treat.$"

Porthliw_Gallery_Text_SloaneToPlayer:
	.string "You must be the trainer everyone's\n"
	.string "talking about.\p"
	.string "Do give Lumen a fair hearing,\n"
	.string "won't you? Ciao!$"

Porthliw_Gallery_Text_EnysToPlayer:
	.string "Well, that's torn it. Worth it,\n"
	.string "though, to see her face.\p"
	.string "The GYM's open now. Come and\n"
	.string "find me at the top of the hill.$"

Porthliw_Gallery_Text_Beauty:
	.string "Did you see Sloane's smile?\n"
	.string "It never moved. Not once.$"

Porthliw_Gallery_Text_Artist:
	.string "Enys is right about the light.\n"
	.string "It's gone flatter out east since\l"
	.string "the drilling started.$"
