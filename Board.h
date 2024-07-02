#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"

class Board {
public:
    std::vector<Tile> tiles;

    Board();
    void printBoard() const;
};


#endif 
