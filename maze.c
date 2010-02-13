/* vim:set sw=2 ts=2 : */
#include <curses.h>
#include <stdlib.h>
#include "huntc.h"

extern player_t PLAYER;

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
  make_random_maze();
}

void redraw_maze(WINDOW* win) {
	int i,j;
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
	mvwaddch(win,MAZEHEIGHT,MAZEWIDTH, 'X' | COLOR_PAIR(COLOR_GOAL));
	mvwaddch(win,PLAYER.y + 1, PLAYER.x + 1, '@' | COLOR_PAIR(COLOR_PLAYER));
}	
