"""Generate data/layouts/Carnrudh/map.bin + border.bin (32x30, General + Dewford).

    python3 tools/kernia/gen_carnrudh.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost. Block IDs are
copied from vanilla maps; see design/Carnrudh.md for the building positions.
"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gbarender import Tileset, render_blocks

LAYOUT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'data', 'layouts', 'Carnrudh')

W, H = 32, 30
ROAD_Y = 12  # Main street rows 12-13; Route 1's road is rows 11-12, so the connection offset is 1.


def B(mid, coll, elev):
    return mid | (coll << 10) | (elev << 12)


GRASS = B(0x001, 0, 3)
FLOWER = B(0x004, 0, 3)
SIGN = B(0x003, 1, 0)

m = [[GRASS] * W for _ in range(H)]
tree = [[False] * W for _ in range(H)]


def trees(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            tree[y][x] = True


def stamp(x0, y0, rows):
    for dy, row in enumerate(rows):
        for dx, v in enumerate(row):
            if v is not None:
                m[y0 + dy][x0 + dx] = v
                tree[y0 + dy][x0 + dx] = False


# Tree masses (2x2 trees: top rows even, bottom rows odd, left columns even, matching Route 1's phase).
trees(0, 0, 31, 3)      # North band.
trees(0, 4, 3, 9)       # West strip above the road, as on Route 1's east end.
trees(0, 14, 3, 29)     # West strip below the road.
trees(28, 0, 31, 29)    # East band; the east road is reserved here for later.
trees(4, 26, 27, 29)    # South band.

# Roads.
for x in range(0, 28):
    tree[ROAD_Y][x] = tree[ROAD_Y + 1][x] = False


def hroad(x0, x1, y):
    for x in range(x0, x1 + 1):
        top = 0x118 if x == x0 and x0 > 0 else (0x11A if x == x1 else 0x119)
        bot = 0x128 if x == x0 and x0 > 0 else (0x12A if x == x1 else 0x129)
        m[y][x] = B(top, 0, 3); m[y + 1][x] = B(bot, 0, 3)


def vroad(x, y0, y1):
    for y in range(y0, y1 + 1):
        tree[y][x] = tree[y][x + 1] = False
        m[y][x] = B(0x120, 0, 3); m[y][x + 1] = B(0x122, 0, 3)


hroad(0, 27, ROAD_Y)
vroad(14, 0, ROAD_Y - 1)          # North to Carn Kowr (phase 2 connects it).
m[ROAD_Y][14] = m[ROAD_Y][15] = B(0x121, 0, 3)
vroad(6, ROAD_Y + 2, H - 1)       # South-west route, reserved.
m[ROAD_Y + 1][6] = m[ROAD_Y + 1][7] = B(0x121, 0, 3)

# Buildings: (x, y) is the top-left block; doors noted for map.json.
PC = [[B(0x048, 0, 3), B(0x049, 0, 3), B(0x04A, 0, 3), B(0x04B, 0, 3)],
      [B(0x050 + i, 1, 0) for i in range(4)],
      [B(0x058 + i, 1, 0) for i in range(4)],
      [B(0x060 + i, 1, 0) for i in range(4)]]
MART = [[B(0x028, 0, 3), B(0x029, 0, 3), B(0x029, 0, 3), B(0x02B, 0, 3)],
        [B(0x030 + i, 1, 0) for i in range(4)],
        [B(0x038 + i, 1, 0) for i in range(4)],
        [B(0x060, 1, 0), B(0x041, 1, 0), B(0x042, 1, 0), B(0x043, 1, 0)]]
GYM = [[B(v, 0, 3) for v in (0x21A, 0x21B, 0x21B, 0x21B, 0x21B, 0x21C)],
       [B(v, 1, 0) for v in (0x222, 0x223, 0x223, 0x223, 0x223, 0x224)],
       [B(v, 1, 0) for v in (0x22B, 0x22C, 0x22D, 0x1B3, 0x22E, 0x22F)],
       [B(v, 1, 0) for v in (0x233, 0x234, 0x235, 0x1C5, 0x236, 0x237)],
       [B(0x23B, 0, 3), B(0x23C, 0, 3), B(0x23D, 1, 0), B(0x1CD, 1, 0), B(0x23E, 1, 0), B(0x23F, 0, 3)]]
HOUSE = [[B(v, 0, 3) for v in (0x20B, 0x20C, 0x20C, 0x20D)],
         [B(v, 1, 0) for v in (0x213, 0x214, 0x214, 0x215)],
         [B(v, 1, 0) for v in (0x20E, 0x21D, 0x21E, 0x20F)],
         [B(v, 1, 0) for v in (0x216, 0x225, 0x226, 0x217)]]
WIDE_HOUSE = [[B(v, 0, 3) for v in (0x20B, 0x20C, 0x20C, 0x20C, 0x20D)],
              [B(v, 1, 0) for v in (0x213, 0x214, 0x214, 0x214, 0x215)],
              [B(v, 1, 0) for v in (0x20E, 0x21F, 0x21D, 0x21E, 0x20F)],
              [B(v, 1, 0) for v in (0x216, 0x227, 0x225, 0x226, 0x217)]]
COTTAGE = [[B(v, 0, 3) for v in (0x008, 0x009, 0x009, 0x00A)],
           [B(v, 1, 0) for v in (0x010, 0x011, 0x011, 0x012)],
           [B(v, 1, 0) for v in (0x018, 0x019, 0x00B, 0x01A)],
           [B(v, 1, 0) for v in (0x020, 0x021, 0x013, 0x022)]]

DOORS = {}
def building(name, rows, x, y, door_dx):
    stamp(x, y, rows)
    DOORS[name] = (x + door_dx, y + len(rows) - 1)

building('gym', GYM, 5, 5, 3)
building('pokemon_center', PC, 18, 7, 1)
building('mart', MART, 23, 7, 1)
building('house1', HOUSE, 9, 16, 1)
building('pasty_shop', COTTAGE, 16, 16, 1)
building('school', WIDE_HOUSE, 21, 16, 2)
building('house2', HOUSE, 9, 21, 1)

# Signs: town sign by the west entrance, gym sign beside its door.
SIGNS = {'town': (4, 11), 'gym': (11, 9)}
for (x, y) in SIGNS.values():
    m[y][x] = SIGN

for (x, y) in [(5, 4), (13, 10), (17, 11), (22, 11), (20, 14), (26, 21), (5, 18), (13, 24), (19, 23)]:
    if m[y][x] == GRASS and not tree[y][x]:
        m[y][x] = FLOWER

# Resolve tree masses into vanilla edge tiles.
for y in range(H):
    for x in range(W):
        if not tree[y][x]:
            continue
        left = x % 2 == 0
        if y % 2 == 0:
            v = 0x1D4 if left else 0x1D5
        else:
            below_open = y + 1 < H and not tree[y + 1][x]
            v = (0x1E4 if left else 0x1E5) if below_open else (0x1DC if left else 0x1DD)
        m[y][x] = B(v, 1, 0)
# Crown tips on open grass directly above a tree mass's top row.
for y in range(H - 1):
    for x in range(W):
        if tree[y + 1][x] and not tree[y][x] and m[y][x] in (GRASS, FLOWER) and (y + 1) % 2 == 0:
            m[y][x] = B(0x1CE if x % 2 == 0 else 0x1CF, 0, 3)

if __name__ == '__main__':
    data = b''.join(struct.pack('<H', v) for row in m for v in row)
    border = struct.pack('<4H', B(0x1D4, 1, 0), B(0x1D5, 1, 0), B(0x1DC, 1, 0), B(0x1DD, 1, 0))
    open(os.path.join(LAYOUT_DIR, 'map.bin'), 'wb').write(data)
    open(os.path.join(LAYOUT_DIR, 'border.bin'), 'wb').write(border)
    print('doors', DOORS, 'signs', SIGNS)
    if len(sys.argv) > 1:
        render_blocks(Tileset('general', 'dewford'), [[v & 0x3FF for v in row] for row in m], sys.argv[1])
