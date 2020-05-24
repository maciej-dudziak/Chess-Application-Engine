#pragma once
#include "Utils.h"
#include <vector>
#include <utility>

class Piece {
    private:
        Color pieceColor;
    public:
        Piece() = default;
        ~Piece() = default;
        Piece(Color color) : pieceColor(color) {};
        Color getColor() const { return pieceColor; }
        virtual std::string printPiece() const { return " "; }
        virtual std::vector<Moves> availableMoves() const { return std::vector<Moves>(); };
};

class King : public Piece {
    public:
        King(Color color) : Piece(color) {};
        std::string printPiece() const { return "K"; }
        std::vector<Moves> availableMoves() const {  return std::vector<Moves>{Moves::King} ; }
};

class Queen : public Piece {
    public:
        Queen(Color color) : Piece(color) {};
        std::string printPiece() const { return "Q"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Diagonals, Moves::Cardinals}; }
};

class Bishop : public Piece {
    public:
        Bishop(Color color) : Piece(color) {};
        std::string printPiece() const { return "B"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Diagonals}; }
};

class Knigth : public Piece {
    public:
        Knigth(Color color) : Piece(color) {};
        std::string printPiece() const { return "H"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Knigth}; }
};
class Rook : public Piece {
    public:
        Rook(Color color) : Piece(color) {};
        std::string printPiece() const { return "R"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Cardinals}; }
};

class Pawn : public Piece {
    public:
        Pawn(Color color) : Piece(color) {};
        std::string printPiece() const { return "O"; }
        std::vector<Moves> availableMoves() const { return std::vector<Moves>{Moves::Pawn}; }
};