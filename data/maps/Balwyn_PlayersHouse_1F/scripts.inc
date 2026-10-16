Balwyn_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Balwyn_PlayersHouse_1F_OnFrame
	.byte 0

Balwyn_PlayersHouse_1F_OnFrame:
	map_script_2 VAR_BALWYN_STATE, BALWYN_STATE_NEW_GAME, Balwyn_PlayersHouse_1F_EventScript_MorningScene
	map_script_2 VAR_BALWYN_STATE, BALWYN_STATE_EVENT_DONE, Balwyn_PlayersHouse_1F_EventScript_KitchenTable
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

@ Mum heals the player's team once they have one; before that she talks about Kelyn.
Balwyn_PlayersHouse_1F_EventScript_Mum::
	lock
	faceplayer
	goto_if_ge VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER, Balwyn_PlayersHouse_1F_EventScript_MumHeal
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumKelyn, MSGBOX_DEFAULT
	release
	end

Balwyn_PlayersHouse_1F_EventScript_MumHeal::
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumRest, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumRightAsRain, MSGBOX_DEFAULT
	release
	end

@ Kelyn walks the player home from Wheal Gwyn (arriving at (8, 7)) and offers the three starters from a menu.
Balwyn_PlayersHouse_1F_EventScript_KitchenTable::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Balwyn_PlayersHouse_1F_Movement_PlayerToTable
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynBroughtThree, MSGBOX_DEFAULT
Balwyn_PlayersHouse_1F_EventScript_ChooseStarter::
	setspeaker SP_NAME_KELYN
	message Balwyn_PlayersHouse_1F_Text_KelynWhichWillItBe
	waitmessage
	dynmultichoice 19, 1, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, Balwyn_PlayersHouse_1F_Text_OptionFletchling, Balwyn_PlayersHouse_1F_Text_OptionSpheal, Balwyn_PlayersHouse_1F_Text_OptionShinx
	switch VAR_RESULT
	case 0, Balwyn_PlayersHouse_1F_EventScript_ConfirmFletchling
	case 1, Balwyn_PlayersHouse_1F_EventScript_ConfirmSpheal
	case 2, Balwyn_PlayersHouse_1F_EventScript_ConfirmShinx
	end

Balwyn_PlayersHouse_1F_EventScript_Kelyn::
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynKeepJournalClose, MSGBOX_NPC
	end

@ Each choice shows the Pokemon with Kelyn's description and asks for confirmation; "no" goes back to the menu.
Balwyn_PlayersHouse_1F_EventScript_ConfirmFletchling::
	showmonpic SPECIES_FLETCHLING, 10, 3
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynFletchling, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Balwyn_PlayersHouse_1F_EventScript_DeclinedStarter
	hidemonpic
	setvar VAR_STARTER_MON, 0
	givemon SPECIES_FLETCHLING, 5
	bufferspeciesname STR_VAR_1, SPECIES_FLETCHLING
	goto Balwyn_PlayersHouse_1F_EventScript_ReceivedStarter

Balwyn_PlayersHouse_1F_EventScript_ConfirmSpheal::
	showmonpic SPECIES_SPHEAL, 10, 3
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynSpheal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Balwyn_PlayersHouse_1F_EventScript_DeclinedStarter
	hidemonpic
	setvar VAR_STARTER_MON, 1
	givemon SPECIES_SPHEAL, 5
	bufferspeciesname STR_VAR_1, SPECIES_SPHEAL
	goto Balwyn_PlayersHouse_1F_EventScript_ReceivedStarter

Balwyn_PlayersHouse_1F_EventScript_ConfirmShinx::
	showmonpic SPECIES_SHINX, 10, 3
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynShinx, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Balwyn_PlayersHouse_1F_EventScript_DeclinedStarter
	hidemonpic
	setvar VAR_STARTER_MON, 2
	givemon SPECIES_SHINX, 5
	bufferspeciesname STR_VAR_1, SPECIES_SHINX
	goto Balwyn_PlayersHouse_1F_EventScript_ReceivedStarter

Balwyn_PlayersHouse_1F_EventScript_DeclinedStarter::
	hidemonpic
	goto Balwyn_PlayersHouse_1F_EventScript_ChooseStarter

Balwyn_PlayersHouse_1F_EventScript_ReceivedStarter::
	setflag FLAG_SYS_POKEMON_GET
	message Balwyn_PlayersHouse_1F_Text_ReceivedStarter
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Balwyn_PlayersHouse_1F_EventScript_StarterHandover
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto Balwyn_PlayersHouse_1F_EventScript_StarterHandover

@ Kelyn adds the Pokedex and Poke Balls, then Mum brings over Grampy's Journal.
Balwyn_PlayersHouse_1F_EventScript_StarterHandover::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynPokedex, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Balwyn_PlayersHouse_1F_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynPokeBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynTownMap, MSGBOX_DEFAULT
	giveitem ITEM_TOWN_MAP
	closemessage
	applymovement LOCALID_BALWYN_PLAYERS_HOUSE_1F_MUM, Balwyn_PlayersHouse_1F_Movement_MumToTable
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumJournal, MSGBOX_DEFAULT
	giveitem ITEM_GRAMPYS_JOURNAL
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	setspeaker SP_NAME_KELYN
	msgbox Balwyn_PlayersHouse_1F_Text_KelynRecognisesJournal, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	setspeaker SP_NAME_MUM
	msgbox Balwyn_PlayersHouse_1F_Text_MumSendOff, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BALWYN_PLAYERS_HOUSE_1F_MUM, Balwyn_PlayersHouse_1F_Movement_MumTableToSink
	waitmovement 0
	@ With a starter in hand, the road grunt is no longer needed.
	setflag FLAG_HIDE_BALWYN_ROAD_GRUNT
	@ Kelyn heads out with the player, and Nova is waiting outside.
	setflag FLAG_HIDE_BALWYN_HOUSE_KELYN
	clearflag FLAG_HIDE_BALWYN_SENDOFF
	setvar VAR_BALWYN_STATE, BALWYN_STATE_HAS_STARTER
	releaseall
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

@ From the doormat side of the room (8, 7) to the table's right-hand side (5, 6), below Kelyn at (5, 5).
Balwyn_PlayersHouse_1F_Movement_PlayerToTable:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ From the sink (2, 3) round to the player's right at (6, 6).
Balwyn_PlayersHouse_1F_Movement_MumToTable:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	face_left
	step_end

Balwyn_PlayersHouse_1F_Movement_MumTableToSink:
	walk_up
	walk_up
	walk_up
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

Balwyn_PlayersHouse_1F_Text_MumRest:
	.string "You look worn out, love.\n"
	.string "Sit down and have a rest.$"

Balwyn_PlayersHouse_1F_Text_MumRightAsRain:
	.string "There, right as rain.\n"
	.string "Off you go, then!$"

Balwyn_PlayersHouse_1F_Text_KelynBroughtThree:
	.string "Your Grampy wrote to me often,\n"
	.string "{PLAYER}. Always about you.\p"
	.string "He hoped you'd see Kernia with\n"
	.string "Pokémon at your side, as he did.\p"
	.string "So I've brought three with me.$"

Balwyn_PlayersHouse_1F_Text_KelynWhichWillItBe:
	.string "Which will it be?$"

Balwyn_PlayersHouse_1F_Text_OptionFletchling:
	.string "FLETCHLING$"

Balwyn_PlayersHouse_1F_Text_OptionSpheal:
	.string "SPHEAL$"

Balwyn_PlayersHouse_1F_Text_OptionShinx:
	.string "SHINX$"

Balwyn_PlayersHouse_1F_Text_KelynFletchling:
	.string "Fletchling, the robin. Bold as\n"
	.string "brass, and loyal with it.\p"
	.string "Will you choose Fletchling?$"

Balwyn_PlayersHouse_1F_Text_KelynSpheal:
	.string "Spheal, a seal pup from the\n"
	.string "coves. Gentle, but tough.\p"
	.string "Will you choose Spheal?$"

Balwyn_PlayersHouse_1F_Text_KelynShinx:
	.string "Shinx, a wildcat cub. Folk say a\n"
	.string "great beast roams the moor...\p"
	.string "Will you choose Shinx?$"

Balwyn_PlayersHouse_1F_Text_ReceivedStarter:
	.string "{PLAYER} received {STR_VAR_1}!$"

Balwyn_PlayersHouse_1F_Text_KelynPokedex:
	.string "A fine choice. You'll want this\n"
	.string "too. A Pokédex, for your notes.$"

Balwyn_PlayersHouse_1F_Text_ReceivedPokedex:
	.string "{PLAYER} received the Pokédex!$"

Balwyn_PlayersHouse_1F_Text_KelynPokeBalls:
	.string "And a few Poké Balls, so you\n"
	.string "can make friends of your own.\p"
	.string "Oh, and you'll want this too.$"

Balwyn_PlayersHouse_1F_Text_KelynTownMap:
	.string "A map of Kernia, so you never\n"
	.string "lose your way home.$"

Balwyn_PlayersHouse_1F_Text_MumJournal:
	.string "{PLAYER}, love... Grampy wanted\n"
	.string "you to have this.$"

Balwyn_PlayersHouse_1F_Text_KelynRecognisesJournal:
	.string "His journal! His legends, and\n"
	.string "his maps of the old mines...\p"
	.string "Keep it close, {PLAYER}. There's\n"
	.string "more to it than stories.$"

Balwyn_PlayersHouse_1F_Text_MumSendOff:
	.string "Go on, then. And if you see that\n"
	.string "Nova, show him a thing or two!$"

Balwyn_PlayersHouse_1F_Text_KelynKeepJournalClose:
	.string "Keep that journal close. Your\n"
	.string "Grampy knew things, {PLAYER}.$"
