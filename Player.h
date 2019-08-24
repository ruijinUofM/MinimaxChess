#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"

class Player {
public:
    Player();
    Player(char side_in);
    char get_side() const;
    void set_side(char side_in);

    virtual Move get_next_move(const Board board) const = 0;
    virtual ~Player() {}
private:
    char side;
};


Player *player_factory(bool human, char side);

#endif
