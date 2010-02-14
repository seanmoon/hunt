#ifndef HUNT__MAZE_H
#define HUNT__MAZE_H

#include <curses.h>
#include <glib.h>
#define MAZEHEIGHT  19
#define MAZEWIDTH   63

GSequence* physics_objects;

typedef struct cell {
	int is_wall : 1;
} cell_t;

typedef enum phys_object_type {
  PO_BULLET,
  MAX_PO_TYPE
} phys_object_type_t;

typedef struct physics_obj {
  phys_object_type_t type;
  int x;
  int y;
  int dx, dy;
  char display_char;
} physics_obj_t;

void new_bullet(int x, int y, int dx, int dy);
gboolean bullet_update(physics_obj_t *obj);
cell_t MAZE[MAZEWIDTH][MAZEHEIGHT];
void redraw_maze(WINDOW* window);
void init_maze();

#endif
