TestTown_MapScripts::
	.byte 0

TestTown_EventScript_PokemonGiver::
        lock
        faceplayer
        goto_if_set FLAG_RECEIVED_TEST_TOWN_POKEMON, TestTown_EventScript_PokemonGiverAfter
        msgbox TestTown_Text_PokemonGiverIntro, MSGBOX_DEFAULT
        givemon SPECIES_RIOLU, 5
        goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
        playfanfare MUS_OBTAIN_ITEM
        message TestTown_Text_ObtainedPokemon
        waitmessage
        waitfanfare
        setflag FLAG_RECEIVED_TEST_TOWN_POKEMON
        setflag FLAG_SYS_POKEMON_GET
        msgbox TestTown_Text_PokemonGiverOutro, MSGBOX_DEFAULT
        release
        end

TestTown_EventScript_PokemonGiverAfter::
        msgbox TestTown_Text_PokemonGiverAfter, MSGBOX_DEFAULT
        release
        end

TestTown_Text_PokemonGiverIntro:
        .string "Oh! You don't have any POKéMON?\p"
        .string "Here, take this one. It's been\n"
        .string "looking for a partner.$"

TestTown_Text_ObtainedPokemon:
        .string "{PLAYER} received a RIOLU!$"

TestTown_Text_PokemonGiverOutro:
        .string "Take good care of it!$"

TestTown_Text_PokemonGiverAfter:
        .string "How's RIOLU doing?$"