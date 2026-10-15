Carnrudh_Gym_MapScripts::
	.byte 0

@ Tanek, gym 1. A stand-in gym with no puzzle yet (see design/plans/carnrudh.md).
Carnrudh_Gym_EventScript_Tanek::
	trainerbattle_single TRAINER_TANEK, Carnrudh_Gym_Text_TanekIntro, Carnrudh_Gym_Text_TanekDefeat, Carnrudh_Gym_EventScript_TanekDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_TM_FLAME_CHARGE, Carnrudh_Gym_EventScript_GiveFlameChargeAgain
	setspeaker SP_NAME_TANEK
	msgbox Carnrudh_Gym_Text_TanekPostBattle, MSGBOX_DEFAULT
	release
	end

Carnrudh_Gym_EventScript_TanekDefeated::
	message Carnrudh_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setspeaker SP_NAME_TANEK
	msgbox Carnrudh_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	setvar VAR_CARNRUDH_STATE, CARNRUDH_STATE_BADGE_WON
	call Carnrudh_Gym_EventScript_GiveFlameCharge
	closemessage
	release
	end

Carnrudh_Gym_EventScript_GiveFlameCharge::
	giveitem ITEM_TM_FLAME_CHARGE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setspeaker SP_NAME_TANEK
	msgbox Carnrudh_Gym_Text_ExplainFlameCharge, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_FLAME_CHARGE
	return

@ If the bag was full after the battle, talking to Tanek again gives the TM.
Carnrudh_Gym_EventScript_GiveFlameChargeAgain::
	giveitem ITEM_TM_FLAME_CHARGE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setspeaker SP_NAME_TANEK
	msgbox Carnrudh_Gym_Text_ExplainFlameCharge, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_FLAME_CHARGE
	release
	end

Carnrudh_Gym_EventScript_Stoker::
	trainerbattle_single TRAINER_CARNRUDH_GYM_STOKER, Carnrudh_Gym_Text_StokerIntro, Carnrudh_Gym_Text_StokerDefeat
	msgbox Carnrudh_Gym_Text_StokerPostBattle, MSGBOX_AUTOCLOSE
	end

Carnrudh_Gym_EventScript_BalMaiden::
	trainerbattle_single TRAINER_CARNRUDH_GYM_BAL_MAIDEN, Carnrudh_Gym_Text_BalMaidenIntro, Carnrudh_Gym_Text_BalMaidenDefeat
	msgbox Carnrudh_Gym_Text_BalMaidenPostBattle, MSGBOX_AUTOCLOSE
	end

Carnrudh_Gym_EventScript_Statue::
	lockall
	goto_if_set FLAG_BADGE01_GET, Carnrudh_Gym_EventScript_StatueCertified
	msgbox Carnrudh_Gym_Text_Statue, MSGBOX_DEFAULT
	releaseall
	end

Carnrudh_Gym_EventScript_StatueCertified::
	msgbox Carnrudh_Gym_Text_StatueCertified, MSGBOX_DEFAULT
	releaseall
	end

Carnrudh_Gym_Text_TanekIntro:
	.string "So you're the one who went round\n"
	.string "the stones.\p"
	.string "I've kept this engine house hot\n"
	.string "since the mines shut.\p"
	.string "Let's see if you can stand\n"
	.string "the heat!$"

Carnrudh_Gym_Text_TanekDefeat:
	.string "Well, I'll be. Banked right\n"
	.string "down, I am.$"

Carnrudh_Gym_Text_ReceivedBadge:
	.string "{PLAYER} received the\n"
	.string "ENGINE BADGE from TANEK.$"

Carnrudh_Gym_Text_ExplainBadge:
	.string "The ENGINE BADGE. Wear it proud.\p"
	.string "And take this as well.$"

Carnrudh_Gym_Text_ExplainFlameCharge:
	.string "That's FLAME CHARGE. Every hit\n"
	.string "builds up a head of steam,\p"
	.string "so your POKéMON gets faster\n"
	.string "and faster. Like an engine!$"

Carnrudh_Gym_Text_TanekPostBattle:
	.string "Peran never once looked back at\n"
	.string "that hill. Like it was nothing.\p"
	.string "…Never mind me. There's more of\n"
	.string "KERNIA than one old tor. Go on.$"

Carnrudh_Gym_Text_StokerIntro:
	.string "Shovel it in! This engine runs\n"
	.string "on coal and grit!$"

Carnrudh_Gym_Text_StokerDefeat:
	.string "Out like a damp fire…$"

Carnrudh_Gym_Text_StokerPostBattle:
	.string "Before the mines shut, the\n"
	.string "engines here ran day and night.$"

Carnrudh_Gym_Text_BalMaidenIntro:
	.string "My nan was a bal maiden. She\n"
	.string "broke ore at the mine all day.\p"
	.string "Bet you can't hit as hard!$"

Carnrudh_Gym_Text_BalMaidenDefeat:
	.string "Nan would be ashamed!$"

Carnrudh_Gym_Text_BalMaidenPostBattle:
	.string "Bal maidens broke the ore with\n"
	.string "hammers. Tough as granite.$"

Carnrudh_Gym_Text_Statue:
	.string "CARNRUDH POKéMON GYM$"

Carnrudh_Gym_Text_StatueCertified:
	.string "CARNRUDH POKéMON GYM\p"
	.string "TANEK'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
