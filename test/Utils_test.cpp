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
}