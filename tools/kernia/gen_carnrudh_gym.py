"""Generate data/layouts/Carnrudh_Gym (15x20, Building + LavaridgeGym): Tanek's engine-house boiler room.

    python3 tools/kernia/gen_carnrudh_gym.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost. A stand-in until the
gym has custom tiles: Lavaridge Gym's brick floor, pipe partitions and Flannery's dais.
Lavaridge's vents are warps down to its B1F, so here they're solid decoration (steam
vents) and the player never steps on one. See design/Carnrudh.md.
"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gbarender import Tileset, render_blocks

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
W, H = 15, 20


def B(mid, coll, elev):
    return mid | (coll << 10) | (elev << 12)


FLOOR = B(0x208, 0, 3)
FLOOR_SHADE_L = B(0x209, 0, 3)  # Shadow from a wall or pipe to the left.
FLOOR_UNDER_WALL = B(0x202, 0, 3)
FLOOR_UNDER_WALL_L = B(0x201, 0, 3)
WALL_TOP = B(0x206, 1, 0)
WALL_FACE = B(0x20E, 1, 0)
PIPE_TOP = B(0x204, 1, 0)       # Where a pipe meets the wall's top row.
PIPE = B(0x20C, 1, 0)
PIPE_END = B(0x20B, 1, 0)
PIPE_FOOT = B(0x210, 0, 3)      # Floor below a pipe's end.
PIPE_FOOT_R = B(0x20A, 0, 3)    # Floor below and right of a pipe's end.
VENT = B(0x212, 1, 0)           # Solid, so its warp behaviour never fires.
VENT_SHADE_L = B(0x213, 1, 0)
STATUE = [[B(0x215, 1, 0)], [B(0x21F, 1, 0)]]
DAIS = [[B(0x218, 1, 0), B(0x219, 0, 0), B(0x21A, 0, 0), B(0x21B, 0, 0), B(0x21C, 1, 0)],
        [B(0x220, 1, 0), B(0x221, 0, 0), B(0x222, 0, 0), B(0x223, 0, 0), B(0x224, 1, 0)]]
EXIT_MAT = [B(0x006, 0, 3), B(0x007, 0, 3)]

PIPES_X = (3, 11)   # The hall runs x 4-10 between them; boiler bays either side.
PIPE_END_Y = 16
DAIS_X, DAIS_Y = 5, 3
TANEK = (7, 3)
STATUES_X = (5, 9)
STATUE_Y = 16
EXIT_X = 7

m = [[FLOOR] * W for _ in range(H)]
for x in range(W):
    m[0][x], m[1][x] = WALL_TOP, WALL_FACE
    m[2][x] = FLOOR_UNDER_WALL
m[2][0] = FLOOR_UNDER_WALL_L
for y in range(3, H):
    m[y][0] = FLOOR_SHADE_L
for px in PIPES_X:
    m[0][px] = PIPE_TOP
    for y in range(1, PIPE_END_Y):
        m[y][px] = PIPE
    m[PIPE_END_Y][px] = PIPE_END
    m[PIPE_END_Y + 1][px] = PIPE_FOOT
    m[2][px + 1] = FLOOR_UNDER_WALL_L
    for y in range(3, PIPE_END_Y + 1):
        m[y][px + 1] = FLOOR_SHADE_L
    m[PIPE_END_Y + 1][px + 1] = PIPE_FOOT_R
# Steam vents in the boiler bays.
for (x, y) in [(1, 4), (2, 7), (1, 10), (2, 13), (13, 4), (12, 8), (14, 11), (13, 14)]:
    m[y][x] = VENT_SHADE_L if m[y][x] == FLOOR_SHADE_L else VENT
for dy, row in enumerate(DAIS):
    for dx, v in enumerate(row):
        m[DAIS_Y + dy][DAIS_X + dx] = v
for sx in STATUES_X:
    m[STATUE_Y][sx], m[STATUE_Y + 1][sx] = STATUE[0][0], STATUE[1][0]
m[H - 1][EXIT_X], m[H - 1][EXIT_X + 1] = EXIT_MAT

if __name__ == '__main__':
    path = os.path.join(REPO, 'data', 'layouts', 'Carnrudh_Gym')
    os.makedirs(path, exist_ok=True)
    open(os.path.join(path, 'map.bin'), 'wb').write(b''.join(struct.pack('<H', v) for row in m for v in row))
    open(os.path.join(path, 'border.bin'), 'wb').write(struct.pack('<4H', *[B(0x001, 1, 0)] * 4))
    if len(sys.argv) > 1:
        render_blocks(Tileset('building', 'lavaridge_gym'), [[v & 0x3FF for v in row] for row in m], sys.argv[1], scale=2)
    print('tanek', TANEK, 'statues (bottom tiles)', [(x, STATUE_Y + 1) for x in STATUES_X], 'exit', [(EXIT_X, H - 1), (EXIT_X + 1, H - 1)])
