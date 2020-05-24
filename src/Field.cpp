#include "Field.h"
#include "Utils.h"

void Field::setColor(Color newColor)
{
    fieldColor = newColor;
}

Color Field::getFieldColor()
{
    return fieldColor;
}

Color Field::getPieceColor()
{
    return piecePtr->getColor();
}

void Field::setOccupation(bool newOccupation)
{
    isOccupied = newOccupation;
}

bool Field::getOccupation()
{
    return isOccupied;
}

void Field::placePiece(std::unique_ptr<Piece> newPiece)
{
    piecePtr = std::move(newPiece);
    isOccupied = true;
}

std::string Field::printField() const
{
    if (fieldColor == Color::black)
    {
        return "b" + piecePtr->printPiece();
    }
    return "w" + piecePtr->printPiece();
}

std::vector<Moves> Field::availableMoves() const
{ 
    return piecePtr->availableMoves(); 
}

std::unique_ptr<Piece> Field::getPiece()
{
    isOccupied = false;
    auto temp = std::move(piecePtr);
    piecePtr = std::make_unique<Piece>();
    return std::move(temp);
}