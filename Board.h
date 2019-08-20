#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>

/*
Rui Jin: This is the board header file to represent a chess board. Includes a 
piece struct
*/

class Board {
public:
    static constexpr const char* const PAWN = "P";
    static constexpr const char* const ROOK = "R";
    static constexpr const char* const KNIGHT = "N";
    static constexpr const char* const BISHOP= "B";
    static constexpr const char* const QUEEN = "Q";
    static constexpr const char* const KING = "K";
    static constexpr const char* const BISHOP_BLACK = "B";
    static constexpr const char BLACK = 'b';
    static constexpr const char WHITE = 'w';
    static constexpr const int BOARD_SIZE = 8;

    struct Piece {
        char side;
        std::string type;
        int x;
        int y;
    };


    //Default constructor
    Board();

    Piece get(int x, int y);

    Piece remove(int x, int y);
    
    void put(int x, int y, Piece p);

    bool in_bounds(int x, int y);

    bool empty_spot(int x, int y);

    bool intersect(int x, int y);

    bool endgame();

    bool checkmate(char side);

    bool check(char side);

    bool stalemate();

    int score();

private:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    char to_move;
    int turn;
};

std::ostream &os 

#endif BOARD_H