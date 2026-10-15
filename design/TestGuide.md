# Test guide

A rough playthrough of Kernia from a new game, with what to check along the way. It isn't exhaustive: each area lists the checks most likely to break, or that would hurt play most if they did, first. ⚠ marks the highest-risk ones. Keep it up to date as areas are added.

## Before you start

- **Start a new game** after any change to flags, vars, trainers, or map groups. Old saves keep old flag positions (the system flags moved when the trainer limit went up to 896), which gives confusing results.
- **Debug menu:** R+Start. Use it to give a Pokémon, warp, and set flags and vars to skip ahead (see Shortcuts).
- **Build:** `make -j$(nproc)`. If it fails with `JSONPROC_ERROR ... unexpected end of input`, a parallel build cut off `src/data/heal_locations.json`: run `git checkout -- src/data/heal_locations.json` and build again.
- **Text:** Kernia lines are kept to about 32 characters. Anything that runs off the box, especially with a long player name (`{PLAYER}` lines), is a bug.

## Things that break across the whole game

- ⚠ **Story flags after the trainer-limit change:** badges, the Pokédex, and the trainer card all use system flags that moved up by 0x20. If any of these look wrong on a new game, suspect the flag shift.
- ⚠ **One-time scenes replaying:** leave and re-enter each map after a scene, and save and reload, to check it doesn't play again.
- ⚠ **Losing a scripted battle:** Nova's battle continues the story either way; Peran's can be lost and retried. Check that neither leaves you stuck.
- ⚠ **Invisible or crashing NPCs:** FireRed overworld sprites don't load in Emerald. An NPC that isn't there, or a crash when a scene moves someone, usually means a FireRed sprite.
- **Map seams:** walking between connected maps should be seamless (trees, roads, and cliffs line up), with the right area popup.
- **Healing and whiting out:** after healing at a Pokémon Center, losing should send you back to that Center.

## 1. Balwyn (the opening)

**Story:** wake up in your bedroom, then get Mum's morning scene downstairs. Roam the village. Head east and a Lumen grunt sends you to the event at Wheal Gwyn: Nova announces the mine's reopening and Kelyn asks about the Bucca. Kelyn walks you home and offers a starter (Fletchling, Spheal, or Shinx), with the Pokédex, Poké Balls, and Grampy's Journal. Nova battles you outside, then leaves for Carnrudh. Walking past the mine fence afterwards plays faint knocking.

- ⚠ The grunt stops you on both road rows (11–12) every time until you have a Pokémon, and Route 1 opens after Nova's send-off.
- ⚠ The event crowd only appears after the grunt sends you there, and the scene plays without anyone walking through walls or each other.
- ⚠ Each starter is the right species at Lv5, and the Pokédex, Poké Balls, and journal (Key Items) are all given.
- ⚠ Nova's battle: win and lose both continue the scene (no whiteout to the house), and re-entering Balwyn doesn't replay it.
- Mum's morning scene plays once; talking to her later heals your team.
- The knocking at the fence plays once only.
- Villagers have "before" lines, then "after" lines once the event is done, and the yard gets the grunts and notice board.

## 2. Route 1

**Story:** a moorland lane east to Carnrudh. Two trainers, a little tall grass, a Poké Ball item, a hidden Potion, and a ledge.

- ⚠ Seamless joins with Balwyn (west) and Carnrudh (east).
- Jory and Tamsin spot you and battle once, and stay beaten after a reload.
- Tall grass gives wild battles (Lv2–4); open ground doesn't.
- The Poké Ball at (10, 13) and the hidden Potion at (10, 5) can each be taken once.
- The ledge at row 8 only lets you hop down, not climb up.

## 3. Carnrudh (arrival)

**Story:** a mining town getting ready for Penhallow Day ("engine day"). The gym is shut: Tanek is up on Carn Kowr with Lumen, surveying the tor for a quarry. The way on is the path north.

- ⚠ The Pokémon Center heals you and sets the respawn point (lose a battle later and check you come back here).
- ⚠ The gym door is blocked by a local who says Tanek is on the tor.
- ⚠ The south-west road is blocked: stepping into the gap turns you back with a Lumen survey worker's line.
- Every door works and comes back to the right spot: the Center, the Mart, the gym (blocked for now), both houses, the pasty shop, and the school.
- The Mart sells Poké Balls, Potions, Antidote, Paralyze Heal, and Awakening.
- Townsfolk have "getting ready" lines. No festival crowd, Nova, or festival music yet.

## 4. Carn Kowr (the riddle)

**Story:** on the climb's road, Grampy's Journal opens to a rhyme naming the giant's stones in order: Hand, Head, Cradle, then the Well. The climb has three terraces of cliffs with stairs; a Lumen grunt guards each stone, and another blocks the gap to the peak until the first three stones are done in order. A wrong stone resets the order with a hint.

- ⚠ The journal rhyme plays once on the climb's road and never again.
- ⚠ **Stone order:** Hand, then Head, then Cradle. Try a wrong stone (e.g. the Head first): you get "Nothing happens", a hint, a reset, and the offer to read the rhyme again. Re-inspecting the stone you just did is harmless.
- ⚠ A stone won't respond until its grunt is beaten.
- ⚠ **The gate:** before the Cradle, the grunt in the gap turns you back (walk into it and talk to him). After the Cradle he battles you once, then lets you up.
- Each grunt spots you and battles once (Lv5–7), and stays beaten after a reload.
- You can't walk through any cliff, boulder, or stone, and the stairs are the only way up.
- Wild battles only come from the tall grass patches, and the riddle route never forces you through them.
- Seamless joins: town ↔ climb ↔ peak.

## 5. Carn Kowr peak (the proof and Peran)

**Story:** Peran (Lumen's Chief Engineer) and Tanek are by the Well. Done last, the Well drains to reveal cup-and-ring carvings: the tor is an ancient monument. Peran calls it weathering, Tanek says somebody made it, and Peran battles you. After losing, Peran lets slip "It's not what's on the hill. It's what's under it." and walks off; Tanek, shaken but loyal, follows to open the gym.

- ⚠ **Crash check:** beating Peran must play the whole walk-off without crashing, and both leave the peak.
- ⚠ Peran steps under you and faces you, from both Well tiles (20, 8) and (21, 8).
- ⚠ Lose to Peran on purpose: you white out to your last heal point (Carnrudh's Center if you healed there), and talking to him on the peak starts the battle again.
- Peran (Lv7–8) is beatable with a starter around Lv8–10.
- Afterwards the Well shows the dry basin with carvings, and Peran and Tanek are gone for good.

## 6. Tanek's gym (badge 1)

**Story:** back in town, the gym blocker is gone. The gym is a boiler room with two trainers (a stoker and a bal maiden) and Tanek on his dais. Beating him gives the ENGINE BADGE and TM51 Flame Charge.

- ⚠ Badge 1 shows on the trainer card (with the Heat Badge's flame art), and TM51 Flame Charge is in your bag.
- ⚠ Talking to Tanek again gives his post-battle line, not a rematch, and still does after a reload.
- Both gym trainers spot you, even if you hug the far wall.
- You can't step onto the steam vents (they'd try to warp you).
- The gym statues read differently before and after the badge.
- Tanek (Litwick Lv11, Torkoal Lv12) is beatable but a step up; Torkoal mustn't set up sun (its ability is White Smoke).

## 7. Carnrudh (Penhallow Day)

**Story:** with the tor saved, the festival is on: a crowd round the *Puffing Bucca* (a stand-in truck), dancers, a treats stall, a Cornish wrestler, and Nova defending Lumen. The miners' school teacher gives you a Hard Stone.

- ⚠ Festival music plays when you walk down from the climb, and again after leaving a building. Before the tor, the town has its normal music.
- ⚠ **The engineman's welcome:** walking down from the tor (from either path tile), the engineman hurries up to you and leads you to the engine without walking through anyone. You pull the whistle, the screen shakes, and he gives you Charcoal. Walking back up and down again doesn't replay it, and afterwards he's at his spot by the engine (also after a reload).
- ⚠ **Missed welcome:** white out after the tor (or reach town without coming down the path) and talk to the engineman by the engine: he offers the whistle and Charcoal instead, once.
- ⚠ The festival crowd, Nova, and the wrestler only appear after the tor, and townsfolk switch to festival lines.
- You can't walk onto any part of the engine.
- The treats stall sells Fresh Water, Soda Pop, Lemonade, and Lava Cookies.
- The wrestler JAGO battles once if you talk to him, then gives his post-battle line.
- The school teacher gives the Hard Stone once; with a full bag, talking again gives it.
- Signs outside the pasty shop and school read correctly.

## 8. Route 2 (the coast path)

**Story:** the coast path south from Carnrudh, opened once the tor is saved. A terraced headland steps down to the sea, with a lighthouse on its summit and a sandy bay at its foot. (Being built: Nova's battle, trainers, tall grass, and the fisherman come in later phases of `design/plans/route-2.md`.)

- ⚠ Before the tor, the survey worker blocks the way out of Carnrudh. After it (`carnrudh_tor_done` or later), the worker's gone and the road is open.
- ⚠ Seamless join with Carnrudh: the tree band and road line up, and the "ROUTE 2" popup shows.
- ⚠ **Levels:** you can only change level by the steps: up two flights to the summit, down to the lower terraces, and down to the beach. Walking along a cliff edge never lets you step down (or up) without steps, and you can't get onto the thin ledges in the sea cliffs.
- You can't walk onto the sea, the lighthouse, or the cottage.
- The lighthouse and cottage draw cleanly, and walking round them never puts them over the player.
- Both signs read correctly.

## Shortcuts

After `make`, `python3 tools/playtest/play.py <scenario>` opens mGBA with a new game already at that point (player KERNOW, Spheal as the starter), with trainers up to that point beaten and a team levelled for the next fight. `--list` shows them all. In VS Code, the **Play scenario** task builds and then lets you pick one.

| Scenario | Starts | Team | To test |
|---|---|---|---|
| `balwyn_done` | Outside the house in Balwyn; Nova beaten, knocking heard | Spheal 6 | Route 1 |
| `carnrudh_arrived` | Outside Carnrudh's Pokémon Center (also the respawn point); Route 1 done | Spheal 8, Rookidee 6 | Carnrudh before the climb, the verse trigger |
| `carnrudh_riddle` | Just past the verse trigger on Carn Kowr (`RIDDLE_READ`) | Spheal 8, Rookidee 6 | The climb grunts and stones |
| `carnrudh_cradle` | Below the gate grunt (`CRADLE_DONE`) | Spheal 9, Rookidee 7, Rolycoly 6 | The gate battle, then read the Well for the proof scene |
| `carnrudh_well` | In front of the Well on the peak, Peran just below; gate grunt beaten (`CRADLE_DONE`) | Spheal 10, Rookidee 8, Rolycoly 7 | Read the Well: the proof scene, Peran's battle and the walk-off. Also try from the right-hand Well tile, and losing. |
| `carnrudh_tor_done` | On the peak in front of the drained Well; Peran beaten, Peran and Tanek gone (`TOR_DONE`) | Spheal 12, Rookidee 10, Rolycoly 9 | The dry Well, then walk down to town for the engineman's welcome and Charcoal |
| `carnrudh_gym` | Outside the gym door; festival on and the engineman's welcome done, with Charcoal (`TOR_DONE`) | Spheal 13, Rookidee 11, Rolycoly 10 | The festival, the gym and Tanek |
| `carnrudh_badge1` | Outside the gym door with badge 1 and TM51 (`BADGE_WON`) | Spheal 14, Rookidee 12, Rolycoly 11 | Post-badge town and NPCs |

- Optional extras (the Carnrudh wrestler, the school's Hard Stone) are left for you to do.
- For anything else, the debug menu (R+Start) sets flags and vars. The values are in `include/constants/vars.h` (`BALWYN_STATE_*`, `CARNRUDH_STATE_*`) and the flag IDs in `include/constants/flags.h`.
- Adding a scenario: see `tools/playtest/README.md`.
