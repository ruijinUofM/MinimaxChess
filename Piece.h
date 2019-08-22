#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
#include <cassert>


struct Move {
    Pos from;
    Pos to;
};

struct Pos {
    int x;
    int y;
    bool operator== (const Pos &rhs) const {
        return (x == rhs.x & y == rhs.y);
    }
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

    void set_coord(Pos pos);

    /*this will be painful, needs a big switch statemnt,
    the alternative might be to make a bunch of derived classes
    with dynamic polymorphism which also doesn't seem optimal
    this gives the potential moves of a piece given that it is
    the right color, otherwise returns an empty vector, this also disregards
    the king being checked or checkmated as a result of the move*/
    std::vector<Move> get_moves(char color_in, const std::vector<Pos> & opponent,
        const std::vector<Pos> & us);

    //checks if our potential position hits other pieces
    bool hit_piece(const Pos destination, const std::vector<Pos> & target);

    /*
    Bishops, Rooks, Queens can move multiple spots but can't skip over other
    pieces, this function returns all the positions they can go to in a certain
    direction, including the first opponent piece they hit, excluding the first
    teammate piece they hit
    */
    void get_directional_moves(std::vector<Move> & current_set,
        const std::vector<Pos> opponent, const std::vector<Pos> us,
        const bool x_right, const bool x_left, const bool y_down,
        const bool y_up);

    void add_if_ally_valid(std::vector<Move> & current_set,
        const std::vector<Pos> & us, const Pos considering);

private:
    Pos position;
    char color;
    char type;
};



std::ostream & operator<<(std::ostream &os, const Piece &piece);


#endif PIECE_H
