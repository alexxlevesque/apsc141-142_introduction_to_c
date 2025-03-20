// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "actor.h"
#include "map.h"   // included for is_wall

extern char * map, * dot_map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int ghost_y, int ghost_x) {
    // check to see if the ghost is eating the player
    // check if neither the x nor y coordinate is the same as the player
    // if one of them is the same, check if the path in between is clear
    // if there's a wall in between, they can't see

    return SEES_NOTHING;
}


int move_player(int * y, int * x, char direction) {


    // calculate the new coordinates to use on success (store in local variables)

    // check if the new coordinates point outside the map
    // check if the new coordinates point to a wall
    int new_y = *y;
    int new_x = *x;

    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (direction != RIGHT && direction != LEFT && direction != UP && direction != DOWN){
        return MOVED_INVALID_DIRECTION;
    }

    if (direction == RIGHT){
        new_x++;
    }
    if (direction == LEFT){
        new_x--;
    }
    if (direction == UP){
        new_y--;
    }
    if (direction == DOWN){
        new_y++;
    }
    if(is_wall(new_y, new_x)) {
        return MOVED_WALL;
    }

    // remove player from the old position and replace with EMPTY
    // set PLAYER in the new position in map
    // set EMPTY in the new position in dot_map
    // update the x/y coordinate pointers
    map[*y*width + *x] = EMPTY;
    map[new_y*width + new_x] = PLAYER;
    *y = new_y;
    *x = new_x;

    dot_map[*y*width + *x] = EMPTY;
    return MOVED_OKAY;
}

int move_ghost(int * y, int * x, char direction) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wall
    // check if the new coordinates point outside the map (also a wall)

    // at this point, the move is known to be valid (OK direction and not a wall)
    // get the value from the old position in the dot_map (either EMPTY or DOT)
    // remove ghost from the old position and replace with what was in dot_map
    // set GHOST in the new position in map
    // update the x/y coordinate pointers

    return MOVED_OKAY;
}
