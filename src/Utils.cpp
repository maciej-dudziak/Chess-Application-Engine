#include <utility>
#include <string>
#include <vector>
#include "Utils.h"

Coordinate Coordinate::operator-(const Coordinate& c2)
{
    int rowDiff = row - c2.row;
    int columnDiff = column - c2.column;
    return Coordinate(rowDiff, columnDiff);
}

Coordinate& Coordinate::operator+=(const Coordinate& c2)
{
    row += c2.row;
    column += c2.column;
    return *this;
}

std::pair<Coordinate, Coordinate> parseInput(std::string input)
{
    int currCol = abs(static_cast<int>(*begin(input)) - 72);
    int currRow = static_cast<int>(*(begin(input)+1)) - 49;
    int targetCol = abs(static_cast<int>(*(begin(input)+3)) - 72);
    int targetRow = static_cast<int>(*(begin(input)+4)) - 49;
    return std::pair<Coordinate, Coordinate>{Coordinate(currRow, currCol), Coordinate(targetRow, targetCol)};
}


std::pair<Coordinate, std::vector<Moves>> Coordinate::analyseMoveType(Coordinate target)
{
    /* Calculate the difference between the actual coordinate and target */
    int move_row = target.row - row;
    int move_col = target.column - column;
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
