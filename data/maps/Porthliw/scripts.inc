Porthliw_MapScripts::
	.byte 0

Porthliw_EventScript_TownSign::
	msgbox Porthliw_Text_TownSign, MSGBOX_SIGN
	end

Porthliw_EventScript_GymSign::
	msgbox Porthliw_Text_GymSign, MSGBOX_SIGN
	end

@ The gym is shut until the gallery's opening night is over.
Porthliw_EventScript_GymDoor::
	msgbox Porthliw_Text_GymDoorShut, MSGBOX_SIGN
	end

Porthliw_EventScript_GallerySign::
	msgbox Porthliw_Text_GallerySign, MSGBOX_SIGN
	end

@ After Barbara Hepworth's garden in St Ives.
Porthliw_EventScript_SculptureGardenSign::
	msgbox Porthliw_Text_SculptureGardenSign, MSGBOX_SIGN
	end

@ The statue in the harbour square, read from below its base.
Porthliw_EventScript_HarbourLight::
	msgbox Porthliw_Text_HarbourLight, MSGBOX_SIGN
	end

Porthliw_Text_TownSign:
	.string "PORTHLIW\n"
	.string "The cove of colour.$"

Porthliw_Text_GymSign:
	.string "PORTHLIW POKéMON GYM\n"
	.string "LEADER: ENYS\p"
	.string "Wings over the bay,\n"
	.string "light in every colour!$"

Porthliw_Text_GymDoorShut:
	.string "The door's locked. There's a note\n"
	.string "pinned to it…\p"
	.string "“GYM SHUT for the gallery's\n"
	.string "opening night. - ENYS”$"

Porthliw_Text_GallerySign:
	.string "PORTHLIW GALLERY\n"
	.string "Grand opening night!\p"
	.string "Proudly sponsored by Lumen.$"

Porthliw_Text_SculptureGardenSign:
	.string "KERENSA'S GARDEN\p"
	.string "The sculptor KERENSA carved here\n"
	.string "for forty years.\p"
	.string "“The sea smooths every stone.\n"
	.string "I just help it along.”$"

Porthliw_Text_HarbourLight:
	.string "THE OLD HARBOUR LIGHT\p"
	.string "For a hundred years it guided\n"
	.string "the pilchard boats home.$"
