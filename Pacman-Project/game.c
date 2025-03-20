// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win(void) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (dot_map[y * width + x] == DOT) {
                return KEEP_GOING;
            }
        }
    }
    return YOU_WIN;
}

int check_loss(int player_y, int player_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < 2; i++) {
        if (player_y == ghosts_y[i] && player_x == ghosts_x[i]) {
            return YOU_LOSE;  // Collision detected
        }
    }
    return KEEP_GOING;  // No collision
}
