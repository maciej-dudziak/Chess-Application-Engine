#pragma once
#include <string>
#include <memory>
#include "Pieces.h"
#include "Utils.h"

class Field {
    private:
        bool                        isOccupied;
        Color                       fieldColor;
        std::unique_ptr<Piece>      piecePtr;
    public:
        Field() : isOccupied(false), piecePtr(std::make_unique<Piece>()) {};
        ~Field() = default;

        void setColor(Color newColor);
        void setOccupation(bool state);
        bool getOccupation();
        Color getFieldColor();
        Color getPieceColor();
        std::unique_ptr<Piece> getPiece();
        void placePiece(std::unique_ptr<Piece> newPiece);
        std::string printField() const;
        std::vector<Moves> availableMoves() const;
};