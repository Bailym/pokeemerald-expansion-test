"""Generate data/layouts/Porthliw_Gym (28x22, Building + FortreeGym): Enys's studio.

    python3 tools/kernia/gen_porthliw_gym.py [preview.png]

Overwrites the layout, so hand edits made in Porymap since are lost. The walkway is a gull
standing side-on, facing left, as Misty's pool is a seahorse. In at the right foot, along the
belly to the tail, back along the bird's back, and up the neck to Enys in the head. The folded
wing is solid right up to the chest, so the belly only joins the back round the tail end. A
stand-in until the studio has custom tiles: Fortree Gym's wooden floor and bushes.
See design/Porthliw.md.
"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gbarender import Tileset, render_blocks

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
W, H = 28, 22


def B(mid, coll, elev):
    return mid | (coll << 10) | (elev << 12)


FLOOR = B(0x202, 0, 3)
BUSH = B(0x218, 1, 0)
STATUE_TOP = B(0x227, 0, 3)
STATUE_BASE = B(0x22F, 1, 0)
EXIT_MAT = [B(0x006, 0, 3), B(0x007, 0, 3)]

m = [[BUSH] * W for _ in range(H)]


def rect(x0, y0, x1, y1, v=FLOOR):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            m[y][x] = v


# Head (round), the beak pointing left, and the neck down to the body.
rect(5, 2, 9, 6); rect(4, 3, 10, 5)
rect(1, 4, 3, 4)
rect(7, 7, 10, 8)
# Body: a rounded oval, with the tail sticking up and out at the back.
rect(7, 9, 21, 15); rect(6, 10, 22, 14)
rect(22, 8, 23, 10); rect(24, 7, 25, 8); rect(26, 6, 26, 7)
# The folded wing, solid across the middle of the body and up to the chest.
rect(6, 11, 19, 13, BUSH)
# Legs and feet. The left leg is a nook for the gym guide; the door is below the right foot.
rect(11, 16, 12, 19); rect(16, 16, 17, 19)
rect(9, 19, 13, 19); rect(15, 19, 19, 19)
rect(16, 20, 17, 20)
# The gym statues stand on the right foot, either side of the way out.
STATUES_X = (15, 18)
for sx in STATUES_X:
    m[19][sx], m[20][sx] = STATUE_TOP, STATUE_BASE
EXIT_X = 16
m[H - 1][EXIT_X], m[H - 1][EXIT_X + 1] = EXIT_MAT

ENYS = (7, 3)
STUDENTS = [(20, 15), (11, 9)]  # Belly (facing up), then back (facing down).
GUIDE = (11, 18)

if __name__ == '__main__':
    path = os.path.join(REPO, 'data', 'layouts', 'Porthliw_Gym')
    os.makedirs(path, exist_ok=True)
    open(os.path.join(path, 'map.bin'), 'wb').write(b''.join(struct.pack('<H', v) for row in m for v in row))
    open(os.path.join(path, 'border.bin'), 'wb').write(struct.pack('<4H', *[BUSH] * 4))
    if len(sys.argv) > 1:
        render_blocks(Tileset('building', 'fortree_gym'), [[v & 0x3FF for v in row] for row in m], sys.argv[1], scale=2)
    print('enys', ENYS, 'students', STUDENTS, 'guide', GUIDE,
          'statues (bottom tiles)', [(x, 20) for x in STATUES_X], 'exit', [(EXIT_X, H - 1), (EXIT_X + 1, H - 1)])
