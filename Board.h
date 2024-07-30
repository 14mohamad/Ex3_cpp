#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "ResourceType.h"

class Tile {
public:
    ResourceType resourceType;
    int number;
    bool settled; // Add this member to track if the tile is settled
    std::vector<Tile*> adjacentTiles;

    // קונסטרוקטור לאתחל אריח עם סוג ומספר משאבים נתונים
    Tile(ResourceType resource, int num) : resourceType(resource), number(num), settled(false) {}
    
    // ממירה את סוג המשאב של האריח לייצוג המחרוזת שלו
    std::string resourceToString() const {
        switch (resourceType) {
            case ResourceType::WOOD: return "Wood";
            case ResourceType::BRICK: return "Brick";
            case ResourceType::WOOL: return "Wool";
            case ResourceType::GRAIN: return "Grain";
            case ResourceType::IRON: return "Iron";
            case ResourceType::NONE: return "Nothing";
            default: return "Unknown";
        }
    }
};

class Board {
public:
    std::vector<Tile> tiles;

    Board();
    void printBoard() const;
};

#endif
