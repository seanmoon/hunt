#define MAZEHEIGHT    20
#define MAZEWIDTH     64
#define MAZEXSTART     0
#define MAZEYSTART     0

#define STATUSHEIGHT  20
#define STATUSWIDTH   15
#define STATUSXSTART   0
#define STATUSYSTART  65

#define NAME_LEN      16

WINDOW* status_win;
WINDOW* maze_win;

typedef struct player {
  char name[NAME_LEN];
  int x;
  int y;
} player_t;

char MAZE[MAZEHEIGHT][MAZEWIDTH];
