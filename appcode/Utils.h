#pragma once
#include <vector>
/* Translation of common A,B,C... indexes to the numbers */
enum class ChessboardColumns {
    H = 0,
    G = 1,
    F = 2,
    E = 3,
    D = 4,
    C = 5,
    B = 6,
    A = 7,
};

/* Definition of the chessboard and pieces colors */
enum class Color { black, white};

enum class Moves{
    Knigth,
    Diagonals,
    Cardinals,
    Pawn,
    King,
};

class Coordinate{
    private:
        int row;
        int column;
    public:
        Coordinate() = default;
        ~Coordinate() = default;
        Coordinate(int _row, int _column) : row(_row), column(_column) {}
        Coordinate operator-(const Coordinate& c2);
        Coordinate& operator+=(const Coordinate& c2);
        int getRow() const { return row; }
        int getColumn() const { return column; }

        friend inline bool operator==(const Coordinate& c1, const Coordinate& c2){ return (c2.row==c1.row && c2.column==c1.column); };
        friend inline bool operator!=(const Coordinate& c1, const Coordinate& c2){ return (c2.row!=c1.row || c2.column!=c1.column); };

};

std::pair<Coordinate, Coordinate> parseInput(std::string input);