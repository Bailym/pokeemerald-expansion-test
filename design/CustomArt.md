# Custom art

Every piece of art Kernia currently borrows from vanilla, and what replaces it. Each entry says what stands in now, where it's used, and what to change in code once the new art exists. Kernia is built as Emerald, so stand-ins must be Emerald art: FireRed's overworld sprites don't load (see Formats).

## Priorities

1. **Named characters' overworld sprites:** Nova, Kelyn, Tanek, Peran, and the Lumen grunt. They're on screen most and carry the story.
2. **The *Puffing Bucca*:** the centrepiece of Carnrudh's festival, now a moving truck.
3. **The engine house:** Carnrudh's gym exterior, and the skyline of Balwyn and Route 1.
4. **Carn Kowr:** the giant's stones and the granite tor.
5. **Trainer battle pics** for the same characters.
6. **The rest:** the badge, the journal's icon, festival dressing, the site hut, the gym interior, and the peak's folly and monument.

## Formats

| Kind | Size | Colours | Lives in | Notes |
|---|---|---|---|---|
| Overworld sprite (person) | 16×32 per frame, 9 frames (standing and two walking frames, facing down, up, and left; right is mirrored) | 15 + transparent, one palette | `graphics/object_events/pics/people/` | Add a graphics info and an `OBJ_EVENT_GFX_*` constant (`include/constants/event_objects.h`, `src/data/object_events/`). Use an Emerald palette tag, not the FRLG `NPC_*` ones. |
| Large object (e.g. the engine) | 32×32, 48×48 or 64×64 | 15 + transparent | `graphics/object_events/pics/misc/` | An object only blocks its anchor tile, so solid ground under the rest must come from the map. |
| Trainer front pic | 64×64 | 15 + transparent | `graphics/trainers/front_pics/` | See `docs/tutorials/how_to_trainer_front_pic.md`. Set with `Pic:` in `src/data/trainers.party`. |
| Item icon | 24×24 | 15 + transparent | `graphics/items/icons/` | Set `.iconPic` and `.iconPalette` in `src/data/items.h`. |
| Trainer card badge | 16×16, one slot of `graphics/trainer_card/badges.png` (128×16, eight badges) | Shares the strip's palette | `graphics/trainer_card/badges.png` | |
| Map tiles | 8×8 tiles built into 16×16 metatiles | Up to 6 palettes in a secondary tileset | `data/tilesets/secondary/<name>/` | Edit in Porymap's tileset editor. Set collision and behaviour per metatile. |

**Tileset room:** Carnrudh, Route 1, Balwyn, and Carn Kowr use `gTileset_General` + `gTileset_Dewford`. Dewford's tile sheet is already full (512 tiles), and it has 132 free metatile slots (up to `0x3FF`). New tiles probably need a new Kernia secondary tileset, which means remapping those maps' Dewford blocks (the generators in `tools/kernia/` make that a find-and-replace on block IDs). Balwyn's notice board (`0x37B`) was squeezed into Dewford, so check what's free first.

## Characters

Each needs an overworld sprite, and a trainer front pic if they battle.

| Character | Now (overworld) | Now (battle pic) | Used in | Look |
|---|---|---|---|---|
| Nova, the rival | `RICH_BOY` | Rich Boy | Balwyn (opening, battle, send-off), Carnrudh (festival cameo) | A young man; Lumen-family polish. Pawmi stays a species sprite. |
| Kelyn, Grampy's old friend | `EXPERT_F` | — | Balwyn (opening, starters) | An older woman. |
| Tanek, gym 1 leader (Fire) | `NORMAN` | Leader Norman | Carn Kowr peak, Carnrudh Gym | A local who watched the town die: a working man, engine-house soot and a stoker's build. |
| Peran, Lumen's Chief Engineer | `SCIENTIST_1` | FRLG Scientist | Carn Kowr peak (proof, battle) | A local who sold out; engineer, not a scientist. Recurs later. |
| Lumen grunt | `DEVON_EMPLOYEE` | FRLG Engineer | Balwyn (road, mine), Carn Kowr (four guards) | Hi-vis survey team. A female variant would help crowds. |
| Bal maiden (gym trainer LOWENA) | `GIRL_3` | Lass | Carnrudh Gym | Optional: an ore-dressing girl with an apron and hammer. |
| Stoker (gym trainer HEDRA) | `MAN_5` | Kindler | Carnrudh Gym | Optional: vanilla Kindler is close. |
| Wrestler JAGO | `BLACK_BELT` | Black Belt | Carnrudh festival | Optional: a Cornish wrestler's canvas jacket. Could serve Cormoran's gym later. |

- Tanek and Peran are on the peak together; Peran's sprite moves (walks off), so it needs full walking frames.
- When a sprite lands, swap the `graphics_id` in each map's `map.json` and the `Pic:` in `trainers.party`, and update the stand-in notes in `Balwyn.md` and `Carnrudh.md`.

## The *Puffing Bucca* (Carnrudh's engine)

- **Now:** `OBJ_EVENT_GFX_TRUCK` (Littleroot's moving truck, 48×48) at (21, 22) in Carnrudh's field, `LOCALID_CARNRUDH_ENGINE`.
- **Wanted:** Cap'n Penhallow's steam road engine, after Trevithick's *Puffing Devil*: a tall chimney, a boiler on wheels, brass fittings. Miners once mistook it for the Bucca, so a slightly monstrous silhouette fits.
- **Size:** 48×48 keeps the current footprint. 64×32 (long and low) or 64×64 would need the solid area changed.
- **Animation (nice to have):** smoke puffs from the chimney on a loop during the festival, and a still, half-polished frame before it. The festival state is `VAR_CARNRUDH_STATE` ≥ `CARNRUDH_STATE_TOR_DONE`.
- **Code:** swap the `graphics_id` in `data/maps/Carnrudh/map.json`. If the footprint changes, update `ENGINE` and the solid area in `tools/kernia/gen_carnrudh.py` (now x 20–22, rows 20–22) and re-run it.
- Also used as a chalk drawing on the miners' school blackboard (text only, no art needed).

## Buildings and tiles

### Engine houses
- **Carnrudh Gym exterior:** now Dewford's gym (6×5, `GYM` in `tools/kernia/layoutlib.py`) at (5, 5), door at (8, 9). Wanted: a restored Cornish engine house, with a tall stone chimney, a granite bob wall, and arched windows. Keep the door at (8, 9) or move the warp with it.
- **Wheal Gwyn (Balwyn):** the mine is now a cave mouth (Granite Cave's entrance, from Route 106) at (6, 4). Wanted: a ruined engine house over the shaft, then a Lumen-restored one in later states.
- **Route 1 skyline:** old engine houses on the moor (`Route1.md`), as scenery only.
- A shared set (chimney, roofless walls, a roofed version) would cover all three.

### Carn Kowr
- **The giant's stones:** all four are the same pointed menhir now (`MENHIR` in `layoutlib.py`: `0x083`, `0x084`, `0x08B`, `0x08C`). Wanted: four distinct shapes that match their texts:
  - **The Hand:** a slab split into five long fingers.
  - **The Head:** a great round boulder perched on the slope.
  - **The Cradle:** a slab with a hollow worn in it, like a cot.
  - **The Well:** a basin full of rainwater, then a dry version showing cup-and-ring carvings after the proof (`STONES_DONE`; switch with `setmetatile` in an `ON_LOAD` map script).
- **The tor:** granite outcrops now use vanilla's rounded boulders, and the summit is a cluster of them. Wanted: stacked, weathered granite slabs (a real tor), with pieces that can sit on each other without gaps.
- **The peak:** Carn Brea's castle folly and the monument to a mine-owning family (no stand-ins yet), and Lumen's survey camp and drill site beside the Well (only a sign now).
- The rest of Carn Kowr (heath, Route 104-style cliffs and stairs) works with vanilla tiles.

### Region map

- Kernia's region map (the Town Map and fly map) is a stand-in: a blocky Cornwall built from Hoenn's plain sea, land, route and town tiles by `tools/kernia/gen_region_map.py`, with no coastline. Wanted: a real Cornwall map (coast, moors, rivers) in the region map's style, plus the frame and town art. Keep the grid positions in the generator in step with it.

### Route 2

- The lighthouse on the headland: a stand-in, the Mirage Tower (Route 111) recoloured to grey granite, copied by `tools/kernia/add_lighthouse_tiles.py` into 18 Dewford metatiles (`0x37C`–`0x38D`, 3 wide by 6 tall) with its own palette (Dewford slot 12). A real lighthouse (a granite tower with a lantern, like Longships or Wolf Rock) can replace the tiles in place; re-run the route generator after changing the size. No interior is planned. (A hand-drawn red-and-white tower was tried first and rejected.)
- The keeper's cottage: the vanilla red-roofed cottage for now. Inside, a copy of Mr Briney's house (Route 104); a keeper's home (nets, an old photo of the light) would suit it better.

### Carnrudh
- **Festival dressing:** bunting across the main street and stalls in the field. Neither exists now (vanilla has nothing that fits). The treats stall keeper stands on open grass at (26, 21). Show them with `setmetatile` in an `ON_LOAD` script once `TOR_DONE` is set, or as objects.
- **Buildings:** Dewford's houses and red cottage stand in for granite miners' cottages, the pasty shop, and the miners' school. Optional, but a granite terrace would sell the town.
- **Gym interior:** Lavaridge Gym's brick, pipes and dais (`tools/kernia/gen_carnrudh_gym.py`). Wanted: an engine-house boiler room with boilers, a beam engine, coal heaps, and pressure gauges. Its vents are solid decoration because Lavaridge's are warps.

### Balwyn
- **Lumen's site hut** in the mine yard: missing now (no tiles fit).
- **Lumen signs and posters** ("Bringing the mines home!"): the notice board is Dewford's, redrawn on grass (`0x37B`).

## UI and icons

- **The ENGINE BADGE:** now Flannery's Heat Badge, shown in slot 1 by a remap table (`sHoennBadgeArt` in `src/trainer_card.c`). Wanted: an engine or flywheel badge. Draw it into slot 1 of `graphics/trainer_card/badges.png`, then remove `sHoennBadgeArt` (and swap the Stone Badge back to slot 4 if that art is still in use).
- **Grampy's Journal:** borrows the Old Sea Map's icon (`src/data/items.h`). Wanted: a battered leather notebook.
- The other seven badges come with their gyms; list them here as they're designed.

## Already custom

- Balwyn's notice board (`0x37B` in `gTileset_Dewford`).
