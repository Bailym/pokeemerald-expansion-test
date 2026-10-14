Balwyn_MapScripts::
	.byte 0

Balwyn_EventScript_MineSign::
	msgbox Balwyn_Text_MineSign, MSGBOX_SIGN
	end

Balwyn_EventScript_PubSign::
	msgbox Balwyn_Text_PubSign, MSGBOX_SIGN
	end

Balwyn_Text_MineSign:
	.string "WHEAL GWYN\n"
	.string "DANGER! Old mine workings.\p"
	.string "Shafts and adits unsafe.\n"
	.string "Keep out by order of the parish.$"

Balwyn_Text_PubSign:
	.string "THE KNOCKER'S ARMS\n"
	.string "Free house, est. 1782.\p"
	.string "Pasties, ale, and old tales.\n"
	.string "Leave a crust for the Knockers!$"
