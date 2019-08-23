#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"

class Player {
public:
    virtual Move get_next_move(const Board board) const = 0;

    virtual ~Player() {}
};




#endif
