#include <curses.h>
#include "hunt.h"
void redraw_maze(WINDOW* win) {
	int i,j;
	for ( j = -1; j < MAZEHEIGHT + 1; j++ ) {
		mvwaddch(win,j+1,0,'#');
		for ( i = 0; i < MAZEWIDTH; i++ ) {
			waddch(win, (j < 0 || j == MAZEHEIGHT || MAZE[i][j].is_wall) ?'#':' ');
		}
		waddch(win,'#');
	}
}	
