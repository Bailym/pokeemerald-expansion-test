KerniaRoute2_KeepersCottage_MapScripts::
	.byte 0

@ The retired keeper at home, once he's given the Old Rod on the beach.
KerniaRoute2_KeepersCottage_EventScript_Keeper::
	lock
	faceplayer
	msgbox KerniaRoute2_KeepersCottage_Text_Keeper, MSGBOX_DEFAULT
	call KerniaRoute2_EventScript_KeeperOnTheOldBull
	release
	end

KerniaRoute2_KeepersCottage_Text_Keeper:
	.string "Forty year I climbed them stairs\n"
	.string "every night to light the lamp.\p"
	.string "One winter, a storm blew three\n"
	.string "nights straight. Never slept.\p"
	.string "Every boat came home, mind.\n"
	.string "Every one.$"
