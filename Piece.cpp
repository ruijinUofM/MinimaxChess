#include "Piece.h"

Piece::Piece() : color(WHITE), type(EMPTY) {
    position.x = 0;
    position.y = 0;
}

//should assert these to be valid inputs
Piece::Piece(char color_in, char type_in, int x_in, int y_in) :
    color(color_in), type(type_in) {
    position.x = x_in;
    position.y = y_in;
}


char Piece::get_color() const {
    return color;
}

char Piece::get_type() const {
    return type;
}

int Piece::get_x() const {
    return position.x;
}

int Piece::get_y() const {
    return position.y;
}

void Piece::set_color(char color_in) {
    color = color_in;
}

void Piece::set_type(char type_in) {
    type = type_in;
}

void Piece::set_x(int x_in) {
    position.x = x_in;
}

void Piece::set_y(int y_in) {
    position.y = y_in;
}

void Piece::set_coord(int x_in, int y_in) {
    position.x = x_in;
    position.y = y_in;
}

void Piece::set_coord(Pos pos) {
    position = pos;
}

//my first time using switch syntax --doublecheck--
//checks for hitting other pieces but not going out of bounds.
//might want more helper functions to break this into smaller parts

std::vector<Move> Piece::get_moves(char color_in, const std::vector<Pos> & opponent,
    const std::vector<Pos> & us) {
    std::vector<Move> potential_moves;
    if (color != color_in) {
        return potential_moves;
    }


    switch (type) {
        case EMPTY: return potential_moves;

        case BISHOP: get_directional_moves(potential_moves,
            opponent, us, true, false, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, true);
            get_directional_moves(potential_moves, opponent,
                us, true, false, false, true);

        case ROOK: get_directional_moves(potential_moves,
            opponent, us, true, false, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, false, true, true);
            get_directional_moves(potential_moves, opponent,
                us, false, false, false, true);

        //we include the diagonals regardless of validity
        //pawns unique because they go up or down based on color
        //not sure how to handle changing to queen yet
        case PAWN: int to_x = position.x;
            int to_y = position.y;
            if (color == BLACK) {
                to_y++;
            }
            else {
                to_y--;
            }
            Pos forward = { to_x, to_y };
            Pos left = { to_x - 1, to_y };
            Pos right = { to_x + 1, to_y };
            add_if_ally_valid(potential_moves, us, forward);
            if (hit_piece(left, opponent)) {
                add_if_ally_valid(potential_moves, us, left);
            }
            if (hit_piece(right, opponent)) {
                add_if_ally_valid(potential_moves, us, right);
            }

        case KNIGHT: 
            int x = position.x;
            int y = position.y;
            add_if_ally_valid(potential_moves, us, { x + 2, y + 1 } );
            add_if_ally_valid(potential_moves, us, { x + 2, y - 1 } );
            add_if_ally_valid(potential_moves, us, { x - 2, y + 1 } );
            add_if_ally_valid(potential_moves, us, { x - 2, y - 1 } );
            add_if_ally_valid(potential_moves, us, { x - 1, y + 2 } );
            add_if_ally_valid(potential_moves, us, { x - 1, y - 2 } );
            add_if_ally_valid(potential_moves, us, { x + 1, y + 2 } );
            add_if_ally_valid(potential_moves, us, { x + 1, y - 2 } );

        case QUEEN: get_directional_moves(potential_moves,
            opponent, us, true, false, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, false, true, true);
            get_directional_moves(potential_moves, opponent,
                us, false, false, false, true);
            get_directional_moves(potential_moves,
                opponent, us, true, false, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, true);
            get_directional_moves(potential_moves, opponent,
                us, true, false, false, true);


        //ordered clockwise
        case KING:
            int x = position.x;
            int y = position.y;
            add_if_ally_valid(potential_moves, us, { x + 1, y });
            add_if_ally_valid(potential_moves, us, { x + 1, y + 1 });
            add_if_ally_valid(potential_moves, us, { x, y + 1 });
            add_if_ally_valid(potential_moves, us, { x - 1, y + 1 });
            add_if_ally_valid(potential_moves, us, { x - 1, y });
            add_if_ally_valid(potential_moves, us, { x - 1, y - 1 });
            add_if_ally_valid(potential_moves, us, { x, y + 1 });
            add_if_ally_valid(potential_moves, us, { x + 1, y - 1 });
    }
    return potential_moves;
}

bool Piece::hit_piece(const Pos destination, const std::vector<Pos> & target) {
    for (int i = 0; i < target.size(); i++) {
        if (destination == target[i]) {
            return true;
        }
    }
    return false;
}

void Piece::add_if_ally_valid(std::vector<Move> & current_set,
    const std::vector<Pos> & us, const Pos considering) {
    if (hit_piece(considering, us)) {
        current_set.push_back({ position, considering });
    }
}

void Piece::get_directional_moves(std::vector<Move> & current_set,
    const std::vector<Pos> opponent, const std::vector<Pos> us,
    const bool x_right, const bool x_left, const bool y_down, 
    const bool y_up) {
    for (int i = 1; i < 8; i++) {
        int to_x = position.x;
        int to_y = position.y;
        if (x_right) {
            to_x += i;
        }
        if (y_down) {
            to_y += i;
        }
        if (x_left) {
            to_x -= i;
        }
        if (y_up) {
            to_y -= i;
        }
        Pos to = { to_x, to_y };

        if (hit_piece(to, us)) {
            return;
        }
        //if we hit an opponent we return, but after only adding this move in
        current_set.push_back({ position, to });
        if (hit_piece(to, opponent)) {
            return;
        }
    }
}

std::ostream & operator<<(std::ostream &os, const Piece &piece) {
    if (piece.get_type() == Piece::EMPTY) {
        os << piece.get_type() << piece.get_type();
        return os;
    }
    os << piece.get_color() << piece.get_type();
    return os;
}