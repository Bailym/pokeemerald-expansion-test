"""Shared helpers for generating Kernia outdoor layouts (General + Dewford tilesets).

A Layout is a grid of blocks plus a mask of tree cells. Trees are resolved into vanilla's
2x2 tree tiles (and their edge pieces) only when the layout is saved, so masses can be
painted freely and cut into afterwards. Block IDs are copied from vanilla maps.
"""
import os, struct
from gbarender import Tileset, render_blocks

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')


def B(mid, coll, elev):
    return mid | (coll << 10) | (elev << 12)


GRASS = B(0x001, 0, 3)
FLOWER = B(0x004, 0, 3)
TALL_GRASS = B(0x00D, 0, 3)
SIGN = B(0x003, 1, 0)

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
STAIRS = [B(0x0AF, 0, 3), B(0x0CF, 0, 3)]  # Two wide; stack them to climb a taller cliff.
# A 2x2 pointed standing stone, used for the giant's stones. Nothing else on Carn Kowr uses it.
MENHIR = [[B(0x083, 1, 0), B(0x084, 1, 0)],
          [B(0x08B, 1, 0), B(0x08C, 1, 0)]]


def outcrop(w, h):
    """A solid rounded granite outcrop on grass, at least 3x2."""
    rows = []
    for y in range(h):
        if y == 0:
            l, m, r = 0x068, 0x069, 0x06A
        elif y == h - 1:
            l, m, r = 0x078, 0x079, 0x07A
        else:
            l, m, r = 0x070, 0x071, 0x072
        rows.append([B(l if x == 0 else (r if x == w - 1 else m), 1, 0) for x in range(w)])
    return rows


def cliff(w, stairs=()):
    """A 2-tall south-facing cliff band on grass, as on Route 104, with rounded end caps.

    stairs: x offsets where a 2-wide flight of steps cuts through it."""
    top = [B(0x07B if x == 0 else (0x07D if x == w - 1 else 0x07C), 1, 0) for x in range(w)]
    bot = [B(0x078 if x == 0 else (0x07A if x == w - 1 else 0x079), 1, 0) for x in range(w)]
    for sx in stairs:
        top[sx:sx + 2] = STAIRS
        bot[sx:sx + 2] = STAIRS
    return [top, bot]


class Layout:
    def __init__(self, w, h):
        self.w, self.h = w, h
        self.m = [[GRASS] * w for _ in range(h)]
        self.tree = [[False] * w for _ in range(h)]

    def trees(self, x0, y0, x1, y1, on=True):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                self.tree[y][x] = on

    def stamp(self, x0, y0, rows):
        for dy, row in enumerate(rows):
            for dx, v in enumerate(row):
                if v is not None:
                    self.m[y0 + dy][x0 + dx] = v
                    self.tree[y0 + dy][x0 + dx] = False

    def fill(self, x0, y0, x1, y1, v):
        self.stamp(x0, y0, [[v] * (x1 - x0 + 1) for _ in range(y1 - y0 + 1)])

    def hroad(self, x0, x1, y, open_left=False, open_right=False):
        """A 2-row sand road; ends get end caps unless they run off the map or into another road."""
        for x in range(x0, x1 + 1):
            cap_l = x == x0 and not open_left and x0 > 0
            cap_r = x == x1 and not open_right
            top = 0x118 if cap_l else (0x11A if cap_r else 0x119)
            bot = 0x128 if cap_l else (0x12A if cap_r else 0x129)
            self.stamp(x, y, [[B(top, 0, 3)], [B(bot, 0, 3)]])

    def vroad(self, x, y0, y1):
        for y in range(y0, y1 + 1):
            self.stamp(x, y, [[B(0x120, 0, 3), B(0x122, 0, 3)]])

    def junction(self, x, y):
        """Mark the two horizontal-road cells where a vertical road joins it."""
        self.stamp(x, y, [[B(0x121, 0, 3), B(0x121, 0, 3)]])

    def resolve(self):
        """Turn tree cells into tiles: tops on even rows, bottoms on odd rows, left halves on even columns."""
        m, tree = self.m, self.tree
        for y in range(self.h):
            for x in range(self.w):
                if not tree[y][x]:
                    continue
                left = x % 2 == 0
                if y % 2 == 0:
                    v = 0x1D4 if left else 0x1D5
                else:
                    below_open = y + 1 < self.h and not tree[y + 1][x]
                    v = (0x1E4 if left else 0x1E5) if below_open else (0x1DC if left else 0x1DD)
                m[y][x] = B(v, 1, 0)
        # Crown tips on open grass directly above a tree mass's top row.
        for y in range(self.h - 1):
            for x in range(self.w):
                if tree[y + 1][x] and not tree[y][x] and m[y][x] in (GRASS, FLOWER) and (y + 1) % 2 == 0:
                    m[y][x] = B(0x1CE if x % 2 == 0 else 0x1CF, 0, 3)

    def save(self, layout_dir, preview=None):
        self.resolve()
        path = os.path.join(REPO, 'data', 'layouts', layout_dir)
        os.makedirs(path, exist_ok=True)
        open(os.path.join(path, 'map.bin'), 'wb').write(b''.join(struct.pack('<H', v) for row in self.m for v in row))
        border = struct.pack('<4H', B(0x1D4, 1, 0), B(0x1D5, 1, 0), B(0x1DC, 1, 0), B(0x1DD, 1, 0))
        open(os.path.join(path, 'border.bin'), 'wb').write(border)
        if preview:
            render_blocks(Tileset('general', 'dewford'), [[v & 0x3FF for v in row] for row in self.m], preview)
