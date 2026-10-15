Carnrudh_MapScripts::
	.byte 0

Carnrudh_EventScript_TownSign::
	msgbox Carnrudh_Text_TownSign, MSGBOX_SIGN
	end

Carnrudh_EventScript_PastyShopSign::
	msgbox Carnrudh_Text_PastyShopSign, MSGBOX_SIGN
	end

Carnrudh_EventScript_SchoolSign::
	msgbox Carnrudh_Text_SchoolSign, MSGBOX_SIGN
	end

Carnrudh_EventScript_GymSign::
	msgbox Carnrudh_Text_GymSign, MSGBOX_SIGN
	end

@ Stands in the gym doorway until Tanek comes back down from Carn Kowr.
Carnrudh_EventScript_GymBlocker::
	msgbox Carnrudh_Text_GymBlocker, MSGBOX_NPC
	end

Carnrudh_Text_TownSign:
	.string "CARNRUDH\n"
	.string "Under the red tor.\p"
	.string "Where the first steam engine\n"
	.string "ever ran on the road!$"

Carnrudh_Text_GymSign:
	.string "CARNRUDH POKéMON GYM\n"
	.string "LEADER: TANEK\p"
	.string "The fire in the boiler,\n"
	.string "the heart of the engine!$"

Carnrudh_Text_GymBlocker:
	.string "Gym's shut, my 'ansum. TANEK's\n"
	.string "gone up CARN KOWR with Lumen.\p"
	.string "They're measuring the tor for\n"
	.string "a quarry, so they say.\p"
	.string "Up the path north, if you want\n"
	.string "him. Mind the giant's stones!$"

@ Townsfolk: a "before" line while the town sets up for Penhallow Day, and a festival line once the tor is done.
Carnrudh_EventScript_BuntingWoman::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_BuntingWomanFestival
	msgbox Carnrudh_Text_BuntingWoman, MSGBOX_NPC
	end

Carnrudh_EventScript_BuntingWomanFestival::
	msgbox Carnrudh_Text_BuntingWomanFestival, MSGBOX_NPC
	end

Carnrudh_EventScript_OldMan::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_OldManFestival
	msgbox Carnrudh_Text_OldMan, MSGBOX_NPC
	end

Carnrudh_EventScript_OldManFestival::
	msgbox Carnrudh_Text_OldManFestival, MSGBOX_NPC
	end

@ Tamsin's brother from Route 1, who came here for a Lumen job.
Carnrudh_EventScript_Recruit::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_RecruitFestival
	msgbox Carnrudh_Text_Recruit, MSGBOX_NPC
	end

Carnrudh_EventScript_RecruitFestival::
	msgbox Carnrudh_Text_RecruitFestival, MSGBOX_NPC
	end

Carnrudh_EventScript_StonesWoman::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_StonesWomanFestival
	msgbox Carnrudh_Text_StonesWoman, MSGBOX_NPC
	end

Carnrudh_EventScript_StonesWomanFestival::
	msgbox Carnrudh_Text_StonesWomanFestival, MSGBOX_NPC
	end

@ A stand-in for the Puffing Bucca until it has its own sprite.
Carnrudh_EventScript_Engine::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_EngineFestival
	msgbox Carnrudh_Text_Engine, MSGBOX_NPC
	end

Carnrudh_EventScript_EngineFestival::
	msgbox Carnrudh_Text_EngineFestival, MSGBOX_NPC
	end

Carnrudh_EventScript_Engineman::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_EventScript_EnginemanFestival
	msgbox Carnrudh_Text_Engineman, MSGBOX_NPC
	end

Carnrudh_EventScript_EnginemanFestival::
	msgbox Carnrudh_Text_EnginemanFestival, MSGBOX_NPC
	end

@ Festival only (FLAG_HIDE_CARNRUDH_FESTIVAL, cleared when the tor is done).
Carnrudh_EventScript_Singer::
	msgbox Carnrudh_Text_Singer, MSGBOX_NPC
	end

Carnrudh_EventScript_Dancer::
	msgbox Carnrudh_Text_Dancer, MSGBOX_NPC
	end

@ Nova's festival cameo; no battle in Carnrudh.
Carnrudh_EventScript_Nova::
	setspeaker SP_NAME_NOVA
	msgbox Carnrudh_Text_Nova, MSGBOX_NPC
	end

Carnrudh_EventScript_Dancer2::
	msgbox Carnrudh_Text_Dancer2, MSGBOX_NPC
	end

Carnrudh_EventScript_SpectatorMan::
	msgbox Carnrudh_Text_SpectatorMan, MSGBOX_NPC
	end

Carnrudh_EventScript_WoolooOwner::
	msgbox Carnrudh_Text_WoolooOwner, MSGBOX_NPC
	end

Carnrudh_EventScript_Wooloo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOLOO, CRY_MODE_NORMAL
	msgbox Carnrudh_Text_Wooloo, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Carnrudh_EventScript_Rolycoly::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ROLYCOLY, CRY_MODE_NORMAL
	msgbox Carnrudh_Text_Rolycoly, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Carnrudh_EventScript_RunningGirl::
	msgbox Carnrudh_Text_RunningGirl, MSGBOX_NPC
	end

@ A festival stall selling treats.
Carnrudh_EventScript_StallKeeper::
	lock
	faceplayer
	message Carnrudh_Text_StallKeeper
	waitmessage
	pokemart Carnrudh_Pokemart_FestivalStall
	msgbox Carnrudh_Text_StallKeeperBye, MSGBOX_DEFAULT
	release
	end

	.align 2
Carnrudh_Pokemart_FestivalStall:
	.2byte ITEM_FRESH_WATER
	.2byte ITEM_SODA_POP
	.2byte ITEM_LEMONADE
	.2byte ITEM_LAVA_COOKIE
	pokemartlistend

@ Cornish wrestling at the festival, a nod to the giants and the Cormoran legend.
Carnrudh_EventScript_Wrestler::
	trainerbattle_single TRAINER_CARNRUDH_WRESTLER, Carnrudh_Text_WrestlerIntro, Carnrudh_Text_WrestlerDefeat
	msgbox Carnrudh_Text_WrestlerPostBattle, MSGBOX_AUTOCLOSE
	end

Carnrudh_EventScript_FestivalOldWoman::
	msgbox Carnrudh_Text_FestivalOldWoman, MSGBOX_NPC
	end

Carnrudh_Text_BuntingWoman:
	.string "Mind the bunting, my lover!\p"
	.string "PENHALLOW DAY's dreckly, and\n"
	.string "there's flags to hang yet.$"

Carnrudh_Text_BuntingWomanFestival:
	.string "PENHALLOW DAY at last! Go on,\n"
	.string "give the engine a wave.$"

Carnrudh_Text_OldMan:
	.string "When the Cap'n's engine first\n"
	.string "came puffing up the hill,\p"
	.string "the miners thought it was the\n"
	.string "BUCCA come up out the ground.\p"
	.string "Ran a mile, they did. That's why\n"
	.string "it's the PUFFING BUCCA.$"

Carnrudh_Text_OldManFestival:
	.string "Hear that hiss? Same as it ever\n"
	.string "was. The PUFFING BUCCA lives!$"

Carnrudh_Text_Recruit:
	.string "Signed on with Lumen last week.\n"
	.string "Steady wage, first in years.\p"
	.string "Our TAMSIN reckons I'm daft.\n"
	.string "She'll see.$"

Carnrudh_Text_RecruitFestival:
	.string "Lumen packed up off the tor.\n"
	.string "Said they'd find me work…\p"
	.string "…somewhere. I hope so.$"

Carnrudh_Text_StonesWoman:
	.string "A quarry, on CARN KOWR? They'd\n"
	.string "blast the giant's stones away.$"

Carnrudh_Text_StonesWomanFestival:
	.string "Carvings, under the WELL!\p"
	.string "I always said those stones were\n"
	.string "older than anyone knew.$"

Carnrudh_Text_Engine:
	.string "The PUFFING BUCCA: the Cap'n's\n"
	.string "engine. It's half polished.$"

Carnrudh_Text_EngineFestival:
	.string "The PUFFING BUCCA, steam up and\n"
	.string "brass shining.$"

Carnrudh_Text_Engineman:
	.string "Polishing her up for the parade.\p"
	.string "CAP'N PENHALLOW built her two\n"
	.string "hundred years back. Still runs!$"

Carnrudh_Text_EnginemanFestival:
	.string "Steam's up! She'll go up the\n"
	.string "hill at noon, same as ever.$"

Carnrudh_Text_Singer:
	.string "Goin' up CARNRUDH hill,\n"
	.string "comin' down…\p"
	.string "The horses stood still, the\n"
	.string "wheels went around…$"

Carnrudh_Text_Dancer:
	.string "Everyone dances on engine day.\n"
	.string "Even the gym leader!$"

Carnrudh_Text_Nova:
	.string "Hey! Heard you had a go at Lumen\n"
	.string "up on the tor.\p"
	.string "It was only a survey, you know.\n"
	.string "Lumen's doing loads for KERNIA.\p"
	.string "Anyway, these pasties are\n"
	.string "brilliant. See you on the road!$"

Carnrudh_Text_PastyShopSign:
	.string "CARNRUDH PASTY SHOP\n"
	.string "Baked fresh, crimped by hand.$"

Carnrudh_Text_SchoolSign:
	.string "OLD MINERS' SCHOOL\n"
	.string "CAP'N PENHALLOW studied here.$"

Carnrudh_Text_Dancer2:
	.string "Round and round! You can't\n"
	.string "stand still on engine day!$"

Carnrudh_Text_SpectatorMan:
	.string "I've watched her go up the hill\n"
	.string "every year since I was a nipper.\p"
	.string "Still gives me goosebumps.$"

Carnrudh_Text_WoolooOwner:
	.string "My WOOLOO's terrified of the\n"
	.string "whistle. Every year, same again.$"

Carnrudh_Text_Wooloo:
	.string "WOOLOO: Baaah!$"

Carnrudh_Text_Rolycoly:
	.string "ROLYCOLY: Roly roly!\p"
	.string "It's puffing little clouds of\n"
	.string "smoke, just like the engine.$"

Carnrudh_Text_RunningGirl:
	.string "I'm going to ride on the engine\n"
	.string "when I'm big!$"

Carnrudh_Text_StallKeeper:
	.string "Festival treats! Get 'em while\n"
	.string "they're cold, my lover!$"

Carnrudh_Text_StallKeeperBye:
	.string "Enjoy the parade!$"

Carnrudh_Text_WrestlerIntro:
	.string "Fancy a bit of wrasslin'?\p"
	.string "Giants wrestled on these hills,\n"
	.string "they say. Let's see your grip!$"

Carnrudh_Text_WrestlerDefeat:
	.string "Thrown fair and square!$"

Carnrudh_Text_WrestlerPostBattle:
	.string "Three points down and you've\n"
	.string "won. That's proper wrasslin'.$"

Carnrudh_Text_FestivalOldWoman:
	.string "Bunting up, engine out, and the\n"
	.string "whole town singing.\p"
	.string "Just like when I was a girl.$"
