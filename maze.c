/* vim:set sw=2 ts=2 : */
#include <curses.h>
#include <stdlib.h>
#include <glib.h>
#include "huntc.h"
#include "maze.h"

extern player_t PLAYER;

void new_bullet(int x, int y, int dx, int dy) {
  physics_obj_t* bullet = g_new(physics_obj_t,1);
  bullet->x = x;
  bullet->y = y;
  bullet->dx = dx;
  bullet->dy = dy;

  bullet->display_char = '.';
  bullet->type = PO_BULLET;
  g_sequence_append(physics_objects,bullet);
}


gboolean bullet_update(physics_obj_t *obj) {
  obj->x += obj->dx;
  obj->y += obj->dy;
  
  if (MAZE[obj->x][obj->y].is_wall ) {
    MAZE[obj->x][obj->y].is_wall = 0;
    return FALSE; /* we are done with this obj */
  } 

  if (obj->x > MAZEWIDTH || obj->x < 0) 
    return FALSE;
  if (obj->y > MAZEHEIGHT || obj->y < 0)
    return FALSE;

  return TRUE;
}

void make_random_maze() {
  int x,y, dx, dy;

#define MW ((MAZEWIDTH + 1) / 2)
#define MH ((MAZEHEIGHT + 1) / 2)
	int filled[MW*MH][2];
	int pos = 0;
  for ( y = 0; y < MAZEHEIGHT; y++ ) {
    for ( x = 0; x < MAZEWIDTH; x++ ) {
      MAZE[x][y].is_wall = 1;
    }
  }
  MAZE[0][0].is_wall = 0;
	x = y = 0;

	filled[0][0] = 0;
	filled[0][1] = 0;
	pos = 1;

	int nfilled = MW * MH;
	nfilled--;
	
	int repos = 0;
	while (nfilled > 0) {
/*		PLAYER.x = x;
		PLAYER.y = y;	
		redraw_maze(stdscr);
		wnoutrefresh(stdscr);
		char outstr[80];
		snprintf(outstr, 80, "x:%d y:%d nf: %d pos: %d dx=%d dy=%d", x, y, nfilled, pos, dx, dy);
		mvaddstr(0,0,outstr);
		refresh();
		sleep(1);
		*/
		if (repos) {
			//do {
				int n = (int)(drand48() * pos);
				x = filled[n][0];
				y = filled[n][1];
				//x = (int)(drand48() * (MAZEWIDTH + 1) / 2) * 2;
				///y = (int)(drand48() * (MAZEHEIGHT + 1) / 2) * 2;
			//} while (MAZE[x][y].is_wall);
			repos = 0;
		}
		// bust a wall.

		int dir = (drand48() >= 0.5) ? 0 : 1;
		int dist = (drand48() >= 0.5) ? -1 : 1;

		dx = (dir == 0) ? 0 : dist;
		dy = (dir == 1) ? 0 : dist;

		// not in maze
		if (x + 2 * dx >= MAZEWIDTH ||
				x + 2 * dx < 0 ||
				y + 2 * dy >= MAZEHEIGHT ||
				y + 2 * dy < 0) {
			repos = 1;
			continue;
		}
		x += 2 * dx;
		y += 2 * dy;
		if (!MAZE[x][y].is_wall)
			repos = 1;
		else {
			MAZE[x-dx][y-dy].is_wall = 0;
			filled[pos][0] = x;
			filled[pos][1] = y;
			pos++;
			nfilled--;
			MAZE[x][y].is_wall = 0;
		}
	}

}

void init_maze() {
  physics_objects = g_sequence_new(NULL);
  make_random_maze();
}

void redraw_maze(WINDOW* win) {
	int i,j;
  GSequenceIter* it;

  /* redraw the walls */
	for ( j = -1; j < MAZEHEIGHT + 1; j++ ) {
		mvwaddch(win,j+1,0, ' ' | A_REVERSE | COLOR_PAIR(COLOR_MAZE));
		for ( i = 0; i < MAZEWIDTH; i++ ) {
			if (j >= 0 && j < MAZEHEIGHT) {
				waddch(win, ' ' |  (MAZE[i][j].is_wall ? A_REVERSE : 0) | COLOR_PAIR(COLOR_MAZE));
      }
			else {
				waddch(win, ' ' | A_REVERSE | COLOR_PAIR(COLOR_MAZE));
      }
		}
		waddch(win, ' ' | A_REVERSE | COLOR_PAIR(COLOR_MAZE));
	}
  
  /* draw physics objects */ 
  for (it  = g_sequence_get_begin_iter(physics_objects) ;
       !g_sequence_iter_is_end(it) ;
       it  = g_sequence_iter_next(it) ) {
    physics_obj_t *obj = g_sequence_get(it);
    switch (obj->type) {
      case PO_BULLET:
        if ( !bullet_update(obj) ) {
          g_sequence_remove(it);
          g_free(obj);
          continue;
        }
        break;
      default:
        g_warn_if_reached();
      }
    mvwaddch(win,obj->y+1,obj->x+1,obj->display_char | COLOR_PAIR(COLOR_POBJ));
  }

  /* draw game objects */ 
	mvwaddch(win,MAZEHEIGHT,MAZEWIDTH, 'X' | COLOR_PAIR(COLOR_GOAL));
	mvwaddch(win,PLAYER.y + 1, PLAYER.x + 1, '@' | COLOR_PAIR(COLOR_PLAYER));

  

}	
