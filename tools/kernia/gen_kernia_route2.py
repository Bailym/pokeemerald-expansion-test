"""Generate data/layouts/KerniaRoute2/map.bin + border.bin (40x50, General + Dewford).

    python3 tools/kernia/gen_kernia_route2.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost. Block IDs are
copied from vanilla maps, apart from the lighthouse, which tools/kernia/add_lighthouse_tiles.py
adds to the Dewford tileset. See design/Route2.md for the layout.
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layoutlib import *

W, H = 40, 50
ROAD_X = 26  # Carnrudh's south-west road is x 6-7, so the connection offset is -20.

WATER = B(0x170, 0, 1)
SHORE_LAND_EAST = B(0x192, 0, 1)  # Sea cell with the land edge on its east side.
SAND = B(0x124, 0, 3)
# Sand beach edges, as on Route 106: each is a water cell with sand drawn on the beach side.
SAND_W, SAND_E, SAND_S = B(0x123, 0, 1), B(0x125, 0, 1), B(0x12C, 0, 1)
SAND_SW, SAND_SE = B(0x12B, 0, 1), B(0x12D, 0, 1)
BOULDER = B(0x0E2, 1, 0)                                          # A boulder on sand (Dewford).
SEA_ROCK = [[B(0x150, 1, 0), B(0x151, 1, 0)], [B(0x158, 1, 0), B(0x159, 1, 0)]]
FENCE_L, FENCE, FENCE_R = B(0x148, 1, 3), B(0x149, 1, 3), B(0x14A, 1, 3)
LIGHTHOUSE = [[B(0x37C + y * 3 + x, 1, 0) for x in range(3)] for y in range(6)]  # 3 wide, 6 tall.

L = Layout(W, H)

# The sea: the west side down to the headland, and the bay below it.
SEA_X = 7         # Sea is x 0-7 above the bay; the coast's edge cells are x 7.
HEAD_CLIFF_Y = 34 # The headland's sea cliff, rows 34-35.
BAY_X1 = 31       # The bay below the cliff is x 0-31; land and trees to the east.
L.fill(0, 0, SEA_X, H - 1, WATER)
L.fill(SEA_X, 0, SEA_X, HEAD_CLIFF_Y + 1, SHORE_LAND_EAST)
L.fill(0, HEAD_CLIFF_Y + 2, BAY_X1, H - 1, WATER)
L.fill(BAY_X1, HEAD_CLIFF_Y + 2, BAY_X1, H - 1, SHORE_LAND_EAST)

# Tree masses (2x2 trees: top rows even, bottom rows odd, left columns even).
L.trees(30, 0, W - 1, H - 1)                # East band: the inland moor, and the way to Porthliw (closed for now).
L.trees(8, 0, 29, 1)                        # North band, continuing Carnrudh's south band; the road cuts through.
L.trees(26, 24, 29, 29)                     # A copse on the lowest terrace, east of the lighthouse.

# The road in from Carnrudh, ending in a cap where the coast path turns to grass.
L.vroad(ROAD_X, 0, 5)
L.stamp(ROAD_X, 6, [[B(0x128, 0, 3), B(0x12A, 0, 3)]])

# The cliff top steps down to the sea in three terraces. The first steps follow the road, the
# second are right at the cliff edge by the sea, and the third lead down to the beach.
L.stamp(8, 12, cliff(22, stairs=(14,)))     # Rows 12-13, steps at x 22-23.
L.stamp(8, 20, cliff(22, stairs=(2,)))      # Rows 20-21, steps at x 10-11.
L.stamp(8, HEAD_CLIFF_Y, cliff(24, stairs=(18,)))  # Rows 34-35 over the sea, steps at x 26-27.

# Tall grass on the two upper terraces. The path can skirt each patch.
L.fill(12, 5, 19, 9, TALL_GRASS)
L.fill(14, 15, 27, 18, TALL_GRASS)

# The headland: the lighthouse at the tip, the keeper's cottage beside it, and a picket fence
# along the cliff edge in front.
LIGHTHOUSE_XY = (8, 24)                     # x 8-10, rows 24-29; its door is (9, 29).
L.stamp(*LIGHTHOUSE_XY, LIGHTHOUSE)
COTTAGE_XY = (13, 26)                       # Rows 26-29, door at (14, 29).
L.stamp(*COTTAGE_XY, COTTAGE)
FENCE_Y = 32
L.stamp(8, FENCE_Y, [[FENCE_L] + [FENCE] * 9 + [FENCE_R]])       # x 8-18, along the cliff edge.
# A sand path past both doors, with a granite outcrop and two shrubs beside the cottage.
PATH_Y = 30                                 # Rows 30-31.
L.hroad(8, 21, PATH_Y)
L.stamp(17, 27, outcrop(3, 3))
L.stamp(20, 28, [[B(0x00E, 1, 0)] * 2, [B(0x016, 1, 0)] * 2])

# The seal cove: a wide sand beach below the headland, open to the bay, with boulders on the
# sand and rocks offshore for the seals.
BEACH_X0, BEACH_X1, BEACH_Y1 = 8, 29, 43    # Frame cells included; sand is x 9-28, rows 36-42.
L.fill(BEACH_X0 + 1, HEAD_CLIFF_Y + 2, BEACH_X1 - 1, BEACH_Y1 - 1, SAND)
L.fill(BEACH_X0, HEAD_CLIFF_Y + 2, BEACH_X0, BEACH_Y1 - 1, SAND_W)
L.fill(BEACH_X1, HEAD_CLIFF_Y + 2, BEACH_X1, BEACH_Y1 - 1, SAND_E)
L.fill(BEACH_X0 + 1, BEACH_Y1, BEACH_X1 - 1, BEACH_Y1, SAND_S)
L.stamp(BEACH_X0, BEACH_Y1, [[SAND_SW]])
L.stamp(BEACH_X1, BEACH_Y1, [[SAND_SE]])
for (x, y) in [(11, 38), (12, 38), (20, 40), (24, 37)]:
    L.m[y][x] = BOULDER
for (x, y) in [(3, 45), (14, 46), (22, 45), (2, 9), (3, 28)]:
    L.stamp(x, y, SEA_ROCK)

SIGNS = {'route': (24, 4), 'lighthouse': (11, 29)}  # The lighthouse sign is read from the path.
for (x, y) in SIGNS.values():
    L.m[y][x] = SIGN

if __name__ == '__main__':
    L.save('KerniaRoute2', sys.argv[1] if len(sys.argv) > 1 else None)
    print('signs', SIGNS, 'lighthouse', LIGHTHOUSE_XY, 'cottage door', (COTTAGE_XY[0] + 1, COTTAGE_XY[1] + 3))
