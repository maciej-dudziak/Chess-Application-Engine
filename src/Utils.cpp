#include <utility>
#include <string>
#include "Utils.h"

Coordinate Coordinate::operator-(Coordinate c2)
{
    int rowDiff = row - c2.row;
    int columnDiff = column - c2.column;
    return Coordinate(rowDiff, columnDiff);
}

void Coordinate::operator+=(Coordinate c2)
{
    row = row + c2.row;
    column = column + c2.column;
}

std::pair<Coordinate, Coordinate> parseInput(std::string input)
{
    int currCol = abs(static_cast<int>(*begin(input)) - 72);
    int currRow = static_cast<int>(*(begin(input)+1)) - 49;
    int targetCol = abs(static_cast<int>(*(begin(input)+3)) - 72);
    int targetRow = static_cast<int>(*(begin(input)+4)) - 49;
    return std::pair<Coordinate, Coordinate>{Coordinate(currRow, currCol), Coordinate(targetRow, targetCol)};
}