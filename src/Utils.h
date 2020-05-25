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
        inline bool operator==(const Coordinate& c1){ return (row==c1.row && column==c1.column); };
        inline bool operator!=(const Coordinate& c1){ return (row!=c1.row || column!=c1.column); };
        int getRow() const { return row; }
        int getColumn() const { return column; }
        std::pair<Coordinate, std::vector<Moves>> analyseMoveType(Coordinate target);
};

std::pair<Coordinate, Coordinate> parseInput(std::string input);