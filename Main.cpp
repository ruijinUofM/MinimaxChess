#include "Board.h"

int main() {
    Board board;
    std::cout << board;
    std::vector<Board> boards = board.generate_valid_boards('b');
    for (int i = 0; i < boards.
        (); i++) {
        std::cout << boards[i];
    }
    return 0;
}