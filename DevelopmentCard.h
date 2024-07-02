#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

#include "ResourceType.h"
#include <vector>

class Player;

class DevelopmentCard {
public:
    virtual void use(Player& player, std::vector<Player*>& allPlayers) = 0;
    virtual ~DevelopmentCard() = default;
};

class MonopolyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};

class RoadBuildingCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};

class YearOfPlentyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
    void use(Player& player, std::vector<Player*>& allPlayers, ResourceType resource1, ResourceType resource2);
};

class VictoryPointCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};
class KnightCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};



#endif // DEVELOPMENTCARD_H
