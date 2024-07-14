#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>

// Enum for Resource Types
enum class ResourceType {
    IRON,
    WOOD,
    BRICK,
    WOOL,
    GRAIN,
    NONE // For desert
};

// Tile Class
class Tile {
public:
    ResourceType resourceType;
    int number;
    bool settled;
    std::vector<Tile*> adjacentTiles;

    Tile(ResourceType resource, int num) : resourceType(resource), number(num), settled(false) {}

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

// Player Class
class Player {
public:
    int id;
    int victoryPoints;
    int knightsPlayed;
    std::map<ResourceType, int> resources;
    std::vector<Tile*> settlements;

    Player(int playerId) : id(playerId), victoryPoints(2), knightsPlayed(0) {
        resources = {
            {ResourceType::WOOD, 0},
            {ResourceType::BRICK, 0},
            {ResourceType::WOOL, 0},
            {ResourceType::GRAIN, 0},
            {ResourceType::IRON, 0}
        };
    }

    void addResource(ResourceType resource, int amount) {
        resources[resource] += amount;
    }

    bool canBuildSettlement(const std::vector<Tile>& tiles) {
        if (resources[ResourceType::WOOD] < 1 || resources[ResourceType::BRICK] < 1 ||
            resources[ResourceType::WOOL] < 1 || resources[ResourceType::GRAIN] < 1) {
            return false;
        }
        for (const auto& tile : tiles) {
            for (const auto& adjacentTile : tile.adjacentTiles) {
                if (adjacentTile->resourceType != ResourceType::NONE && std::find(settlements.begin(), settlements.end(), adjacentTile) == settlements.end()) {
                    return true;
                }
            }
        }
        return false;
    }

    void buildSettlement(std::vector<Tile>& tiles) {
        if (canBuildSettlement(tiles)) {
            resources[ResourceType::WOOD]--;
            resources[ResourceType::BRICK]--;
            resources[ResourceType::WOOL]--;
            resources[ResourceType::GRAIN]--;
            victoryPoints++;
            for (auto& tile : tiles) {
                for (auto& adjacentTile : tile.adjacentTiles) {
                    if (adjacentTile->resourceType != ResourceType::NONE && std::find(settlements.begin(), settlements.end(), adjacentTile) == settlements.end()) {
                        settlements.push_back(adjacentTile);
                        std::cout << "Player " << id << " built a settlement on tile with resource: " << adjacentTile->resourceToString() << ". Total Victory Points: " << victoryPoints << std::endl;
                        return;
                    }
                }
            }
        } else {
            std::cout << "Player " << id << " cannot build a settlement." << std::endl;
        }
    }
};

// DevelopmentCard Class
class DevelopmentCard {
public:
    virtual void use(Player& player) = 0;
    virtual ~DevelopmentCard() = default;
};

class ProgressCard : public DevelopmentCard {
public:
    void use(Player& player) override {
        std::cout << "Player " << player.id << " used a Progress Card." << std::endl;
    }
};

class KnightCard : public DevelopmentCard {
public:
    void use(Player& player) override {
        std::cout << "Player " << player.id << " used a Knight Card." << std::endl;
    }
};

class VictoryPointCard : public DevelopmentCard {
public:
    void use(Player& player) override {
        player.victoryPoints++;
        std::cout << "Player " << player.id << " used a Victory Point Card. Total Victory Points: " << player.victoryPoints << std::endl;
    }
};

// Board Class
class Board {
public:
    std::vector<Tile> tiles;

    Board() {
        tiles = {
            Tile(ResourceType::WOOD, 5), Tile(ResourceType::BRICK, 6),
            Tile(ResourceType::WOOL, 8), Tile(ResourceType::GRAIN, 3),
            Tile(ResourceType::IRON, 4), Tile(ResourceType::NONE, 7), // Desert
            Tile(ResourceType::WOOD, 9), Tile(ResourceType::BRICK, 10),
            Tile(ResourceType::WOOL, 11), Tile(ResourceType::GRAIN, 12)
        };
        // Example adjacency setup
        if (tiles.size() >= 4) { // Ensure there are enough tiles
            tiles[0].adjacentTiles = { &tiles[1], &tiles[2] };
            tiles[1].adjacentTiles = { &tiles[0], &tiles[3] };
        }
    }
};

// Game Class
class Game {
public:
    std::vector<Player> players;
    Board board;

    Game() : players({Player(1), Player(2), Player(3)}) {}

    void play() {
        std::srand(std::time(0));
        const int maxTurns = 10;
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

    void playerTurn(Player& player) {
        std::cout << "Player " << player.id << "'s turn." << std::endl;
        int diceRoll = rollDice();
        std::cout << "Dice roll: " << diceRoll << std::endl;
        gatherResources(player, diceRoll);
        if (player.canBuildSettlement(board.tiles)) {
            player.buildSettlement(board.tiles);
        }
    }

    int rollDice() {
        return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
    }

    void gatherResources(Player& player, int diceRoll) {
        for (const auto& tile : board.tiles) {
            if (tile.number == diceRoll) {
                player.addResource(tile.resourceType, 1);
                std::cout << "Player " << player.id << " receives 1 " << resourceToString(tile.resourceType) << std::endl;
            }
        }
    }

    std::string resourceToString(ResourceType resource) {
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
};

// Tests
void testPlayerCanBuildSettlement() {
    Player player(1); // Create a player for testing
    std::vector<Tile> tiles = {
        Tile(ResourceType::WOOD, 5), Tile(ResourceType::BRICK, 6),
        Tile(ResourceType::WOOL, 8), Tile(ResourceType::GRAIN, 3),
        Tile(ResourceType::IRON, 4), Tile(ResourceType::NONE, 7), // Desert
        Tile(ResourceType::WOOD, 9), Tile(ResourceType::BRICK, 10),
        Tile(ResourceType::WOOL, 11), Tile(ResourceType::GRAIN, 12)
    };

    // Simulate having enough resources to build a settlement
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    player.addResource(ResourceType::WOOL, 1);
    player.addResource(ResourceType::GRAIN, 1);

    assert(player.canBuildSettlement(tiles));
}

void testPlayerBuildSettlement() {
    Player player(1); // Create a player for testing
    std::vector<Tile> tiles = {
        Tile(ResourceType::WOOD, 5), Tile(ResourceType::BRICK, 6),
        Tile(ResourceType::WOOL, 8), Tile(ResourceType::GRAIN, 3),
        Tile(ResourceType::IRON, 4), Tile(ResourceType::NONE, 7), // Desert
        Tile(ResourceType::WOOD, 9), Tile(ResourceType::BRICK, 10),
        Tile(ResourceType::WOOL, 11), Tile(ResourceType::GRAIN, 12)
    };

    // Simulate having enough resources to build a settlement
    player.addResource(ResourceType::WOOD, 1);
    player.addResource(ResourceType::BRICK, 1);
    player.addResource(ResourceType::WOOL, 1);
    player.addResource(ResourceType::GRAIN, 1);

    // Build a settlement
    player.buildSettlement(tiles);

    // Assert that settlement is built and resources are deducted
    assert(player.victoryPoints == 3); // Assuming initial points were 2
    assert(player.resources[ResourceType::WOOD] == 0);
    assert(player.resources[ResourceType::BRICK] == 0);
    assert(player.resources[ResourceType::WOOL] == 0);
    assert(player.resources[ResourceType::GRAIN] == 0);
}

void testPlayerCannotBuildSettlement() {
    Player player(1); // Create a player for testing
    std::vector<Tile> tiles = {
        Tile(ResourceType::WOOD, 5), Tile(ResourceType::BRICK, 6),
        Tile(ResourceType::WOOL, 8), Tile(ResourceType::GRAIN, 3),
        Tile(ResourceType::IRON, 4), Tile(ResourceType::NONE, 7), // Desert
        Tile(ResourceType::WOOD, 9), Tile(ResourceType::BRICK, 10),
        Tile(ResourceType::WOOL, 11), Tile(ResourceType::GRAIN, 12)
    };

    // Simulate not having enough resources to build a settlement
    player.addResource(ResourceType::WOOD, 0);
    player.addResource(ResourceType::BRICK, 0);
    player.addResource(ResourceType::WOOL, 0);
    player.addResource(ResourceType::GRAIN, 0);

    assert(!player.canBuildSettlement(tiles));
}

void testGameInitialization() {
    Game game;

    // Assert that game initializes with 3 players
    assert(game.players.size() == 3);

    // Assert that the board has 10 tiles
    assert(game.board.tiles.size() == 10);
}

void runTests() {
    testPlayerCanBuildSettlement();
    testPlayerBuildSettlement();
    testPlayerCannotBuildSettlement();
    testGameInitialization();

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    Game game;
    game.play(); // Simulate the game
    runTests();  // Run the tests

    return 0;
}
