#include "DevelopmentCard.h"
#include "Player.h"
#include <iostream>


void YearOfPlentyCard::use(Player& player, std::vector<Player*>& allPlayers) {
 //it is a virtual Function
}

void RoadBuildingCard::use(Player& player, std::vector<Player*>& allPlayers) {
    player.buildRoad();
    player.buildRoad();
    std::cout << "Player " << player.id << " used a Road Building Card." << std::endl;
}

void MonopolyCard::use(Player& player, std::vector<Player*>& allPlayers) {
    ResourceType chosenResource = ResourceType::WOOD; // Simplified choice
    for (auto& p : allPlayers) {
        if (p->id != player.id) {
            player.resources[chosenResource] += p->resources[chosenResource];
            p->resources[chosenResource] = 0;
        }
    }
    std::cout << "Player " << player.id << " used a Monopoly Card." << std::endl;
}



void YearOfPlentyCard::use(Player& player, std::vector<Player*>& allPlayers, ResourceType resource1, ResourceType resource2) {
    player.resources[resource1]++;
    player.resources[resource2]++;
    std::cout << "Player " << player.id << " used a Year of Plenty Card." << std::endl;
}

void KnightCard::use(Player& player, std::vector<Player*>& allPlayers) {
    player.knightsPlayed++;
    if (player.knightsPlayed == 3) {
        player.victoryPoints += 2;
    }
    std::cout << "Player " << player.id << " used a Knight Card." << std::endl;
}

void VictoryPointCard::use(Player& player, std::vector<Player*>& allPlayers) {
    player.victoryPoints++;
    std::cout << "Player " << player.id << " used a Victory Point Card. Total Victory Points: " << player.victoryPoints << std::endl;
}
