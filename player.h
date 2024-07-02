#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <vector>
#include "ResourceType.h"
#include "Tile.h"

// Forward declare DevelopmentCard class
class DevelopmentCard;

class Player {
public:
    int id;
    int victoryPoints;
    int knightsPlayed;
    std::map<ResourceType, int> resources;
    std::vector<DevelopmentCard*> developmentCards;

    Player(int playerId);
    void addResource(ResourceType resource, int count);
    bool canBuildSettlement(const std::vector<Tile>& tiles);
    void buildSettlement(std::vector<Tile>& tiles);
    bool canBuildRoad();
    void buildRoad();
    bool canBuildCity();
    void buildCity();
    bool canBuildDevCard();
    void addDevelopmentCard(DevelopmentCard* card);
    void useDevelopmentCard(int index, std::vector<Player*>& allPlayers);
    bool trade(Player& otherPlayer, ResourceType giveResource, ResourceType receiveResource, int amount);
    std::string resourceToString(ResourceType resource);
};

#endif // PLAYER_H
