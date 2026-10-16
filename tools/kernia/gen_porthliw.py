"""Generate data/layouts/Porthliw/map.bin + border.bin (44x46, General + Dewford).

    python3 tools/kernia/gen_porthliw.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost: copy them back in here.
A harbour bowl, after St Ives: the harbour basin opens to the sea at the bottom, and a paved
street runs along its top behind a kerbed harbour wall, with the Center, Mart, and gallery facing
the water. The town climbs two terraces behind it to the gym at the back, and Route 2's beach
comes in from the east. The paving, kerbs, bollards, and boats are Slateport's, copied into
Dewford by tools/kernia/add_harbour_tiles.py. See design/Porthliw.md for the layout.
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layoutlib import *
from add_harbour_tiles import HARBOUR

W, H = 44, 46
# Route 2's beach is its rows 35-41; here it's rows 29-35, so Route 2's row 0 is our row -6.
ROUTE2_OFFSET = -6
BEACH_TOP, BEACH_BOTTOM = 29, 35
SEA_Y = BEACH_BOTTOM + 1

WATER = B(0x170, 0, 1)
SAND = B(0x124, 0, 3)
PAVING = B(HARBOUR['PAVING'], 0, 3)
def kerb(side):
    return B(HARBOUR['KERB_' + side], 1, 0)

L = Layout(W, H)

# The harbourfront: grass behind the buildings, the paved street, the paved headland west of the
# basin, the basin, the beach to the east, and the sea.
STREET_Y0, STREET_Y1 = 26, 28        # The street's rows; its last row is the harbour wall.
STREET_X1 = 32                       # The street's east end, where it meets the beach.
HEAD_X0, HEAD_X1 = 2, 11             # The paved headland west of the basin.
BASIN_X0, BASIN_X1 = 12, 30          # The basin's water, from the street down to the sea.
L.fill(0, STREET_Y0, W - 1, BEACH_BOTTOM, SAND)
L.fill(HEAD_X0, STREET_Y0, STREET_X1, STREET_Y1, PAVING)
L.fill(HEAD_X0, STREET_Y1 + 1, HEAD_X1, BEACH_BOTTOM, PAVING)
L.fill(BASIN_X0, STREET_Y1 + 1, BASIN_X1, BEACH_BOTTOM, WATER)
L.fill(0, SEA_Y, W - 1, H - 1, WATER)

# The harbour wall: a kerb wherever the paving drops to the water.
L.fill(BASIN_X0, STREET_Y1, BASIN_X1, STREET_Y1, kerb('S'))
L.fill(HEAD_X1, STREET_Y1 + 1, HEAD_X1, BEACH_BOTTOM - 1, kerb('E'))
L.fill(HEAD_X0, BEACH_BOTTOM, HEAD_X1 - 1, BEACH_BOTTOM, kerb('S'))
L.m[BEACH_BOTTOM][HEAD_X1] = kerb('SE')

# The water's own edges: the shore below the paving, and Route 106's sand frame by the beach.
L.fill(BASIN_X0 + 1, STREET_Y1 + 1, BASIN_X1 - 1, STREET_Y1 + 1, B(0x189, 0, 1))   # Land above.
L.m[STREET_Y1 + 1][BASIN_X0] = B(0x188, 0, 1)                                      # Land above and left.
L.fill(BASIN_X0, STREET_Y1 + 2, BASIN_X0, BEACH_BOTTOM, B(0x190, 0, 1))            # Land left.
L.fill(BASIN_X1, STREET_Y1 + 1, BASIN_X1, BEACH_BOTTOM, B(0x123, 0, 1))            # Sand right.
L.fill(0, SEA_Y, HEAD_X1, SEA_Y, B(0x189, 0, 1))
L.m[SEA_Y][BASIN_X0] = B(0x198, 0, 1)                                              # Land up-left only.
L.fill(BASIN_X1 + 1, SEA_Y, W - 1, SEA_Y, B(0x12C, 0, 1))
L.m[SEA_Y][BASIN_X1] = B(0x12B, 0, 1)

# A wooden pier (Dewford's) out from the headland into the basin, boats, and bollards.
PIER_Y, PIER_X1 = 31, 17
L.stamp(HEAD_X1, PIER_Y, [[B(0x228, 0, 3)] + [B(0x229, 0, 3)] * (PIER_X1 - HEAD_X1),
                          [B(0x230, 1, 0)] + [B(0x231, 1, 0)] * (PIER_X1 - HEAD_X1)])
BOAT = [[B(HARBOUR['BOAT_%d' % (y * 3 + x)], 1, 1) for x in range(3)] for y in range(3)]
for (x, y) in [(20, 30), (25, 32), (14, 33)]:
    L.stamp(x, y, BOAT)
for x in (16, 23, 28):
    L.m[STREET_Y1][x] = B(HARBOUR['BOLLARD'], 1, 0)

# The bowl: wooded slopes down each side, and two terraces climbing to the gym at the back.
# Each terrace's cliff steps down at its ends.
L.trees(0, 0, W - 1, 1)
L.trees(0, 2, 7, 11)
L.trees(0, 12, 5, 20)
L.trees(0, 21, 1, BEACH_BOTTOM)
L.trees(36, 2, W - 1, 11)
L.trees(38, 12, 39, 25)
L.trees(40, 12, W - 1, BEACH_TOP - 2)   # Route 2's moor, down to its beach.

STAIRS_X = 21
def band(x0, x1, y, stairs=()):
    L.stamp(x0, y, cliff(x1 - x0 + 1, stairs=[s - x0 for s in stairs]))
band(8, 12, 11)
band(12, 31, 10, stairs=[STAIRS_X])
band(31, 35, 11)
band(6, 10, 20)
band(10, 33, 19, stairs=[STAIRS_X])
band(33, 37, 20)

# The way up: from the gym's plaza down both flights to the street.
L.fill(STAIRS_X, 12, STAIRS_X + 1, 18, PAVING)
L.fill(STAIRS_X, 21, STAIRS_X + 1, STREET_Y0 - 1, PAVING)

DOORS = {}
def building(name, rows, x, y, door_dx):
    L.stamp(x, y, rows)
    DOORS[name] = (x + door_dx, y + len(rows) - 1)

building('gym', GYM, 18, 2, 3)
building('house1', HOUSE, 9, 14, 1)
building('house2', HOUSE, 30, 14, 1)
building('pokemon_center', PC, 4, 22, 1)
building('mart', MART, 9, 22, 1)
building('gallery', WIDE_HOUSE, 26, 22, 2)
building('harbour_house1', HOUSE, 15, 22, 1)   # Harbourfront cottages, interiors in phase 5.
building('harbour_house2', HOUSE, 32, 22, 1)

# The gym's plaza and gardens, after St Ives's sculpture garden: a paved plaza with planters,
# a fenced garden of standing stones to the west, and a lily pond ringed with shrubs to the east.
SHRUB = B(0x00E, 1, 0)
PLANTER = B(0x007, 1, 0)
L.fill(16, 6, 27, 9, PAVING)
L.stamp(18, 2, GYM)                                     # Its corners sit on the plaza.
for (x, y) in [(16, 7), (27, 7), (16, 9), (27, 9)]:
    L.m[y][x] = PLANTER

GARDEN_X0, GARDEN_X1, GARDEN_Y0, GARDEN_Y1 = 9, 15, 3, 8
L.stamp(GARDEN_X0, GARDEN_Y0, [[B(0x139, 1, 0)]] + [[B(0x140, 1, 0)]] * 4)              # West side.
L.stamp(GARDEN_X1, GARDEN_Y0, [[B(0x141, 1, 0)], [B(0x142, 1, 0)], [B(0x142, 1, 0)]])  # East side, with
L.stamp(GARDEN_X1, GARDEN_Y1 - 1, [[B(0x141, 1, 0)]])                                  # a gate on row 6.
L.stamp(GARDEN_X0, GARDEN_Y1, [[B(0x148, 1, 0)] + [B(0x149, 1, 0)] * 5 + [B(0x14A, 1, 0)]])
L.stamp(10, 4, MENHIR)
L.stamp(13, 4, MENHIR)
L.fill(10, 7, 14, 7, FLOWER)
L.m[3][12] = FLOWER

POND_X0, POND_X1, POND_Y0, POND_Y1 = 30, 33, 4, 6
L.fill(POND_X0, POND_Y0, POND_X1, POND_Y1, WATER)
L.fill(POND_X0, POND_Y0, POND_X1, POND_Y0, B(0x189, 0, 1))
L.m[POND_Y0][POND_X0], L.m[POND_Y0][POND_X1] = B(0x188, 0, 1), B(0x18A, 0, 1)
L.fill(POND_X0, POND_Y0 + 1, POND_X0, POND_Y1, B(0x190, 0, 1))
L.fill(POND_X1, POND_Y0 + 1, POND_X1, POND_Y1, B(0x192, 0, 1))
L.fill(POND_X0, POND_Y1 + 1, POND_X1, POND_Y1 + 1, B(0x002, 0, 3))   # Grass with the water above.
for (x, y) in [(29, 3), (34, 3), (29, 7), (34, 7), (28, 5), (35, 5)]:
    L.m[y][x] = SHRUB
for (x, y) in [(31, 3), (32, 3), (30, 8), (33, 8), (29, 5), (34, 5)]:
    L.m[y][x] = FLOWER

SIGNS = {'town': (32, 30), 'gym': (24, 6)}
for (x, y) in SIGNS.values():
    L.m[y][x] = SIGN

for (x, y) in [(8, 13), (16, 15), (26, 16), (34, 17), (24, 23), (13, 24)]:
    if L.m[y][x] == GRASS:
        L.m[y][x] = FLOWER

# Hand edits from Porymap: the cliff caps where each terrace's middle band meets its stepped ends.
HAND_EDITS = {
    (12, 11): B(0x07C, 1, 0),
    (31, 11): B(0x07C, 1, 0),
    (10, 20): B(0x07C, 1, 0),
    (33, 20): B(0x07C, 1, 0),
    # The gardens: a full fence round the sculpture garden with its gate at the bottom right,
    # shrubs and planters rearranged, and the top flight of steps three wide under the gym door.
    (9, 2): B(0x138, 1, 0),
    (10, 2): B(0x149, 1, 0),
    (11, 2): B(0x149, 1, 0),
    (12, 2): B(0x149, 1, 0),
    (13, 2): B(0x149, 1, 0),
    (14, 2): B(0x149, 1, 0),
    (15, 2): B(0x13A, 1, 0),
    (27, 2): B(0x004, 0, 3),
    (25, 4): B(0x004, 0, 3),
    (29, 4): B(0x016, 1, 0),
    (34, 4): B(0x016, 1, 0),
    (15, 6): B(0x142, 1, 0),
    (27, 6): B(0x001, 0, 3),
    (28, 6): B(0x016, 1, 0),
    (35, 6): B(0x016, 1, 0),
    (15, 7): B(0x001, 0, 3),
    (16, 7): B(0x38E, 0, 3),
    (27, 7): B(0x001, 0, 3),
    (9, 8): B(0x140, 1, 0),
    (10, 8): B(0x001, 0, 3),
    (11, 8): B(0x001, 0, 3),
    (12, 8): B(0x001, 0, 3),
    (13, 8): B(0x001, 0, 3),
    (14, 8): B(0x001, 0, 3),
    (15, 8): B(0x001, 0, 3),
    (27, 8): B(0x001, 0, 3),
    (29, 8): B(0x016, 1, 0),
    (34, 8): B(0x016, 1, 0),
    (9, 9): B(0x148, 1, 0),
    (10, 9): B(0x149, 1, 0),
    (11, 9): B(0x149, 1, 0),
    (12, 9): B(0x149, 1, 0),
    (13, 9): B(0x149, 1, 0),
    (14, 9): B(0x149, 1, 0),
    (15, 9): B(0x149, 1, 0),
    (16, 9): B(0x38E, 0, 3),
    (27, 9): B(0x001, 0, 3),
    (20, 10): B(0x0AF, 0, 3),
    (21, 10): B(0x0CF, 0, 3),
    (20, 11): B(0x0AF, 0, 3),
    (21, 11): B(0x0CF, 0, 3),
    (20, 12): B(0x38E, 0, 3),
    (20, 13): B(0x38E, 0, 3),
    (20, 14): B(0x38E, 0, 3),
}
for (x, y), v in HAND_EDITS.items():
    L.stamp(x, y, [[v]])

if __name__ == '__main__':
    L.save('Porthliw', sys.argv[1] if len(sys.argv) > 1 else None)
    print('doors', DOORS, 'signs', SIGNS)
