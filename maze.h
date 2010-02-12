#ifndef HUNT__MAZE_H
#define HUNT__MAZE_H

#include <curses.h>
#define MAZEHEIGHT  20
#define MAZEWIDTH   64

typedef struct cell {
	int is_wall : 1;
} cell_t;

cell_t MAZE[MAZEWIDTH][MAZEHEIGHT];
void redraw_maze(WINDOW* window);

#endif
