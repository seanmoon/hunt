#ifndef HUNT__HUNT_H
#define HUNT__HUNT_H

#include "maze.h"

#define NAME_LEN      16

WINDOW* status_win;
WINDOW* maze_win;

typedef struct player {
  char name[NAME_LEN];
  int x;
  int y;
} player_t;

#endif
