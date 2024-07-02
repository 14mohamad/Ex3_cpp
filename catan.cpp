#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
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
    std::vector<Tile*> adjacentTiles;

    Tile(ResourceType resource, int num) : resourceType(resource), number(num) {}

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
    std::map<ResourceType, int> resources;
    std::vector<Tile*> settlements;

    Player(int playerId) : id(playerId), victoryPoints(2) {
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
        tiles[0].adjacentTiles = { &tiles[1], &tiles[2] };
        tiles[1].adjacentTiles = { &tiles[0], &tiles[3] };
        // Add other tile adjacencies as necessary
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
        bool gameEnd = false;
        while (!gameEnd) {
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
        }
    }

    void playerTurn(Player& player) {
        std::cout << "Player " << player.id << "'s turn." << std::endl;
        int diceRoll = rollDice();
        std::cout << "Dice roll: " << diceRoll << std::endl;
        gatherResources(diceRoll);
        if (player.canBuildSettlement(board.tiles)) {
            player.buildSettlement(board.tiles);
        }
    }

    int rollDice() {
        return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
    }

    void gatherResources(int diceRoll) {
        for (auto& player : players) {
            for (const auto& tile : board.tiles) {
                if (tile.number == diceRoll) {
                    player.addResource(tile.resourceType, 1);
                    std::cout << "Player " << player.id << " receives 1 " << tile.resourceToString() << std::endl;
                }
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

int main() {
    Game game;
    game.play();
    return 0;
}
