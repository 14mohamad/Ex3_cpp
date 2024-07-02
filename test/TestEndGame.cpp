#include <cassert>
#include <iostream>
#include "Game.h"

void testEndGame() {
    Game game;

    // Manually set player victory points
    Player& player = game.players[0];
    player.victoryPoints = 9;

    // Simulate a turn where the player builds a city and wins
    player.addResource(ResourceType::IRON, 3);
    player.addResource(ResourceType::GRAIN, 2);
    player.buildCity();

    // Check if player has won
    assert(player.victoryPoints >= 10);
}
