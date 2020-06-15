#pragma once
#include "Utils.h"
#include <vector>
#include <utility>

class Piece {
    private:
        Color pieceColor;
        Coordinate location;
    public:
        Piece() = default;
        ~Piece() = default;
        Piece(Color color, Coordinate newLocation) : pieceColor(color), location(newLocation) {};
        Color getPieceColor() const { return pieceColor; }
        Coordinate getLocation () const { return location; }
        bool getOccupation() const { return printPiece() != " "; }
        void setLocation(Coordinate newLocation) { location = newLocation; }
        virtual std::string printPiece() const { return " "; }
        virtual std::vector<Moves> availableMoves() const { return std::vector<Moves>(); };
};

class King : public Piece {
    public:
        King(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "K"; }
        std::vector<Moves> availableMoves() const {  return std::vector<Moves>{Moves::King} ; }
};

class Queen : public Piece {
    public:
        Queen(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "Q"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Diagonals, Moves::Cardinals}; }
};

class Bishop : public Piece {
    public:
        Bishop(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "B"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Diagonals}; }
};

class Knigth : public Piece {
    public:
        Knigth(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "H"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Knigth}; }
};
class Rook : public Piece {
    public:
        Rook(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "R"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Cardinals}; }
};

class Pawn : public Piece {
    public:
        Pawn(Color color, Coordinate newLocation) : Piece(color, newLocation) {};
        std::string printPiece() const { return "O"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Pawn}; }
};