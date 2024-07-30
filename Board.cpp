#include "Board.h"
#include <iostream>

Board::Board() {
    // קונסטרוקטור המאתחל את הלוח עם 19 אריחים מוגדרים מראש המייצגים משאבים ומספרים שונים
    // מגדיר סמיכות בין כמה אריחים כדוגמה
    tiles = {
        Tile(ResourceType::WOOD, 5), Tile(ResourceType::BRICK, 6),
        Tile(ResourceType::WOOL, 8), Tile(ResourceType::GRAIN, 3),
        Tile(ResourceType::IRON, 4), Tile(ResourceType::NONE, 7), // Desert
        Tile(ResourceType::WOOD, 2), Tile(ResourceType::BRICK, 9),
        Tile(ResourceType::WOOL, 10), Tile(ResourceType::GRAIN, 11),
        Tile(ResourceType::IRON, 12), Tile(ResourceType::WOOD, 4),
        Tile(ResourceType::BRICK, 5), Tile(ResourceType::WOOL, 6),
        Tile(ResourceType::GRAIN, 8), Tile(ResourceType::IRON, 3),
        Tile(ResourceType::WOOD, 9), Tile(ResourceType::BRICK, 10),
        Tile(ResourceType::WOOL, 11)
    };

    // Example adjacency setup (ensure indices are within bounds)
    if (tiles.size() >= 4) { // Ensure there are enough tiles
        tiles[0].adjacentTiles = { &tiles[1], &tiles[2] };
        tiles[1].adjacentTiles = { &tiles[0], &tiles[3] };
    }
}

// מדפיס את פריסת הלוח, כולל סוג המשאב והמספר של כל אריח
void Board::printBoard() const {
    std::cout << "Board Layout:" << std::endl;
    for (const auto& tile : tiles) {
        std::cout << "Tile: " << tile.resourceToString() << ", Number: " << tile.number << std::endl;
    }
}
