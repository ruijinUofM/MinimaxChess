#include "Player.h"

char find_player_type();

int main() {
    Board board;
    std::vector<Player *> players;
    char human_type;
    human_type = find_player_type();
    players.push_back(player_factory(true, human_type));
    char ai_type = Piece::BLACK;
    if (human_type == ai_type) {
        ai_type = Piece::WHITE;
    }

    players.push_back(player_factory(false, ai_type));

    while (!board.endgame()) {
        std::cout << board;
        char turn = board.get_to_move();
        for (unsigned int i = 0; i < players.size(); i++) {
            if (players[i]->get_side() == turn) {
                board.execute_move(players[i]->get_next_move(board));
                i = 4;
            }
        }
    }
    return 0;
}

char find_player_type() {
    char side = ' ';
    std::cout << "Would you like to play (w)hite or (b)lack?" << std::endl;
    while (side != Piece::BLACK && side != Piece::WHITE) {
        std::cout << "Enter w or b:" << std::endl;
        std::cin >> side;
    }
    return side;
}