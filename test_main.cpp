#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

// Enum for Resource Types
enum class ResourceType {
    IRON,
    WOOD,
    BRICK,
    WOOL,
    GRAIN,
    NONE // For desert
};

// Player Class
class DevelopmentCard; // Forward declaration

class Player {
public:
    int id;
    int victoryPoints;
    std::map<ResourceType, int> resources;
    std::vector<DevelopmentCard*> developmentCards;

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

    bool canBuildSettlement() {
        return resources[ResourceType::WOOD] >= 1 &&
               resources[ResourceType::BRICK] >= 1 &&
               resources[ResourceType::WOOL] >= 1 &&
               resources[ResourceType::GRAIN] >= 1;
    }

    void buildSettlement() {
        if (canBuildSettlement()) {
            resources[ResourceType::WOOD]--;
            resources[ResourceType::BRICK]--;
            resources[ResourceType::WOOL]--;
            resources[ResourceType::GRAIN]--;
            victoryPoints++;
            std::cout << "Player " << id << " built a settlement. Total Victory Points: " << victoryPoints << std::endl;
        } else {
            std::cout << "Player " << id << " cannot build a settlement." << std::endl;
        }
    }

    bool canBuildRoad() {
        return resources[ResourceType::WOOD] >= 1 &&
               resources[ResourceType::BRICK] >= 1;
    }

    void buildRoad() {
        if (canBuildRoad()) {
            resources[ResourceType::WOOD]--;
            resources[ResourceType::BRICK]--;
            std::cout << "Player " << id << " built a road." << std::endl;
        } else {
            std::cout << "Player " << id << " cannot build a road." << std::endl;
        }
    }

    bool canBuildCity() {
        return resources[ResourceType::IRON] >= 3 &&
               resources[ResourceType::GRAIN] >= 2;
    }

    void buildCity() {
        if (canBuildCity()) {
            resources[ResourceType::IRON] -= 3;
            resources[ResourceType::GRAIN] -= 2;
            victoryPoints += 2;
            std::cout << "Player " << id << " built a city. Total Victory Points: " << victoryPoints << std::endl;
        } else {
            std::cout << "Player " << id << " cannot build a city." << std::endl;
        }
    }

    bool canBuildDevCard() {
        return resources[ResourceType::IRON] >= 1 &&
               resources[ResourceType::WOOL] >= 1 &&
               resources[ResourceType::GRAIN] >= 1;
    }

    void addDevelopmentCard(DevelopmentCard* card) {
        developmentCards.push_back(card);
    }

    void useDevelopmentCard(int index, std::vector<Player*>& players);
};

// DevelopmentCard Class
class DevelopmentCard {
public:
    virtual void use(Player& player, std::vector<Player*>& players) = 0;
    virtual ~DevelopmentCard() = default;
};

class ProgressCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        std::cout << "Player " << player.id << " used a Progress Card." << std::endl;
    }
};

class KnightCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        std::cout << "Player " << player.id << " used a Knight Card." << std::endl;
    }
};

class VictoryPointCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        player.victoryPoints++;
        std::cout << "Player " << player.id << " used a Victory Point Card. Total Victory Points: " << player.victoryPoints << std::endl;
    }
};

class RoadBuildingCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        std::cout << "Player " << player.id << " used a Road Building Card." << std::endl;
    }
};

class YearOfPlentyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        std::cout << "Player " << player.id << " used a Year of Plenty Card." << std::endl;
    }
};

class MonopolyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& players) override {
        std::cout << "Player " << player.id << " used a Monopoly Card." << std::endl;
    }
};

void Player::useDevelopmentCard(int index, std::vector<Player*>& players) {
    if (index < 0 || index >= static_cast<int>(developmentCards.size())) {
        std::cout << "Invalid development card index." << std::endl;
        return;
    }
    DevelopmentCard* card = developmentCards[index];
    card->use(*this, players);
    delete card;
    developmentCards.erase(developmentCards.begin() + index);
}

// Board Class
class Board {
public:
    std::vector<int> tiles;
};

// Game Class
class Game {
public:
    Game();
    void play();

private:
    std::vector<Player> players;
    Board board;

    void playerTurn(Player& player);
    int rollDice();
    void gatherResources(int diceRoll);
    std::string resourceToString(ResourceType resource);
    DevelopmentCard* drawDevelopmentCard();
};

Game::Game() {
    players = {Player(1), Player(2), Player(3)};
    board.tiles = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
}

void Game::play() {
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
        std::cout << "No one won after " << maxTurns << " turns per player." << std::endl;
    }
}

void Game::playerTurn(Player& player) {
    std::cout << "Player " << player.id << "'s turn." << std::endl;

    int diceRoll = rollDice();
    std::cout << "Dice roll: " << diceRoll << std::endl;

    gatherResources(diceRoll);

    if (player.canBuildSettlement()) {
        player.buildSettlement();
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
        for (const auto& tileNumber : board.tiles) {
            if (tileNumber == diceRoll) {
                player.addResource(ResourceType::WOOD, 1); // Assuming wood for simplicity
                std::cout << "Player " << player.id << " receives 1 " << resourceToString(ResourceType::WOOD) << std::endl;
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
    int cardType = (std::rand() % 5);
    switch (cardType) {
        case 0: return new KnightCard();
        case 1: return new VictoryPointCard();
        case 2: return new RoadBuildingCard();
        case 3: return new YearOfPlentyCard();
        case 4: return new MonopolyCard();
        default: return nullptr;
    }
}

// Main Function
int main() {
    Game game;
    game.play();
    return 0;
}
