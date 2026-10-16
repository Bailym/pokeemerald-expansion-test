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
