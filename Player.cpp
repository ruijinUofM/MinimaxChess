#include "Player.h"

Player::Player() :side(Piece::WHITE) {}

Player::Player(char side_in) : side(side_in) {
    assert(side_in == Piece::BLACK || side_in == Piece::WHITE);
}

char Player::get_side() const {
    return side;
}

void Player::set_side(char side_in) {
    assert(side_in == Piece::BLACK || side_in == Piece::WHITE);
    side = side_in;
}

class AI : public Player {

public:
    
    AI() :Player(Piece::BLACK) {}

    AI(char side_in)
        :Player(side_in) {}

    Move get_next_move(const Board board) const override {
        Move best_move;
        std::vector<Move> assorted_moves = board.generate_valid_moves(get_side());
        int best_score = -1000000;
        for (unsigned int i = 0; i < assorted_moves.size(); i++) {
            Board next_considered = board;
            next_considered.execute_move(assorted_moves[i]);
            int next_considered_score = minimax(next_considered, 3);
            if (best_score < next_considered_score) {
                best_score = next_considered_score;
                best_move = assorted_moves[i];
            }
        }
        return best_move;
    }

    /*Minimax predicts the score of the entered board assuming the players will follow a
    pattern based on the minimax algorithm. It predicts that the maximizing player 
    will always make the best move, and the nonmaximizing player will find the worst 
    possible move (for the maximizing player). Given this pattern, we search for 
    the board that we would arrive to after a certain number of turns and return the score.
    Really, the effectiveness of the algorithm depends on the score evaluation function.*/
    int minimax(const Board board, int depth) const {
        //return the score if we've reached the target depth, or if there are
        //no more turns
        if (depth == 0 || board.endgame()) {

            return board.score(get_side());
        }
        //if the next move is to be made by the maximizing player (the ai's side)
        //then we find the highest score of the next depth
        if (board.get_to_move() == get_side()) {
            int best_score = -1000000;
            std::vector<Board> valid_boards = 
                board.generate_valid_boards(board.get_to_move());
            for (unsigned int i = 0; i < valid_boards.size(); i++) {
                int board_true_score = minimax(valid_boards[i], depth - 1);
                if (best_score < board_true_score) {
                    best_score = board_true_score;
                }
            }
            return best_score;
        }
        //if the next move is to be made by the non_maximizing player (human's side)
        //then we find the lowest score of the next depth
        else {
            int worst_score = 1000000;
            std::vector<Board> valid_boards = 
                board.generate_valid_boards(board.get_to_move());
            for (unsigned int i = 0; i < valid_boards.size(); i++) {
                int board_true_score = minimax(valid_boards[i], depth - 1);
                if (worst_score < board_true_score) {
                    worst_score = board_true_score;
                }
            }
            return worst_score;
        }
        assert(false);
        return 0;

    }

};

class Human : public Player {

public:

    Human() : Player(Piece::WHITE) {}

    Human(char side_in) 
        :Player(side_in) {
        assert(side_in == Piece::BLACK || side_in == Piece::WHITE);
    }


    Move get_next_move(const Board board) const override {
        bool valid = false;
        Move move;
        while (!valid) {
            std::vector<Move> valid_moves = board.generate_valid_moves(get_side());
            Pos from;
            Pos to;
            std::cout << "Which piece would you like to move?" << std::endl;
            std::cout << "Enter in x coordinate: leftmost is 0, rightmost is 7"
                << std::endl;
            from.x = get_coord();

            std::cout << "Enter in y coordinate: topmost is 0, bottommost is 7"
                << std::endl;
            from.y = get_coord();

            std::cout << "Moving piece: " << board.get(from) << std::endl;

            std::cout << "Pick x coordinate to move to" << std::endl;
            to.x = get_coord();
            
            std::cout << "Pick y coordinate to move to" << std::endl;
            to.y = get_coord();

            move = { from, to };
            for (unsigned int i = 0; i < valid_moves.size(); i++) {
                if (move == valid_moves[i]) {
                    return move;
                }
            }
            std::cout << "Invalid move, try again" << std::endl;
        }
        return { {0, 0}, {0, 0} };
    }

    int get_coord() const {
        int coord = 8;
        while (coord > 7 || coord < 0) {
            while (std::cout << "Enter a number 0 to 7:" << std::endl &&
                !(std::cin >> coord)) {
                std::cout << "That's a not a number" << std::endl;
                std::cin.clear();
            }
        }
        return coord;
    }
};

Player *player_factory(bool human, char side) {
    if (human) {
        return new Human(side);
    }
    return new AI(side);
}