void redraw_maze() {
	int i,j;
	for ( j = -1; j < MAZEHEIGHT + 1; j++ ) {
		mvaddch(0,j+1,'#');
		for ( i = 0; i < MAZEWIDTH; i++ ) {
			addch((MAZE[i][j].is_wall || j < 0 || j == MAZEHEIGHT) ?'#':' ');
		}
		addch('#');
	}
}	
