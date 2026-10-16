"""Generate data/layouts/KerniaRoute2/map.bin + border.bin (40x52, General + Dewford).

    python3 tools/kernia/gen_kernia_route2.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost: copy them back in here.
The landform is copied from Mossdeep City's hill, whose cliffs step down in terraces and in
layers down its east coast to the sea; the bay and the rest are built from vanilla blocks around
it. The lighthouse is added to the Dewford tileset by tools/kernia/add_lighthouse_tiles.py.
See design/Route2.md for the layout.
"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layoutlib import *

W, H = 40, 52
ROAD_X = 10  # Carnrudh's south-west road is x 6-7, so the connection offset is -4.

WATER = B(0x170, 0, 1)
BOULDER = B(0x0E2, 1, 0)
SEA_ROCK = [[B(0x150, 1, 0), B(0x151, 1, 0)], [B(0x158, 1, 0), B(0x159, 1, 0)]]
LIGHTHOUSE = [[B(0x37C + y * 3 + x, 1, 0) for x in range(3)] for y in range(6)]  # 3 wide, 6 tall.

L = Layout(W, H)

# The landform: Mossdeep City's hill (x 40-79, rows 4-39) becomes rows 2-37. Its cliffs step down
# in terraces on every side, in layers down the east coast into the sea, with steps between the
# levels. Mossdeep's real elevations are kept, renumbered so the plateau you enter on is 3 like
# Carnrudh: the game then only lets the player between levels by the steps. Mossdeep's town
# (buildings, trees, signs, sand paths, its shallows) becomes grass at the level around it.
SRC_X, SRC_Y, DST_Y = 40, 4, 2
MOSSDEEP = os.path.join(REPO, 'data', 'layouts', 'MossdeepCity', 'map.bin')
LEVELS = {7: 3, 9: 5, 5: 7, 3: 9, 4: 3, 0: 0}   # Mossdeep elevation -> Route 2 elevation.
SUMMIT = 5


def is_town(mid):
    return mid >= 0x200 or mid == 0x003 or 0x118 <= mid <= 0x12A or 0x0F0 <= mid <= 0x0F7


def walkable(v):
    return (v >> 10) & 3 == 0 and v >> 12 != 1


d = open(MOSSDEEP, 'rb').read()
unknown = set()
for y in range(DST_Y, DST_Y + 36):
    for x in range(W):
        v = struct.unpack_from('<H', d, ((SRC_Y + y - DST_Y) * 80 + SRC_X + x) * 2)[0]
        mid, coll, elev = v & 0x3FF, (v >> 10) & 3, v >> 12
        if is_town(mid) or (y < DST_Y + 3 and x < 12 and elev == 1):
            unknown.add((x, y))       # Grass, at the level of the ground around it (below).
        elif elev == 1:
            L.m[y][x] = v             # Sea and its edges.
        elif coll == 0:
            L.m[y][x] = B(mid, 0, LEVELS[elev])
        else:
            L.m[y][x] = v             # Cliffs.
while unknown:
    for (x, y) in sorted(unknown):
        near = [L.m[ny][nx] >> 12 for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
                if 0 <= nx < W and DST_Y <= ny < DST_Y + 36 and (nx, ny) not in unknown
                and walkable(L.m[ny][nx]) and L.m[ny][nx] >> 12 != 0]
        if near:
            L.m[y][x] = B(0x001, 0, max(set(near), key=near.count))
            unknown.discard((x, y))
            break
    else:
        for (x, y) in unknown:        # Walled in by cliffs: unreachable, so any level will do.
            L.m[y][x] = GRASS
        break

# Trees: the north band continuing Carnrudh's south band (the road cuts through), and the moor
# along the west edge. Beyond x 11 the top rows are sea, as they were above Mossdeep's north shore.
L.trees(0, 0, 11, 1)
L.trees(0, 2, 1, H - 1)
L.fill(12, 0, W - 1, 1, WATER)
L.m[0][12] = B(0x190, 0, 1)

# Mossdeep's north shore, tidied: its water corners by the road become grass, the summit ends at
# row 4 with the sea above it (where Mossdeep's rocket stood), and both shores get their edges.
for (x, y) in [(2, 2), (6, 2), (7, 2), (5, 4)]:
    L.m[y][x] = GRASS
L.fill(19, 2, 29, 3, WATER)
for x in range(12, 19):
    L.m[2][x] = B(0x002, 0, 3)
for x in range(19, 30):
    if walkable(L.m[4][x]):
        L.m[4][x] = B(0x002, 0, SUMMIT)

# The road in from Carnrudh, ending in a cap where the path turns to grass.
L.vroad(ROAD_X, 0, 3)
L.stamp(ROAD_X, 4, [[B(0x128, 0, 3), B(0x12A, 0, 3)]])

# The bay: below the lowest terrace's cliff (row 34), a sand beach replaces Mossdeep's shallows,
# with steps down through the cliff. The sea is to the east and south. The beach is on level 3,
# not the lowest terrace's 7: the game only lets the player fish (and later surf) from level 3,
# so its steps are level 0 to join the two.
LOW = 7
BAY = 3
SAND = B(0x124, 0, BAY)
BAY_TOP, BAY_Y1, BAY_X1 = 35, 42, 30        # Sand rows 35-41, x 0-29; edges on row 42 and x 30.
for y in range(33, BAY_TOP):                # Mossdeep's shallows above the beach become grass.
    for x in range(2, 9):
        if L.m[y][x] & 0x3FF in (0x19E, 0x1A4, 0x1BE, 0x1BF, 0x166, 0x16E) or walkable(L.m[y][x]):
            L.m[y][x] = B(0x001, 0, BAY if y == 34 else LOW)
L.m[34][8] = B(0x078, 1, 0)                 # The cliff's left end, now on land.
L.m[34][24] = B(0x07A, 1, 0)                # Its right end, above the beach.
L.stamp(14, 34, [[B(0x0AF, 0, 0), B(0x0CF, 0, 0)]])
L.fill(0, BAY_TOP, W - 1, H - 1, WATER)
L.trees(0, BAY_TOP, 1, H - 1, False)        # The moor stops at the shore: the beach runs to the edge.
L.fill(0, BAY_TOP, BAY_X1 - 1, BAY_Y1 - 1, SAND)
L.fill(25, BAY_TOP, BAY_X1 - 1, BAY_TOP, B(0x11C, 0, BAY))   # Sea above, east of the cliff.
L.stamp(BAY_X1, BAY_TOP, [[B(0x11D, 0, 1)]])
L.fill(BAY_X1, BAY_TOP + 1, BAY_X1, BAY_Y1 - 1, B(0x125, 0, 1))
L.fill(0, BAY_Y1, BAY_X1 - 1, BAY_Y1, B(0x12C, 0, 1))
L.stamp(BAY_X1, BAY_Y1, [[B(0x12D, 0, 1)]])
for (x, y) in [(6, 37), (7, 37), (19, 39), (26, 38)]:
    L.m[y][x] = BOULDER
for (x, y) in [(5, 45), (16, 46), (27, 44)]:
    L.stamp(x, y, SEA_ROCK)

# The lighthouse and the keeper's cottage on the summit, looking out over the coast.
LIGHTHOUSE_XY = (25, 5)                     # x 25-27, rows 5-10; its door is (26, 10).
L.stamp(*LIGHTHOUSE_XY, LIGHTHOUSE)
COTTAGE_XY = (19, 7)                        # Rows 7-10, door at (20, 10).
L.stamp(*COTTAGE_XY, [[v if (v >> 10) & 3 else (v & 0x3FF) | (SUMMIT << 12) for v in row] for row in COTTAGE])

# Shorelines from the hand tidy-up in Porymap: the sea's top row meets Carnrudh's land above it,
# and the east column meets the land beyond the map's edge.
L.fill(13, 0, W - 2, 0, B(0x189, 0, 1))
L.m[0][12], L.m[0][W - 1] = B(0x188, 0, 1), B(0x18A, 0, 1)
for (x, y) in [(12, 1), (19, 2), (19, 3)]:
    L.m[y][x] = B(0x190, 0, 1)
L.fill(W - 1, 1, W - 1, 10, B(0x192, 0, 1))

# The rest of the hand tidy-up: cliff edges by the road, the summit's west corner, the west cliff
# at x 2, the cliff foot at row 20, steps down to the bay at x 5-6, and the rock islet cleared.
HAND_EDITS = {
    (7, 2): B(0x068, 1, 0),
    (8, 2): B(0x002, 0, 3),
    (9, 2): B(0x002, 0, 3),
    (6, 4): B(0x068, 1, 0),
    (17, 4): B(0x068, 1, 0),
    (18, 4): B(0x002, 0, 5),
    (17, 5): B(0x070, 1, 0),
    (16, 6): B(0x002, 0, 5),
    (17, 6): B(0x070, 1, 0),
    (18, 6): B(0x001, 0, 5),
    (2, 10): B(0x073, 1, 0),
    (2, 11): B(0x073, 1, 0),
    (2, 12): B(0x073, 1, 0),
    (2, 13): B(0x073, 1, 0),
    (2, 14): B(0x073, 1, 0),
    (26, 20): B(0x091, 1, 0),
    (27, 20): B(0x091, 1, 0),
    (28, 20): B(0x091, 1, 0),
    (29, 20): B(0x091, 1, 0),
    (2, 33): B(0x078, 1, 0),
    (5, 33): B(0x0AF, 0, 0),
    (6, 33): B(0x0CF, 0, 0),
    (0, 34): B(0x001, 0, 3),    # The moor stops a row short of the beach.
    (1, 34): B(0x001, 0, 3),
    (35, 33): WATER,            # The last of Mossdeep's rock islet, cleared.
    (36, 33): WATER,
    (34, 34): WATER,
    (35, 34): WATER,
    (36, 34): WATER,
    (3, 29): B(0x001, 0, 7),    # The nook behind the Rock Smash rock, plain grass under its item.
}
for (x, y), v in HAND_EDITS.items():
    L.stamp(x, y, [[v]])           # Stamping also clears any tree there.

# Tall grass on the way down: the entry plateau, the middle terraces below the summit's steps,
# and the lower terraces above the bay's steps. Only open grass and flowers turn into tall grass,
# each at its own cell's level, so cliff edges and the terraces' levels stay as they are.
TALL_GRASS_PATCHES = [(4, 10, 8, 15), (26, 22, 30, 25), (4, 30, 9, 32)]   # x 3 is the Rock Smash rock's way in.
for (x0, y0, x1, y1) in TALL_GRASS_PATCHES:
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            v = L.m[y][x]
            if v & 0x3FF in (0x001, 0x004) and walkable(v):
                L.m[y][x] = (TALL_GRASS & 0xFFF) | (v & 0xF000)

SIGNS = {'route': (8, 3), 'lighthouse': (24, 10), 'porthliw': (12, 35)}   # The last points west along the beach.
for (x, y) in SIGNS.values():
    L.m[y][x] = SIGN

if __name__ == '__main__':
    L.save('KerniaRoute2', sys.argv[1] if len(sys.argv) > 1 else None)
    print('signs', SIGNS)
