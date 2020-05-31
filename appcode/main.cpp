#include <iostream>
#include "Game.h"

int main()
{
    std::string input;
    /* Create a game */
    Game Chess = Game();
    Chess.printGame();
    std::cout << std::endl;
    while ( true )
    {
        std::cout << "Input next move in format: <A-H><1-8>,<A-H><1-8>" << std::endl;
        std::cin >> input;
        std::pair<Coordinate, Coordinate> moveCoords = parseInput(input);
        Chess.playMove(moveCoords.first, moveCoords.second);
        Chess.printGame();
    }
    return 0;
}
