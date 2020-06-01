#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include "../Utils.h"

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
    /* Check the input out of bound */
    if (currCol > 7 || currRow > 7 || currRow < 0 || targetCol > 7 || targetRow > 7 || targetRow < 0)
    {
        return std::pair<Coordinate, Coordinate>{Coordinate(-1,-1), Coordinate(-1,-1)};
    }
    return std::pair<Coordinate, Coordinate>{Coordinate(currRow, currCol), Coordinate(targetRow, targetCol)};
}