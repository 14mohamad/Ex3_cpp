#include <cassert>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Board.h"

void testGame() {
    Game game;
    assert(game.getPlayers().size() == 3);
    
    // Test playerTurn and resource gathering
    Player& player = game.getPlayers()[0];
    
    // Simulate a turn
    game.playerTurn(player);
    
    // Test rollDice
    int diceRoll = game.rollDice();
    assert(diceRoll >= 2);
    assert(diceRoll <= 12);
    
    // Test gatherResources
    game.gatherResources(diceRoll);

    // Test trade
    Player& player1 = game.getPlayers()[0];
    Player& player2 = game.getPlayers()[1];
    player1.addResource(ResourceType::WOOD, 1);
    player2.addResource(ResourceType::BRICK, 1);

    // Simulate a trade: player1 trades 1 wood for 1 brick from player2
    bool tradeSuccess = player1.trade(player2, ResourceType::WOOD, ResourceType::BRICK, 1);
    assert(tradeSuccess == true);

    assert(player1.resources[ResourceType::WOOD] == 0);
    assert(player1.resources[ResourceType::BRICK] == 2);
    assert(player2.resources[ResourceType::WOOD] == 1);
    assert(player2.resources[ResourceType::BRICK] == 1);
}

int main() {
    testGame();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
