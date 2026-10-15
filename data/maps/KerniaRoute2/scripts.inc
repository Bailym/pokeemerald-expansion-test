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
	.string "THE LIGHTHOUSE\n"
	.string "Keep to the path. Cliffs unsafe.$"
