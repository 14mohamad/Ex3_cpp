#include "Tile.h"

Tile::Tile(ResourceType resource, int num) : resourceType(resource), number(num), settled(false) {}

std::string Tile::resourceToString() const {
    switch (resourceType) {
        case ResourceType::WOOD: return "Wood";
        case ResourceType::BRICK: return "Brick";
        case ResourceType::WOOL: return "Wool";
        case ResourceType::GRAIN: return "Grain";
        case ResourceType::IRON: return "Iron";
        case ResourceType::NONE: return "None";
        default: return "Unknown";
    }
    
}
