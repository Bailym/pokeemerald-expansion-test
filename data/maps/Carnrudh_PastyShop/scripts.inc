Carnrudh_PastyShop_MapScripts::
	.byte 0

Carnrudh_PastyShop_EventScript_Keeper::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_PastyShop_EventScript_KeeperFestival
	msgbox Carnrudh_PastyShop_Text_Keeper, MSGBOX_NPC
	end

Carnrudh_PastyShop_EventScript_KeeperFestival::
	msgbox Carnrudh_PastyShop_Text_KeeperFestival, MSGBOX_NPC
	end

@ Foreshadows the crust offering at the climax.
Carnrudh_PastyShop_EventScript_Customer::
	msgbox Carnrudh_PastyShop_Text_Customer, MSGBOX_NPC
	end

Carnrudh_PastyShop_Text_Keeper:
	.string "Pasties for PENHALLOW DAY!\n"
	.string "Crimped on the side, proper job.\p"
	.string "Come back on the day, my lover.$"

Carnrudh_PastyShop_Text_KeeperFestival:
	.string "Sold out by noon, every engine\n"
	.string "day. Never fails.$"

Carnrudh_PastyShop_Text_Customer:
	.string "Always leave the crust for the\n"
	.string "KNOCKERS, my nan used to say.\p"
	.string "Keeps 'em sweet, down the mine.$"
