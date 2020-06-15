#include "../Game.h"
#include "../Utils.h"

using namespace std;
/***
 * Constructor for the whole game
 * Initiates the chessboard with all the Fields empty
 * Then place all the Pieces in starting positions 
 * */
Game::Game()
{
    /* Create a chessboard fields and color them */
    /*int column = 0, row = 0;
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
    }*/
    /* Initiate chessboard array */
    for (auto& elem : chessboard) elem = std::make_unique<Piece>();
    /* Initiate TURN variable to white */
    turn = Color::white;
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
    chessboard[0] = std::make_unique<Rook>(Color::white, Coordinate(0,0));
    chessboard[7] = std::make_unique<Rook>(Color::white, Coordinate(0,7));
    /* Knights */
    chessboard[1] = std::make_unique<Knigth>(Color::white, Coordinate(0,1));
    chessboard[6] = std::make_unique<Knigth>(Color::white, Coordinate(0,6));
    /* Bishops */
    chessboard[2] = std::make_unique<Bishop>(Color::white, Coordinate(0,2));
    chessboard[5] = std::make_unique<Bishop>(Color::white, Coordinate(0,5));
    /* Queen */
    chessboard[3] = std::make_unique<Queen>(Color::white, Coordinate(0,3));
    /* King */
    chessboard[4] = std::make_unique<King>(Color::white, Coordinate(0,4));
    /* Pawns */
    for (int i = 8; i < 16; i++)
    {
        chessboard[i] = std::make_unique<Pawn>(Color::white, Coordinate(1,i-8));
    }
    /* Black Pieces */
    /* Rooks */
    chessboard[56] = std::make_unique<Rook>(Color::black, Coordinate(7,0));
    chessboard[63] = std::make_unique<Rook>(Color::black, Coordinate(7,7));
    /* Knights */
    chessboard[57] = std::make_unique<Knigth>(Color::black, Coordinate(7,1));
    chessboard[62] = std::make_unique<Knigth>(Color::black, Coordinate(7,6));
    /* Bishops */
    chessboard[58] = std::make_unique<Bishop>(Color::black, Coordinate(7,2));
    chessboard[61] = std::make_unique<Bishop>(Color::black, Coordinate(7,5));
    /* Queen */
    chessboard[59] = std::make_unique<Queen>(Color::black, Coordinate(7,3));
    /* King */
    chessboard[60] = std::make_unique<King>(Color::black, Coordinate(7,4));
    /* Pawns */
    for (int i = 48; i < 56; i++)
    {
        chessboard[i] = std::make_unique<Pawn>(Color::black, Coordinate(7,i-48));
    }
}
/* Get the index if the field in the chessboard array */
int Game::getIndex(Coordinate coord) const
{
    return coord.getRow() * Game::boardsize + coord.getColumn();
}

void Game::printGame() const
{
    std::string message = (turn == Color::white ? "White" : "Black");
    std::cout << " Player Turn >>> " << message << " <<<" << std::endl;
    std::cout << "   H  G  F  E  D  C  B  A " << std::endl;
    std::cout << "  =========================" << std::endl;
    int column = 0, row = 0;
    std::string line("");
    for ( auto& field : chessboard )
    {
        line = line + "  " + field->printPiece();
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
    /* If the current and target are the same - return */
    if (currentCoord == targetCoord) return;
    int currentIdx = Game::getIndex(currentCoord);
    /* if the current field is not occupied - no Piece to move -> return from the function */
    if (!chessboard[currentIdx]->getOccupation()) return;
    /* Check the players turn */
    if (chessboard[currentIdx]->getPieceColor() != turn) return;
    /* check if we can move the piece to the target location */
    /* if the target location is occupied then we can play the move only if the piece colors are different */
    int targetIdx = Game::getIndex(targetCoord);
    if ( chessboard[targetIdx]->getOccupation() && chessboard[targetIdx]->getPieceColor() == chessboard[currentIdx]->getPieceColor() )
    {
        /* if we are inside this means that the target field is occupied by a friendly Piece so the move cannot be done */
        /* therefore it also includes situation when target==current*/
        return; //TODO: take care about the castle
    }
    /* Now we will obtain a normalised direction and investigate what moves are possibly intended */
    auto result = Game::analyseMoveType(currentCoord ,targetCoord);
    Coordinate direction = result.first;
    std::vector<Moves> possibleMoves = result.second;   /* Possible moves in that direction */
    /* Now we will investigate which moves can be played by the resident piece */
    auto availableMoves = chessboard[currentIdx]->availableMoves();
    /* Now find the common move type between the possible intended moves and moves of the resident piece */
    auto actualMove = find_first_of(begin(availableMoves), end(availableMoves), begin(possibleMoves), end(possibleMoves));
    /* If any common element exists - there can be only one */
    if (actualMove != end(availableMoves))
    {
        /* Variable to steer Pawn behaviour */
        bool inFirstRow = false;
        /* Additional consideration for the Pawn case*/
        if (*actualMove == Moves::Pawn)
        {
            Color pieceColor = chessboard[currentIdx]->getPieceColor();
            /* Check if the Pawn is in second row and can move by two fields */
            inFirstRow = Game::isPawnInSecondRow(pieceColor, currentCoord.getRow());
            /* Check the legality of the Pawn move */
            if (!isPawnMoveLegal(direction, pieceColor, chessboard[targetIdx]->getOccupation())) return;
        }
        /* Play a move: increment a CURRENT by DIRECTION and check on every step   */
        /* If the field on the way is occupied by any piece and therefore the move */
        /* Is not possible - for Knigth the DIRECTION has a value of the move so we*/
        /* Arrive at the target after first iteration                              */
        Coordinate temp = currentCoord;
        int tempIndex;
        do {
            /* Initiate temporary coord variable and calculate its chessboard index*/
            temp += direction;
            tempIndex = Game::getIndex(temp);
            /* If the Piece is a Pawn take care to limit its move to one field, or two when it is in his starting row */
            if (*actualMove == Moves::Pawn)
            {
                if (!inFirstRow) break;
                inFirstRow = false;
            }
            /* Iterate until the target coordinate is achieved or the move is blocked by the piece on its way */
        } while (temp != targetCoord && !chessboard[tempIndex]->getOccupation());
        /* If the target can be reached - execute the move */
        if ( temp == targetCoord)
        {
            /* Now if the target field is occupied - remove that Piece */
            /* Case of the friendly Piece at target location is handled at the beginning */
            if (chessboard[targetIdx]->getOccupation())
            {
                /* Remove the enemy's Piece */
                removedPieces.push_back(std::move(chessboard[targetIdx]));
            }
            /* Finalise the move by placing played Piece at the target's location */
            chessboard[targetIdx] = std::move(chessboard[currentIdx]);
            chessboard[currentIdx] = std::make_unique<Piece>();
            /* If the Pawn was played and reached the end of chessboard - allow replacing it */
            if (*actualMove == Moves::Pawn && (targetCoord.getRow()==0 || targetCoord.getRow()==7)) Game::replacePawn(targetIdx, targetCoord);
            /* Move has been played - change the turn */
            if (turn == Color::white) turn=Color::black; else turn=Color::white;
        }
    }
    return;
}

void Game::replacePawn(int targetIdx, Coordinate location)
{
    auto newPiece = Game::getPawnToReplace(location);
    /* Remove the Pawn */
    removedPieces.push_back(std::move(chessboard[targetIdx]));
    /* Place selected Piece */
    chessboard[targetIdx] = std::move(newPiece);
}

bool Game::isPawnMoveLegal(Coordinate direction, Color pawnColor, bool targetOccupation)
{
    /* White Pawn can only move downwards, Black one upwards */
    if (pawnColor == Color::white && direction.getRow()<0) return false;
    else if (pawnColor == Color::black && direction.getRow()>0) return false;
    /* Pawns can move to the side only when beating enemy Piece */
    if (direction.getColumn()!=0 && !targetOccupation) return false;
    return true;
}

bool Game::isPawnInSecondRow(Color pawnColor, int pawnRow)
{
    if (pawnColor == Color::white && pawnRow == 1) return true;
    else if (pawnColor == Color::black && pawnRow == 6) return true;
    else return false;
}

std::unique_ptr<Piece> Game::getPawnToReplace(Coordinate location){
    std::string message = (turn == Color::white ? "White" : "Black");
    std::string pieceName;
    std::unique_ptr<Piece> newPiece = std::make_unique<Piece>();
    std::cout << "Player: " << message << " - your Pawn reached the end of the board" << std::endl;
    std::cout << "Which Piece you want to replace it? Type its name in low case." << std::endl;
    std::cin >> pieceName;
    if (pieceName == "queen") newPiece = std::make_unique<Queen>(turn, location);
    else if (pieceName == "rook") newPiece = std::make_unique<Rook>(turn, location);
    else if (pieceName == "bishop") newPiece = std::make_unique<Bishop>(turn, location);
    else if (pieceName == "knight") newPiece = std::make_unique<Knigth>(turn, location);
    return std::move(newPiece);
}

std::pair<Coordinate, std::vector<Moves>> Game::analyseMoveType(Coordinate current ,Coordinate target)
{
    /* Calculate the difference between the actual coordinate and target */
    int move_row = target.getRow() - current.getRow();
    int move_col = target.getColumn() - current.getColumn();
    /* Now create a vector of possible MoveTypes in that direction */
    std::vector<Moves> moves;
    if(abs(move_row) == abs(move_col)){
        /* And normalise it - to express direction in terms of (-1,1) to allow iterative approach to move */
        move_row = move_row > 0 ? 1 : -1;
        move_col = move_col > 0 ? 1 : -1;
        moves.insert(begin(moves),{Moves::Diagonals,Moves::Pawn, Moves::King});
    } else if (move_row*move_col == 0) {
        /* And normalise it - to express direction in terms of (-1,0,1) to allow iterative approach to move */
        move_row = move_row > 0 ? 1 : (move_row < 0 ? -1 : 0);
        move_col = move_col > 0 ? 1 : (move_col < 0 ? -1 : 0);
        moves.insert(begin(moves),{Moves::Cardinals,Moves::Pawn});
    } else {
        moves.push_back(Moves::Knigth);
    }
    return std::pair<Coordinate, std::vector<Moves>>{Coordinate(move_row,move_col),moves};
}
/*
bool Game::isCheck()
{
    std::array<Coordinate, 16> directions{Coordinate(-1,-1), Coordinate(-1,0), Coordinate(-1,1),
        Coordinate(0,1), Coordinate(0,-1), Coordinate(1,1), Coordinate(1,0), Coordinate(1,-1),
        Coordinate(-2,-1), Coordinate(-2,1), Coordinate(2,-1), Coordinate(2,1),
        Coordinate(1,2), Coordinate(1,-2), Coordinate(-1,2), Coordinate(-1,-2)};
    
    for (auto& direction : directions)
    {

    }
}
*/