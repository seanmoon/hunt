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
  cbreak();
  keypad(stdscr,true);
  noecho();
  nodelay(NULL,true);

  /* intialize windows */
  status_win  = newwin(STATUS_WIN_HEIGHT,STATUS_WIN_WIDTH,
                       STATUS_WIN_YSTART,STATUS_WIN_XSTART);
  maze_win    = newwin(MAZE_WIN_HEIGHT,MAZE_WIN_WIDTH,
                       MAZE_WIN_YSTART,MAZE_WIN_XSTART);
  message_win = newwin(MESSAGE_WIN_HEIGHT,MESSAGE_WIN_WIDTH,
                       MESSAGE_WIN_YSTART,MESSAGE_WIN_XSTART);
  
  init_maze();
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
  wclear(message_win);
  mvwaddstr(message_win,0,0,"Commands: q=quit");
}

void redraw_status(WINDOW* status_win) {
  mvwaddstr(status_win,0,0,"Name: ");
  mvwaddstr(status_win,1,1,PLAYER.name);
  mvwaddstr(status_win,20,0,"Press '?'");
  mvwaddstr(status_win,21,0," for commands");
}

void redraw() {
	redraw_maze(maze_win);
	redraw_status(status_win);
	wnoutrefresh(maze_win);
	wnoutrefresh(status_win);
	wnoutrefresh(message_win);
	doupdate();
}

int try_move(int dx,int dy) {
  
  /* sanity check */
  if ( PLAYER.x + dx < 0 || PLAYER.x + dx >= MAZEWIDTH )
    return false;
  if ( PLAYER.y + dy < 0 || PLAYER.y + dy >= MAZEHEIGHT )
    return false;

  /* try the move */
  PLAYER.x += dx;
  PLAYER.y += dy;

  /* if we hit a wall, undo move */
  if ( MAZE[PLAYER.x][PLAYER.y].is_wall ) {
    PLAYER.x -= dx;
    PLAYER.y -= dy;
  }

  return 0;
}

void move_player(int direction) {
  switch (direction) {
    case KEY_UP:
      try_move(0,-1);
      break;
    case KEY_DOWN:
      try_move(0,1);
      break;
    case KEY_LEFT:
      try_move(-1,0);
      break;
    case KEY_RIGHT:
      try_move(1,0);
      break;
  } 
}

void play_game() {
  
  int ch;

  while (redraw(), ch = getch() ) {
    switch (ch) {
      case 'q':
        goto end_game;
      case KEY_UP:
      case KEY_DOWN:
      case KEY_LEFT:
      case KEY_RIGHT:
        move_player(ch);
        break;
      case '?':
        show_commands();
        break;
      default:
        mvwaddstr(message_win,0,0,"Unknown command ");
        waddch(message_win,ch);
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
