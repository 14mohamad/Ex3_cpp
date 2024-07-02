#include <cassert>
#include <iostream>
#include "Board.h"
#include "Tile.h"

void testBoard() {
    Board board;
    assert(board.tiles.size() == 19);
    assert(board.tiles[0].resourceType == ResourceType::WOOD);
    assert(board.tiles[0].number == 5);
}
