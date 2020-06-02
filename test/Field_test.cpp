#include "../../catch2/catch.hpp"
#include "../appcode/Field.h"

TEST_CASE("4: Test the behaviour of the Field class and functions", "[multi-file:4]")
{
    Field field;
    REQUIRE(field.getOccupation() == false);
    SECTION("Color operation")
    {
        field.setColor(Color::black);
        REQUIRE(field.getColor() == Color::black);
    }
    SECTION("Occupation operation")
    {
        field.setOccupation(true);
        REQUIRE(field.getOccupation() == true);
    }
    SECTION("Piece operations")
    {
        field.setColor(Color::black);
        field.placePiece(std::make_unique<Rook>(Color::white));
        REQUIRE(field.getPieceColor() == Color::white);
        REQUIRE(field.availableMoves() == std::vector<Moves>{ Moves::Cardinals });
        REQUIRE(field.printField() == "bR");
    }
}