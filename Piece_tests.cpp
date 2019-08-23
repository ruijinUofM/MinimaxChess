#include "Piece.h"
#include "unit_test_framework.h"

TEST(constructor) {
    std::vector<Move> empty_moveset;
    std::vector<Pos> empty_posset;
    Piece p;
    Piece q(Piece::BLACK, Piece::BISHOP, 4, 5);
    ASSERT_TRUE(q.get_color() == Piece::BLACK);
    ASSERT_TRUE(p.get_color() == Piece::WHITE);
    ASSERT_TRUE(q.get_type() == Piece::BISHOP);
    ASSERT_TRUE(p.get_type() == Piece::EMPTY);
    ASSERT_TRUE(q.get_x() == 4);
    ASSERT_TRUE(p.get_x() == 0);
    ASSERT_TRUE(q.get_y() == 5);
    ASSERT_TRUE(p.get_y() == 0);
    ASSERT_FALSE(p.get_pawn_skip());
    ASSERT_FALSE(q.get_pawn_skip());
    ASSERT_TRUE(p.get_moves(Piece::WHITE, empty_posset, empty_posset) == empty_moveset);
}

TEST(sets) {
    Piece p;
    ASSERT_TRUE(p.get_color() == Piece::WHITE);
    p.set_color(Piece::BLACK);
    ASSERT_TRUE(p.get_color() == Piece::BLACK);
    ASSERT_TRUE(p.get_type() == Piece::EMPTY);
    ASSERT_FALSE(p.get_pawn_skip());
    p.set_type(Piece::QUEEN);
    ASSERT_TRUE(p.get_type() == Piece::QUEEN);
    Pos pos = { 2, 3 };
    p.set_coord(pos);
    ASSERT_TRUE(p.get_x() == 2 && p.get_y() == 3);
    p.set_coord(7, 7);
    ASSERT_TRUE(p.get_x() == 7 && p.get_y() == 7);
    p.set_type(Piece::PAWN);
    p.set_pawn_skip(true);
    ASSERT_TRUE(p.get_pawn_skip());
}

TEST(hit_piece_add_if_ally) {
    Piece p;
    Pos pos_one = { 3, 1 };
    Pos pos_two = { 1, 7 };
    Pos pos_three = { 2, 5 };
    Pos pos_four = { 4, 5 };
    Pos pos_from = p.get_pos();
    
    Move move_two = { pos_from, pos_two };
    Move move_four = { pos_from, pos_four };

    std::vector<Pos> target;
    target.push_back({ 3, 1 });
    target.push_back({ 7, 6 });
    target.push_back({ 2, 5 });
    target.push_back(pos_from);

    std::vector<Move> correct_set;
    correct_set.push_back(move_two);
    correct_set.push_back(move_four);

    std::vector<Move> test_set;
    //basically a push_back function that checks for hit piece
    p.add_if_ally_valid(test_set, target, pos_one);
    p.add_if_ally_valid(test_set, target, pos_two);
    p.add_if_ally_valid(test_set, target, pos_three);
    p.add_if_ally_valid(test_set, target, pos_four);

    ASSERT_TRUE(p.hit_piece(pos_one, target));
    ASSERT_FALSE(p.hit_piece(pos_two, target));
    ASSERT_TRUE(p.hit_piece(pos_three, target));
    ASSERT_FALSE(p.hit_piece(pos_four, target));
    ASSERT_TRUE(test_set == correct_set);

}

TEST(directional_moves_right) {
    Piece p;
    std::vector<Pos> us;
    std::vector<Pos> opp;
    std::vector<Pos> empty;
    std::vector<Move> correct;
    std::vector<Move> test;
    Pos from = p.get_pos();
    us.push_back(from);
    correct.push_back({ from, {1, 0} });
    correct.push_back({ from, {2, 0} });
    correct.push_back({ from, {3, 0} });
    correct.push_back({ from, {4, 0} });
    
    us.push_back({ 5, 0 });
    opp.push_back({ 5, 0 });
    //test should stop at four because of us vector
    p.get_directional_moves(test, opp, us, true, false, false, false);
    ASSERT_TRUE(test == correct);
    
    us.clear();
    us.push_back({ 7, 0 });
    correct.push_back({ from, {5, 0} });
    test.clear();
    //test should stop at 5 (inclusive) because of opp vector
    p.get_directional_moves(test, opp, us, true, false, false, false);
    ASSERT_TRUE(test == correct);
    test.clear();

    correct.push_back({ from, {6, 0} });
    correct.push_back({ from, {7, 0} });
    p.get_directional_moves(test, empty, empty, true, false, false, false);
    ASSERT_TRUE(test == correct);
}

TEST(directional_moves_diag) {
    Piece p;
    std::vector<Pos> us;
    std::vector<Pos> opp;
    std::vector<Pos> empty;
    std::vector<Move> correct;
    std::vector<Move> test;
    p.set_x(7);
    p.set_y(7);
    Pos from = p.get_pos();
    ASSERT_TRUE(p.get_x() == 7);
    ASSERT_TRUE(p.get_y() == 7);

    us.push_back(from);
    correct.push_back({ from, {6, 6} });
    correct.push_back({ from, {5, 5} });
    correct.push_back({ from, {4, 4} });
    correct.push_back({ from, {3, 3} });

    us.push_back({ 2, 2 });
    opp.push_back({ 2, 2 });
    //test should stop at three because of us vector
    p.get_directional_moves(test, opp, us, false, true, false, true);
    ASSERT_TRUE(test == correct);

    us.clear();
    us.push_back({ 0, 0 });
    correct.push_back({ from, { 2, 2 } });
    test.clear();
    //test should stop at two (inclusive) because of opp vector
    p.get_directional_moves(test, opp, us, false, true, false, true);
    ASSERT_TRUE(test == correct);

    test.clear();
    correct.push_back({ from, {1, 1} });
    correct.push_back({ from, {0, 0} });
    p.get_directional_moves(test, empty, empty, false, true, false, true);
    ASSERT_TRUE(test == correct);
}

TEST(test_moves) {
    std::vector<Pos> us;
    std::vector<Pos> opp;
    std::vector<Pos> empty;
    std::vector<Move> correct;
    std::vector<Move> test;
    Piece p(Piece::WHITE, Piece::PAWN, 4, 4);
    Pos pos = p.get_pos();
    p.set_pawn_skip(true);

    correct.push_back({ pos, { 4, 3 } });
    correct.push_back({ pos, { 4, 2 } });
    test = p.get_moves('w', empty, empty);
    ASSERT_TRUE(test == correct);

    //no going forward or skipping if there's something in the way
    correct.clear();
    us.push_back({ 4, 3 });
    test = p.get_moves('w', empty, us);
    ASSERT_TRUE(test == correct);
    opp.push_back({ 4, 3 });
    test = p.get_moves('w', opp, empty);
    ASSERT_TRUE(test == correct);

    us.clear();
    opp.clear();
    correct.clear();
    p.set_pawn_skip(false);
    opp.push_back({ 3, 3 });
    opp.push_back({ 5, 3 });
    correct.push_back({ pos, { 4, 3 } });
    correct.push_back({ pos, { 3, 3 } });
    correct.push_back({ pos, { 5, 3 } });
    test = p.get_moves('w', opp, us);
    ASSERT_TRUE(test == correct);
    
    p.set_color(Piece::BLACK);
    correct.clear();
    us.clear();
    opp.clear();
    correct.push_back({ pos, { 4, 5 } });
    test = p.get_moves('b', opp, us);
    ASSERT_TRUE(test == correct);
}

TEST_MAIN()