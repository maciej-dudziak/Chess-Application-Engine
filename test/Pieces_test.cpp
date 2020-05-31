#include "../../catch2/catch.hpp"
#include "../appcode/Pieces.h"

TEST_CASE("2: Test the behaviour of the Pieces class", "[multi-file:2]")
{
    Piece *piece;
    SECTION("Base Piece Class")
    {
        piece = new Piece(Color::white);
        REQUIRE(piece->getColor() == Color::white);
        REQUIRE(piece->printPiece() == " ");
        REQUIRE(piece->availableMoves() == std::vector<Moves>());
    }
    SECTION("Pawn Piece Class")
    {
        piece = new Pawn(Color::black);
        REQUIRE(piece->getColor() == Color::black);
        REQUIRE(piece->printPiece() == "O");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Pawn });
    }
    SECTION("Knight Piece Class")
    {
        piece = new Knigth(Color::white);
        REQUIRE(piece->getColor() == Color::white);
        REQUIRE(piece->printPiece() == "H");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Knigth });
    }
    SECTION("Bishop Piece Class")
    {
        piece = new Bishop(Color::white);
        REQUIRE(piece->getColor() == Color::white);
        REQUIRE(piece->printPiece() == "B");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Diagonals });
    }
    SECTION("Rook Piece Class")
    {
        piece = new Rook(Color::black);
        REQUIRE(piece->getColor() == Color::black);
        REQUIRE(piece->printPiece() == "R");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Cardinals });
    }
    SECTION("Queen Piece Class")
    {
        piece = new Queen(Color::white);
        REQUIRE(piece->getColor() == Color::white);
        REQUIRE(piece->printPiece() == "Q");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Diagonals, Moves::Cardinals });
    }
    SECTION("King Piece Class")
    {
        piece = new King(Color::black);
        REQUIRE(piece->getColor() == Color::black);
        REQUIRE(piece->printPiece() == "K");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::King });
    }
}