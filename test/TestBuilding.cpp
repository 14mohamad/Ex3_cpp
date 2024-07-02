#include <cassert>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Board.h"


void testBuilding() {
    Player player(1);

    // Test building a settlement
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    player.addResource(ResourceType::WOOL, 1);
    player.addResource(ResourceType::GRAIN, 1);
    player.buildSettlement();
    assert(player.victoryPoints == 3);
    assert(player.resources[ResourceType::WOOD] == 0);
    assert(player.resources[ResourceType::BRICK] == 0);
    assert(player.resources[ResourceType::WOOL] == 0);
    assert(player.resources[ResourceType::GRAIN] == 0);

    // Test building a road
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    player.buildRoad();
    assert(player.resources[ResourceType::WOOD] == 0);
    assert(player.resources[ResourceType::BRICK] == 0);

    // Test building a city
    player.addResource(ResourceType::IRON, 3);
    player.addResource(ResourceType::GRAIN, 2);
    player.buildCity();
    assert(player.victoryPoints == 5);
    assert(player.resources[ResourceType::IRON] == 0);
    assert(player.resources[ResourceType::GRAIN] == 0);
}
