#include <cassert>
#include <iostream>
#include "Player.h"
#include "ResourceType.h"

void testPlayer() {
    Player player(1);
    
    // Test canBuildSettlement
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    player.addResource(ResourceType::WOOL, 1);
    player.addResource(ResourceType::GRAIN, 1);
    assert(player.canBuildSettlement() == true);

    player = Player(1);  // Reset player
    assert(player.canBuildSettlement() == false);
    
    // Test buildSettlement
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
    
    // Test canBuildRoad
    assert(player.canBuildRoad() == false);
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    assert(player.canBuildRoad() == true);

    // Test buildRoad
    player.buildRoad();
    assert(player.resources[ResourceType::WOOD] == 0);
    assert(player.resources[ResourceType::BRICK] == 0);

    // Test canBuildCity
    player.addResource(ResourceType::IRON, 3);
    player.addResource(ResourceType::GRAIN, 2);
    assert(player.canBuildCity() == true);

    // Test buildCity
    player.buildCity();
    assert(player.victoryPoints == 5);
    assert(player.resources[ResourceType::IRON] == 0);
    assert(player.resources[ResourceType::GRAIN] == 0);
}
