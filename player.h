#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <vector>
#include "ResourceType.h"
#include "Board.h" // To get the Tile class definition

class DevelopmentCard;

class Player {
public:
    int id;
    int victoryPoints;
    int knightsPlayed;
    std::map<ResourceType, int> resources;
    std::vector<DevelopmentCard*> developmentCards;
    
    // קונסטרוקטור המאתחל שחקן עם מזהה נתון וקובע משאבים ראשוניים ונקודות ניצחון
    Player(int playerId);

    // מוסיף משאבים למלאי של השחקן
    void addResource(ResourceType resource, int count);

    // בודק אם השחקן יכול לבנות יישוב על האריחים הנתונים על ידי הבטחה שיש אריחים לא מסודרים סמוכים
    bool canBuildSettlement(const std::vector<Tile>& tiles);

    // מנסה לבנות יישוב על האריחים הנתונים ומפחית את המשאבים הדרושים מהמלאי של השחקן
    void buildSettlement(std::vector<Tile>& tiles);

    // בודק אם לשחקן יש מספיק משאבים לבנות כביש
    bool canBuildRoad();

    // מנסה לבנות כביש ומפחית את המשאבים הדרושים מהמלאי של השחקן
    void buildRoad();

    // בודק אם לשחקן יש מספיק משאבים לבנות עיר
    bool canBuildCity();
    
    // מנסה לבנות עיר ומפחית את המשאבים הדרושים מהמלאי של השחקן
    void buildCity();
    
    // בודק אם לשחקן יש מספיק משאבים לבנות כרטיס פיתוח
    bool canBuildDevCard();
    
    // מוסיף כרטיס פיתוח למלאי של השחקן
    void addDevelopmentCard(DevelopmentCard* card);
    
    // משתמש בכרטיס פיתוח מהמלאי של השחקן באינדקס שצוין
    void useDevelopmentCard(int index, std::vector<Player*>& allPlayers);
    
    // מקל על משאבי מסחר בין שחקנים
    bool trade(Player& otherPlayer, ResourceType giveResource, ResourceType receiveResource, int amount);
    
    // ממירה סוג משאב לייצוג המחרוזת שלו
    std::string resourceToString(ResourceType resource);
};

#endif // PLAYER_H
