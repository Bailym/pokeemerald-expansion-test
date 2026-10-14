KerniaRoute1_MapScripts::
	.byte 0

KerniaRoute1_EventScript_RouteSign::
	msgbox KerniaRoute1_Text_RouteSign, MSGBOX_SIGN
	end

KerniaRoute1_Text_RouteSign:
	.string "ROUTE 1\n"
	.string "{LEFT_ARROW} BALWYN   CARNRUDH {RIGHT_ARROW}$"

KerniaRoute1_EventScript_Jory::
	trainerbattle_single TRAINER_JORY, KerniaRoute1_Text_JoryIntro, KerniaRoute1_Text_JoryDefeated
	setspeaker SP_NAME_JORY
	msgbox KerniaRoute1_Text_JoryPostBattle, MSGBOX_AUTOCLOSE
	end

KerniaRoute1_EventScript_Tamsin::
	trainerbattle_single TRAINER_TAMSIN, KerniaRoute1_Text_TamsinIntro, KerniaRoute1_Text_TamsinDefeated
	setspeaker SP_NAME_TAMSIN
	msgbox KerniaRoute1_Text_TamsinPostBattle, MSGBOX_AUTOCLOSE
	end

KerniaRoute1_Text_JoryIntro:
	.string "Grampy says you can hear the\n"
	.string "Knockers in old Wheal Gwyn.\p"
	.string "I've never heard nothing. Bet\n"
	.string "you haven't either! Battle me!$"

KerniaRoute1_Text_JoryDefeated:
	.string "Proper job! You're handy, you.$"

KerniaRoute1_Text_JoryPostBattle:
	.string "Grampy leaves pasty crust by the\n"
	.string "mine fence for the Knockers.\p"
	.string "He says it keeps 'em sweet.\n"
	.string "I'll try it myself, dreckly!$"

KerniaRoute1_Text_TamsinIntro:
	.string "My brother's gone up Carnrudh\n"
	.string "for one of them Lumen jobs.\p"
	.string "Says they're opening the old\n"
	.string "mines again. Fancy a battle?$"

KerniaRoute1_Text_TamsinDefeated:
	.string "Oh, fair play! You're strong.$"

KerniaRoute1_Text_TamsinPostBattle:
	.string "Lumen's posters are everywhere\n"
	.string "up Carnrudh.\p"
	.string "'Bringing the mines home!'\n"
	.string "That's what they say, anyway.\p"
	.string "Mam reckons some holes are\n"
	.string "best left shut, mind.$"
