#pragma once
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

class Coordinate{
    private:
        int row;
        int column;
    public:
        Coordinate();
        Coordinate(int _row, int _column) : row(_row), column(_column) {}
        Coordinate operator-(Coordinate c2);
        void operator+=(Coordinate c2);
        int getRow() const { return row; }
        int getColumn() const { return column; }
        std::pair<Coordinate, std::vector<Moves>> Coordinate::analyseMoveType(Coordinate target);
};

enum class Moves{
    Knigth,
    Diagonals,
    Cardinals,
    Pawn,
    King,
};

std::pair<Coordinate, Coordinate> parseInput(std::string input);