"""Copy Slateport's harbour pieces into the Dewford tileset for Porthliw's harbourfront.

    python3 tools/kernia/add_harbour_tiles.py [preview.png]

Porthliw shares Route 2's General + Dewford tilesets, but Dewford has no paving or harbour walls.
Slateport's grey paving, white kerbed quay edges (solid, so they work as the harbour railing),
bollards, and moored sailboats are copied in whole: both layers, their attributes, and their
palettes. Slateport's palette 6 goes into Dewford's unused slot 6 and its palette 8 into unused
slot 11; the tiles go into blank slots.

Run after tools/kernia/add_lighthouse_tiles.py: these metatiles are appended after the lighthouse.
Safe to re-run: earlier harbour tiles are cleared first, then appended again in the same order, so
the IDs (see HARBOUR) stay the same. A stand-in until real art exists (see design/CustomArt.md).
"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gbarender import Tileset, read_png_indexed, render_blocks
from add_lighthouse_tiles import png_chunk, write_png_indexed, get_tile, put_tile, free_slots

REPO = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
TILESETS = os.path.join(REPO, 'data', 'tilesets', 'secondary')
DEWFORD = os.path.join(TILESETS, 'dewford')
SLATEPORT = os.path.join(TILESETS, 'slateport')
FIRST_METATILE = 0x38E      # Appended after the lighthouse (0x37C-0x38D).
PALETTES = {6: 6, 8: 11}    # Slateport palette -> Dewford slot. Both Dewford slots are unused.

# Slateport metatile -> name. The kerbed pieces are paving with a white kerb on the named side(s),
# where the quay drops to the water.
PIECES = [
    (0x202, 'PAVING'),
    (0x25D, 'KERB_S'), (0x245, 'KERB_N'), (0x234, 'KERB_W'), (0x23C, 'KERB_E'),
    (0x255, 'KERB_NW'), (0x24D, 'KERB_NE'), (0x2FE, 'KERB_SW'), (0x2FF, 'KERB_SE'),
    (0x32D, 'BOLLARD'),
    (0x338, 'BOAT_0'), (0x339, 'BOAT_1'), (0x33A, 'BOAT_2'),     # A 3x3 moored sailboat.
    (0x340, 'BOAT_3'), (0x341, 'BOAT_4'), (0x342, 'BOAT_5'),
    (0x348, 'BOAT_6'), (0x349, 'BOAT_7'), (0x34A, 'BOAT_8'),
]
HARBOUR = {name: FIRST_METATILE + i for i, (_, name) in enumerate(PIECES)}


def main():
    tiles_path = os.path.join(DEWFORD, 'tiles.png')
    meta_path = os.path.join(DEWFORD, 'metatiles.bin')
    attr_path = os.path.join(DEWFORD, 'metatile_attributes.bin')
    meta = bytearray(open(meta_path, 'rb').read())
    attrs = bytearray(open(attr_path, 'rb').read())
    w, h, rows = read_png_indexed(tiles_path)
    plte, trns = png_chunk(tiles_path, b'PLTE'), png_chunk(tiles_path, b'tRNS')
    before = FIRST_METATILE - 0x200
    assert len(meta) // 16 >= before, 'Run add_lighthouse_tiles.py first.'

    # Clear any harbour pieces from an earlier run.
    for i in range(before * 16, len(meta), 2):
        t = struct.unpack_from('<H', meta, i)[0] & 0x3FF
        if t >= 512:
            put_tile(rows, w, t - 512, [[0] * 8 for _ in range(8)])
    meta, attrs = meta[:before * 16], attrs[:before * 2]

    # Copy each distinct secondary tile once; primary tiles (the water) are shared already.
    sw, sh, srows = read_png_indexed(os.path.join(SLATEPORT, 'tiles.png'))
    smeta = open(os.path.join(SLATEPORT, 'metatiles.bin'), 'rb').read()
    sattrs = open(os.path.join(SLATEPORT, 'metatile_attributes.bin'), 'rb').read()
    entries = [struct.unpack_from('<8H', smeta, (mid - 512) * 16) for mid, _ in PIECES]
    sources = sorted({(e & 0x3FF) - 512 for ent in entries for e in ent if e & 0x3FF >= 512})
    slots = dict(zip(sources, free_slots(rows, w, meta, len(sources))))
    for src, dst in slots.items():
        put_tile(rows, w, dst, get_tile(srows, sw, src))

    def remap(e):
        t, pal = e & 0x3FF, e >> 12
        if t >= 512:
            t = 512 + slots[t - 512]
        if pal >= 6:
            pal = PALETTES[pal]
        return t | (e & 0x0C00) | (pal << 12)

    for (mid, _), ent in zip(PIECES, entries):
        meta += struct.pack('<8H', *(remap(e) for e in ent))
        attrs += sattrs[(mid - 512) * 2:(mid - 512) * 2 + 2]

    for src, dst in PALETTES.items():
        pal = open(os.path.join(SLATEPORT, 'palettes', f'{src:02d}.pal')).read()
        open(os.path.join(DEWFORD, 'palettes', f'{dst:02d}.pal'), 'w', newline='\r\n').write(pal.replace('\r\n', '\n'))

    write_png_indexed(tiles_path, w, h, rows, plte, trns)
    open(meta_path, 'wb').write(meta)
    open(attr_path, 'wb').write(attrs)
    print('metatiles', hex(FIRST_METATILE), '-', hex(FIRST_METATILE + len(PIECES) - 1), 'tiles', len(slots))
    if len(sys.argv) > 1:
        ids = list(HARBOUR.values())
        grid = [[0x170] * (len(ids) * 2 + 1), [0x170] + sum([[i, 0x170] for i in ids], []), [0x170] * (len(ids) * 2 + 1)]
        render_blocks(Tileset('general', 'dewford'), grid, sys.argv[1], scale=2)


if __name__ == '__main__':
    main()
