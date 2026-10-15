"""Render GBA metatile sheets and map.bin layouts to PNG without Pillow.

    python3 tools/kernia/gbarender.py sheet general dewford 0x200 256 out.png
    python3 tools/kernia/gbarender.py map general dewford data/layouts/Carnrudh/map.bin 32 out.png
"""
import struct, zlib, sys, os

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'data', 'tilesets')


def read_png_indexed(path):
    d = open(path, 'rb').read()
    assert d[:8] == b'\x89PNG\r\n\x1a\n'
    i = 8; idat = b''; w = h = depth = ctype = None
    while i < len(d):
        ln, = struct.unpack('>I', d[i:i+4]); t = d[i+4:i+8]; c = d[i+8:i+8+ln]; i += 12 + ln
        if t == b'IHDR':
            w, h, depth, ctype = struct.unpack('>IIBB', c[:10])
        elif t == b'IDAT':
            idat += c
    raw = zlib.decompress(idat)
    bpp = 1
    stride = (w * depth + 7) // 8
    rows = []; prev = bytearray(stride); p = 0
    for _ in range(h):
        f = raw[p]; line = bytearray(raw[p+1:p+1+stride]); p += 1 + stride
        for x in range(stride):
            a = line[x-bpp] if x >= bpp else 0; b = prev[x]; cc = prev[x-bpp] if x >= bpp else 0
            if f == 1: line[x] = (line[x] + a) & 255
            elif f == 2: line[x] = (line[x] + b) & 255
            elif f == 3: line[x] = (line[x] + (a + b) // 2) & 255
            elif f == 4:
                pa, pb, pc = abs(b - cc), abs(a - cc), abs(a + b - 2*cc)
                pr = a if pa <= pb and pa <= pc else (b if pb <= pc else cc)
                line[x] = (line[x] + pr) & 255
        prev = line
        if depth == 4:
            px = []
            for byte in line: px += [byte >> 4, byte & 15]
            rows.append(px[:w])
        elif depth == 8:
            rows.append(list(line[:w]))
        else:
            raise ValueError(depth)
    return w, h, rows


def write_png(path, w, h, rgb_rows):
    raw = b''.join(b'\x00' + bytes(r) for r in rgb_rows)
    def chunk(t, c): return struct.pack('>I', len(c)) + t + c + struct.pack('>I', zlib.crc32(t + c) & 0xffffffff)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0))
                           + chunk(b'IDAT', zlib.compress(raw, 6)) + chunk(b'IEND', b''))


def read_pal(path):
    lines = open(path).read().split('\n')[3:]
    return [tuple(int(v) for v in l.split()) for l in lines if l.strip()][:16]


class Tileset:
    def __init__(self, primary, secondary):
        self.ptiles = self._tiles(f'{ROOT}/primary/{primary}/tiles.png')
        self.stiles = self._tiles(f'{ROOT}/secondary/{secondary}/tiles.png') if secondary else []
        self.pals = []
        for n in range(13):
            src = primary if n < 6 else secondary
            kind = 'primary' if n < 6 else 'secondary'
            p = f'{ROOT}/{kind}/{src}/palettes/{n:02d}.pal'
            self.pals.append(read_pal(p) if src and os.path.exists(p) else [(255, 0, 255)] * 16)
        self.pmeta = self._meta(f'{ROOT}/primary/{primary}/metatiles.bin')
        self.smeta = self._meta(f'{ROOT}/secondary/{secondary}/metatiles.bin') if secondary else []

    @staticmethod
    def _tiles(p):
        w, h, rows = read_png_indexed(p)
        out = []
        for ty in range(h // 8):
            for tx in range(w // 8):
                out.append([rows[ty*8+y][tx*8:tx*8+8] for y in range(8)])
        return out

    @staticmethod
    def _meta(p):
        d = open(p, 'rb').read(); a = struct.unpack('<%dH' % (len(d)//2), d)
        return [a[i*8:i*8+8] for i in range(len(a)//8)]

    def tile(self, idx):
        if idx < 512:
            return self.ptiles[idx] if idx < len(self.ptiles) else None
        idx -= 512
        return self.stiles[idx] if idx < len(self.stiles) else None

    def metatile_px(self, mid):
        """16x16 list of RGB tuples."""
        meta = self.pmeta[mid] if mid < 512 else (self.smeta[mid-512] if mid-512 < len(self.smeta) else None)
        px = [[(0, 0, 0)] * 16 for _ in range(16)]
        if meta is None:
            return px
        for layer in range(2):
            for q in range(4):
                e = meta[layer*4+q]
                t = self.tile(e & 0x3FF)
                if t is None: continue
                hf, vf, pal = (e >> 10) & 1, (e >> 11) & 1, e >> 12
                ox, oy = (q % 2) * 8, (q // 2) * 8
                for y in range(8):
                    for x in range(8):
                        c = t[7-y if vf else y][7-x if hf else x]
                        if c == 0 and layer: continue
                        px[oy+y][ox+x] = self.pals[pal][c]
        return px


def render_blocks(ts, grid, path, scale=1, mark=None):
    """grid: rows of metatile ids (or None)."""
    h = len(grid); w = len(grid[0])
    img = [[0]*(w*16*3) for _ in range(h*16)]
    cache = {}
    for by, row in enumerate(grid):
        for bx, mid in enumerate(row):
            if mid is None: continue
            if mid not in cache: cache[mid] = ts.metatile_px(mid)
            px = cache[mid]
            for y in range(16):
                r = img[by*16+y]
                for x in range(16):
                    c = px[y][x]
                    if mark and mark(bx, by, x, y): c = (255, 0, 0)
                    r[(bx*16+x)*3:(bx*16+x)*3+3] = c
    if scale > 1:
        img = [sum(([r[i*3:i*3+3]*1 for i in range(len(r)//3) for _ in range(scale)]), []) for r in img for _ in range(scale)]
    write_png(path, w*16*scale, h*16*scale, img)


def sheet(ts, start, count, path, cols=16):
    grid = []
    for r in range((count + cols - 1)//cols):
        grid.append([start + r*cols + c if r*cols + c < count else None for c in range(cols)])
    render_blocks(ts, grid, path)


def load_map(path, w):
    d = open(path, 'rb').read(); a = struct.unpack('<%dH' % (len(d)//2), d)
    return [list(a[i*w:(i+1)*w]) for i in range(len(a)//w)]


if __name__ == '__main__':
    cmd = sys.argv[1]
    if cmd == 'sheet':
        prim, sec, start, count, out = sys.argv[2], sys.argv[3], int(sys.argv[4], 0), int(sys.argv[5], 0), sys.argv[6]
        sheet(Tileset(prim, sec if sec != '-' else None), start, count, out)
    elif cmd == 'map':
        prim, sec, mp, w, out = sys.argv[2], sys.argv[3], sys.argv[4], int(sys.argv[5]), sys.argv[6]
        ts = Tileset(prim, sec)
        grid = [[v & 0x3FF for v in row] for row in load_map(mp, w)]
        render_blocks(ts, grid, out)
