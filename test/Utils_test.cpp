#include "../../catch2/catch.hpp"
#include "../appcode/Utils.h"

TEST_CASE("3: Test the behaviour of the Utils classes and functions", "[multi-file:3]")
{
    Coordinate c1(4,2), c2(1,6);
    SECTION("Substraction")
    {
        REQUIRE(c1 - c2 == Coordinate(3,-4));
    }
    SECTION("Add-Assign")
    {
        REQUIRE( (c1+=c2) == Coordinate(5,8));
    }
    SECTION("Getters")
    {
        REQUIRE(c1.getRow() == 4);
        REQUIRE(c1.getColumn() == 2);
    }
    SECTION("Input Parser")
    {
        auto result = parseInput("H3,A6");
        REQUIRE(result.first == Coordinate(2,0));
        REQUIRE(result.second == Coordinate(5,7));
        // TODO: add case with outofbound input
        result = parseInput("Z9,V4");
        REQUIRE(result.first == Coordinate(-1,-1));
        REQUIRE(result.second == Coordinate(-1,-1));
    }
}