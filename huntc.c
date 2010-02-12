#include <stdlib.h>
#include <curses.h>

#include "hunt.h"
#include "huntc.h"

player_t PLAYER;

void init_hunt() {
  /* curses magic */
  atexit((void(*)(void))endwin);
  initscr();
  noecho();
  nodelay(NULL,true);

  /* intialize windows */
  status_win = newwin(STATUS_WIN_HEIGHT,STATUS_WIN_WIDTH,
                      STATUS_WIN_YSTART,STATUS_WIN_XSTART);
  maze_win   = newwin(MAZE_WIN_HEIGHT,MAZE_WIN_WIDTH,
                      MAZE_WIN_YSTART,MAZE_WIN_XSTART);

}

void setup_player() {

  /* get name */
  echo();
  mvaddstr(0,0,"Enter your codename: ");
  getnstr(PLAYER.name,NAME_LEN);
  noecho();

  /* set position */
  PLAYER.x = 1; /* begin in top left corner */
  PLAYER.y = 1; /*                          */
}

void show_commands() {
  mvaddstr(24,0,"Commands: q=quit");
}

void redraw_status(WINDOW* status_win) {
  mvwaddstr(status_win,0,0,"Name: ");
  mvwaddstr(status_win,6,0,PLAYER.name);
}

void play_game() {
  
  char ch;

  while ( redraw_maze(maze_win), ch = getch() ) {
    switch (ch) {
      case 'q':
        goto end_game;
      case '?':
        show_commands();
        break;
      default:
        mvaddstr(24,0,"Unknown command ");
        addch(ch);
    }
  }

end_game:
  return;
}

int main(int argc, const char* argv[]){
 
  init_hunt();
  setup_player();
  play_game();

  return 0;
}
