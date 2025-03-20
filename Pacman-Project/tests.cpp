// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "actor.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

// tests for is_wall

TEST_SUITE_END();

/* tests for actor.c */
TEST_SUITE_BEGIN("Actor tests");

// tests for sees_player

// tests for move_player
TEST_CASE("A test for move_player right") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, DOT, WALL};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {EMPTY, DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_player left") {
    int player_y = 0;
    int player_x = 2;
    char tiny_map[] = {WALL, DOT, PLAYER};
    map = tiny_map;
    height = 1;
    width = 3;
    char tiny_dot_map[] = {WALL, DOT, EMPTY};
    dot_map = tiny_dot_map;
    char direction = LEFT;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_player down") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, WALL,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, WALL,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = DOWN;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for move_player up") {
    int player_y = 2;
    int player_x = 0;
    char tiny_map[] = {WALL, DOT,
                       DOT, DOT,
                       PLAYER, DOT};
    map = tiny_map;
    height = 3;
    width = 2;
    char tiny_dot_map[] = {WALL, DOT,
                           DOT, DOT,
                           EMPTY, DOT};
    dot_map = tiny_dot_map;
    char direction = UP;
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("A test for invalid direction") {
    int player_y = 0;
    int player_x = 0;
    char tiny_map[] = {PLAYER, DOT,
                       DOT, WALL};
    map = tiny_map;
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    char direction = RIGHT;
    direction = 'Q';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'L';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
    direction = 'Z';
    CHECK((move_player(&player_y, &player_x, direction) == MOVED_INVALID_DIRECTION));
}

// tests for move_ghost

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("A test for check_win") {
    height = 2;
    width = 2;
    char tiny_dot_map[] = {EMPTY, DOT,
                           DOT, WALL};
    dot_map = tiny_dot_map;
    CHECK((check_win() == KEEP_GOING));

    // Reset map dimensions and dot_map for win condition
    height = 2;
    width = 2;
    char empty_tiny_dot_map[] = {EMPTY, EMPTY,
                                EMPTY, EMPTY}; 
    dot_map = empty_tiny_dot_map;
    CHECK((check_win() == YOU_WIN));
}

// test for check_loss

TEST_CASE("Player loses by hitting a ghost") {
    int player_y = 1;
    int player_x = 1;
    int ghosts_y[NUM_GHOSTS] = {1, 3};
    int ghosts_x[NUM_GHOSTS] = {1, 4};
    
    // Player at (1,1) collides with ghost at (1,1)
    CHECK(check_loss(player_y, player_x, ghosts_y, ghosts_x) == 1);
}

TEST_CASE("Player collides with a ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 4};
    int ghosts_x[NUM_GHOSTS] = {3, 5};

    CHECK(check_loss(2, 3, ghosts_y, ghosts_x) == 1);
}

TEST_CASE("Player does not collide with any ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 4};
    int ghosts_x[NUM_GHOSTS] = {3, 5};

    CHECK(check_loss(1, 1, ghosts_y, ghosts_x) == 0);
}

TEST_CASE("Player collides with another ghost") {
    int ghosts_y[NUM_GHOSTS] = {2, 6};
    int ghosts_x[NUM_GHOSTS] = {3, 7};

    CHECK(check_loss(6, 7, ghosts_y, ghosts_x) == 1);
}

TEST_SUITE_END();