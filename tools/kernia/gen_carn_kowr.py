"""Generate Carn Kowr's two layouts: the climb (32x40) and the peak (32x20), General + Dewford.

    python3 tools/kernia/gen_carn_kowr.py [preview_dir]

Overwrites both layouts, so hand edits made in Porymap since are lost. The climb's path
passes the stones in the order Hand, Cradle, Head, so the riddle (Hand, Head, Cradle)
means stepping back down from the Head to the Cradle. See design/Carnrudh.md.
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layoutlib import *

PEAK_GAP_X = 22  # The climb's top gap and the peak's bottom gap, x 22-23 (connection offset 0).
TOWN_PATH_X = 14  # Carnrudh's north path, x 14-15.
BAND_W = 24  # Cliff bands run x 4-27, between the tree belts.


def stone(L, x, y):
    """A menhir with a ring of flowers and a name sign to its right, so it reads as a landmark."""
    L.stamp(x, y, MENHIR)
    for (fx, fy) in [(x - 1, y), (x + 2, y), (x - 1, y + 1), (x - 1, y + 2), (x + 2, y + 2)]:
        L.m[fy][fx] = FLOWER
    L.m[y + 1][x + 2] = SIGN


# The climb: three terraces, each reached by stairs on alternating sides, so the path
# zigzags up the hill. The riddle sends the player up and down it, and grunts guard the
# stones, so the tall grass is in optional patches off the path.
climb = Layout(32, 40)
climb.trees(0, 0, 3, 39)
climb.trees(28, 0, 31, 39)
climb.trees(4, 0, 27, 1)
climb.trees(4, 36, 27, 39)
climb.trees(PEAK_GAP_X, 0, PEAK_GAP_X + 1, 1, on=False)
climb.vroad(TOWN_PATH_X, 30, 39)
# Foot of the hill (y 30-35).
climb.trees(24, 30, 27, 35)
climb.fill(8, 30, 11, 35, TALL_GRASS)
climb.stamp(4, 28, cliff(BAND_W, stairs=[TOWN_PATH_X - 4]))  # The road runs up to these stairs.
# First terrace (y 20-27): the Hand to the west, the way on to the east.
climb.stamp(11, 21, outcrop(4, 3))
climb.fill(17, 20, 22, 25, TALL_GRASS)
climb.trees(26, 20, 27, 25)
climb.stamp(4, 18, cliff(BAND_W, stairs=[20]))      # Stairs at x 24-25.
# Second terrace (y 10-17): the Cradle in the middle, the way on to the west.
climb.trees(24, 10, 27, 13)
climb.stamp(19, 11, outcrop(4, 3))
climb.fill(4, 14, 9, 17, TALL_GRASS)
climb.stamp(4, 8, cliff(BAND_W, stairs=[2]))        # Stairs at x 6-7.
# Top terrace (y 2-7): the Head, then the gap up to the peak.
climb.trees(4, 2, 5, 5)
climb.stamp(16, 2, outcrop(4, 3))
climb.fill(12, 6, 17, 7, TALL_GRASS)

STONES = {'hand': (6, 22), 'cradle': (14, 12), 'head': (10, 3)}
for (x, y) in STONES.values():
    stone(climb, x, y)
for (x, y) in [(13, 33), (17, 32), (5, 26), (21, 15), (9, 11), (25, 5)]:
    if climb.m[y][x] == GRASS and not climb.tree[y][x]:
        climb.m[y][x] = FLOWER

# The peak: up one more cliff from the climb to the summit tor, Lumen's survey camp, and the Well.
peak = Layout(32, 20)
peak.trees(0, 0, 3, 19)
peak.trees(28, 0, 31, 19)
peak.trees(4, 0, 27, 1)
peak.trees(4, 18, 27, 19)
peak.trees(PEAK_GAP_X, 18, PEAK_GAP_X + 1, 19, on=False)
peak.stamp(4, 12, cliff(BAND_W, stairs=[PEAK_GAP_X - 4]))
peak.stamp(6, 14, outcrop(3, 2))
# The summit tor: a cluster of granite boulders. Stacking outcrops leaves grass in the
# corners where they meet, as vanilla has no boulder corners drawn over rock.
for (x, y, w, h) in [(5, 5, 4, 4), (9, 3, 5, 4), (9, 7, 3, 2), (14, 5, 3, 3)]:
    peak.stamp(x, y, outcrop(w, h))
WELL = (20, 6)
stone(peak, *WELL)
SURVEY_SIGN = (25, 9)
peak.m[SURVEY_SIGN[1]][SURVEY_SIGN[0]] = SIGN
for (x, y) in [(13, 15), (18, 16), (26, 4), (16, 10)]:
    if peak.m[y][x] == GRASS and not peak.tree[y][x]:
        peak.m[y][x] = FLOWER

if __name__ == '__main__':
    out = sys.argv[1] if len(sys.argv) > 1 else None
    climb.save('CarnKowr', out and os.path.join(out, 'carn_kowr.png'))
    peak.save('CarnKowr_Peak', out and os.path.join(out, 'carn_kowr_peak.png'))
    # Each stone is inspected from below, so its bg_events go on its bottom row.
    print('stones', {k: [(x, y + 1), (x + 1, y + 1)] for k, (x, y) in STONES.items()})
    print('stone signs', {k: (x + 2, y + 1) for k, (x, y) in STONES.items()}, 'well sign', (WELL[0] + 2, WELL[1] + 1))
    print('well', [(WELL[0], WELL[1] + 1), (WELL[0] + 1, WELL[1] + 1)], 'survey sign', SURVEY_SIGN)
