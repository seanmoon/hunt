#define MAZEHEIGHT  20
#define MAZEWIDTH   64

typedef struct cell {
	int is_wall : 1;
} cell_t;

cell_t MAZE[MAZEHEIGHT][MAZEWIDTH];
void redraw_maze(void);
