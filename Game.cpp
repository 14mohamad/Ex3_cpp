#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "DevelopmentCard.h"

Game::Game() {
    players = {Player(1), Player(2), Player(3)};
    // Initialize board with tiles
    board.tiles = {
        Tile(ResourceType::WOOD, 2),
        Tile(ResourceType::BRICK, 3),
        Tile(ResourceType::WOOL, 4),
        Tile(ResourceType::GRAIN, 5),
        Tile(ResourceType::IRON, 6),
        Tile(ResourceType::NONE, 7),  // Desert tile
        Tile(ResourceType::WOOD, 8),
        Tile(ResourceType::BRICK, 9),
        Tile(ResourceType::WOOL, 10),
        Tile(ResourceType::GRAIN, 11),
        Tile(ResourceType::IRON, 12)
    };
}

void Game::play() {
    std::srand(std::time(0));
    const int maxTurns = 100;
    bool gameEnd = false;
    int currentTurn = 0;
    while (currentTurn < maxTurns && !gameEnd) {
            for (auto& player : players) {
                std::cout << "Turn for Player Started Player ID: " << player.id << " with Victory Points: " << player.victoryPoints << std::endl;
                playerTurn(player);
                std::cout << "Turn for Player Ended Player ID: " << player.id << " with Victory Points: " << player.victoryPoints << std::endl;
                if (player.victoryPoints >= 10) {
                    gameEnd = true;
                    std::cout << "Player " << player.id << " wins!" << std::endl;
                    break;
                }
            }
            currentTurn++;
        }

        if (!gameEnd) {
            std::cout << "No one won after " << maxTurns << " turns." << std::endl;
        }

}

void Game::playerTurn(Player& player) {
    std::cout << "Player " << player.id << "'s turn." << std::endl;

    int diceRoll = rollDice();
    std::cout << "Dice roll: " << diceRoll << std::endl;

    gatherResources(diceRoll);

    if (player.canBuildSettlement(board.tiles)) {
        player.buildSettlement(board.tiles);
    }
    if (player.canBuildRoad()) {
        player.buildRoad();
    }
    if (player.canBuildCity()) {
        player.buildCity();
    }
    if (player.canBuildDevCard()) {
        DevelopmentCard* card = drawDevelopmentCard();
        player.addDevelopmentCard(card);
        std::cout << "Player " << player.id << " drew a development card." << std::endl;
    }

    if (!player.developmentCards.empty()) {
        int cardIndex = 0; // Simplified, choose the first card for this example
        std::vector<Player*> playerPointers;
        for (auto& p : players) {
            playerPointers.push_back(&p);
        }
        player.useDevelopmentCard(cardIndex, playerPointers);
    }
}

int Game::rollDice() {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}

void Game::gatherResources(int diceRoll) {
    for (auto& player : players) {
        for (const auto& tile : board.tiles) {
            if (tile.number == diceRoll) {
                player.addResource(tile.resourceType, 1);
                std::cout << "Player " << player.id << " receives 1 " << resourceToString(tile.resourceType) << std::endl;
            }
        }
    }
}

std::string Game::resourceToString(ResourceType resource) {
    switch (resource) {
        case ResourceType::WOOD: return "Wood";
        case ResourceType::BRICK: return "Brick";
        case ResourceType::WOOL: return "Wool";
        case ResourceType::GRAIN: return "Grain";
        case ResourceType::IRON: return "Iron";
        case ResourceType::NONE: return "Nothing";
        default: return "Unknown";
    }
}

DevelopmentCard* Game::drawDevelopmentCard() {
    int cardType = (std::rand() % 5); // Ensure Victory Point Card is drawn for testing
    switch (cardType) {
        case 0: return new KnightCard();
        case 1: return new VictoryPointCard();
        case 2: return new RoadBuildingCard();
        case 3: return new YearOfPlentyCard();
        case 4: return new MonopolyCard();
        default: return nullptr;
    }
}
