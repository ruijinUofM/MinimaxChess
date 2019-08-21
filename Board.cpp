#include "Board.h"

Board::Board() {
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
        board[i][black_row].set_color(Piece::BLACK);
        board[i][white_pawn_row].set_type(Piece::PAWN);
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
    board[2][black_row].set_type(Piece::BISHOP);
    board[5][white_row].set_type(Piece::BISHOP);
    board[5][white_row].set_type(Piece::BISHOP);

    board[3][black_row].set_type(Piece::QUEEN);
    board[4][white_row].set_type(Piece::QUEEN);

    board[4][black_row].set_type(Piece::KING);
    board[3][white_row].set_type(Piece::KING);
}