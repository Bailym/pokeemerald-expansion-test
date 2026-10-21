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

Porthliw_Gallery_EventScript_Curator::
	msgbox Porthliw_Gallery_Text_Curator, MSGBOX_NPC
	end

Porthliw_Gallery_EventScript_SchoolKid::
	msgbox Porthliw_Gallery_Text_SchoolKid, MSGBOX_NPC
	end

Porthliw_Gallery_EventScript_HarbourPainting::
	msgbox Porthliw_Gallery_Text_HarbourPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_GullsPainting::
	msgbox Porthliw_Gallery_Text_GullsPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_LastShiftPainting::
	msgbox Porthliw_Gallery_Text_LastShiftPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_PastyPainting::
	msgbox Porthliw_Gallery_Text_PastyPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_LightPainting::
	msgbox Porthliw_Gallery_Text_LightPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_KerensaPainting::
	msgbox Porthliw_Gallery_Text_KerensaPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_BuccaPainting::
	msgbox Porthliw_Gallery_Text_BuccaPainting, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_CarvedSlab::
	msgbox Porthliw_Gallery_Text_CarvedSlab, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_BronzeGull::
	msgbox Porthliw_Gallery_Text_BronzeGull, MSGBOX_SIGN
	end

Porthliw_Gallery_EventScript_HoledStone::
	msgbox Porthliw_Gallery_Text_HoledStone, MSGBOX_SIGN
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

Porthliw_Gallery_Text_Curator:
	.string "Lumen paid for the frames, the\n"
	.string "wine, and every poster in town.\p"
	.string "Then Enys had her say, and the\n"
	.string "posters came down by morning.\p"
	.string "Don't bother me, my 'ansum.\n"
	.string "Folk are looking at the paintings.$"

Porthliw_Gallery_Text_SchoolKid:
	.string "Miss says we've got to find a\n"
	.string "POKéMON in every painting.\p"
	.string "I found the gulls. And the one\n"
	.string "that ate the pasty!$"

Porthliw_Gallery_Text_HarbourPainting:
	.string "“Evening, Porthliw Harbour.”\p"
	.string "The old light glows over a bay\n"
	.string "full of pilchard boats.\p"
	.string "The card says the shoals haven't\n"
	.string "come in like that for fifty years.$"

Porthliw_Gallery_Text_GullsPainting:
	.string "“Gulls Over the Bay,” by Enys.\p"
	.string "Hundreds of seabirds wheel over\n"
	.string "the water in a low, gold light.\p"
	.string "The paint's thick enough to\n"
	.string "feel the wind in it.$"

Porthliw_Gallery_Text_LastShiftPainting:
	.string "“Wheal Gwyn, the Last Shift.”\p"
	.string "Tinners file out of an engine\n"
	.string "house on a clifftop.\p"
	.string "The young one at the back…\n"
	.string "That's Grampy's grin, surely?$"

Porthliw_Gallery_Text_PastyPainting:
	.string "“Still Life with Pasty.”\p"
	.string "A golden pasty on a harbour wall.\p"
	.string "The card says it was painted fast.\n"
	.string "A gull had the pasty before the\l"
	.string "paint was dry.$"

Porthliw_Gallery_Text_LightPainting:
	.string "“West Light,” painter unknown.\p"
	.string "Nothing but sea and sky, in a\n"
	.string "hundred shades of blue.\p"
	.string "Painters have come to Porthliw\n"
	.string "for this light for a hundred years.$"

Porthliw_Gallery_Text_KerensaPainting:
	.string "“Kerensa in Her Garden.”\p"
	.string "An old woman, chisel in hand,\n"
	.string "among her stones up the hill.\p"
	.string "She carved there for forty years,\n"
	.string "the card says.$"

Porthliw_Gallery_Text_BuccaPainting:
	.string "“Bucca.” Just a shadow under\n"
	.string "dark water.\p"
	.string "Fishermen once left a fish on the\n"
	.string "sand for Bucca, for a safe catch.\p"
	.string "Miners swore it lived under the\n"
	.string "ground instead. Nobody's painted\l"
	.string "more than its shadow.$"

Porthliw_Gallery_Text_CarvedSlab:
	.string "A granite slab, carved by Kerensa.\p"
	.string "Old tinners' words run across it:\n"
	.string "“Leave a crust for the Knockers.”$"

Porthliw_Gallery_Text_BronzeGull:
	.string "A bronze gull by Kerensa.\p"
	.string "It looks ready to snatch\n"
	.string "something right out of your hand.$"

Porthliw_Gallery_Text_HoledStone:
	.string "A round stone with a hole\n"
	.string "through the middle.\p"
	.string "The card says children were once\n"
	.string "passed through stones like this,\l"
	.string "for luck.$"
