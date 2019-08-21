#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <iostream>

/*
Rui Jin: This is the board header file to represent a chess board. Includes a 
piece struct
*/

class Board {
public:
    static constexpr const int BOARD_SIZE = 8;

    //Default constructor
    Board();

    Piece get(int x, int y);

    void next_turn();

    Piece remove(int x, int y);
    
    void execute_move(Move move);

    bool in_bounds(Move move);

    std::vector<Move> generate_valid_moves();

    bool endgame();

    bool checkmate(char color);

    bool check(char color);

    bool stalemate();

    int score();
    
    std::vector<Board> generate_valid_boards();

private:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    char to_move;
    int turn;
};

std::ostream & operator<<(std::ostream &os, const Board &b);

#endif BOARD_H