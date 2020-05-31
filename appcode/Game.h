#pragma once
#include <array>
#include <utility>
#include "Utils.h"
#include "Pieces.h"
#include "Field.h"
/**
 *  class Game
 *  
 *  represents the chess game
 *  contains the declaration of the chessboard and the collection of the pieces
 *  
 *  Chessboard is represented as follows:
 *  #  H/0 G/1 F/2 E/3 D/4 C/5 B/6 A/7
 *  0   -   -   -   -   -   -   -   -
 *  1   -   -   -   -   -   -   -   -
 *  2   -   -   -   -   -   -   -   -
 *  3   -   -   -   -   -   -   -   -
 *  4   -   -   -   -   -   -   -   -
 *  5   -   -   -   -   -   -   -   -
 *  6   -   -   -   -   -   -   -   -
 *  7   -   -   -   -   -   -   -   -
 * 
 * With White Pieces on the top
 */
class Game
{
    private:
        /* Size of the chessboard edge */
        int const boardsize = 8;
        /**
         * Single dimensional array representing the chessboard;
         * the index will be obtained with the get_index() method 
         */
        std::array<Field, 64> chessboard;
        std::vector<std::unique_ptr<Piece>> removedPieces;
        Color turn;
    public:
        Game();
        void placePieces();
        void printGame() const;
        void playMove(Coordinate currentCoord ,Coordinate targetCoord);
        std::unique_ptr<Piece> replacePawn();
        int getIndex(Coordinate coord) const;
        std::pair<Coordinate, std::vector<Moves>> analyseMoveType(Coordinate current, Coordinate target);
};