#ifndef HUNT__HUNT_H
#define HUNT__HUNT_H

#include "maze.h"

#define NAME_LEN       16
#define DIRECTION_UP    0
#define DIRECTION_LEFT  1
#define DIRECTION_DOWN  2
#define DIRECTION_RIGHT 3

typedef struct player {
  char name[NAME_LEN];
  int x;
  int y;
  int direction;
} player_t;

#endif
