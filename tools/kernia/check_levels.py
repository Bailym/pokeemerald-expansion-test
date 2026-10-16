"""Check a layout's elevation levels and its map's object elevations.

    python3 tools/kernia/check_levels.py KerniaRoute2 entry=10,0 summit=22,12 bay=10,38

Flood fills the walkable land (not water) as the game moves the player: between cells of the
same level, or to and from level 0 (steps). With level-0 cells blocked, each named point must
be in a region of its own, so the steps are the only way between them; with them open, every
named point must be reachable from the first. Also checks that every object event in the
map's map.json stands on walkable land at its own elevation.
"""
import json, os, struct, sys

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')


def load(name):
    layouts = json.load(open(os.path.join(REPO, 'data', 'layouts', 'layouts.json')))['layouts']
    lay = next(l for l in layouts if l.get('name') == name + '_Layout')
    d = open(os.path.join(REPO, lay['blockdata_filepath']), 'rb').read()
    w, h = lay['width'], lay['height']
    return w, h, [[struct.unpack_from('<H', d, (y * w + x) * 2)[0] for x in range(w)] for y in range(h)]


def regions(w, h, m, steps_open):
    def land(x, y):
        v = m[y][x]
        return (v >> 10) & 3 == 0 and v >> 12 != 1 and (steps_open or v >> 12 != 0)

    region, n = {}, 0
    for y0 in range(h):
        for x0 in range(w):
            if (x0, y0) in region or not land(x0, y0):
                continue
            n += 1
            region[(x0, y0)] = n
            todo = [(x0, y0)]
            while todo:
                x, y = todo.pop()
                e = m[y][x] >> 12
                for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
                    if 0 <= nx < w and 0 <= ny < h and (nx, ny) not in region and land(nx, ny):
                        ne = m[ny][nx] >> 12
                        if ne == e or ne == 0 or e == 0:
                            region[(nx, ny)] = n
                            todo.append((nx, ny))
    return region


def main():
    name, points = sys.argv[1], {}
    for arg in sys.argv[2:]:
        label, xy = arg.split('=')
        points[label] = tuple(int(c) for c in xy.split(','))
    w, h, m = load(name)
    ok = True

    closed = regions(w, h, m, False)
    seen = {}
    for label, xy in points.items():
        r = closed.get(xy)
        if r is None:
            print('FAIL: %s %s is not walkable land' % (label, xy))
            ok = False
        elif r in seen.values():
            other = next(k for k, v in seen.items() if v == r)
            print('FAIL: %s and %s are joined without steps' % (other, label))
            ok = False
        seen[label] = r

    opened = regions(w, h, m, True)
    first = next(iter(points), None)
    for label, xy in points.items():
        if first and opened.get(xy) != opened.get(points[first]):
            print('FAIL: %s %s cannot be reached from %s' % (label, xy, first))
            ok = False

    levels = {m[y][x] >> 12 for y in range(h) for x in range(w) if (m[y][x] >> 10) & 3 == 0}
    print('walkable levels:', sorted(levels))

    map_json = os.path.join(REPO, 'data', 'maps', name, 'map.json')
    if os.path.exists(map_json):
        for obj in json.load(open(map_json)).get('object_events', []):
            x, y, e = obj['x'], obj['y'], obj['elevation']
            v = m[y][x]
            what = '%s at (%d, %d)' % (obj.get('local_id') or obj['graphics_id'], x, y)
            if v >> 12 == 1 and (v >> 10) & 3 == 0:
                continue    # On water: a swimmer or a Pokémon in the sea, any level is fine.
            if (v >> 10) & 3:
                print('note: %s stands on a solid cell' % what)
            elif v >> 12 != e:
                print('FAIL: %s has elevation %d, but its cell is level %d' % (what, e, v >> 12))
                ok = False

    print('OK' if ok else 'FAILED')
    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
