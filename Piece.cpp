#include "Piece.h"

Piece::Piece() : color(WHITE), type(EMPTY), pawn_skip(false) {
    position.x = 0;
    position.y = 0;
    assert_valid();
}

//should assert these to be valid inputs
Piece::Piece(char color_in, char type_in, int x_in, int y_in) :
    color(color_in), type(type_in), pawn_skip(false) {
    position.x = x_in;
    position.y = y_in;
    assert_valid();
}


void Piece::assert_valid() const {
    assert(color == BLACK || color == WHITE);
    assert(type == EMPTY || type == PAWN || type == KING || type == QUEEN
        || type == ROOK || type == KNIGHT || type == BISHOP);
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

Pos Piece::get_pos() const {
    return position;
}

void Piece::set_color(const char color_in) {
    assert(color_in == BLACK || color_in == WHITE);
    color = color_in;
}

void Piece::set_type(const char type_in) {
    assert(type_in == EMPTY || type_in == PAWN || type_in == ROOK ||
        type_in == KNIGHT || type_in == BISHOP || type_in == QUEEN ||
        type_in == KING);
    type = type_in;
}

void Piece::set_x(const int x_in) {
    assert(x_in < 8 && x_in >= 0);
    position.x = x_in;
}

void Piece::set_y(const int y_in) {
    assert(y_in < 8 && y_in >= 0);
    position.y = y_in;
}

void Piece::set_coord(const int x_in, const int y_in) {
    assert(x_in < 8 && x_in >= 0);
    assert(y_in < 8 && y_in >= 0);
    position.x = x_in;
    position.y = y_in;
}

void Piece::set_coord(const Pos pos) {
    assert(pos.x < 8 && pos.x >= 0);
    assert(pos.y < 8 && pos.y >= 0);
    position = pos;
}

void Piece::set_pawn_skip(const bool skip) {
    if (skip) {
        assert(type == PAWN);
    }
    pawn_skip = skip;
}

bool Piece::get_pawn_skip() const {
    return pawn_skip;
}

//my first time using switch syntax --doublecheck--
//checks for hitting other pieces but not going out of bounds.
//might want more helper functions to break this into smaller parts

std::vector<Move> Piece::get_moves(const char color_in, const std::vector<Pos> & opponent,
    const std::vector<Pos> & us) const {
    std::vector<Move> potential_moves;
    if (color != color_in) {
        return potential_moves;
    }

    int x = position.x;
    int y = position.y;

    switch (type) {
        case EMPTY: {
            return potential_moves;
        }
                    break;
        case BISHOP: {
            get_directional_moves(potential_moves,
                opponent, us, true, false, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, true);
            get_directional_moves(potential_moves, opponent,
                us, true, false, false, true);
        }
                     break;
        case ROOK: {
            get_directional_moves(potential_moves,
                opponent, us, true, false, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, false, true, false);
            get_directional_moves(potential_moves, opponent,
                us, false, false, false, true);
        }
                   break;
            //we include the diagonals regardless of validity
            //pawns unique because they go up or down based on color
            //not sure how to handle changing to queen yet
        case PAWN: {
            int to_x = x;
            int to_y = y;
            int skip_y;
            if (color == BLACK) {
                to_y++;
                skip_y = to_y + 1;
            }
            else {
                to_y--;
                skip_y = to_y - 1;
            }
            Pos skip = { to_x, skip_y };
            Pos forward = { to_x, to_y };
            Pos left = { to_x - 1, to_y };
            Pos right = { to_x + 1, to_y };
            /*can only go forward if we don't hit anything
            can only skip if pawn skip is true and we can go forward
            AND we don't hit anything*/
            if (!hit_piece(forward, opponent) &&
                !hit_piece(forward, us)) {
                add_if_ally_valid(potential_moves, us, forward);
                if (pawn_skip) {
                    if (!hit_piece(skip, opponent)) {
                        add_if_ally_valid(potential_moves, us, skip);
                    }
                }
            }
            if (hit_piece(left, opponent)) {
                add_if_ally_valid(potential_moves, us, left);
            }
            if (hit_piece(right, opponent)) {
                add_if_ally_valid(potential_moves, us, right);
            }
        }
                   break;

        case KNIGHT: {
            add_if_ally_valid(potential_moves, us, { x + 2, y + 1 });
            add_if_ally_valid(potential_moves, us, { x + 2, y - 1 });
            add_if_ally_valid(potential_moves, us, { x - 2, y + 1 });
            add_if_ally_valid(potential_moves, us, { x - 2, y - 1 });
            add_if_ally_valid(potential_moves, us, { x - 1, y + 2 });
            add_if_ally_valid(potential_moves, us, { x - 1, y - 2 });
            add_if_ally_valid(potential_moves, us, { x + 1, y + 2 });
            add_if_ally_valid(potential_moves, us, { x + 1, y - 2 });
        }
                     break;

        case QUEEN: {
            get_directional_moves(potential_moves,
                opponent, us, true, false, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, true, false, false);
            get_directional_moves(potential_moves, opponent,
                us, false, false, true, false);
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
        }
                    break;

            //ordered clockwise
        case KING: {

            add_if_ally_valid(potential_moves, us, { x + 1, y });
            add_if_ally_valid(potential_moves, us, { x + 1, y + 1 });
            add_if_ally_valid(potential_moves, us, { x, y + 1 });
            add_if_ally_valid(potential_moves, us, { x - 1, y + 1 });
            add_if_ally_valid(potential_moves, us, { x - 1, y });
            add_if_ally_valid(potential_moves, us, { x - 1, y - 1 });
            add_if_ally_valid(potential_moves, us, { x, y + 1 });
            add_if_ally_valid(potential_moves, us, { x + 1, y - 1 });
        }
    }
    return potential_moves;
}

bool Piece::hit_piece(const Pos destination, const std::vector<Pos> & target) const {
    for (unsigned int i = 0; i < target.size(); i++) {
        if (destination == target[i]) {
            return true;
        }
    }
    return false;
}

void Piece::add_if_ally_valid(std::vector<Move> & current_set,
    const std::vector<Pos> & us, const Pos considering) const {
    if (!hit_piece(considering, us)) {
        current_set.push_back({ position, considering });
    }
}

void Piece::get_directional_moves(std::vector<Move> & current_set,
    const std::vector<Pos> opponent, const std::vector<Pos> us,
    const bool x_right, const bool x_left, const bool y_down, 
    const bool y_up) const {
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

bool Piece::operator==(const Piece &rhs) const {
    return (position == rhs.position && color == rhs.color
        && type == rhs.type && pawn_skip == rhs.pawn_skip);
}


std::ostream & operator<<(std::ostream &os, const Piece &piece) {
    if (piece.get_type() == Piece::EMPTY) {
        os << piece.get_type() << piece.get_type();
        return os;
    }
    os << piece.get_color() << piece.get_type();
    return os;
}

std::ostream & operator<<(std::ostream &os, const Pos &pos) {
    os << pos.x << ", " << pos.y;
    return os;
}

std::ostream & operator<<(std::ostream &os, const Move &move) {
    os << "From: " << move.from << std::endl;
    os << "To: " << move.to << std::endl;
    return os;
}