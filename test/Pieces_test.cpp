#include "../../catch2/catch.hpp"
#include "../appcode/Pieces.h"

TEST_CASE("2: Test the behaviour of the Pieces class", "[multi-file:2]")
{
    Piece *piece;
    SECTION("Base Piece Class")
    {
        piece = new Piece(Color::white, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::white);
        REQUIRE(piece->printPiece() == " ");
        REQUIRE(piece->availableMoves() == std::vector<Moves>());
        REQUIRE(piece->getOccupation() == false);
    }
    SECTION("Pawn Piece Class")
    {
        piece = new Pawn(Color::black, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::black);
        REQUIRE(piece->printPiece() == "O");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Pawn });
        REQUIRE(piece->getOccupation() == true);
    }
    SECTION("Knight Piece Class")
    {
        piece = new Knigth(Color::white, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::white);
        REQUIRE(piece->printPiece() == "H");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Knigth });
        REQUIRE(piece->getOccupation() == true);
    }
    SECTION("Bishop Piece Class")
    {
        piece = new Bishop(Color::white, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::white);
        REQUIRE(piece->printPiece() == "B");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Diagonals });
        REQUIRE(piece->getOccupation() == true);
    }
    SECTION("Rook Piece Class")
    {
        piece = new Rook(Color::black, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::black);
        REQUIRE(piece->printPiece() == "R");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Cardinals });
        REQUIRE(piece->getOccupation() == true);
    }
    SECTION("Queen Piece Class")
    {
        piece = new Queen(Color::white, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::white);
        REQUIRE(piece->printPiece() == "Q");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::Diagonals, Moves::Cardinals });
        REQUIRE(piece->getOccupation() == true);
    }
    SECTION("King Piece Class")
    {
        piece = new King(Color::black, Coordinate());
        REQUIRE(piece->getPieceColor() == Color::black);
        REQUIRE(piece->printPiece() == "K");
        REQUIRE(piece->availableMoves() == std::vector<Moves>{ Moves::King });
        REQUIRE(piece->getOccupation() == true);
    }
}