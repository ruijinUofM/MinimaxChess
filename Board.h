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

    //Returns the piece at x, y
    Piece get(int x, int y) const;

    Piece get(Pos pos) const;

    void next_turn();

    int get_turn() const;

    char get_to_move() const;

    //changes x, y piece to empty and returns what was removed
    Piece remove(int x, int y);

    Piece remove(Pos pos);
    
    //sets p at x, y, returning what was at x, y before
    //also updates p's Pos member to the new coordinate
    Piece set(Piece p, int x, int y);

    Piece set(Piece p, Pos pos);

    //executes a move, updating the piece's position accordingly
    void execute_move(Move move);

    //checks for in bound move
    bool in_bounds(Move move) const;

    //returns a vector with all the in bound moves of each piece in the board
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