#include <stdlib.h>
#include <curses.h>

#include "hunt.h"

player_t PLAYER;

void init_hunt() {
  /* curses magic */
  atexit((void(*)(void))endwin);
  initscr();
  noecho();
  nodelay(NULL,true);
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

void play_game() {
  
  char ch;

  while ( redraw_maze(), ch = getch() ) {
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
