# Porthliw

> Draft only: nothing here is set, and everything is subject to change.

## Overview

- The second gym town, at the end of Route 2. Name from porth (cove) + liw (colour), "cove of colour", for its artists and its famous light.
- A harbour artists' colony: galleries, studios, beaches, and gulls that steal pasties.
- Gym 2: Enys, Flying type, who resists Lumen.

## Inspiration

- St Ives: the harbour and its artists' colony, the light painters come for, the galleries, and the gulls.

## Story

1. Arrival: the town is getting ready for the gallery's big opening night, an exhibition sponsored by Lumen. The gym is shut: Enys is tied up with the opening.
   - The player meets Enys painting on the harbour wall: walking along the harbourfront, she calls out and comes over, so it can't be missed. She invites them to the opening. The gallery's door staff let the player in once they've met her. Until then the town is free to explore (Center, Mart, townsfolk).
2. The opening night: the player attends. Sloane, Lumen's Head of PR, makes her first appearance and gives a polished speech presenting Lumen as friends of the arts: general PR about lighting up Kernia's creative coast, with a nod to jobs in Carnrudh, and nothing concrete to attack.
3. Enys answers with a counter-speech and turns the room against Lumen. She names Lumen's closures, Carnrudh's east road included. She says painters come for the light and the wild coast, and Lumen's quarries and drills are what's dulling it. And she's heard Lumen were "surveying" Carn Kowr's giant's stones until some kid turned up (a nod to the player: word of the tor has spread despite Lumen's spin). This is the public row the rest of Kernia hears about.
4. After the opening, the gym opens. The gallery stays open as a real gallery: paintings with short lore captions, a curator, and visitors.
5. Gym 2: the player beats Enys for badge 2 (the GULL BADGE) and TM Aerial Ace. After the battle, Enys shares her suspicion: her seabirds have gone quiet, won't fly over Lumen's sites, and the flocks wheel away west whenever the ground hums (an early hint of Bucca stirring). She also mentions that Lumen have reopened the east road, so the way to Treveur is open (see `Carnrudh.md`).

## Characters

- Enys (Cornish for "island"): a young painter, sharp and outspoken, who paints the seabirds over the bay. Flying gym leader. Resists Lumen, and like the other resisting leaders, shares a suspicion about them after her battle.
- Sloane: Lumen's Head of PR and Nova's manager (see `DESIGN.md`). First appearance, at the opening night, on her own (Nova has moved on after the lighthouse). Stand-in sprite: Teala.
- Townsfolk: artists, fishermen, gallery staff, and visitors, with lore lines on the colony, the light, and how the town feels about Lumen's money.

## The gym

- A rooftop studio: skylights, canvases, and gull perches.
- At the top of the hill at the back of the town, entered by an ordinary front door; the interior is the rooftop.
- A short trainer gauntlet like gym 1, with no puzzle: two of Enys's painting students in a line (Lv14–15, a bird or two each), then Enys.
- Enys's team: Wingull Lv15, Wattrel Lv15, and her ace Cramorant Lv16.
- Reward: badge 2, the GULL BADGE, and TM Aerial Ace.

## The town

- A St Ives-style harbour bowl: a curved harbour with boats and a pier in the middle, and the town packed round it on rising ground.
- The Pokémon Center, Mart, and gallery on the harbourfront; the gym at the top of the hill at the back.

## Already built that the plan must hook into

- **The way in:** Route 2's beach runs to its west edge (x 0–1, rows 34–41, level 3), the likely connection to Porthliw. Route 2's map section is `MAPSEC_KERNIA_ROUTE_2`. Any new route or town needs Kernia's own `MAPSEC_*` (appended to `src/data/region_map/region_map_sections.json`): FireRed's sections open the Kanto map.
- **Badge 2 unlocks Fly** (`design/plans/hm-free-field-moves.md`). After Enys's badge line, her script does `buffermovename STR_VAR_1, MOVE_FLY` then `call EventScript_FieldMoveUnlocked` (the jingle and "You can now use Fly outside of battle!"), as Tanek does for Rock Smash in `Carnrudh_Gym/scripts.inc`. Enys gets a line of her own about flying, in her voice.
- **Porthliw as a fly point**, like Balwyn and Carnrudh:
  - a `MAPSEC_PORTHLIW` section;
  - a `FLAG_VISITED_PORTHLIW` (next free Kernia flag) set in the town's `ON_TRANSITION` script and in its scenario story part;
  - a `HEAL_LOCATION_PORTHLIW` outside its Pokémon Center;
  - a `GetMapsecType` case, `sFlyLocations` entry and `sMapHealLocations` entry in `src/region_map.c`;
  - a `PLACES` entry in `tools/kernia/gen_region_map.py` (planned at grid (5, 10), west of Route 2's cells), then re-run it.
- **Field moves:** with badge 1 the player can already smash rocks; Cut and Flash wait for badge 3. Breakable rocks need a `FLAG_TEMP_*` each.
- **Scenarios:** `route2_bay` is the latest. Add Porthliw ones chained from it (`tools/playtest/README.md`).

## Decided against

- Penzance and a tidal-island gym (after St Michael's Mount), or a blend of both towns: Porthliw is the St Ives-style art town.
- Other Lumen beats: a harbour development, billboards and branding, closing the coast path.
- Other opening-night scenes: Enys pulling her painting off the wall, a battle at the gallery, Enys simply not turning up.
- Sloane with Nova, Nova or Sterling as Lumen's speaker.
- The gym open on arrival, or a small errand instead of the opening night.
- Other ways into the opening: walking straight into the gallery (Enys would first appear mid-speech), a door attendant with no Enys meeting, or a fade to an evening version of the town (needs a night tint or map state).
- A wind-current puzzle or a gallery maze in the gym.
- Reopening the east road straight after the speech: it stays gated on badge 2.
- Porthwyn, Treliw, and Golowyn as the town's name.

## Open questions

- The exact lines of the speeches, the meeting, and the suspicion (the beats are settled above).
- The town's exact layout and the other interiors (houses, studios), settled with a render.
