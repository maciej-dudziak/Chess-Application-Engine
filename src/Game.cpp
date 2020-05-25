#include <array>
#include <iostream>
#include <memory>
#include <algorithm>
#include "Game.h"
#include "Utils.h"

using namespace std;
/***
 * Constructor for the whole game
 * Initiates the chessboard with all the Fields empty
 * Then place all the Pieces in starting positions 
 * */
Game::Game()
{
    /* Create a chessboard fields and color them */
    int column = 0, row = 0;
    for ( auto& field : chessboard )
    {
        if ( (row + column)%2 == 0)
        {
            field.setColor(Color::white);
        }
        else
        {
            field.setColor(Color::black);
        }
        row++;
        if ( row == 8 ){ row = 0; column++; }
    }
    /* Create pieces and place them */
    Game::placePieces();
    /* Create an empty vector of removedPieces */
    removedPieces = std::vector<std::unique_ptr<Piece>>();
}
/* Place the pieces in their starting positions */
void Game::placePieces()
{
    /* White Pieces */
    /* Rooks */
    chessboard[0].placePiece(std::move(std::make_unique<Rook>(Color::white)));
    chessboard[7].placePiece(std::move(std::make_unique<Rook>(Color::white)));
    /* Knights */
    chessboard[1].placePiece(std::move(std::make_unique<Knigth>(Color::white)));
    chessboard[6].placePiece(std::move(std::make_unique<Knigth>(Color::white)));
    /* Bishops */
    chessboard[2].placePiece(std::move(std::make_unique<Bishop>(Color::white)));
    chessboard[5].placePiece(std::move(std::make_unique<Bishop>(Color::white)));
    /* Queen */
    chessboard[3].placePiece(std::move(std::make_unique<Queen>(Color::white)));
    /* King */
    chessboard[4].placePiece(std::move(std::make_unique<King>(Color::white)));
    /* Pawns */
    for (int i = 8; i < 16; i++)
    {
        chessboard[i].placePiece(std::move(std::make_unique<Pawn>(Color::white)));
    }
    /* Black Pieces */
    /* Rooks */
    chessboard[56].placePiece(std::move(std::make_unique<Rook>(Color::black)));
    chessboard[63].placePiece(std::move(std::make_unique<Rook>(Color::black)));
    /* Knights */
    chessboard[57].placePiece(std::move(std::make_unique<Knigth>(Color::black)));
    chessboard[62].placePiece(std::move(std::make_unique<Knigth>(Color::black)));
    /* Bishops */
    chessboard[58].placePiece(std::move(std::make_unique<Bishop>(Color::black)));
    chessboard[61].placePiece(std::move(std::make_unique<Bishop>(Color::black)));
    /* Queen */
    chessboard[59].placePiece(std::move(std::make_unique<Queen>(Color::black)));
    /* King */
    chessboard[60].placePiece(std::move(std::make_unique<King>(Color::black)));
    /* Pawns */
    for (int i = 48; i < 56; i++)
    {
        chessboard[i].placePiece(std::move(std::make_unique<Pawn>(Color::black)));
    }
}
/* Get the index if the field in the chessboard array */
int Game::getIndex(Coordinate coord) const
{
    return (coord.getRow()) * Game::boardsize + coord.getColumn();
}

void Game::printGame() const
{
    std::cout << "      H     G     F     E     D     C     B     A " << std::endl;
    std::cout << "    ==============================================" << std::endl;
    int column = 0, row = 0;
    std::string line("");
    for ( auto& field : chessboard )
    {
        line = line + "    " + field.printField();
        column ++;
        if (column == 8)
        {
            column = 0; row++;
            std::cout << std::to_string(row) + line << std::endl;
            line = "";
        }
    }
}

void Game::playMove(Coordinate currentCoord, Coordinate targetCoord)
{
    int currentIdx = Game::getIndex(currentCoord);
    /* if the current field is not occupied - no Piece to move -> return from the function */
    if (!chessboard[currentIdx].getOccupation()) return;
    /* check if we can move the piece to the target location */
    /* if the target location is occupied then we can play the move only if the piece colors are different */
    int targetIdx = Game::getIndex(targetCoord);
    if ( chessboard[targetIdx].getOccupation() && chessboard[targetIdx].getPieceColor() == chessboard[currentIdx].getPieceColor() )
    {
        /* if we are inside this means that the target field is occupied by a friendly Piece so the move cannot be done */
        /* therefore it also includes situation when target==current*/
        return; //TODO: take care about the castle
    }
    /* Now we will obtain a normalised direction and investigate what moves are possibly intended */
    auto result = currentCoord.analyseMoveType(targetCoord);
    Coordinate direction = result.first;
    std::vector<Moves> possibleMoves = result.second;   /* Possible moves in that direction */
    /* Now we will investigate which moves can be played by the resident piece */
    auto availableMoves = chessboard[currentIdx].availableMoves();
    /* Now find the common move type between the possible intended moves and moves of the resident piece */
    auto actualMove = find_first_of(begin(availableMoves), end(availableMoves), begin(possibleMoves), end(possibleMoves));
    /* If any common element exists - there can be only one */
    if (actualMove != end(availableMoves))
    {
        /* Play a move: increment a CURRENT by DIRECTION and check on every step   */
        /* If the field on the way is occupied by any piece and therefore the move */
        /* Is not possible - for Kingth the DIRECTION has a value of the move so we*/
        /* Arrive at the target after first iteration                              */
        Coordinate temp = currentCoord;
        int tempIndex;
        do {
            /* Initiate temporary coord variable and calculate its chessboard index*/
            temp += direction;
            tempIndex = Game::getIndex(temp);
            /* Iterate until the target coordinate is achieved or the move is blocked by the piece on its way */
        } while (temp != targetCoord && !chessboard[tempIndex].getOccupation());
        /* If the target can be reached - execute the move */
        if ( temp == targetCoord)
        {
            /* Now if the target field is occupied - remove that Piece */
            /* Case of the friendly Piece at target location is handled at the beginning */
            if (chessboard[targetIdx].getOccupation())
            {
                /* Remove the enemy's Piece */
                removedPieces.push_back(chessboard[targetIdx].getPiece());
            }
            /* Finalise the move by placing played Piece at the target's location */
            chessboard[targetIdx].placePiece(chessboard[currentIdx].getPiece());
        }
    }
    // TODO: add the King's case - CHECK instead of beating the King
    // TODO: add Castle consideratiom
    // TODO: Pawn cases - starting move (2fields) and the diagonal move for beating
    // TODO: add the consideration it the Pawn reached the end of the board
    // TODO: Pawn case that it can move only in the one direction
    return;
}