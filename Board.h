#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <iostream>
#include <cassert>

/*
Rui Jin: This is the board header file to represent a chess board. Includes a 
piece struct
*/

static constexpr const int BOARD_SIZE = 8;

class Board {
public:

    //Default constructor
    Board();

    Piece get(int x, int y) const;

    Piece get(Pos pos) const;

    void next_turn();

    Piece remove(int x, int y);

    Piece remove(Pos pos);
    
    Piece set(Piece p, int x, int y);

    Piece set(Piece p, Pos pos);

    void execute_move(Move move);

    bool in_bounds(Move move) const;

    std::vector<Move> generate_valid_moves(const char ally_char) const;

    bool endgame() const;

    bool checkmate(char ally) const;

    bool check(char ally) const;

    bool stalemate() const;

    int score(char ally) const;
    
    std::vector<Board> generate_valid_boards(const char c) const;

    std::vector<Pos> generate_positions(char c) const;

    Pos find_king(char ally) const;

private:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    char to_move;
    int turn;
};

std::ostream & operator<<(std::ostream &os, const Board &b);

#endif