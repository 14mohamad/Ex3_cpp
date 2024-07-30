#include "Player.h"
#include "DevelopmentCard.h"  // Include the full definition of DevelopmentCard

// קונסטרוקטור המאתחל שחקן עם מזהה נתון וקובע משאבים ראשוניים ונקודות ניצחון
Player::Player(int playerId) : id(playerId), victoryPoints(2), knightsPlayed(0) {
    resources = {
        {ResourceType::WOOD, 0},
        {ResourceType::BRICK, 0},
        {ResourceType::WOOL, 0},
        {ResourceType::GRAIN, 0},
        {ResourceType::IRON, 0}
    };
}
// מוסיף משאבים למלאי של השחקן
void Player::addResource(ResourceType resource, int count) {
    resources[resource] += count;
}

// בודק אם השחקן יכול לבנות יישוב על האריחים הנתונים על ידי הבטחה שיש אריחים לא מסודרים סמוכים
bool Player::canBuildSettlement(const std::vector<Tile>& tiles) {
    // יישם היגיון כדי לבדוק אם יש אריחים צמודים שבהם ניתן לבנות יישוב
    for (const auto& tile : tiles) {
        if (tile.settled == false) {
            // היגיון לדוגמה: בדוק אריחים סמוכים
            // למען הפשטות, נניח ש'מספר' מציין את המיקום ולאריחים הסמוכים יש מספרים עוקבים
            for (const auto& neighbor : tiles) {
                if (neighbor.number == tile.number + 1 || neighbor.number == tile.number - 1) {
                    if (neighbor.settled == false) {
                        return true;
                    }
                }
            }
        }
    }
    return false; // No adjacent tile found where a settlement can be built
}

// מנסה לבנות יישוב על האריחים הנתונים ומפחית את המשאבים הדרושים מהמלאי של השחקן
void Player::buildSettlement(std::vector<Tile>& tiles) {
    if (canBuildSettlement(tiles)) {
        for (auto& tile : tiles) {
            if (tile.settled == false) {
                for (auto& neighbor : tiles) {
                    if (neighbor.number == tile.number + 1 || neighbor.number == tile.number - 1) {
                        if (neighbor.settled == false) {
                            tile.settled = true;
                            resources[ResourceType::WOOD]--;
                            resources[ResourceType::BRICK]--;
                            resources[ResourceType::WOOL]--;
                            resources[ResourceType::GRAIN]--;
                            victoryPoints++;
                            std::cout << "Player " << id << " built a settlement on Tile " << tile.number << ". Total Victory Points: " << victoryPoints << std::endl;
                            return;
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "Cannot build a settlement here. No adjacent tiles available." << std::endl;
    }
}

// בודק אם לשחקן יש מספיק משאבים לבנות כביש
bool Player::canBuildRoad() {
    return resources[ResourceType::WOOD] >= 1 && resources[ResourceType::BRICK] >= 1;
}

// מנסה לבנות כביש ומפחית את המשאבים הדרושים מהמלאי של השחקן
void Player::buildRoad() {
    if (canBuildRoad()) {
        resources[ResourceType::WOOD]--;
        resources[ResourceType::BRICK]--;
        std::cout << "Player " << id << " built a road." << std::endl;
    } else {
        std::cout << "Player " << id << " cannot build a road." << std::endl;
    }
}

// בודק אם לשחקן יש מספיק משאבים לבנות עיר
bool Player::canBuildCity() {
    return resources[ResourceType::IRON] >= 3 && resources[ResourceType::GRAIN] >= 2;
}

// מנסה לבנות עיר ומפחית את המשאבים הדרושים מהמלאי של השחקן
void Player::buildCity() {
    if (canBuildCity()) {
        resources[ResourceType::IRON] -= 3;
        resources[ResourceType::GRAIN] -= 2;
        victoryPoints += 2;
        std::cout << "Player " << id << " built a city. Total Victory Points: " << victoryPoints << std::endl;
    } else {
        std::cout << "Player " << id << " cannot build a city." << std::endl;
    }
}

// בודק אם לשחקן יש מספיק משאבים לבנות כרטיס פיתוח
bool Player::canBuildDevCard() {
    return resources[ResourceType::IRON] >= 1 && resources[ResourceType::WOOL] >= 1 && resources[ResourceType::GRAIN] >= 1;
}

// מוסיף כרטיס פיתוח למלאי של השחקן
void Player::addDevelopmentCard(DevelopmentCard* card) {
    developmentCards.push_back(card);
}

// משתמש בכרטיס פיתוח מהמלאי של השחקן באינדקס שצוין
void Player::useDevelopmentCard(int index, std::vector<Player*>& allPlayers) {
    if (index < static_cast<int>(developmentCards.size())) {
        developmentCards[index]->use(*this, allPlayers);
        delete developmentCards[index];  // Assume one-time use cards, so delete after use
        developmentCards.erase(developmentCards.begin() + index);
    } else {
        std::cout << "Invalid card index." << std::endl;
    }
}

// מקל על משאבי מסחר בין שחקנים
bool Player::trade(Player& otherPlayer, ResourceType giveResource, ResourceType receiveResource, int amount) {
    std::cout << "Player " << id << " trading " << amount << " " << resourceToString(giveResource)
              << " for " << amount << " " << resourceToString(receiveResource) << " with Player " << otherPlayer.id << std::endl;

    if (resources[giveResource] >= amount && otherPlayer.resources[receiveResource] >= amount) {
        resources[giveResource] -= amount;
        otherPlayer.resources[giveResource] += amount;
        resources[receiveResource] += amount;
        otherPlayer.resources[receiveResource] -= amount;
        return true;
    }
    std::cout << "Trade failed - insufficient resources" << std::endl;
    return false;
}

// ממירה סוג משאב לייצוג המחרוזת שלו
std::string Player::resourceToString(ResourceType resource) {
    switch (resource) {
        case ResourceType::WOOD: return "Wood";
        case ResourceType::BRICK: return "Brick";
        case ResourceType::WOOL: return "Wool";
        case ResourceType::GRAIN: return "Grain";
        case ResourceType::IRON: return "Iron";
        case ResourceType::NONE: return "None";
        default: return "Unknown";
    }
}
