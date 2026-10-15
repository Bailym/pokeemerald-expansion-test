"""Generate data/layouts/Carnrudh/map.bin + border.bin (32x30, General + Dewford).

    python3 tools/kernia/gen_carnrudh.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost. Block IDs are
copied from vanilla maps; see design/Carnrudh.md for the building positions.
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layoutlib import *

W, H = 32, 30
ROAD_Y = 12  # Main street rows 12-13; Route 1's road is rows 11-12, so the connection offset is 1.

L = Layout(W, H)

# Tree masses (2x2 trees: top rows even, bottom rows odd, left columns even, matching Route 1's phase).
L.trees(0, 0, 31, 3)      # North band.
L.trees(0, 4, 3, 9)       # West strip above the road, as on Route 1's east end.
L.trees(0, 14, 3, 29)     # West strip below the road.
L.trees(28, 0, 31, 29)    # East band; the east road is reserved here for later.
L.trees(4, 26, 27, 29)    # South band.

L.hroad(0, 27, ROAD_Y)
L.vroad(14, 0, ROAD_Y - 1)          # North to Carn Kowr.
L.junction(14, ROAD_Y)
L.vroad(6, ROAD_Y + 2, H - 1)       # South-west route, reserved.
L.junction(6, ROAD_Y + 1)

DOORS = {}
def building(name, rows, x, y, door_dx):
    L.stamp(x, y, rows)
    DOORS[name] = (x + door_dx, y + len(rows) - 1)

building('gym', GYM, 5, 5, 3)
building('pokemon_center', PC, 18, 7, 1)
building('mart', MART, 23, 7, 1)
building('house1', HOUSE, 9, 16, 1)
building('pasty_shop', COTTAGE, 16, 16, 1)
building('school', WIDE_HOUSE, 22, 16, 2)
building('house2', HOUSE, 9, 21, 1)

# Signs: town sign by the west entrance; the gym, pasty shop, and school each have one right of their front.
SIGNS = {'town': (4, 11), 'gym': (11, 9), 'pasty_shop': (20, 19), 'school': (27, 19)}
for (x, y) in SIGNS.values():
    L.m[y][x] = SIGN

for (x, y) in [(5, 4), (13, 10), (17, 11), (22, 11), (20, 14), (26, 21), (5, 18), (13, 24), (19, 23)]:
    if L.m[y][x] == GRASS and not L.tree[y][x]:
        L.m[y][x] = FLOWER

# The engine on show (a 48x48 object event at (21, 22)) covers x 20-22, rows 20-22. Object events
# only block their anchor tile, so the grass under the rest of it is made solid.
ENGINE = (21, 22)
for y in range(ENGINE[1] - 2, ENGINE[1] + 1):
    for x in range(ENGINE[0] - 1, ENGINE[0] + 2):
        L.m[y][x] = (L.m[y][x] & 0x3FF) | (1 << 10) | (3 << 12)

if __name__ == '__main__':
    L.save('Carnrudh', sys.argv[1] if len(sys.argv) > 1 else None)
    print('doors', DOORS, 'signs', SIGNS)
