/* vim:set sw=2 ts=2 : */
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <ev.h>

#include "hunt.h"
#include "huntc.h"
#include "maze.h"

player_t PLAYER;
ev_timer timeout_watcher;
ev_io    stdin_watcher;
struct ev_loop *loop; 


void init_hunt() {
  /* curses magic */
  atexit((void(*)(void))endwin);
  initscr();
  cbreak();
  keypad(stdscr,true);
  curs_set(0); /* make cursor invisible */
  noecho();
  nodelay(NULL,true);
	start_color();
	init_pair(COLOR_PLAYER, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_MAZE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_GOAL, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_POBJ, COLOR_YELLOW, COLOR_BLACK);

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
  mvaddstr(0,0,"Enter your code name: ");
  getnstr(PLAYER.name,NAME_LEN);
  noecho();

  /* set position */
  PLAYER.x = 0; /* begin in top left corner */
  PLAYER.y = 0; 
  PLAYER.level = 1;

}

void show_commands() {
  wclear(message_win);
  mvwaddstr(message_win,0,0,"Commands: q=quit arrow-keys=movement");
}

void redraw_status(WINDOW* status_win) {
  mvwaddstr(status_win,0,0,"Name: ");
  mvwaddstr(status_win,1,1,PLAYER.name);
  mvwaddstr(status_win,3,0,"Level: ");
  mvwprintw(status_win,4,1,"%d",PLAYER.level);
  mvwaddstr(status_win,19,0,"Press '?'");
  mvwaddstr(status_win,20,0," for commands");
}

void redraw() {
	redraw_maze(maze_win);
	redraw_status(status_win);
	wnoutrefresh(maze_win);
	wnoutrefresh(status_win);
	wnoutrefresh(message_win);
	doupdate();
}

void refresh_win(WINDOW* win) {
	wnoutrefresh(win);
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

void shoot (int direction) {

  int dx,dy;

  /* report shooting in status */
  wclear(message_win);
  mvwaddstr(message_win,0,0,"kapow!");

  /* TODO: do shooting logic */

  /* TODO: draw shot to screen */
  switch (direction) {
    case 'w':
      dx = 0;
      dy = -1;
      break;
    case 's':
      dx = 0;
      dy = 1;
      break;
    case 'a':
      dx = -1;
      dy = 0;
      break;
    case 'd':
      dx = 1;
      dy = 0;
      break;
  }
  new_bullet(PLAYER.x,PLAYER.y,dx,dy);
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

int check_victory () {
  if (PLAYER.x+1 == MAZEWIDTH && PLAYER.y+1 == MAZEHEIGHT)
    return 0; 
  else
    return -1;
}

void next_level() {

  /* report victory */
  wclear(message_win);
  mvwaddstr(message_win,0,0,"VICTORY IS YOURS");
  mvwaddstr(message_win,1,0," press a key to continue...");
  redraw();
  getch();
  wclear(message_win);
  
  /* set up next level */
  PLAYER.x = 0;
  PLAYER.y = 0; 
  PLAYER.level++;
  init_maze();
}



static void timeout_cb (EV_P_ ev_timer *w, int revents) {
  redraw();
}

static void stdin_cb (EV_P_ ev_io *w, int revents) {
  
  int ch;

  ch = getch();
    
  switch (ch) {
    case 'q':
      ev_unloop(loop,EVUNLOOP_ALL);
      ev_io_stop (EV_A_ w);
      ev_unloop (EV_A_ EVUNLOOP_ALL);
      return;
    case KEY_UP:
    case KEY_DOWN:
    case KEY_LEFT:
    case KEY_RIGHT:
      move_player(ch);
      break;
    case 'w':
    case 'a':
    case 's':
    case 'd':
      shoot(ch);
      break;
    case '?':
      show_commands();
      break;
    default:
      wclear(message_win);
      mvwaddstr(message_win,0,0,"Unknown command ");
      waddch(message_win,ch);
  }

  if ( check_victory() == 0 ) 
    next_level();

}


int main(int argc, const char* argv[]){
  
  /* ev setup code */
  loop = ev_default_loop (0);
  ev_timer_init(&timeout_watcher, timeout_cb, 0.1, 0.1); /* redraw every 1/10 sec */
  ev_timer_start(loop, &timeout_watcher);
  ev_io_init (&stdin_watcher, stdin_cb, 0, EV_READ);
  ev_io_start (loop, &stdin_watcher);

  /* hunt stuff */
  init_hunt();
  setup_player();

  /* start game loop */
  ev_loop (loop, 0);

  return 0;
}
