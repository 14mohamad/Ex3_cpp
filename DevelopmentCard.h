#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

#include "ResourceType.h"
#include <vector>

class Player;

// שיעור בסיס מופשט לכרטיסי פיתוח בשיטת שימוש וירטואלי טהור
class DevelopmentCard {
public:
    virtual void use(Player& player, std::vector<Player*>& allPlayers) = 0;
    virtual ~DevelopmentCard() = default;
};

// מיישם את שיטת השימוש כדי לקחת את כל המשאב הנבחר משחקנים אחרים DevelopmentCard נגזר מ
class MonopolyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};

// מיישם את שיטת השימוש כדי לאפשר לשחקן לבנות שני כבישים בחינם DevelopmentCard נגזר מ
class RoadBuildingCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};

// מיישם את שיטת השימוש כדי לאפשר לשחקן לבחור שני משאבים להרוויח DevelopmentCard נגזר מ
class YearOfPlentyCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
    void use(Player& player, std::vector<Player*>& allPlayers, ResourceType resource1, ResourceType resource2);
};

// מיישם את שיטת השימוש כדי להעניק לשחקן נקודת ניצחון נוספת DevelopmentCard נגזר מ
class VictoryPointCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};

// מיישם את שיטת השימוש כדי להזיז את השודד ולהעניק נקודות ניצחון נוספות אם השחקן שיחק שלושה קלפי אביר DevelopmentCard נגזר מ
class KnightCard : public DevelopmentCard {
public:
    void use(Player& player, std::vector<Player*>& allPlayers) override;
};



#endif // DEVELOPMENTCARD_H
