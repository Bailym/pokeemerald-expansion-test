KerniaRoute2_MapScripts::
	.byte 0

KerniaRoute2_EventScript_RouteSign::
	msgbox KerniaRoute2_Text_RouteSign, MSGBOX_SIGN
	end

@ A stand-in building until the lighthouse has its own art (see design/CustomArt.md).
KerniaRoute2_EventScript_LighthouseSign::
	msgbox KerniaRoute2_Text_LighthouseSign, MSGBOX_SIGN
	end

KerniaRoute2_Text_RouteSign:
	.string "ROUTE 2\n"
	.string "{UP_ARROW} CARNRUDH$"

KerniaRoute2_Text_LighthouseSign:
	.string "PEN MORLO LIGHT\n"
	.string "Keep to the path. Cliffs unsafe.$"

@ The coast path's walker, and the huers who once kept watch from the headland.
KerniaRoute2_EventScript_Hiker::
	trainerbattle_single TRAINER_KERNIA_ROUTE2_HIKER, KerniaRoute2_Text_HikerIntro, KerniaRoute2_Text_HikerDefeat
	setspeaker SP_NAME_BRYOK
	msgbox KerniaRoute2_Text_HikerPostBattle, MSGBOX_AUTOCLOSE
	end

@ Cornwall's chough, and the legend that King Arthur lives on in one.
KerniaRoute2_EventScript_BirdKeeper::
	trainerbattle_single TRAINER_KERNIA_ROUTE2_BIRD_KEEPER, KerniaRoute2_Text_BirdKeeperIntro, KerniaRoute2_Text_BirdKeeperDefeat
	setspeaker SP_NAME_KENWYN
	msgbox KerniaRoute2_Text_BirdKeeperPostBattle, MSGBOX_AUTOCLOSE
	end

@ The mermaid who sang a chapel lad into the sea, told without its real village's name.
KerniaRoute2_EventScript_Picnicker::
	trainerbattle_single TRAINER_KERNIA_ROUTE2_PICNICKER, KerniaRoute2_Text_PicnickerIntro, KerniaRoute2_Text_PicnickerDefeat
	setspeaker SP_NAME_DEMELZA
	msgbox KerniaRoute2_Text_PicnickerPostBattle, MSGBOX_AUTOCLOSE
	end

KerniaRoute2_Text_HikerIntro:
	.string "I walk this coast path every\n"
	.string "summer. Let's see your legs!$"

KerniaRoute2_Text_HikerDefeat:
	.string "Puffed out, I am!$"

KerniaRoute2_Text_HikerPostBattle:
	.string "In my gramfer's day, a huer kept\n"
	.string "watch up on PEN MORLO.\p"
	.string "When he saw pilchards, he'd cry\n"
	.string "“HEVVA!” and the boats put out.$"

KerniaRoute2_Text_BirdKeeperIntro:
	.string "Shh! I'm watching for a CHOUGH.\n"
	.string "Now you've scared it off!$"

KerniaRoute2_Text_BirdKeeperDefeat:
	.string "Flown the nest, my lot…$"

KerniaRoute2_Text_BirdKeeperPostBattle:
	.string "Red legs, red beak. They say\n"
	.string "KING ARTHUR's spirit lives on\l"
	.string "in a chough.\p"
	.string "So you never harm one, see?$"

KerniaRoute2_Text_PicnickerIntro:
	.string "A pasty on the cliffs, a sea\n"
	.string "breeze… and then you turn up!$"

KerniaRoute2_Text_PicnickerDefeat:
	.string "Sand in my pasty now!$"

KerniaRoute2_Text_PicnickerPostBattle:
	.string "Gran says a mermaid once sang\n"
	.string "a chapel lad into the sea.\p"
	.string "On still nights you can hear\n"
	.string "them both singing out there.$"

@ Coming up the summit's steps (row 15, x 23-25) into Lumen's photo shoot by the lighthouse. The
@ director wants a battle for the reel, the player steps in front of Nova at (24, 14), and Nova
@ battles for the cameras. trainerbattle_earlyrival continues either way; VAR_RESULT is TRUE if
@ the player lost (and the team is healed). Then the shoot wraps and the crew is gone for good.
KerniaRoute2_EventScript_NovaShoot::
	goto_if_set FLAG_HIDE_KERNIA_ROUTE2_SHOOT, KerniaRoute2_EventScript_NovaShootEnd
	lockall
	playse SE_PIN
	applymovement LOCALID_KERNIA_ROUTE2_DIRECTOR, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox KerniaRoute2_Text_DirectorCut, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 23, KerniaRoute2_EventScript_PlayerStepsInFromLeft
	call_if_eq VAR_0x8004, 24, KerniaRoute2_EventScript_PlayerStepsInFromMiddle
	call_if_eq VAR_0x8004, 25, KerniaRoute2_EventScript_PlayerStepsInFromRight
	msgbox KerniaRoute2_Text_DirectorWantsBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_KERNIA_ROUTE2_NOVA, Common_Movement_FaceRight
	waitmovement 0
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaToCamera, MSGBOX_DEFAULT
	applymovement LOCALID_KERNIA_ROUTE2_NOVA, Common_Movement_FaceDown
	waitmovement 0
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_earlyrival TRAINER_NOVA_ROUTE2, RIVAL_BATTLE_HEAL_AFTER, KerniaRoute2_Text_NovaDefeated, KerniaRoute2_Text_NovaVictory
	goto_if_eq VAR_RESULT, TRUE, KerniaRoute2_EventScript_NovaWon
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaAfterPlayerWon, MSGBOX_DEFAULT
	goto KerniaRoute2_EventScript_ShootWraps

KerniaRoute2_EventScript_NovaWon::
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaAfterPlayerLost, MSGBOX_DEFAULT
KerniaRoute2_EventScript_ShootWraps::
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaSurveyHiccup, MSGBOX_DEFAULT
	msgbox KerniaRoute2_Text_DirectorWrap, MSGBOX_DEFAULT
	setspeaker SP_NAME_NOVA
	msgbox KerniaRoute2_Text_NovaGoodbye, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_KERNIA_ROUTE2_NOVA
	removeobject LOCALID_KERNIA_ROUTE2_PAWMI
	removeobject LOCALID_KERNIA_ROUTE2_CAMERAMAN
	removeobject LOCALID_KERNIA_ROUTE2_DIRECTOR
	setflag FLAG_HIDE_KERNIA_ROUTE2_SHOOT
	fadescreen FADE_FROM_BLACK
	releaseall
KerniaRoute2_EventScript_NovaShootEnd::
	end

KerniaRoute2_EventScript_PlayerStepsInFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, KerniaRoute2_Movement_StepInFromLeft
	waitmovement 0
	return

KerniaRoute2_EventScript_PlayerStepsInFromMiddle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	return

KerniaRoute2_EventScript_PlayerStepsInFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, KerniaRoute2_Movement_StepInFromRight
	waitmovement 0
	return

KerniaRoute2_Movement_StepInFromLeft:
	walk_up
	walk_right
	face_up
	step_end

KerniaRoute2_Movement_StepInFromRight:
	walk_up
	walk_left
	face_up
	step_end

KerniaRoute2_Text_DirectorCut:
	.string "Cut! Cut! Who's that on the\n"
	.string "steps? …A local trainer?\p"
	.string "Oh, that's gold. Pure gold!$"

KerniaRoute2_Text_DirectorWantsBattle:
	.string "Nova, a quick battle for the\n"
	.string "reel, yeah?\p"
	.string "Sunset, lighthouse, plucky\n"
	.string "local. The brand team will cry!$"

KerniaRoute2_Text_NovaToCamera:
	.string "Hey hey, Kernia! It's Nova, live\n"
	.string "from PEN MORLO LIGHT!\p"
	.string "Lumen: bringing light to\n"
	.string "Kernia! Isn't it gorgeous?$"

KerniaRoute2_Text_NovaChallenge:
	.string "…Phew. Is the red light off?\p"
	.string "Hey, it's you again! Look, I've\n"
	.string "got a new partner. Lumen sent\l"
	.string "Klink over special!\p"
	.string "Let's give 'em a show, yeah?$"

KerniaRoute2_Text_NovaDefeated:
	.string "Ha! Nice! Keep rolling, we can\n"
	.string "use that!$"

KerniaRoute2_Text_NovaVictory:
	.string "And that's Lumen quality! No\n"
	.string "hard feelings, local!$"

KerniaRoute2_Text_NovaAfterPlayerWon:
	.string "You're getting good, you know.\n"
	.string "Klink's still finding its feet.$"

KerniaRoute2_Text_NovaAfterPlayerLost:
	.string "Hey, chin up! It's not easy with\n"
	.string "a camera in your face.$"

KerniaRoute2_Text_NovaSurveyHiccup:
	.string "Oh, did you hear? Some survey\n"
	.string "hiccup up on CARN KOWR.\p"
	.string "Lumen sorted it in no time.\n"
	.string "They're the best, honestly.$"

KerniaRoute2_Text_DirectorWrap:
	.string "And… that's a wrap! Lovely\n"
	.string "stuff, people. Pack it up!$"

KerniaRoute2_Text_NovaGoodbye:
	.string "Next shoot's further down the\n"
	.string "coast. Catch you later, local!$"
