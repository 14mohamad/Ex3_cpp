#include <cassert>
#include <iostream>
#include "Player.h"

void testTrading() {
    Player player1(1);
    Player player2(2);

    player1.addResource(ResourceType::WOOD, 1);
    player2.addResource(ResourceType::BRICK, 1);

    // Simulate a trade: player1 trades 1 wood for 1 brick from player2
    bool tradeSuccess = player1.trade(player2, ResourceType::WOOD, ResourceType::BRICK, 1);
    assert(tradeSuccess == true);

    assert(player1.resources[ResourceType::WOOD] == 0);
    assert(player1.resources[ResourceType::BRICK] == 1);
    assert(player2.resources[ResourceType::WOOD] == 1);
    assert(player2.resources[ResourceType::BRICK] == 0);
}
