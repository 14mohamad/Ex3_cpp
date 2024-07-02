#include "TestPlayer.cpp"
#include "TestTile.cpp"
#include "TestBoard.cpp"
#include "TestBuilding.cpp"
#include "TestTrade.cpp"
#include "TestResourceGathering.cpp"
int main() {
    testPlayer();
    testTile();
    testBoard();
    testResourceGathering();
    testBuilding();
    testTrading();
    
    std::cout << "All tests passed!" << std::endl;
    
    // Create a board and print it
    Board board;
    board.printBoard();
    
    return 0;
}
