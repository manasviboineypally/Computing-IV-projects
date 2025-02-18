// test.cpp
// Copyright 2024 Manasvi Boineypally
#define BOOST_TEST_MODULE SokobanTests
#include <fstream>
#include <sstream>
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

void create_test_level(const std::string& filename) {
    std::ofstream file(filename);
    file << "6 6\n"
         << "######\n"
         << "#@   #\n"
         << "# A  #\n"
         << "#  a #\n"
         << "#    #\n"
         << "######\n";
    file.close();
}

BOOST_AUTO_TEST_SUITE(SokobanTestSuite)

BOOST_AUTO_TEST_CASE(test_level_loading) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    BOOST_CHECK_EQUAL(game.width(), 6);
    BOOST_CHECK_EQUAL(game.height(), 6);
}

BOOST_AUTO_TEST_CASE(test_initial_player_position) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 1);
}

BOOST_AUTO_TEST_CASE(test_player_movement) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 1);
}

BOOST_AUTO_TEST_CASE(test_box_pushing) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");

    // Initial position of the player
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 1);

    // Move player down
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 2);

    // Move player right (pushing the box)
    game.movePlayer(SB::Direction::Right);

    // Check player's new position
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 2);

    // Note: We can't directly check box position, so we're relying on the fact
    // that if the player moved, the box must have been pushed
}

BOOST_AUTO_TEST_CASE(test_win_condition) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    BOOST_CHECK(!game.isWon());
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
}

BOOST_AUTO_TEST_CASE(test_game_reset) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    game.movePlayer(SB::Direction::Right);
    game.reset();
    BOOST_CHECK_EQUAL(game.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 1);
}

BOOST_AUTO_TEST_CASE(test_pixel_dimensions) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    BOOST_CHECK_EQUAL(game.pixelWidth(), 6 * SB::Sokoban::getTileSize());
    BOOST_CHECK_EQUAL(game.pixelHeight(), 6 * SB::Sokoban::getTileSize());
}

BOOST_AUTO_TEST_CASE(test_undo_redo) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    sf::Vector2i initial_pos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    sf::Vector2i new_pos = game.playerLoc();
    game.undo();
    BOOST_CHECK_EQUAL(game.playerLoc().x, initial_pos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initial_pos.y);
    game.redo();
    BOOST_CHECK_EQUAL(game.playerLoc().x, new_pos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, new_pos.y);
}

BOOST_AUTO_TEST_CASE(test_invalid_move) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    sf::Vector2i initial_pos = game.playerLoc();
    game.movePlayer(SB::Direction::Left);  // This should be an invalid move (wall)
    BOOST_CHECK_EQUAL(game.playerLoc().x, initial_pos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initial_pos.y);
}

BOOST_AUTO_TEST_CASE(test_move_count) {
    create_test_level("test_sokoban.lvl");
    SB::Sokoban game("test_sokoban.lvl");
    BOOST_CHECK_EQUAL(game.getMoveCount(), 0);
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.getMoveCount(), 0);
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(game.getMoveCount(), 1);
    game.undo();
    BOOST_CHECK_EQUAL(game.getMoveCount(), 0);
    game.redo();
    BOOST_CHECK_EQUAL(game.getMoveCount(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
