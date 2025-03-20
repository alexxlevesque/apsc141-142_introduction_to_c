// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "actor.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width, height;


/**
 * This is the hardcoded map used for labs 1-3.
 * Once you implement load_map in lab 4 you should remove this map, as it cannot be used for the
 * final version of the project.
 * The map's dimensions are 9x9
 */
#define HARDCODED_WIDTH 9
#define HARDCODED_HEIGHT 9
char hardcoded_map[] = {
        GHOST, DOT, DOT, DOT, WALL, DOT, DOT, DOT, EMPTY,
        DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
        DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
        DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
        DOT, DOT, DOT, DOT, PLAYER, DOT, DOT, DOT, DOT,
        DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
        DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
        DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
        EMPTY, DOT, DOT, DOT, WALL, DOT, DOT, DOT, GHOST
};

// You are NOT allowed to add more global variables!
// The globals that are included in the starter code provide a convenient way to share information
// between the many functions that all need access to the same data, but all other data must be
// passed using function arguments.  If you add new globals, the autograder tests will fail to run
// and you will not receive a good mark.


// define a return code for a memory error
#define ERR_MEMORY 4

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PLAYER when no player is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    // This ensures that printf writes to the console immediately, instead of buffering.
    // If you remove this, you will not be able to rely on printf to work if your program crashes.
    setbuf(stdout, NULL);

    // set the map to point to the hardcoded map
    width = HARDCODED_WIDTH;
    height = HARDCODED_HEIGHT;
    // we don't actually have to use dot_map for lab1
    map = hardcoded_map;
    // allocate space for the dots
    dot_map = malloc(width * height);
    if (dot_map == NULL) {
        return ERR_MEMORY;
    }
    // copy dots into dot_map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == DOT) {
                dot_map[y * width + x] = DOT;
            } else {
                dot_map[y * width + x] = EMPTY;
            }
        }
    }

    // input holds the user input
    char input = 0;
    // we need the player position - we can hardcode it for now
    int player_x = 4, player_y = 4;

    int ghosts_y[] = {0,8};
    int ghosts_x[] = {0,8};

    // loop until we hit the end of input
    while (input != EOF) {
        // print the map
        print_map();

        // get a character - blocks until one is input
        input = getch();

        // move the player
        move_player(&player_y, &player_x, input);

        if (check_loss(player_y, player_x, ghosts_y, ghosts_x) == YOU_LOSE) {
            printf("YOU_LOSE!");
            break;
        }
        if (check_win() == YOU_WIN) {
            printf("YOU_WIN!");
            break;
        }
        print_map();
    }
    // free the dot_map
    free(dot_map);

    // You must return the correct error code from defines.h from main depending on what happened
    return NO_ERROR;
}
