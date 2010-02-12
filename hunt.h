#define MAZEHEIGHT  20
#define MAZEWIDTH   64
#define NAME_LEN    16

typedef struct player {
  char name[NAME_LEN];
  int x;
  int y;
} player_t;

char MAZE[MAZEHEIGHT][MAZEWIDTH];
