#include "../../catch2/catch.hpp"
#include "../appcode/Game.h"

TEST_CASE("5: The behaviour of the Game class and functions", "[multi-file:5]")
{
    Game game;
    SECTION("Check the basic results of default constructor")
    {
        REQUIRE(game.getTurn() == Color::white);
        Coordinate c(2,3);
        REQUIRE(game.getIndex(c)==19);
    }
    
}