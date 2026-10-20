Porthliw_Gym_MapScripts::
	.byte 0

@ Enys, gym 2, in the gull's head. Badge 2 unlocks Fly, then she gives TM40 Aerial Ace.
Porthliw_Gym_EventScript_Enys::
	trainerbattle_single TRAINER_ENYS, Porthliw_Gym_Text_EnysIntro, Porthliw_Gym_Text_EnysDefeat, Porthliw_Gym_EventScript_EnysDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, Porthliw_Gym_EventScript_GiveAerialAceAgain
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_EnysSuspicion, MSGBOX_DEFAULT
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_EnysEastRoad, MSGBOX_DEFAULT
	release
	end

Porthliw_Gym_EventScript_EnysDefeated::
	message Porthliw_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_BADGE02_GET
	setvar VAR_PORTHLIW_STATE, PORTHLIW_STATE_BADGE_WON
	buffermovename STR_VAR_1, MOVE_FLY
	call EventScript_FieldMoveUnlocked
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_TakeThisToo, MSGBOX_DEFAULT
	call Porthliw_Gym_EventScript_GiveAerialAce
	closemessage
	release
	end

Porthliw_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

@ If the bag was full after the battle, talking to Enys again gives the TM.
Porthliw_Gym_EventScript_GiveAerialAceAgain::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setspeaker SP_NAME_ENYS
	msgbox Porthliw_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

Porthliw_Gym_EventScript_Sketcher::
	trainerbattle_single TRAINER_PORTHLIW_GYM_SKETCHER, Porthliw_Gym_Text_SketcherIntro, Porthliw_Gym_Text_SketcherDefeat
	msgbox Porthliw_Gym_Text_SketcherPostBattle, MSGBOX_AUTOCLOSE
	end

Porthliw_Gym_EventScript_Painter::
	trainerbattle_single TRAINER_PORTHLIW_GYM_PAINTER, Porthliw_Gym_Text_PainterIntro, Porthliw_Gym_Text_PainterDefeat
	msgbox Porthliw_Gym_Text_PainterPostBattle, MSGBOX_AUTOCLOSE
	end

Porthliw_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, Porthliw_Gym_EventScript_GymGuidePostVictory
	msgbox Porthliw_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

Porthliw_Gym_EventScript_GymGuidePostVictory::
	msgbox Porthliw_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

Porthliw_Gym_EventScript_Statue::
	lockall
	goto_if_set FLAG_BADGE02_GET, Porthliw_Gym_EventScript_StatueCertified
	msgbox Porthliw_Gym_Text_Statue, MSGBOX_DEFAULT
	releaseall
	end

Porthliw_Gym_EventScript_StatueCertified::
	msgbox Porthliw_Gym_Text_StatueCertified, MSGBOX_DEFAULT
	releaseall
	end

Porthliw_Gym_Text_EnysIntro:
	.string "Made it round my gull, then?\n"
	.string "Not bad at all.\p"
	.string "I paint them every morning.\n"
	.string "Watch how they ride the wind.\p"
	.string "Let's see you keep up with mine!$"

Porthliw_Gym_Text_EnysDefeat:
	.string "Ha! You've got an eye for it.\n"
	.string "Proper job.$"

Porthliw_Gym_Text_ReceivedBadge:
	.string "{PLAYER} received the\n"
	.string "GULL BADGE from ENYS.$"

Porthliw_Gym_Text_ExplainBadge:
	.string "The GULL BADGE. It's yours.\p"
	.string "With that, you can fly anywhere\n"
	.string "you've been. No bird needed.\p"
	.string "Go on. See Kernia from up top.$"

Porthliw_Gym_Text_TakeThisToo:
	.string "And have this, for the road.$"

Porthliw_Gym_Text_ExplainAerialAce:
	.string "That's AERIAL ACE. It never\n"
	.string "misses.\p"
	.string "Sharp and sure, like a gull\n"
	.string "going for your pasty!$"

Porthliw_Gym_Text_EnysSuspicion:
	.string "Something's been bothering me.\n"
	.string "My gulls have gone quiet.\p"
	.string "They won't fly over Lumen's\n"
	.string "sites. And when the ground hums…\p"
	.string "…the whole flock wheels away\n"
	.string "west. Like they know something.$"

Porthliw_Gym_Text_EnysEastRoad:
	.string "Word is Lumen have opened\n"
	.string "Carnrudh's east road again.\p"
	.string "Right after the opening, too.\n"
	.string "Funny timing, that.$"

Porthliw_Gym_Text_SketcherIntro:
	.string "Hold still! I'm sketching\n"
	.string "your POKéMON!$"

Porthliw_Gym_Text_SketcherDefeat:
	.string "Smudged it…$"

Porthliw_Gym_Text_SketcherPostBattle:
	.string "Enys says draw what moves, not\n"
	.string "what sits still. Hard, that.$"

Porthliw_Gym_Text_PainterIntro:
	.string "The light up here's lovely.\n"
	.string "Let's see your colours!$"

Porthliw_Gym_Text_PainterDefeat:
	.string "All washed out!$"

Porthliw_Gym_Text_PainterPostBattle:
	.string "Painters come from all over for\n"
	.string "Porthliw's light. Me included.$"

Porthliw_Gym_Text_GymGuideAdvice:
	.string "Alright, my 'ansum? Enys's birds\n"
	.string "ride the sea wind.\p"
	.string "ROCK moves'll bring 'em down\n"
	.string "to earth. ELECTRIC, better still.\p"
	.string "Caught a YAMPER up on the moor?\n"
	.string "Its NUZZLE'll ground her birds!$"

Porthliw_Gym_Text_GymGuidePostVictory:
	.string "Enys, grounded! Proper job,\n"
	.string "my 'ansum.$"

Porthliw_Gym_Text_Statue:
	.string "PORTHLIW POKéMON GYM$"

Porthliw_Gym_Text_StatueCertified:
	.string "PORTHLIW POKéMON GYM\p"
	.string "ENYS'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
