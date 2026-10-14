#include "global.h"
#include "item.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("Grampy's Journal goes in the Key Items pocket when given")
{
    const enum Pocket expectedPocket = POCKET_KEY_ITEMS;
    enum Pocket actualPocket;

    RUN_OVERWORLD_SCRIPT(
        additem ITEM_GRAMPYS_JOURNAL;
    );

    actualPocket = GetItemPocket(ITEM_GRAMPYS_JOURNAL);
    EXPECT_EQ(actualPocket, expectedPocket);
    EXPECT(CheckBagHasItem(ITEM_GRAMPYS_JOURNAL, 1));
}

TEST("Grampy's Journal is an important item that can't be tossed or sold")
{
    const u8 expectedImportance = 1;
    u8 actualImportance = GetItemImportance(ITEM_GRAMPYS_JOURNAL);

    EXPECT_EQ(actualImportance, expectedImportance);
}
