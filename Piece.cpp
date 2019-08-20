#include "Piece.h"

Piece::Piece() : x(0), y(0), color(WHITE), type(EMPTY) {}

//should assert these to be valid inputs
Piece::Piece(char color_in, char type_in, int x_in, int y_in) :
    x(x_in), y(y_in), color(color_in), type(type_in) {}


char Piece::get_color() const {
    return color;
}

char Piece::get_type() const {
    return type;
}

int Piece::get_x() const {
    return x;
}

int Piece::get_y() const {
    return y;
}

void Piece::set_color(char color_in) {
    color = color_in;
}

void Piece::set_type(char type_in) {
    type = type_in;
}

void Piece::set_x(int x_in) {
    x = x_in;
}
void Piece::set_y(int y_in) {
    y = y_in;
}

void Piece::set_coord(int x_in, int y_in) {
    x = x_in;
    y = y_in;
}


//my first time using switch syntax --doublecheck--
//disregards hitting other pieces or going out of bounds
std::vector<Move> Piece::get_moves(char color_in) {
    std::vector<Move> potential_moves;
    if (color != color_in) {
        return potential_moves;
    }
    switch (type) {
        case EMPTY: return potential_moves;
        case BISHOP: for (int i = -8; i < 9; i++) {
            if (i != 0) {
                potential_moves.push_back({ x, y, x + i, y + i });
                potential_moves.push_back({ x, y, x + i, y - i });
            }
        }
        case ROOK: for (int i = -8; i < 9; i++) {
            if (i != 0) {
                potential_moves.push_back({ x, y, x + i, y });
                potential_moves.push_back({ x, y, x, y + i });
            }
        }
        //we include the diagonals regardless of validity
        //not sure how to handle changing to queen yet
        case PAWN: if (color == BLACK) {
            potential_moves.push_back({ x, y, x + 1, y + 1 });
            potential_moves.push_back({ x, y, x, y + 1 });
            potential_moves.push_back({ x, y, x - 1, y + 1 });
        }
                   else {
            potential_moves.push_back({ x, y, x + 1, y - 1 });
            potential_moves.push_back({ x, y, x, y - 1 });
            potential_moves.push_back({ x, y, x - 1, y - 1 });
        }
        case KNIGHT: potential_moves.push_back({ x, y, x + 2, y + 1 });
            potential_moves.push_back({ x, y, x + 2, y - 1 });
            potential_moves.push_back({ x, y, x - 2, y + 1 });
            potential_moves.push_back({ x, y, x - 2, y - 1 });
            potential_moves.push_back({ x, y, x - 1, y + 2 });
            potential_moves.push_back({ x, y, x - 1, y - 2 });
            potential_moves.push_back({ x, y, x + 1, y + 2 });
            potential_moves.push_back({ x, y, x + 1, y - 2 });
        case QUEEN: for (int i = -8; i < 9; i++) {
            if (i != 0) {
                potential_moves.push_back({ x, y, x + i, y });
                potential_moves.push_back({ x, y, x, y + i });
                potential_moves.push_back({ x, y, x + i, y + i });
                potential_moves.push_back({ x, y, x + i, y - i });
            }
        }
        //ordered clockwise
        case KING:
            potential_moves.push_back({ x, y, x + 1, y });
            potential_moves.push_back({ x, y, x + 1, y + 1 });
            potential_moves.push_back({ x, y, x, y + 1 });
            potential_moves.push_back({ x, y, x - 1, y + 1 });
            potential_moves.push_back({ x, y, x - 1, y });
            potential_moves.push_back({ x, y, x - 1, y - 1 });
            potential_moves.push_back({ x, y, x, y - 1 });
            potential_moves.push_back({ x, y, x + 1, y - 1 });
    }
    return potential_moves;
}

std::ostream & operator<<(std::ostream &os, const Piece &piece) {
    os << piece.get_color() << piece.get_type();
}