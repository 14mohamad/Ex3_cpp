#include <cassert>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Board.h"

void testResourceGathering() {
    Game game;
    Player& player = game.players[0];

    // Simulate initial resource distribution
    game.board.tiles[0].number = 6; // Wood
    game.board.tiles[1].number = 8; // Brick

    // Assume player has settlements on these tiles
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);

    // Simulate dice roll of 6
    game.gatherResources(6);
    assert(player.resources[ResourceType::WOOD] == 2);
    assert(player.resources[ResourceType::BRICK] == 1);

    // Simulate dice roll of 8
    game.gatherResources(8);
    assert(player.resources[ResourceType::WOOD] == 2);
    assert(player.resources[ResourceType::BRICK] == 2);
}
