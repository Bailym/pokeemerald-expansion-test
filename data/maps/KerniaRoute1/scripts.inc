KerniaRoute1_MapScripts::
	.byte 0

KerniaRoute1_EventScript_RouteSign::
	msgbox KerniaRoute1_Text_RouteSign, MSGBOX_SIGN
	end

KerniaRoute1_Text_RouteSign:
	.string "ROUTE 1\n"
	.string "{LEFT_ARROW} BALWYN   CARNRUDH {RIGHT_ARROW}$"
