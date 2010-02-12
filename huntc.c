/* vim:set sw=2 ts=2 : */
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
  PLAYER.x = 0; /* begin in top left corner */
  PLAYER.y = 0; /*                          */
}

void show_commands() {
  mvaddstr(24,0,"Commands: q=quit");
}

void redraw_status(WINDOW* status_win) {
  mvwaddstr(status_win,0,0,"Name: ");
  mvwaddstr(status_win,0,6,PLAYER.name);
}
void redraw() {
	redraw_maze(maze_win);
	redraw_status(status_win);
	wnoutrefresh(maze_win);
	wnoutrefresh(status_win);
	doupdate();
}

void play_game() {
  
  char ch;

  while (redraw(), ch = getch() ) {
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
