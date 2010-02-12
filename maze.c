#include <curses.h>
#include "hunt.h"
void redraw_maze(WINDOW* win) {
	int i,j;
	for ( j = -1; j < MAZEHEIGHT + 1; j++ ) {
		mvwaddch(win,j+1,0,'#');
		for ( i = 0; i < MAZEWIDTH; i++ ) {
			if (j >= 0 && j < MAZEHEIGHT)
				waddch(win, MAZE[i][j].is_wall ?'#':' ');
			else
				waddch(win, '@');
		}
		waddch(win,'#');
	}
}	
