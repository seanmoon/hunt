#define MAZEHEIGHT  20
#define MAZEWIDTH   64

typedef struct cell {
	int is_wall : 1;
	int player_no : 1; // player 0 is no player at all!
} cell_t;

cell_t MAZE[MAZEHEIGHT][MAZEWIDTH];
