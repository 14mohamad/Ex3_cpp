Here's the rewritten README for your Catan game project:

# Catan Game README

## Introduction

This project is a C++ implementation of a simplified version of the popular board game "Catan." The game is designed for multiple players who trade, build, and compete to be the first to reach 10 victory points. The implementation features various classes to represent the game board, players, tiles, and development cards.

## Class and Method Descriptions

### Board Class

**Header File:** `Board.h`  
**Source File:** `Board.cpp`

The `Board` class represents the game board consisting of 19 tiles.

#### Methods

- **Constructor: `Board()`**
  - Initializes the board with 19 predefined tiles representing different resources and numbers.
  
- **`void printBoard() const`**
  - Displays the layout of the board, including each tile's resource type and number.

### DevelopmentCard Class

**Header File:** `DevelopmentCard.h`  
**Source File:** `DevelopmentCard.cpp`

The `DevelopmentCard` class serves as an abstract base class for different types of development cards in the game.

#### Derived Classes and Their Methods

- **MonopolyCard**
  - **`void use(Player& player, std::vector<Player*>& allPlayers)`**
    - Allows the player to select a resource and take all of that resource from other players.

- **RoadBuildingCard**
  - **`void use(Player& player, std::vector<Player*>& allPlayers)`**
    - Enables the player to build two roads for free.

- **YearOfPlentyCard**
  - **`void use(Player& player, std::vector<Player*>& allPlayers)`**
    - (Empty implementation to fulfill pure virtual function requirement).
  - **`void use(Player& player, std::vector<Player*>& allPlayers, ResourceType resource1, ResourceType resource2)`**
    - Lets the player choose two resources to gain.

- **KnightCard**
  - **`void use(Player& player, std::vector<Player*>& allPlayers)`**
    - Allows the player to move the robber and potentially earn additional victory points.

- **VictoryPointCard**
  - **`void use(Player& player, std::vector<Player*>& allPlayers)`**
    - Inherits from DevelopmentCard and represents a card that grants a victory point to the player.

### Game Class

**Header File:** `Game.h`  
**Source File:** `Game.cpp`

The `Game` class handles the overall gameplay, including player turns, resource gathering, and determining the winner.

#### Methods

- **Constructor: `Game()`**
  - Sets up the game with three players.
  
- **`void play()`**
  - Manages the main game loop, allowing players to take turns until one reaches 10 victory points.
  
- **`void playerTurn(Player& player)`**
  - Handles the actions taken by a player during their turn.
  
- **`int rollDice()`**
  - Simulates rolling two six-sided dice.
  
- **`void gatherResources(int diceRoll)`**
  - Distributes resources to players based on the dice roll and the tiles' numbers.
  
- **`DevelopmentCard* drawDevelopmentCard()`**
  - Draws a random development card.

- **`std::string resourceToString(ResourceType resource)`**
  - Converts a resource type to its string representation.

### Player Class

**Header File:** `Player.h`  
**Source File:** `Player.cpp`

The Player class represents a player in the game.

#### Methods

- **`Constructor: Player(std::string name)`**
  - Initializes a player with a given name.

- **`void gatherResources(ResourceType resource, int amount)`**
  - Adds resources to the player's inventory.

- **`bool buildRoad()`**
  - Attempts to build a road, returning whether the player had enough resources to do so.

- **`bool buildSettlement()`**
  - Attempts to build a settlement, returning whether the player had enough resources to do so.

- **`bool buildCity()`**
  - Attempts to build a city, returning whether the player had enough resources to do so.

- **`bool buildDevelopmentCard()`**
  - Attempts to build a development card, returning whether the player had enough resources to build a development card.

- **`void addDevelopmentCard(DevelopmentCard* card)`**
  - Adds a development card to the player's inventory.

- **`void useDevelopmentCard(int index, std::vector<Player*>& allPlayers)`**
  - Uses a development card from the player's inventory.

- **`bool trade(Player& otherPlayer, ResourceType giveResource, ResourceType receiveResource, int amount)`**
  - Facilitates trading resources between players.

- **`std::string resourceToString(ResourceType resource)`**
  - Converts a resource type to its string representation.

### Tile Class


The Tile class represents a single tile on the game board, holding a resource type and a number.

#### Methods

- **Constructor: `Tile(ResourceType resource, int num)`**
  - Initializes a tile with a given resource type and number.
  
- **`std::string resourceToString() const`**
  - Converts the tile's resource type to its string representation.

## Running the Game

To run the game :

```sh
make catan
```

To run tests:

```sh
make test_main
```

## Conclusion

This Catan implementation offers a simplified yet functional version of the game, demonstrating key concepts of object-oriented programming and game mechanics. Potential future improvements could include more advanced AI for player actions, a graphical interface, and networked multiplayer support.