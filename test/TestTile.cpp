#include <cassert>
#include <iostream>
#include "Tile.h"
#include "ResourceType.h"

void testTile() {
    Tile tile(ResourceType::WOOD, 5);
    assert(tile.resourceType == ResourceType::WOOD);
    assert(tile.number == 5);
}
