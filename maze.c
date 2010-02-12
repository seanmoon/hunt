#include <curses.h>
#include "hunt.h"
void redraw_maze() {
	int i,j;
	for ( j = -1; j < MAZEHEIGHT + 1; j++ ) {
		mvaddch(j+1,0,'#');
		for ( i = 0; i < MAZEWIDTH; i++ ) {
			addch((MAZE[i][j].is_wall || j < 0 || j == MAZEHEIGHT) ?'#':' ');
		}
		addch('#');
	}
}	
