#include "Board.h"

Board::Board() :to_move(Piece::WHITE) , turn(0) {
    int black_pawn_row = 1;
    int black_row = 0;
    int white_pawn_row = 6;
    int white_row = 7;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j].set_coord(i, j);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i][black_pawn_row].set_type(Piece::PAWN);
        board[i][black_pawn_row].set_color(Piece::BLACK);
        board[i][black_pawn_row].set_pawn_skip(true);
        board[i][black_row].set_color(Piece::BLACK);
        board[i][white_pawn_row].set_type(Piece::PAWN);
        board[i][white_pawn_row].set_pawn_skip(true);
    }
    board[0][black_row].set_type(Piece::ROOK);
    board[0][white_row].set_type(Piece::ROOK);
    board[7][black_row].set_type(Piece::ROOK);
    board[7][white_row].set_type(Piece::ROOK);

    board[1][black_row].set_type(Piece::KNIGHT);
    board[6][black_row].set_type(Piece::KNIGHT);
    board[1][white_row].set_type(Piece::KNIGHT);
    board[6][white_row].set_type(Piece::KNIGHT);

    board[2][black_row].set_type(Piece::BISHOP);
    board[5][black_row].set_type(Piece::BISHOP);
    board[2][white_row].set_type(Piece::BISHOP);
    board[5][white_row].set_type(Piece::BISHOP);

    board[3][black_row].set_type(Piece::QUEEN);
    board[4][white_row].set_type(Piece::QUEEN);

    board[4][black_row].set_type(Piece::KING);
    board[3][white_row].set_type(Piece::KING);
}

Piece Board::get(int x, int y) const {
    return board[x][y];
}

Piece Board::get(Pos pos) const {
    return board[pos.x][pos.y];
}

void Board::next_turn() {
    if (to_move == Piece::BLACK) {
        to_move = Piece::WHITE;
    }
    else {
        to_move = Piece::BLACK;
    }
    turn++;
}

int Board::get_turn() const {
    return turn;
}

char Board::get_to_move() const {
    return to_move;
}

Piece Board::remove(int x, int y) {
    Piece save = board[x][y];
    Piece p;
    p.set_coord(x, y);
    board[x][y] = p;
    return save;
}

Piece Board::remove(Pos pos) {
    return remove(pos.x, pos.y);
}

Piece Board::set(Piece p, int x, int y) {
    Piece save = remove(x, y);
    p.set_coord(x, y);
    board[x][y] = p;
    return save;
}

Piece Board::set(Piece p, Pos pos) {
    return set(p, pos.x, pos.y);
}

//does not check validity of move!
void Board::execute_move(Move move) {
    Piece p = remove(move.from);
    p.set_pawn_skip(false);
    set(p, move.to);

    next_turn();
}

bool Board::in_bounds(Move move) const {
    int from_x = move.from.x;
    int from_y = move.from.y;
    if (from_x >= BOARD_SIZE || from_x < 0 || from_y >= BOARD_SIZE || from_y < 0) {
        std::cout << "Something's wrong, location of piece out of bounds" << std::endl;
        return false;
    }

    int to_x = move.to.x;
    int to_y = move.to.y;
    if (to_x >= BOARD_SIZE || to_x < 0 || to_y >= BOARD_SIZE || to_y < 0) {
        return false;
    }
    return true;

}

std::vector<Pos> Board::generate_positions(char c) const {
    std::vector<Pos> positions;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].get_color() == c && 
                board[i][j].get_type() != Piece::EMPTY) {
                positions.push_back({ i, j });
            }
        }
    }
    return positions;
}

std::vector<Move> Board::generate_valid_moves(const char ally_char) const {
    std::vector<Pos> ally;
    std::vector<Pos> enemy;
    char enemy_char = Piece::WHITE;
    if (ally_char == Piece::WHITE) {
        enemy_char = Piece::BLACK;
    }
    ally = generate_positions(ally_char);
    enemy = generate_positions(enemy_char);

    std::vector<Move> valid_moves;
    std::vector<Move> upcoming_piece_moves;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece p = board[i][j];
            upcoming_piece_moves = p.get_moves(ally_char, enemy, ally);
            for (unsigned int k = 0; k < upcoming_piece_moves.size(); k++) {
                if (in_bounds(upcoming_piece_moves[k])) {
                    valid_moves.push_back(upcoming_piece_moves[k]);
                }
            }
        }
    }

    return valid_moves;
}

bool Board::endgame() const {
    return (checkmate(Piece::WHITE) || checkmate(Piece::BLACK) || stalemate());
}

Pos Board::find_king(char ally) const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].get_type() == Piece::KING &&
                board[i][j].get_color() == ally) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}

//generates all possible boards we could create by making a move
//if all of these end up in a check then we're in checkmate
bool Board::checkmate(char ally) const {
    std::vector<Board> checkmate_boards = generate_valid_boards(ally);
    for (unsigned int i = 0; i < checkmate_boards.size(); i++) {
        if (!checkmate_boards[i].check(ally)) {
            return false;
        }
    }
    return true;
}

bool Board::check(char ally) const {
    char enemy = Piece::WHITE;
    if (ally == Piece::WHITE) {
        enemy = Piece::BLACK;
    }
    Pos holy_pos = find_king(ally);

    std::vector<Move> enemy_moves = generate_valid_moves(enemy);

    for (unsigned int i = 0; i < enemy_moves.size(); i++) {
        if (enemy_moves[i].to == holy_pos) {
            return true;
        }
    }
    return false;
}

bool Board::stalemate() const {
    return (turn > 50);
}

int Board::score(char ally) const {
    char opp = Piece::BLACK;
    if (ally == opp) {
        opp = Piece::WHITE;
    }
    if (checkmate(ally) || check(ally)) {
        return -1000;
    }
    if (checkmate(opp)) {
        return 1000;
    }
    if (check(opp)) {
        return 100;
    }
    return 0;
}

//Doesn't care about going into a check/mate, that's just a really bad score
std::vector<Board> Board::generate_valid_boards(const char c) const {
    std::vector<Board> valid_boards;
    std::vector<Move> valid_moves = generate_valid_moves(c);
    for (unsigned int i = 0; i < valid_moves.size(); i++) {
        //Copy not reference
        Board next_board = *this;
        next_board.execute_move(valid_moves[i]);
        valid_boards.push_back(next_board);
    }
    return valid_boards;
}

std::ostream & operator<<(std::ostream &os, const Board &b) {
    os << std::endl << " -- -- -- -- -- -- -- -- " << std::endl;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            os << "|" << b.get(j, i);
        }
        os << "|" << std::endl << " -- -- -- -- -- -- -- -- " << std::endl;
    }
    
    return os;
}