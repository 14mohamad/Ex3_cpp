// Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Board.h"

class Game {
public:
    Game();
    std::vector<Player> players;
    Board board;

    void play();
    void playerTurn(Player& player);
    int rollDice();
    void gatherResources(int diceRoll);
    std::string resourceToString(ResourceType resource);
    DevelopmentCard* drawDevelopmentCard();

    // Public accessors for testing
    std::vector<Player>& getPlayers() { return players; }
    Board& getBoard() { return board; }

private:
};

#endif // GAME_H
