Carnrudh_House2_MapScripts::
	.byte 0

Carnrudh_House2_EventScript_OldMiner::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_House2_EventScript_OldMinerFestival
	msgbox Carnrudh_House2_Text_OldMiner, MSGBOX_NPC
	end

Carnrudh_House2_EventScript_OldMinerFestival::
	msgbox Carnrudh_House2_Text_OldMinerFestival, MSGBOX_NPC
	end

Carnrudh_House2_EventScript_Wife::
	goto_if_ge VAR_CARNRUDH_STATE, CARNRUDH_STATE_TOR_DONE, Carnrudh_House2_EventScript_WifeFestival
	msgbox Carnrudh_House2_Text_Wife, MSGBOX_NPC
	end

Carnrudh_House2_EventScript_WifeFestival::
	msgbox Carnrudh_House2_Text_WifeFestival, MSGBOX_NPC
	end

Carnrudh_House2_Text_OldMiner:
	.string "Forty years I worked the mines,\n"
	.string "man and boy.\p"
	.string "When they shut, my brothers went\n"
	.string "overseas. Never came back.$"

Carnrudh_House2_Text_OldMinerFestival:
	.string "Lumen wanted the tor for gravel.\n"
	.string "Some things you just keep.$"

Carnrudh_House2_Text_Wife:
	.string "He won't say it, but he misses\n"
	.string "the mine every day.$"

Carnrudh_House2_Text_WifeFestival:
	.string "We'll watch the parade from\n"
	.string "the window. Best seat in town.$"
