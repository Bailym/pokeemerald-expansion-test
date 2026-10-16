# Design

> Draft only: nothing here is set, and everything is subject to change.

## Region

- UK-based region, themed largely around Cornwall in the South West.
- Region name: Kernia, from Kernow (Cornish for Cornwall).
- Main game covers Cornwall; other UK areas open up postgame.
- Tone mixes cosy seaside towns, Cornish myth, rugged nature, and industrial (mining) heritage.
- Place names: Pokémon-style names with Cornish-language roots.
- Wild Area, like the one in Pokémon Sword/Shield, set on Bodmin Moor in the middle of the region.

## Story

- Main themes: industry vs. the wild land and coast, with a thread of myth running through.
- A corporation publicly revives Cornwall's old mines and brings back jobs. Secretly, it wants to harness the power of a legendary Pokémon.
- The legendary, Bucca (a real Cornish name for the spirit), is a spirit of the mines, inspired by the Knockers of Cornish folklore.
  - Like the Knockers, it helps those who respect the mine and punishes those who exploit it.
- The corporation awakens it, it rampages, and the player calms it and can catch it.
  - The rampage starts with eerie knocking heard across the region as an early warning, then builds to earthquakes, collapsing mine shafts, and rockfalls blocking routes.
  - To calm it, the player destroys the corporation's control device and battles it. Then, following the grandparent's journal, they leave the traditional miners' offering (the crust of a pasty) to end its rage.
- The corporation plot resolves before the player takes on the League.

## Lore and dialogue

- Lore everywhere: the region's story is told mostly through its text. Every NPC, trainer (intro, defeat, and post-battle lines), sign, and notice should add a piece of Kernia where it can, rather than generic filler.
- What to weave in:
  - Cornish folklore: the Knockers and Bucca, piskies, giants, the Mermaid of Zennor, black dogs. Later this ties in with the Elite Four's legends.
  - Mining heritage: wheals and engine houses, tinners and bal maidens, pasties and the crust left for the Knockers, and families who emigrated when the mines closed.
  - The decline and the divide: closed mines, young people leaving, and how locals feel about Lumen's promised jobs (some hopeful, some suspicious).
  - The grandparent's legends, so the journal feels grounded in what people already half-remember.
- Foreshadow and escalate: early text plants the legends (the knocking, the crust offering) as old superstition. After key story beats, such as the tremors after badge 5, dialogue should change to match, using flags where it's cheap to do.
- Voice:
  - Locals speak with a light Cornish dialect and a few Cornish words ("dreckly", "proper job", "my 'ansum", "emmet" for outsiders).
  - Lumen staff use upbeat corporate and PR speak.
  - Keep both readable, not caricatured.
- Name boxes: named characters always show their name above the text box, in cutscenes and in ordinary chats alike (`setspeaker SP_NAME_*`, with names in `src/data/speaker_names.h`). Unnamed NPCs ("a regular", grunts) don't get one. Trainers show theirs automatically when they spot the player (`OW_NAME_BOX_NPC_TRAINER` in `include/config/name_box.h`), and their after-battle lines use `setspeaker`.
- Brevity: GBA text boxes are small, so aim for one to three short pages per speaker. Each line should carry one idea.
- No real-world place names in dialogue:
  - Places in Kernia use their Kernia names.
  - Places outside it stay vague ("overseas", "up-country", "across the sea"), like most Pokémon regions.
  - If a Kernia name isn't decided yet, write around it rather than using the real-world name as a placeholder.
- Consistency: recurring lore facts (names, legends, dates) are recorded here or in the town docs, so the same story is told everywhere.

## Characters

- Naming: Cornish names for locals; pun or brand-style names for Lumen and outsiders. Trainer names must fit 10 characters (`TRAINER_NAME_LENGTH`), Pokémon names 12.
- Player: from a mining family.
- Mum: at home in the village; the classic parent who heals your team and sends you off. The game calls her "Mum" (British spelling).
- Grandparent: an old miner who knew the legends, passed away before the game starts. Leaves the player a journal of legends and mine maps (the key item "Grampy's Journal", `ITEM_GRAMPYS_JOURNAL`) that reveals story locations as the game goes on.
- Rival — Nova (a stage name given by Lumen's PR team): a trainer sponsored by the corporation as the PR face of its gym challenge.
  - A media darling: polished, confident, always on camera, and fully believes the corporation's message.
  - Their partner Pokémon, a Pawmi (cute Electric mascot for an energy brand), was issued by the corporation, not chosen from the starter trio.
  - Nova is their only name; no real name behind it.
  - Reads as a young man (stand-in sprite: Rich Boy).
  - Turns against the corporation when that partner is harmed or taken by its experiments, and the grandparent's journal makes the legends click.
- Professor — Kelyn (Cornish for 'holly', after the tradition of professors named for trees): a folklore scholar who studies how Pokémon shaped Cornish legends; the link between myth and science.
  - Reads as an older woman (stand-in sprite: Expert, female).
  - An old friend of the grandparent, which is why they visit the village and give the player their starter. Has a lab in Treveur.
  - Secretly also the Champion at Land's End (see Gyms and League).
- Corporation leader — Sterling: an outside CEO who sees Cornwall as a resource. A charming visionary who gives inspiring speeches, but is driven by wanting the legendary's power for themselves.

## Corporation

- Name: Lumen, a sleek, abstract corporate brand (like Macro Cosmos or Silph).
- Logo: a stylised green leaf with a lightning spark (eco-energy branding).
- Public image: heritage revival ("bringing the mines home", local pride) combined with green energy (lithium and rare metals for a clean future).
- Headquarters in Treveur. Also sponsors the Pokémon League.
- Look varies by rank: grunts wear hi-vis and hard hats on site; admins and HQ staff wear sleek corporate dress.
- Field operations: a uniformed security division of grunts, led by 2–3 admins.
  - Admins are split by department:
    - Peran (after St Piran, patron saint of tinners): Chief Engineer, building the control device. The local who sold out; a miner's child who knows the old tunnels.
    - Vance: Head of Security.
    - Sloane: Head of PR, managing Nova.
- The plan: build a control device to bind the legendary and command it.
- The legendary sleeps in the deepest old mine, near the player's village, so the climax brings the story full circle.
- The public is never told the truth; they stay fooled until the legendary rampages.
- Aftermath: the CEO is arrested, and the rival takes over and reforms the company into one they can believe in.

## Towns and Routes

- Structure: hub and spokes, with the Bodmin Moor Wild Area as the hub and gym towns branching off it.
- Sections of the moor unlock with badges or story progress.
- Hometown: Balwyn, a quiet former tin-mining village in the far west (see `Balwyn.md`).
- Main city: Treveur, from tre (town) + meur (great), "great town". Inspired by Truro.
- First gym town: Carnrudh, from carn (rocky hill or tor) + rudh (red), "red tor". Inspired by Camborne / Redruth, and named for Carn Brea, the hill between them, and for Redruth.
- Second gym town: Porthliw, from porth (cove) + liw (colour), "cove of colour". Inspired by St Ives, reached over Route 2's lighthouse headland and along its beach (see `Porthliw.md` and `Route2.md`).
- Carn Kowr, from carn (tor) + kowr (giant), "giant's tor": the hill above Carnrudh (inspired by Carn Brea), with the giant's stones. Lumen survey it for a quarry before gym 1 (see `Carnrudh.md`).
- Treveur is the main city: corporation HQ, the professor's lab, and the region's main shopping and services.
- Towns inspired by (and renamed from): St Ives / Penzance, Camborne / Redruth, Truro, St Austell clay country, Falmouth, and the north coast (Newquay, Padstow, Tintagel).
- Pokémon League: Land's End.

## Bodmin Moor Wild Area

- The central hub, like Sword/Shield's Wild Area, with gym towns branching off it.
- Zones, each its own map (or set of maps) with its own encounter table and weather:
  - Heath & tors: open heather and gorse, granite tors.
  - Bog & mire: wet, misty bogland.
  - Lake & river: moorland pools, reservoirs, streams, and waterfalls.
  - Woods & ruins: oak valleys, old engine houses, and abandoned quarries.
- Unlocking:
  - Heath & tors opens first, from Treveur, around badge 3.
  - Woods & ruins and Lake & river both open after badge 4.
  - After badge 5, the first tremors and knocking from Bucca stirring shift rocks or drain water, opening the bog and the way to the north coast. This foreshadows the legendary.
- Wild Pokémon:
  - Both visible Pokémon roaming the map and random encounters in tall grass.
  - Visible Pokémon appear only on the moor, not on regular routes.
  - Wild levels scale with the player's badge count, so the moor stays relevant all game. The exact rise per badge is decided when balancing trainer levels.
- Weather is fixed per zone: Heath & tors sunny, Bog & mire fog, Lake & river rain, Woods & ruins shade.
- Other things to do: hidden items and berry trees; landmarks and lore (standing stones, old inns, engine houses), with the grandparent's journal tying in.
- Technical notes:
  - A single map can be at most about 86×86 tiles (`MAX_MAP_DATA_SIZE` check in `src/fieldmap.c`), so each zone is built from connected maps.
  - Visible Pokémon use the expansion's Overworld Wild Encounters (`WE_OW_ENCOUNTERS` in `include/config/wild_encounter.h`, which needs `OW_POKEMON_OBJECT_EVENTS`). They spawn on encounter tiles (e.g. tall grass), so open areas meant to have roaming Pokémon need encounter tiles. See `docs/tutorials/how_to_overworld_wild_encounters.md`.
  - Visible spawning is a global setting. Keeping it moor-only means assigning a flag to `WE_OWE_FLAG_DISABLED` and setting/clearing it when entering and leaving the moor.
  - Badge-scaled wild levels aren't built in; they need a code change around `ChooseWildMonLevel` in `src/wild_encounter.c`.

## Gyms and League

- Classic structure: 8 gym badges, then the Pokémon League.
- Gyms are taken in a fixed order.
- Gym types are driven by each town's character and by the story.
- Leaders have split loyalties: some back the corporation (at least at first), others resist it.
  - The five resisting leaders push back mainly by warning the player: each shares a suspicion or clue about Lumen after their battle.
  - The three backing leaders don't act in time when Bucca rampages, but each has a remorseful line afterwards.

| # | Town (inspired by) | Type | Leader | Stance on corporation |
|---|---|---|---|---|
| 1 | Carnrudh (Camborne / Redruth) | Fire | Tanek (tan = fire) | Backs it |
| 2 | Porthliw (St Ives) | Flying | Enys (island) | Resists |
| 3 | Treveur (Truro) | Psychic | Locryn (a legendary king) | Backs it |
| 4 | Falmouth | Steel | Hornor (horn = iron) | Backs it |
| 5 | St Austell clay country | Rock | Karrek (rock) | Resists |
| 6 | Newquay | Water | Mordon (mor = sea) | Resists |
| 7 | Padstow | Ice | Rew (frost) | Resists |
| 8 | Tintagel | Dragon | Pendra (from Pendragon) | Resists |

- Route through the order: the far west first (1–2), then Treveur (3), then the south coast (4–5), then across Bodmin Moor to the north coast, travelling south-west to north-east (6–8).
- The Fire gym opening introduces the mines and the corporation straight away. All three corporation-backing leaders come in the first four gyms.
- After badge 5, the way across the moor to the north coast opens when Bucca's first tremors shift rocks or drain water (see Bodmin Moor Wild Area).
- After badge 8, the player heads home to the far west for the climax at the deepest mine, then on to the League at Land's End.
- Elite Four: each member embodies a Cornish legend, and dresses and acts the part (a storyteller, a wrestler, a singer, a moor-walker). Faced in this order:
  1. Kitto — Piskies (mischievous little folk who lead travellers astray): Fairy.
  2. Zennor — the Mermaid of Zennor (lured a man into the sea with her singing): Water dual-types, e.g. Water/Fairy, Water/Psychic, Water/Ghost.
  3. Cormoran — the Giants (Cormoran and Bolster; Cornish wrestling): Fighting.
  4. Sable — black dogs (spectral hounds of the moors and lanes): Dark.
- Each Elite Four member has a line reacting to the corporation's fall, since it sponsored the League.
- Champion: the professor. An ageing Champion who still holds the title, and whose final match is against the player. Can't openly act against the corporation because the League is officially neutral and the corporation sponsors it.

## Pokémon

- Starters: a themed trio of British wildlife, given by the professor in the player's village. All are 3-stage lines that evolve purely by level. No Grass starter.
  - Fletchling line (robin): Normal/Flying, becoming Fire/Flying when it evolves at 17.
  - Spheal line (grey seal, a Cornish coast icon): Ice/Water.
  - Shinx line (big cat, after the Beast of Bodmin Moor legend): Electric.
- Main-story legendary: just one. Groudon is a placeholder for now; if it becomes a fakemon later, it would be Ground/Ghost.

## Postgame

- Driven by exploration and legends, with a light story.
- Professor Kelyn, free of Champion duties, researches legends beyond Cornwall and sends the player to each area.
- Three small areas, each with one town, a route or two, and the legend's site. Reached by real-world routes:

| Area | Getting there | Legend | Placeholder legendary |
|---|---|---|---|
| Devon / Dartmoor | Across the Tamar bridge | Old Crockern, the ancient spirit of Dartmoor guarding its granite and tin (a counterpart to Bucca) | Regigigas |
| Isles of Scilly | Ferry from Penzance (like the real Scillonian) | Lyonesse, the sunken kingdom between Land's End and Scilly | Walking Wake |
| Wales | Train or boat | The red and white dragons fighting beneath Dinas Emrys | Reshiram & Zekrom |

- All postgame legendaries are existing species as placeholders for now.

## Ideas

## Open questions

- How much moor wild levels rise per badge (decide when balancing trainer levels).
