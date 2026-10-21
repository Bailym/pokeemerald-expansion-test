"""Generate design/Pokedex.md: every Pokémon the player can meet in Kernia, from the game's data.

    python3 tools/kernia/gen_pokedex.py

Kernia's maps are the ones in its map groups (data/maps/map_groups.json). For those maps it reads:
  - wild encounters (src/data/wild_encounters.json), with each species' chance per method;
  - gifts (givemon) and one-off wild battles (setwildbattle) in their scripts;
  - the parties of the trainers they reference (src/data/trainers.party);
  - species named in their dialogue and signs, or played by a cry or picture.
Species that can be caught or given also bring in what they evolve into. Re-run it after changing
any of these, and commit the result with the change.
"""
import glob, json, os, re

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
OUT = os.path.join(REPO, 'design', 'Pokedex.md')

KERNIA_GROUPS = ['gMapGroup_KerniaTownsAndRoutes', 'gMapGroup_IndoorBalwyn', 'gMapGroup_IndoorCarnrudh',
                 'gMapGroup_IndoorKerniaRoute2', 'gMapGroup_IndoorPorthliw']
# How the player meets a species, best first. A species is listed under the best one it has.
STATUSES = ['Catchable', 'Gift', 'Evolution', "Trainer's", 'Mentioned']
METHOD_NAMES = {'land_mons': 'Grass', 'water_mons': 'Surfing', 'rock_smash_mons': 'Rock Smash',
                'old_rod': 'Old Rod', 'good_rod': 'Good Rod', 'super_rod': 'Super Rod'}
# Species names that are also everyday words, so a match in dialogue isn't a mention.
NOT_MENTIONS = set()


def read(path):
    return open(os.path.join(REPO, path), encoding='utf-8').read()


def map_label(name):
    """'KerniaRoute2_KeepersCottage' -> 'Route 2: Keepers Cottage'."""
    parts = name.replace('Kernia', '').split('_')
    words = [re.sub(r'(?<=[a-z])(?=[A-Z0-9])', ' ', p) for p in parts]
    words[0] = re.sub(r'Route(\d)', r'Route \1', words[0].replace('Route ', 'Route'))
    label = words[0] + (': ' + ' '.join(words[1:]) if len(words) > 1 else '')
    return re.sub(r'\b(Player|Keeper|Fisherman|Huer)s\b', r"\1's", label)


def load_species():
    """SPECIES_X -> {name, types, dex, evolutions: [(method, target)]}, plus the national dex order."""
    dex_order = re.findall(r'^\s*(NATIONAL_DEX_[A-Z0-9_]+)', read('include/constants/pokedex.h'), re.M)
    dex_num = {d: i for i, d in enumerate(dex_order)}
    species = {}
    paths = sorted(glob.glob(os.path.join(REPO, 'src/data/pokemon/species_info/gen_*_families.h')))
    # Some families' types are macros on a config, e.g. (P_UPDATED_TYPES >= GEN_2 ? TYPE_STEEL : TYPE_ELECTRIC).
    # The configs default to the latest generation, so take the first type.
    type_macros = {}
    for path in paths:
        for d in re.finditer(r'^#define (\w+) \(.*?\? (TYPE_\w+) :', open(path, encoding='utf-8').read(), re.M):
            type_macros[d.group(1)] = d.group(2)
    for path in paths:
        src = open(path, encoding='utf-8').read()
        for m in re.finditer(r'^    \[(SPECIES_[A-Z0-9_]+)\] =\n    \{\n(.*?)^    \},', src, re.M | re.S):
            body = m.group(2)
            name = re.search(r'\.speciesName = _\("(.*?)"\)', body)
            types = re.search(r'\.types = MON_TYPES\((.*?)\)', body)
            dex = re.search(r'\.natDexNum = (NATIONAL_DEX_[A-Z0-9_]+)', body)
            evos = []
            e = body.find('.evolutions = EVOLUTION(')
            if e >= 0:
                depth, i = 0, e + len('.evolutions = EVOLUTION')
                for j in range(i, len(body)):
                    depth += {'(': 1, ')': -1}.get(body[j], 0)
                    if depth == 0:
                        break
                for ev in re.finditer(r'\{(EVO_[A-Z_]+), ([^,]+), (SPECIES_[A-Z0-9_]+)(, CONDITIONS)?', body[i:j]):
                    evos.append((evo_method(ev.group(1), ev.group(2).strip(), bool(ev.group(4))), ev.group(3)))
            if name and m.group(1) not in species:
                species[m.group(1)] = {
                    'name': name.group(1),
                    'types': [type_macros.get(t, t).replace('TYPE_', '').title() for t in (types.group(1).split(', ') if types else [])],
                    'dex': dex_num.get(dex.group(1)) if dex else None,
                    'evolutions': evos,
                }
    for s in species.values():
        s['types'] = list(dict.fromkeys(s['types']))
    return species


def evo_method(kind, param, conditional):
    if kind == 'EVO_LEVEL':
        text = f'Lv{param}'
    elif kind == 'EVO_ITEM':
        text = param.replace('ITEM_', '').replace('_', ' ').title()
    elif kind == 'EVO_TRADE':
        text = 'Trade'
    else:
        text = kind.replace('EVO_', '').replace('_', ' ').lower()
    return text + (' (conditions)' if conditional else '')


def kernia_maps():
    groups = json.loads(read('data/maps/map_groups.json'))
    return [m for g in KERNIA_GROUPS for m in groups[g]]


def map_constant(name):
    return json.loads(read(f'data/maps/{name}/map.json'))['id']


def wild(maps):
    """[(map, method, species, min, max, chance %)] for Kernia's maps."""
    data = json.loads(read('src/data/wild_encounters.json'))
    group = next(g for g in data['wild_encounter_groups'] if g['label'] == 'gWildMonHeaders')
    fields = {f['type']: f for f in group['fields']}
    by_const = {map_constant(m): m for m in maps}
    rows = []
    for enc in group['encounters']:
        name = by_const.get(enc.get('map'))
        if not name:
            continue
        for kind, info in enc.items():
            if not kind.endswith('_mons'):
                continue
            rates = fields[kind]['encounter_rates']
            slot_groups = fields[kind].get('groups') or {kind: list(range(len(rates)))}
            for method, slots in slot_groups.items():
                total = sum(rates[s] for s in slots)
                merged = {}
                for s in slots:
                    mon = info['mons'][s]
                    key = mon['species']
                    lo, hi, pct = merged.get(key, (mon['min_level'], mon['max_level'], 0))
                    merged[key] = (min(lo, mon['min_level']), max(hi, mon['max_level']), pct + 100 * rates[s] / total)
                for sp, (lo, hi, pct) in merged.items():
                    rows.append((name, METHOD_NAMES.get(method, method), sp, lo, hi, pct))
    return rows


def scripted(maps):
    """Gifts and one-off wild battles: [(map, 'Gift' | 'One-off battle', species, level)]."""
    rows = []
    for m in maps:
        src = read(f'data/maps/{m}/scripts.inc')
        for kind, label in (('givemon', 'Gift'), ('setwildbattle', 'One-off battle')):
            for g in re.finditer(rf'^\t{kind} (SPECIES_[A-Z0-9_]+), (\d+)', src, re.M):
                rows.append((m, label, g.group(1), int(g.group(2))))
    return rows


def trainers(maps, by_name):
    """[(map, trainer name, species, level, trainer)] for the trainers Kernia's maps reference."""
    used = {}
    for m in maps:
        text = read(f'data/maps/{m}/scripts.inc') + read(f'data/maps/{m}/map.json')
        for t in re.findall(r'\b(TRAINER_[A-Z0-9_]+)\b', text):
            if not re.match(r'TRAINER_(TYPE|PIC|BACK)_', t):
                used.setdefault(t, m)
    rows = []
    for block in re.split(r'^(?==== TRAINER_)', read('src/data/trainers.party'), flags=re.M):
        head = re.match(r'=== (TRAINER_[A-Z0-9_]+) ===', block)
        if not head or head.group(1) not in used:
            continue
        name = re.search(r'^Name: (.*)$', block, re.M).group(1).strip()
        mons = block.split('\n\n')[1:]
        for mon in mons:
            first = mon.strip().split('\n')[0]
            if not first:
                continue
            nick = re.search(r'\(([^)]+)\)', first.split(' @')[0])
            sp_name = (nick.group(1) if nick else first.split(' @')[0]).strip()
            level = re.search(r'^Level: (\d+)', mon, re.M)
            sp = by_name.get(sp_name.lower())
            if sp:
                rows.append((used[head.group(1)], name.title(), sp, int(level.group(1)) if level else None, head.group(1)))
    return rows


def mentions(maps, by_name):
    """[(map, species)] for species named in dialogue or signs, or shown by a cry or picture."""
    rows = []
    names = sorted((n for n in by_name if n not in NOT_MENTIONS and len(n) > 2), key=len, reverse=True)
    pattern = re.compile(r'\b(' + '|'.join(re.escape(n) for n in names) + r')\b', re.I)
    for m in maps:
        src = read(f'data/maps/{m}/scripts.inc')
        text = ' '.join(re.findall(r'\.string "(.*)"', src)).replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' ')
        found = {by_name[x.lower()] for x in pattern.findall(text)}
        found |= set(re.findall(r'(?:playmoncry|showmonpic) (SPECIES_[A-Z0-9_]+)', src))
        rows += [(m, sp) for sp in sorted(found)]
    return rows


def main():
    species = load_species()
    by_name = {}
    for k, s in species.items():
        by_name.setdefault(s['name'].lower(), k)
    maps = kernia_maps()
    outdoor = json.loads(read('data/maps/map_groups.json'))[KERNIA_GROUPS[0]]
    order = {m: next((i for i, o in reversed(list(enumerate(outdoor))) if m == o or m.startswith(o + '_')), len(outdoor))
             for m in maps}
    maps.sort(key=lambda m: (order[m], m not in outdoor))
    w, s, t, n = wild(maps), scripted(maps), trainers(maps, by_name), mentions(maps, by_name)

    # Each species' best status, and where the player first meets it (for the Kernia dex order).
    best, first, where = {}, {}, {}

    def note(sp, status, m, text):
        if sp not in species:
            return
        if sp not in best or STATUSES.index(status) < STATUSES.index(best[sp]):
            best[sp] = status
        first[sp] = min(first.get(sp, len(maps)), order.get(m, len(maps)))
        where.setdefault(sp, {}).setdefault(status, []).append(text)

    for m, method, sp, lo, hi, pct in w:
        note(sp, 'Catchable', m, f'{map_label(m)} ({method})')
    for m, kind, sp, lv in s:
        note(sp, 'Catchable' if kind == 'One-off battle' else 'Gift', m, f'{map_label(m)} ({kind.lower()}, Lv{lv})')
    for m, tname, sp, lv, _ in t:
        note(sp, "Trainer's", m, f'{tname} ({map_label(m)})')
    for m, sp in n:
        note(sp, 'Mentioned', m, map_label(m))
    # Evolutions of anything the player can own, through whole chains.
    owned = [sp for sp, st in best.items() if st in ('Catchable', 'Gift')]
    while owned:
        sp = owned.pop()
        for method, target in species[sp]['evolutions']:
            if target in species and best.get(target) not in ('Catchable', 'Gift', 'Evolution'):
                note(target, 'Evolution', None, f'{species[sp]["name"]} ({method})')
                first[target] = min(first[target], first[sp])
                owned.append(target)

    ranked = sorted(best, key=lambda sp: (first[sp], STATUSES.index(best[sp]), species[sp]['dex'] or 0))
    out = ['# Kernia Pokédex', '',
           '> Generated by `tools/kernia/gen_pokedex.py` from the game data. Don\'t edit it by hand: change the data, then re-run the script.', '',
           'Every Pokémon the player can meet in Kernia so far, in the order they first turn up. **Catchable** means wild, '
           'including one-off battles. **Gift** means given. **Evolution** means it evolves from something catchable or given. '
           '**Trainer\'s** means only seen in a Kernia trainer\'s team. **Mentioned** means only named in dialogue or a sign, or heard as a cry.', '']
    counts = {st: sum(1 for sp in best if best[sp] == st) for st in STATUSES}
    out.append(f'**{len(best)} species**: ' + ', '.join(f'{counts[st]} {st.lower()}' for st in STATUSES) + '.')
    out += ['', '## Pokédex', '', '| # | Pokémon | Type | Status | Where |', '|---|---|---|---|---|']
    for i, sp in enumerate(ranked, 1):
        info = species[sp]
        places = '; '.join(dict.fromkeys(where[sp][best[sp]]))
        out.append(f'| {i} | {info["name"]} | {"/".join(info["types"])} | {best[sp]} | {places} |')

    out += ['', '## By location', '']
    for m in maps:
        rows = [r for r in w if r[0] == m]
        extra = [r for r in s if r[0] == m]
        if not rows and not extra:
            continue
        out += [f'### {map_label(m)}', '', '| Method | Pokémon | Levels | Chance |', '|---|---|---|---|']
        for _, method, sp, lo, hi, pct in sorted(rows, key=lambda r: (list(METHOD_NAMES.values()).index(r[1]), -r[5])):
            lv = f'{lo}' if lo == hi else f'{lo}–{hi}'
            out.append(f'| {method} | {species[sp]["name"]} | {lv} | {pct:g}% |')
        for _, kind, sp, lv in extra:
            out.append(f'| {kind} | {species[sp]["name"]} | {lv} | — |')
        out.append('')

    out += ["## Trainers' Pokémon", '', '| Trainer | Where | Team |', '|---|---|---|']
    teams = {}
    # Keyed by trainer constant, since several trainers can share a name (Carn Kowr's grunts).
    for m, tname, sp, lv, tid in t:
        teams.setdefault((order[m], m, tid, tname), []).append(f'{species[sp]["name"]} {lv}')
    for (_, m, _, tname), team in sorted(teams.items()):
        out.append(f'| {tname} | {map_label(m)} | {", ".join(team)} |')
    out.append('')
    open(OUT, 'w', encoding='utf-8').write('\n'.join(out))
    print(f'{len(best)} species ->', os.path.relpath(OUT, REPO))


if __name__ == '__main__':
    main()
