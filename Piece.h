#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
#include <cassert>


struct Move {
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

class Piece {
public:
    static constexpr const char PAWN = 'P';
    static constexpr const char ROOK = 'R';
    static constexpr const char KNIGHT = 'N';
    static constexpr const char BISHOP = 'B';
    static constexpr const char QUEEN = 'Q';
    static constexpr const char KING = 'K';
    static constexpr const char EMPTY = ' ';

    static constexpr const char BLACK = 'b';
    static constexpr const char WHITE = 'w';
    
    //sets it to empty piece, color white, type empty, 
    Piece();
    Piece(char color_in, char type_in, int x_in, int y_in);

    char get_color() const;
    char get_type() const;

    int get_x() const;
    int get_y() const;

    void set_color(char color_in);
    void set_type(char type_in);

    void set_x(int x_in);
    void set_y(int y_in);

    void set_coord(int x_in, int y_in);

    /*this will be painful, needs a big switch statemnt,
    the alternative might be to make a bunch of derived classes
    with dynamic polymorphism which also doesn't seem optimal
    this gives the potential moves of a piece given that it is 
    the right color, otherwise returns an empty vector*/
    std::vector<Move> get_moves(char color_in);

private:
    int x;
    int y;
    char color;
    char type;
};



std::ostream & operator<<(std::ostream &os, const Piece &piece);


#endif PIECE_H
