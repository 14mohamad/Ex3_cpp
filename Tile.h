#ifndef TILE_H
#define TILE_H

#include "ResourceType.h"
#include <string> // Add this line

class Tile {
public:
    ResourceType resourceType;
    int number;
    bool settled; // Add this line to indicate if a tile is settled

    Tile(ResourceType resource, int num);
    std::string resourceToString() const;
};


#endif 
